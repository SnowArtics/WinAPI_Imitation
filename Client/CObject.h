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

	bool	m_bAlive;//false�� ���� ����

	bool            m_bMouseOn;     //UI ���� ���콺�� �ִ���
	bool            m_bLbtnDown;    //UI�� ���� ��ư�� �������� �ִ���
	bool            m_bRbtnDown;    //UI�� ������ ��ư�� �������� �ִ���

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

	void ViewScale(HDC _dc);//������Ʈ�� ũ�⸦ �����ִ� �Լ� Render���� ȣ�����ֱ�

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void start() {}; // Scene�� ���۵Ǳ� ������ ȣ��Ǵ� �Լ�
	virtual void update()=0;
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

//���콺 �Է� ���� �Լ���
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

	//�ڱ� �ڽ��� ���������� �ǵ��� �ش�.
	virtual CObject* Clone() =0 ;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject(); 

	friend class CEventMgr;
	friend class CObjectMgr;
};

