#include "pch.h"
#include "CBridge.h"

#include "CResMgr.h"

#include "CTexture.h"
#include "CCamera.h"

void CBridge::start()
{
	//¿©±â¿¡ Bridge Æ÷Áö¼Å´× ÇØÁÖ±â
	Vec2 position = GetPos();

	//S¶ûNÀº xÁÂÇ¥ ¸ÂÃß±â
	//E¶û W´Â yÁÂÇ¥ ¸ÂÃß±â
	switch (m_iDirection)
	{
	case 'E':
	{
		SetPos(GetPos() + Vec2(1090.f - 100.f, 395.f - 100.f));
	}
	break;

	case 'W':
	{
		SetPos(GetPos() + Vec2(10.f - 100.f, 395.f - 100.f));
	}
	break;

	case 'S':
	{
		SetPos(GetPos()+Vec2(500.f - 100.f, 805.f - 100.f));
	}
	break;

	case'N':
	{
		SetPos(GetPos()+Vec2(500.f - 100.f, 30.f - 100.f));
	}
	break;
	}
}

void CBridge::update()
{
}

void CBridge::render(HDC _dc)
{
	component_render(_dc);

	if (nullptr == m_pBridgeTex)
		return;

	//m_pBackgroundTexÀÇ Å©±â¸¦ ÀúÀå
	UINT iWidth = m_pBridgeTex->Width();
	UINT iHeight = m_pBridgeTex->Height();

	Vec2 vScale = GetScale();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		,(int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, iWidth//(int)(vScale.x)
		, iHeight//(int)(vScale.y)
		, m_pBridgeTex->GetDC()
		, 0
		, 0
		, iWidth//(int)(vScale.x)
		, iHeight//(int)(vScale.y)
		, RGB(255, 255, 255));

	ViewScale(_dc);
}

void CBridge::MouseOn()
{
}

void CBridge::MouseLbtnDown()
{
}

void CBridge::MouseLbtnUp()
{
}

void CBridge::MouseLbtnClicked()
{
}

void CBridge::MouseRbtnDown()
{
}

void CBridge::MouseRbtnUp()
{
}

void CBridge::MouseRbtnClicked()
{
}


CBridge::CBridge(char _direction)
	: m_pBridgeTex(nullptr)
{
	m_iDirection = _direction;
	switch (m_iDirection)
	{
	case 'E':
	{
		m_pBridgeTex = CResMgr::GetInst()->LoadTexture(L"Bridge_Right", L"background\\sunny_forest\\sunny_forest_bridge_right.png");
	}
		break;

	case 'W':
	{
		m_pBridgeTex = CResMgr::GetInst()->LoadTexture(L"Bridge_Left", L"background\\sunny_forest\\sunny_forest_bridge_left.png");
	}
		break;

	case 'S':
	{
		//m_pBridgeTex = CResMgr::GetInst()->LoadTexture(L"Bridge_South", L"background\\sunny_forest\\sunny_forest_bridge_down.png");
		m_pBridgeTex = CResMgr::GetInst()->LoadTexture(L"Bridge_South", L"background\\sunny_forest\\sunny_forest_bridge_down.png");
	}
		break;

	case'N':
	{
		m_pBridgeTex = CResMgr::GetInst()->LoadTexture(L"Bridge_North", L"background\\sunny_forest\\sunny_forest_bridge_up.png");
	}
		break;
	}
	
}

CBridge::CBridge(const CBridge& _origin)
{
}

CBridge::~CBridge()
{
}
