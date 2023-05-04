#include "pch.h"
#include "CBackground.h"

#include "CResMgr.h"

#include "CTexture.h"
#include "CCamera.h"

void CBackground::update()
{
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

	BitBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y
		, iWidth//(int)(vScale.x)
		, iHeight//(int)(vScale.y)
		, m_pBackgroundTex->GetDC()
		, 0
		, 0
		, SRCCOPY);

}

CBackground::CBackground()
	:m_pBackgroundTex(nullptr)
{
	m_pBackgroundTex = CResMgr::GetInst()->LoadTexture(L"Sunny_Forest", L"background\\sunny_forest\\sunny_forest.png");
}

CBackground::CBackground(const CBackground& _origin)
	: CObject(_origin)
{
}

CBackground::~CBackground()
{
}
