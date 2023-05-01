#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"

#include "resource.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "CUIMgr.h"
#include "CPathMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

void CScene_Tool::update()
{
	CScene::update();

	//if (KEY_TAP(KEY::ENTER)) {
	//	ChangeScene(SCENE_TYPE::START);
	//}

	SetTileIdx();

	//if (KEY_TAP(KEY::LSHIFT)) {
	//	//CUIMgr::GetInst()->SetFocusedUI(m_pUI);
	//	SaveTileData();
	//}

	if (KEY_TAP(KEY::CTRL)) {
		//CUIMgr::GetInst()->SetFocusedUI(m_pUI);
		LoadTileData();
	}
}

void CScene_Tool::Enter()
{
	//SceneTool�� �޴��� ���δ�.
	CCore::GetInst()->DockMenu();

	//Ÿ�� ����
	CreateTile(5, 5);

	//UI ������
	Vec2 vResolution = CCore::GetInst()->GetResolution();	

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(700.f, 300.f));
	pPanelUI->SetPos(Vec2(vResolution.x- pPanelUI->GetScale().x,0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	//���纻 UI
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	//((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);
	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pClonePanel;

	//Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}

void CScene_Tool::SetTileIdx()
{

	if (KEY_TAP(KEY::LBTN)) {
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol || vMousePos.y < 0.f || iTileY <= iRow) {
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
}

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();//���� ���� ������
	ofn.lpstrFile = szName; //������ ���� ���
	ofn.nMaxFile = sizeof(szName);//����� ũ��
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";	//Ư�����ϸ� �����ְ� �ϴ� ����
	ofn.nFilterIndex = 0;//���Ϳ��� �⺻���� ���� �Ǿ��ֳ�
	ofn.lpstrFileTitle = nullptr;//â�� ����
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();		//�ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//��ο� ������ �ݵ�� �����ؾ� �Ѵ�.

	//Modal
	if (GetSaveFileName(&ofn)) {
		SaveTile(szName);
	}

}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	//Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb");
	//���Ͽ������
	assert(pFile);

	//Ÿ�� ���μ��� ���� ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	//��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ���
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	
	for (size_t i = 0; i < vecTile.size(); i++) {
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();//���� ���� ������
	ofn.lpstrFile = szName; //������ ���� ���
	ofn.nMaxFile = sizeof(szName);//����� ũ��
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";	//Ư�����ϸ� �����ְ� �ϴ� ����
	ofn.nFilterIndex = 0;//���Ϳ��� �⺻���� ���� �Ǿ��ֳ�
	ofn.lpstrFileTitle = nullptr;//â�� ����
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();		//�ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//��ο� ������ �ݵ�� �����ؾ� �Ѵ�.

	//Modal
	if (GetOpenFileName(&ofn)) {
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}

CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}


//�����Լ���
void ChangeScene(DWORD_PTR, DWORD_PTR) {
	ChangeScene(SCENE_TYPE::START);
}


//======================
//Tile Count Window Proc
//======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			//ToolScene Ȯ��
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}else if(LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;



}