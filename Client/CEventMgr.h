#pragma once

struct tEvent {
	EVENT_TYPE	eEven;
	DWORD_PTR		lParam;
	DWORD_PTR		WParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)

private:
	vector<tEvent> m_vecEvent;

	vector<CObject*> m_vecDead;//죽을 오브젝트를 모음.


public:
	void update();

private:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }
};

