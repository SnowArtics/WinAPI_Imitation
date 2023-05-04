#include "pch.h"
#include "CScene_Start.h"

#include "CPathMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

#include "CResMgr.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

#include "CGround.h"
#include "CBackground.h"

void CScene_Start::update()
{
	if (KEY_HOLD(KEY::LBTN)) {
		m_bUseForce = true;
		CreateForce();
	}
	else {
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j) {
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody()) {
					//힘이 발생한 곳과 거리를 잼
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					//힘이 발생한 곳의 반경 안에 있을 때
					if (fLen < m_fForceRadius) {
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce* fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normailize() * fForce);						
					}
				}

				vecObj[j]->update();
			}
		}
	}

	//if (KEY_TAP(KEY::ENTER)) {
	//	ChangeScene(SCENE_TYPE::TOOL);
	//}

	//클릭시 카메라 움직임
	//if (KEY_TAP(KEY::LBTN)) {
	//	Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	CCamera::GetInst()->SetLookAt(vLookAt);
	//}


}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius *3.f * fDT;
	if (m_fCurRadius > m_fForceRadius) {
		m_fCurRadius = 0.f;
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));

}

void CScene_Start::Enter()
{
	//시작시 오브젝트를 넣어줌.
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");

	pObj->SetPos(Vec2(960.f,340.f));
	pObj->SetScale(Vec2(100.f,100.f));

	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);


	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(860.f, 540.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	//Monster 오브젝트 생성
	//int iMonCount = 1;
	//float fObjScale = 50.f;

	//Vec2 vResolution = CCore::GetInst()->GetResolution();

	//AI* pAI = new AI;
	//pAI->AddState(new CIdleState);
	//pAI->AddState(new CTraceState);

	//CMonster* pMonsterObj = nullptr;
	//for (int i = 0; i < iMonCount; ++i) {
	//	pMonsterObj = new CMonster;
	//	pMonsterObj->SetName(L"Monster");
	//	pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	pMonsterObj->SetPos(vResolution / 2.f-Vec2(0.f,300.f));

	//	pMonsterObj->SetAI(pAI);

	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	//}


	////몬스터 배치
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//땅 물체 배치
	CObject* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(960.f, 740.f));
	pGround->SetScale(Vec2(700.f, 120.f));
	AddObject(pGround, GROUP_TYPE::GROUND);

	//CObject* pBackground = new CBackground;
	//pBackground->SetName(L"Background");
	//pBackground->SetPos(Vec2(0.f, 0.f));
	//pBackground->SetScale(Vec2(600.f, 600.f));
	//AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	//타일 로딩
	//LoadTile(L"Tile\\Start.tile");

	//충돌 지정
	// Player 그룹과 Monster 그룹간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	//Camera Look 시점 맨처음 호출
	CCamera::GetInst()->SetLookAt(vResolution/2.f);

	//Camera 효과 지정
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}

CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{

}

CScene_Start::~CScene_Start()
{
}
