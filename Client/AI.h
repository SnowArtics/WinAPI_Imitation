#pragma once

class CMonster;
class CState;

class AI
{
private:
	map<MON_STATE, CState*>	m_mapState;
	CState*					m_pCurState;
	CMonster*				m_pOwner;
	CMonster*				m_pCurTarget;//쫓거나 공격시 타겟 몬스터

public:
	void update();


public:
	void AddState(CState* _pState);
	CState* GetState(MON_STATE _eState);
	CMonster* GetCurTarget() { return m_pCurTarget; }

	void SetCurState(MON_STATE _eState);
	void SetCurTarget(CMonster* _pMonster) { m_pCurTarget = _pMonster; }

	void ChangeState(MON_STATE _eNextState);
	
	CMonster* GetOwner() { return m_pOwner; }

public:
	AI();
	~AI();

	friend class CMonster;
};

