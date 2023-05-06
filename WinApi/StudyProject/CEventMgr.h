#pragma once

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)

private:

	vector<tEvent>		m_vecEvent;		// 호출된 이벤트들
	vector<CObject*>	m_vecDead;		// 삭제 예정 오브젝트

public:
	void update();

private:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }
};

