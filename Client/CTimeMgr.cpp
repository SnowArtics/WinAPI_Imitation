#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include <tchar.h>

CTimeMgr::CTimeMgr() 
	:m_liCurCount{}
	, m_liFrequency{}
	, m_liPrevCount{}
	,	m_dDT(0.f)
	,	m_iCallCount(0)
	,	m_dAcc(0.f)
	,	m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr() {

}

void CTimeMgr::init()
{

	QueryPerformanceCounter(&m_liPrevCount);//�ʴ� õ���� ����.
	//1�ʰ� ���������� ī��Ʈ�� �󸶳� ���̳����� �����;��Ѵ�. ���� ī��Ʈ�̴�.
	QueryPerformanceFrequency(&m_liFrequency);//1�ʴ� ī��Ʈ�� �󸶳� �߻��ϴ��� ��´�.
	//�ߴ����� ��� m_liFrequency���� õ���� ����Ǿ� �ִ°� Ȯ���� �� �ִ�.�ʴ� ī��Ʈ Ƚ���̴�.

	//�׷� ���� �� ������ ȣ���ϴµ� �ɸ��ð��� ���غ���.

}

void CTimeMgr::update() {
	QueryPerformanceCounter(&m_liCurCount);


	m_dDT = (double)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart)/(double)m_liFrequency.QuadPart;
	//�� ƽ�� �󸶳� ȣ��Ǵ��� ���ϰ� �̸� 1���� �ð����� ����� DeltaTime�� ���Ѵ�.



	m_liPrevCount = m_liCurCount;//PrevCount�� ���� CurCount�� ������ �� ������Ʈ������ �ʱ�ȭ�� �Ǵµ�,
	//�ٽ� �� update�� ����Ǿ����� curCount-prevCount�� ���� �� ƽ�� ���������� ������?
	//�׷��ٸ� �ð��� �������� ���ҷ��� 1�ʴ� �ð��� ������ �ǰڳ�?

#ifdef _DEBUG
	if (m_dDT > (1.f / 60.f))
		m_dDT = (1.f / 60.f);

#endif
}

void CTimeMgr::render()
{
	++m_iCallCount;//���� 1�ʰ� �Ǿ����� ���� ���Ѵ�.
	m_dAcc += m_dDT;//DT ����
	if (m_dAcc >= 1.f) {
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
