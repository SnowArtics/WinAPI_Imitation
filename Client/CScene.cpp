#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CCore.h"
#include "CCamera.h"

void CScene::start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			m_arrObj[i][j]->start();
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

//플레이어가 이동을 하지 않고 시스템상으로 업데이트
void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {

		if ((UINT)GROUP_TYPE::TILE == i) {
			render_tile(_dc);
			continue;
		}

		//오브젝트가 죽는 상황일 때
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter < m_arrObj[i].end();) {
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				iter++;
			}
			else {
				iter = m_arrObj[i].erase(iter);//삭제했을때 다음을 받음
			}
		}
	}
}

void CScene::render_tile(HDC _dc)
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	//카메라의 위치를 계산중
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vLeftTop = vCamLook - vResolution / 2;

	int iTileSize = TILE_SIZE;

	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	//LeftTop타일의 인덱스가 바로 이거다.
	int iLTIdx = m_iTileX * iLTRow + iLTCol;

	int iClientWidth = ((int)vResolution.x / iTileSize)+1;
	int iClientHeight = ((int)vResolution.y / iTileSize)+2;

	//카메라범위만큼 반복문을 돈다.
	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); iCurRow++) {
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); iCurCol++) {
			if (iCurCol < 0 || (int)m_iTileX <= iCurCol
				|| iCurRow < 0 || (int)m_iTileY <= iCurRow) {
				continue;
			}

			int iIdx = (m_iTileX * iCurRow) + iCurCol;
			 
			vecTile[iIdx]->render(_dc);
		}
	}

}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++) {
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\TILE.bmp");

	//타일 생성
	for (UINT i = 0; i < _iYCount; i++) {
		for (UINT j = 0; j < _iXCount; j++) {
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	//커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	//파일 열기 실패
	assert(pFile);

	// 타일 가로 세로 개수 불러오기
	UINT xCount =0;
	UINT yCount =0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	//불러온 개수에 맞게 EmptyTile 들 만들어두기
	CreateTile(xCount, yCount);
	
	//만들어진 타일 개별로 필요한 정보를 불러오게 함.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++) {
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_pPlayer(nullptr)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			//m_arrObj[i] 그룹 벡터의 j 물체 삭제
			delete m_arrObj[i][j];
		}
	}
}
