#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

#include "CTexture.h"

void CPanelUI::update()
{

}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);

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

void CPanelUI::MouseOn()
{
	//if (IsLbtnDown()) {
	//	Vec2 vDiff = MOUSE_POS - m_vDragStart;

	//	Vec2 vCurPos = GetPos();
	//	vCurPos += vDiff;
	//	SetPos(vCurPos);

	//	m_vDragStart = MOUSE_POS;
	//}
}

void CPanelUI::MouseLbtnDown()
{
	//m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}

void CPanelUI::MouseRbtnDown()
{
}

void CPanelUI::MouseRbtnUp()
{
}

CPanelUI::CPanelUI()
	:CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}
