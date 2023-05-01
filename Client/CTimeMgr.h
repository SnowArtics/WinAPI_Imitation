#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	//FPS
	//FPS ������ ���ؼ� 1�����Ӵ� �ð��� ���Ѵ�.
	//�̰� (Delta Time) �̶�� �Ѵ�.

	LARGE_INTEGER	m_liCurCount;
	LARGE_INTEGER	m_liFrequency;
	LARGE_INTEGER	m_liPrevCount;

	//DeltaTime
	double			m_dDT;//������ ���� �ð� ��
	double			m_dAcc;//DT�� ������ ��
	UINT			m_iCallCount;//�ʴ� ���� Ƚ��
	UINT			m_iFPS;//����Ƚ���� ���� 1�ʴ� �������� ����.

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

};

