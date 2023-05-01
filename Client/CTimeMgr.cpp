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

	QueryPerformanceCounter(&m_liPrevCount);//초당 천만을 샌다.
	//1초가 벌어졌을때 카운트가 얼마나 차이나는지 가져와야한다. 현재 카운트이다.
	QueryPerformanceFrequency(&m_liFrequency);//1초당 카운트가 얼마나 발생하는지 얻는다.
	//중단점을 골면 m_liFrequency에는 천만이 저장되어 있는걸 확인할 수 있다.초당 카운트 횟수이다.

	//그럼 이제 한 프레임 호출하는데 걸린시간을 구해보자.

}

void CTimeMgr::update() {
	QueryPerformanceCounter(&m_liCurCount);


	m_dDT = (double)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart)/(double)m_liFrequency.QuadPart;
	//한 틱에 얼마나 호출되는지 구하고 이를 1초의 시간으로 나누어서 DeltaTime을 구한다.



	m_liPrevCount = m_liCurCount;//PrevCount의 값은 CurCount의 값으로 매 업데이트때마다 초기화가 되는데,
	//다시 이 update가 실행되었을때 curCount-prevCount의 값은 한 틱당 프레임이지 않을까?
	//그렇다면 시간당 프레임을 구할려면 1초당 시간을 나누면 되겠네?

#ifdef _DEBUG
	if (m_dDT > (1.f / 60.f))
		m_dDT = (1.f / 60.f);

#endif
}

void CTimeMgr::render()
{
	++m_iCallCount;//이후 1초가 되었을때 값을 구한다.
	m_dAcc += m_dDT;//DT 누적
	if (m_dAcc >= 1.f) {
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
