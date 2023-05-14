#include "pch.h"
#include "CScene_Intro.h"
#include "CScene.h"

#include "CCore.h"
#include "CObject.h"

#include "CResMgr.h"

#include "CTexture.h"

#include "CBack.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

void CScene_Intro::Enter()
{
	//배경이미지를 만들어 보자.
	CObject* _pBack = new CBack();
	CTexture* _pTexture = CResMgr::GetInst()->LoadTexture(L"Main Back", L"intro\\intro_background.png");
	((CBack*)_pBack)->SetTexture(_pTexture);

	AddObject(_pBack, GROUP_TYPE::BACK);

	//UI만들어 보자
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//panel UI Created
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"PanelUI");
	pPanelUI->SetScale(Vec2(550.f, 496.f));
	pPanelUI->SetPos(Vec2((vResolution.x / 2) - (pPanelUI->GetScale().x / 2), (vResolution.y / 2) - (pPanelUI->GetScale().y / 2)));

	//Set panel UI texture
	_pTexture = CResMgr::GetInst()->LoadTexture(L"Main Panel", L"intro\\panel.png");
	pPanelUI->SetTexture(_pTexture);

	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	AddObject((CObject*)pPanelUI, GROUP_TYPE::UI);
}

void CScene_Intro::Exit()
{
}

void CScene_Intro::render(HDC _dc)
{
	CScene::render(_dc);

}

void CScene_Intro::update()
{
	CScene::update();
}

CScene_Intro::CScene_Intro()
	: m_pPanelUI(nullptr)
	, m_pUI1(nullptr)
	, m_pUI2(nullptr)
{

}

CScene_Intro::~CScene_Intro()
{
}