#include "pch.h"
#include "CBack.h"
#include "CObject.h"

#include "CTexture.h"

void CBack::update()
{
}

void CBack::render(HDC _dc)
{
	if (nullptr == m_pBackgroundTex)
		return;

	//m_pBackgroundTex의 크기를 저장
	UINT iWidth = m_pBackgroundTex->Width();
	UINT iHeight = m_pBackgroundTex->Height();

	TransparentBlt(_dc
		, 0
		, 0
		, iWidth//(int)(vScale.x)
		, iHeight//(int)(vScale.y)
		, m_pBackgroundTex->GetDC()
		, 0
		, 0
		, iWidth//(int)(vScale.x)
		, iHeight//(int)(vScale.y)
		, RGB(255, 0, 255));
}

CBack::CBack()
	: m_pBackgroundTex(nullptr)
{
}

CBack::~CBack()
{
}
