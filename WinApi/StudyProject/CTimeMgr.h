#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;			// 프레임 간의 시간 값
	double			m_dAcc;			// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// 함수 호출 횟수
	UINT			m_iFPS;			// 초당 호출 횟수
	// FPS
	// 1 프레임당 시간 Delta Time

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

	// 내 맘대로 함수
	double GetdAcc() { return m_dAcc; } // 1초 근방을 얻기 위한 함수
};

