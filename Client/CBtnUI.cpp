#include "pch.h"
#include "CBtnUI.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

#include "CMonFactory.h"

void CBtnUI::start()
{
	if (m_sBtnName == L"button_worker") {
		m_eMonType = MON_TYPE::WORKER;
		m_eMonName = MON_NAME::WORKER;
	}else if (m_sBtnName == L"button_guard") {
		m_eMonType = MON_TYPE::MELEE;
		m_eMonName = MON_NAME::GUARD;
	}
	else if (m_sBtnName == L"button_archer") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::ARCHER;
	}
	else if (m_sBtnName == L"button_axe_thrower") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::AXE_TRHOWER;
	}
	else if (m_sBtnName == L"button_hammerman") {
		m_eMonType = MON_TYPE::MELEE;
		m_eMonName = MON_NAME::HAMMERMAN;
	}
	else if (m_sBtnName == L"button_knight") {
		m_eMonType = MON_TYPE::MELEE;
		m_eMonName = MON_NAME::KNIGHT;
	}
	else if (m_sBtnName == L"button_healer") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::HEALER;
	}
	else if (m_sBtnName == L"button_farm") {
		m_eMonType = MON_TYPE::BUILDING;
		m_eMonName = MON_NAME::FARM;
	}
	else if (m_sBtnName == L"button_wall") {
		m_eMonType = MON_TYPE::BUILDING;
		m_eMonName = MON_NAME::WALL;
	}
	else if (m_sBtnName == L"button_wizard") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::WIZARD;
	}
	else if (m_sBtnName == L"button_necromancer") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::NECROMANCER;
	}
	else if (m_sBtnName == L"button_dragon") {
		m_eMonType = MON_TYPE::MELEE;
		m_eMonName = MON_NAME::RED_DRAGON;
	}
	else if (m_sBtnName == L"button_catapult") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::CATAPULT;
	}
	else if (m_sBtnName == L"button_hunter") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::ICE_HUNTER;
	}
	else if (m_sBtnName == L"button_horse_archer") {
		m_eMonType = MON_TYPE::RANGE;
		m_eMonName = MON_NAME::HORSE_ARCHER;
	}
	else if (m_sBtnName == L"button_storehouse") {
		m_eMonType = MON_TYPE::BUILDING;
		m_eMonName = MON_NAME::STOREHOUSE;
	}
}

void CBtnUI::update()
{
	CUI::update();

}

void CBtnUI::finalupdate()
{
	CUI::finalupdate();
}

void CBtnUI::render(HDC _dc)
{
	//버튼 클릭시 초록색으로 변경되는 부분은 부모 CUI에서 해주고 있음
	//카메라 렌더포즈로 변경하는 것도
	//자식 UI렌더해주는것도
	//흰색 칠해주는 것도
	CUI::render(_dc);

	Vec2 vPos = GetPos();

	CTexture* pTex = GetTexture();
	if (nullptr == pTex)
		return;

	//m_pBackgroundTex의 크기를 저장
	UINT iWidth = pTex->Width();
	UINT iHeight = pTex->Height();

	Vec2 vScale = GetScale();
	//Vec2 vRenderPos = CCamera::GetInst()->GetRealPos(GetPos());

	TransparentBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, iWidth
		, iHeight
		, pTex->GetDC()
		, 0
		, 0
		, iWidth
		, iHeight
		, RGB(255, 0, 255));


}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	//if (nullptr != m_pFunc) {
	//	m_pFunc(m_param1, m_param2);
	//}

	//if (m_pSceneInst && m_pSceneFunc) {
	//	//((*m_pSceneInst).*m_pSceneFunc)();
	//	(m_pSceneInst->*m_pSceneFunc)();
	//}

	//if (nullptr != m_pSpawnFunc) {
	//	m_pSpawnFunc(m_param1, m_param2, m_param3);
	//}

	if (m_pSceneInst && m_pSceneCursorIcon) {
		(m_pSceneInst->*m_pSceneCursorIcon)(m_pCursorIcon, m_eMonType, m_eMonName);
	}
}

void CBtnUI::MouseRbtnDown()
{
}

void CBtnUI::MouseRbtnUp()
{
}

void CBtnUI::MouseRbtnClicked()
{
}

void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	//m_pSceneInst = _pScene;
	//m_pSceneFunc = _pSceneFunc;
}

void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_CURSOR_FUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneCursorIcon = _pSceneFunc;
}


CBtnUI::CBtnUI()
	: CUI(false)
	, m_sBtnName(L"")
	, m_pSceneInst(nullptr)
	, m_pCursorIcon(nullptr)
	, m_pSceneCursorIcon(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}
