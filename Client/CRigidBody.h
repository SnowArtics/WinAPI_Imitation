#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce; // 크기, 방향
	Vec2		m_vAccel; //가속도
	Vec2		m_vAccelA;	// 추가 가속도
	Vec2		m_vVelocity; // 속도 (크기: 속력, 방향)
	Vec2		m_vMaxVelocity; // 최대 속도

	float		m_fMass; // 질량
	float		m_fFricCoeff; // 마찰 계수(마찰력은 무조건 힘의 반대방향)
		
	// F = M * A; //힘
	// V += A * DT; // 속도는 가속도 * 시간

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; }

	void SetMass(float _fMass) { m_fMass = _fMass; }	
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vec2 GetVelocity() { return m_vVelocity; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMAXVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
	void SetAccelAlpha(Vec2 _vAccelA) { m_vAccelA = _vAccelA; }

private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

