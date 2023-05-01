#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CObject.h"

void CRigidBody::finalupdate()
{
	float fForce = m_vForce.Length();//순수한 힘의 크기

	if (fForce != 0.f) {
		m_vForce.Normailize();//순수한 힘의 방향

		float m_fAccel = fForce / m_fMass; //가속도의 크기

		//여기서 m_vForce는 노멀라이즈된 방향값임
		m_vAccel = m_vForce * m_fAccel; //가속도 = 힘 * 가속도의 크기
		// m_vAccel = m_vForce*m_fAccel;
	}

	m_vAccel += m_vAccelA; // 중력과 같은 가속도는 기존 가속도에 추가되는 것이라서 다짜고짜 더해줌
	//중력은 질량이나 힘에 상관없이 그냥 가속도가 더해지는 것이라서 다짜고짜 더해줌

	//최종 속도
	//힘이 있든 없든 속도는 계산
	m_vVelocity += m_vAccel * fDT;

	//속도가 0이 아닐때만 
	if (!m_vVelocity.IsZero()) {
		//마찰력에 의한 반대방향으로의 가속도
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normailize();
		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length()) {
			//마찰가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else {
			m_vVelocity += vFriction;
		}
	}


	//속도 제한 검사
	if (abs(m_vMaxVelocity.x)<abs(m_vVelocity.x)) {
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y)) {
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// 속도에 따른 이동
	Move();

	//기존의 힘 말고 새롭게 받은 힘으로 업데이트 하기 위해서 초기화
	m_vForce = Vec2(0.f, 0.f);

	//가속도 초기화
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f) {
		//이동 방향
		// 최종속도는 누적되어야 ㅎ해서 Normalize하면 안됨
		Vec2 vDir = m_vVelocity;
		vDir.Normailize();

		//이동 속력
		Vec2 vPos = m_pOwner->GetPos();

		//사실 그냥 최종속도에 시간 곱하면 됨
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
