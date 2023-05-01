#include "pch.h"
#include "CGravity.h"

#include "CObject.h"
#include "CRigidBody.h"

void CGravity::SetGround(bool _b)
{
	m_bGround = _b;
	if (m_bGround) {
		Vec2 vV = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2(vV.x, 0.f));
	}
}

void CGravity::finalupdate()
{
	//중력은 따지면 9.8mh 인데 지구의 질량이 엄청 커서 m(질량)은 계산할 필요가 없다.
	//즉, 고정된 가속도 값을 준다
	//추가로, 기존에 가속도가 있다면 거기에 추가로 중력값이 들어가야 한다.
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2(0.f, 800.f));
}

CGravity::CGravity()
	: m_pOwner(nullptr)
	, m_bGround(false)
{
}

CGravity::~CGravity()
{
}
