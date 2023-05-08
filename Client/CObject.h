#pragma once

#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{

private:
	wstring	m_strName;

	Vec2	m_vPos;
	Vec2	m_vScale;

	//Component
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;
	CRigidBody* m_pRigidBody;
	CGravity*	m_pGravity;

	bool	m_bAlive;//false면 죽은 상태

	bool            m_bMouseOn;     //UI 위에 마우스가 있는지
	bool            m_bLbtnDown;    //UI에 왼쪽 버튼이 눌린적이 있는지
	bool            m_bRbtnDown;    //UI에 오른쪽 버튼이 눌린적이 있는지

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity() { return m_pGravity; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	void ViewScale(HDC _dc);//오브젝트의 크기를 보여주는 함수 Render에서 호출해주기

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void start() {}; // Scene이 시작되기 직전에 호출되는 함수
	virtual void update()=0;
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

//마우스 입력 관련 함수들
public:
	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }
	bool IsRbtnDown() { return m_bRbtnDown; }

public:
	void MouseOnCheck();

	virtual void MouseOn();

	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	virtual void MouseRbtnDown();
	virtual void MouseRbtnUp();
	virtual void MouseRbtnClicked();

	//자기 자신의 복제버전을 되돌려 준다.
	virtual CObject* Clone() =0 ;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject(); 

	friend class CEventMgr;
	friend class CObjectMgr;
};

