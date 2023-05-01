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
	//�߷��� ������ 9.8mh �ε� ������ ������ ��û Ŀ�� m(����)�� ����� �ʿ䰡 ����.
	//��, ������ ���ӵ� ���� �ش�
	//�߰���, ������ ���ӵ��� �ִٸ� �ű⿡ �߰��� �߷°��� ���� �Ѵ�.
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
