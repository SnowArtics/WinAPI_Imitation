#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CCamera.h"

#include "CCore.h"

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

void CObject::ViewScale(HDC _dc)
{
	//background의 크기를 나타내는 부분
	PEN_TYPE ePen = PEN_TYPE::BLUE;

	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 cPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	//Vec2 vScale = CCamera::GetInst()->GetRenderPos(GetScale());

	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));
}

void CObject::finalupdate()
{
	if (m_pAnimator != nullptr)
		m_pAnimator->finalupdate();
	if (m_pGravity != nullptr)
		m_pGravity->finalupdate();
	if (m_pRigidBody != nullptr)
		m_pRigidBody->finalupdate();
	if (m_pCollider != nullptr)
		m_pCollider->finalupdate();
}

void CObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	if (m_bLbtnDown) {
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc,
			(int)(vRenderPos.x - m_vScale.x / 2.f),
			(int)(vRenderPos.y - m_vScale.y / 2.f),
			(int)(vRenderPos.x + m_vScale.x / 2.f),
			(int)(vRenderPos.y + m_vScale.y / 2.f));
	}else{
		Rectangle(_dc,
			(int)(vRenderPos.x - m_vScale.x / 2.f),
			(int)(vRenderPos.y - m_vScale.y / 2.f),
			(int)(vRenderPos.x + m_vScale.x / 2.f),
			(int)(vRenderPos.y + m_vScale.y / 2.f));
	}
	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (nullptr != m_pAnimator) {
		m_pAnimator->render(_dc);
	}

	if (nullptr != m_pCollider) {
 		m_pCollider->render(_dc);
	}
}

void CObject::MouseOnCheck()
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vPos);
	Vec2 vMousePos = MOUSE_POS;
	//Vec2 vMousePos = CCamera::GetInst()->GetRenderPos(MOUSE_POS);
	Vec2 vScale = GetScale();
	
	Vec2 vResolution = CCore::GetInst()->GetResolution();
		
	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
		&& vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y//MousePos가 오브젝트의 범위 안에 있을 때,
		&& vMousePos.x >= 0 && vMousePos.x <= vResolution.x 
		&& vMousePos.y >=0 && vMousePos.y <=vResolution.y ){//vMpisePos가 화면 해상도 안에 있을 때
		m_bMouseOn = true;
	}
	else {
		m_bMouseOn = false;
	}
}

void CObject::MouseOn()
{
}

void CObject::MouseLbtnDown()
{
}

void CObject::MouseLbtnUp()
{
}

void CObject::MouseLbtnClicked()
{
}

void CObject::MouseRbtnDown()
{
}

void CObject::MouseRbtnUp()
{
}

void CObject::MouseRbtnClicked()
{
}


CObject::CObject()
	:m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_bRbtnDown(false)
{
}

CObject::CObject(const CObject& _origin)
	:m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
	, m_bLbtnDown(false)
	, m_bRbtnDown(false)
	, m_bMouseOn(false)
{
	if (_origin.m_pCollider) {
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (_origin.m_pAnimator) {
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}

	if (_origin.m_pRigidBody) {
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}

	if (_origin.m_pGravity) {
		m_pGravity = new CGravity(*_origin.m_pGravity);
		m_pGravity->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (nullptr != m_pCollider) delete m_pCollider;
	if (nullptr != m_pAnimator) delete m_pAnimator;
	if (nullptr != m_pRigidBody) delete m_pRigidBody;
	if (nullptr != m_pGravity) delete m_pGravity;
}
