#include "pch.h"
#include "CBackground.h"
#include "CBridge.h"

#include "CResMgr.h"

#include "CObject.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CMonFactory.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CScene_Test.h"
#include "CMonster.h"

void CBackground::start()
{
	for (int i = 0; i < m_vBridgeDirection.size(); i++) {
		//bridge생성
		CObject* bridge = new CBridge(m_vBridgeDirection[i]);
		//Bridge의 자세한 위치는 Bridge가 스스로 해줌
		bridge->SetPos(GetPos());
		bridge->SetScale(Vec2(150.f, 237.f));
		m_pScene->AddObject(bridge, GROUP_TYPE::BRIDGE);
		m_mapBridge.insert(make_pair(m_vBridgeDirection[i], bridge));
	}
}

void CBackground::update()
{
	MouseOnCheck();
}

void CBackground::render(HDC _dc)
{
	component_render(_dc);

	if (nullptr == m_pBackgroundTex)
		return;

	//m_pBackgroundTex의 크기를 저장
	UINT iWidth = m_pBackgroundTex->Width();
	UINT iHeight = m_pBackgroundTex->Height();

	Vec2 vScale = GetScale();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, (int)(vRenderPos.x-100.f)
		, (int)(vRenderPos.y-100.f)
		, iWidth//(int)(vScale.x)
		, iHeight//(int)(vScale.y)
		, m_pBackgroundTex->GetDC()
		, 0
		, 0
		, iWidth//(int)(vScale.x)
		, iHeight//(int)(vScale.y)
		, RGB(255, 255, 255));

	ViewScale(_dc);

}

void CBackground::MouseOn()
{
}

void CBackground::MouseLbtnDown()
{
}

void CBackground::MouseLbtnUp()
{
}

void CBackground::MouseLbtnClicked()
{
	if (m_bTriggerCursor&& m_iOwn==1) {
		//Vec2 vMousePos = MOUSE_POS;
		//Vec2 vMousePos = CCamera::GetInst()->GetRenderPos(MOUSE_POS);
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CMonster* pMon = CMonFactory::CreateMonster(m_eMonType, m_eMonName, vMousePos);

		switch (m_eMonType)
		{
		case MON_TYPE::NORMAL:
			assert(true);
			break;
		case MON_TYPE::WORKER:
			CreateObject((CObject*)pMon, GROUP_TYPE::P1_WORKER);
			break;
		case MON_TYPE::MELEE:
			CreateObject((CObject*)pMon, GROUP_TYPE::P1_MELEE_CREATURE);
			break;
		case MON_TYPE::RANGE:
			CreateObject((CObject*)pMon, GROUP_TYPE::P1_RANGE_CREATURE);
			break;
		case MON_TYPE::BUILDING:
			CreateObject((CObject*)pMon, GROUP_TYPE::P1_BUILDING);
			break;
		}

		CScene_Test* pCurScene = (CScene_Test*)CSceneMgr::GetInst()->GetCurScene();
		pCurScene->AddP1Mon((CObject*)pMon);
	}	
}

void CBackground::MouseRbtnDown()
{
}

void CBackground::MouseRbtnUp()
{
}

void CBackground::MouseRbtnClicked()
{
	//Vec2 vMousePos = MOUSE_POS;
	Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*> vP1Mon = ((CScene_Test*)pCurScene)->GetP1Mon();

	for (UINT i = 0; i < vP1Mon.size(); i++) {
		if (((CMonster*)vP1Mon[i])->GetClicked()) {
			((CMonster*)vP1Mon[i])->SetTargetPosition(Vec2(vMousePos.x+(i*30.f), vMousePos.y + (i * 30.f)));
		}
	}
}

CBackground::CBackground(vector<char> _BridgeDirection, CScene* _Scene)
	: m_pBackgroundTex(nullptr)
	, m_pScene(nullptr)
	, m_bTriggerCursor(false)
{
	m_pBackgroundTex = CResMgr::GetInst()->LoadTexture(L"Sunny_Forest", L"background\\sunny_forest\\sunny_forest.png");
	m_vBridgeDirection = _BridgeDirection;
	m_pScene = _Scene;
}

CBackground::CBackground(const CBackground& _origin)
	: CObject(_origin)
	, m_pBackgroundTex(nullptr)
	, m_pScene(nullptr)
	, m_iOwn(0)
{
}

CBackground::~CBackground()
{
}
