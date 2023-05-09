#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
	, m_iTimerID(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	
	// 이전 카운트 값을 현재 값으로 갱신(다음번의 계산을 위해서)
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG
	// 디버그 모드라면 자동으로 전처리기가 활성화됨
	// 디버그 모드 중 정지했을 때 다음 프레임까지의 시간을 60분의 1초로 보장해줌
	if (m_dDT > 1.f / 60.f)
		m_dDT = 1.f / 60.f;
#endif
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT 누적

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %lf", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}

//LARGE_INTEGER CTimeMgr::GetCurTime()
//{
//	return LARGE_INTEGER();
//}
