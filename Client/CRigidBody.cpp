#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CObject.h"

void CRigidBody::finalupdate()
{
	float fForce = m_vForce.Length();//������ ���� ũ��

	if (fForce != 0.f) {
		m_vForce.Normailize();//������ ���� ����

		float m_fAccel = fForce / m_fMass; //���ӵ��� ũ��

		//���⼭ m_vForce�� ��ֶ������ ���Ⱚ��
		m_vAccel = m_vForce * m_fAccel; //���ӵ� = �� * ���ӵ��� ũ��
		// m_vAccel = m_vForce*m_fAccel;
	}

	m_vAccel += m_vAccelA; // �߷°� ���� ���ӵ��� ���� ���ӵ��� �߰��Ǵ� ���̶� ��¥��¥ ������
	//�߷��� �����̳� ���� ������� �׳� ���ӵ��� �������� ���̶� ��¥��¥ ������

	//���� �ӵ�
	//���� �ֵ� ���� �ӵ��� ���
	m_vVelocity += m_vAccel * fDT;

	//�ӵ��� 0�� �ƴҶ��� 
	if (!m_vVelocity.IsZero()) {
		//�����¿� ���� �ݴ���������� ���ӵ�
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normailize();
		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length()) {
			//�������ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else {
			m_vVelocity += vFriction;
		}
	}


	//�ӵ� ���� �˻�
	if (abs(m_vMaxVelocity.x)<abs(m_vVelocity.x)) {
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y)) {
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// �ӵ��� ���� �̵�
	Move();

	//������ �� ���� ���Ӱ� ���� ������ ������Ʈ �ϱ� ���ؼ� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);

	//���ӵ� �ʱ�ȭ
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f) {
		//�̵� ����
		// �����ӵ��� �����Ǿ�� ���ؼ� Normalize�ϸ� �ȵ�
		Vec2 vDir = m_vVelocity;
		vDir.Normailize();

		//�̵� �ӷ�
		Vec2 vPos = m_pOwner->GetPos();

		//��� �׳� �����ӵ��� �ð� ���ϸ� ��
		vPos += m_vVelocity * fDT;
		m_pOwner->SetPos(vPos);
	}
}

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_vForce(Vec2(0.f,0.f))
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vec2(200.f,600.f))
{
}

CRigidBody::~CRigidBody()
{
}
