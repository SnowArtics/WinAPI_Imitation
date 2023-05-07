#include "pch.h"
#include "CBtnUI.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

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
		(m_pSceneInst->*m_pSceneCursorIcon)(m_pCursorIcon);
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
	, m_pSceneInst(nullptr)
	, m_pCursorIcon(nullptr)
	, m_pSceneCursorIcon(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}
