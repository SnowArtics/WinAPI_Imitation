#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	//FPS
	//FPS 역수를 취해서 1프레임당 시간을 구한다.
	//이걸 (Delta Time) 이라고 한다.

	LARGE_INTEGER	m_liCurCount;
	LARGE_INTEGER	m_liFrequency;
	LARGE_INTEGER	m_liPrevCount;

	//DeltaTime
	double			m_dDT;//프레임 간의 시간 값
	double			m_dAcc;//DT를 누적한 값
	UINT			m_iCallCount;//초당 누적 횟수
	UINT			m_iFPS;//누적횟수를 통해 1초당 프레임을 구함.

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

};

