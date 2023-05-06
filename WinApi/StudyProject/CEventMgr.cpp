#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"

#include "CScene.h"
#include "CSceneMgr.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// 이벤트 매니저는 프레임의 마지막에 실행되므로
	// 다음 프레임까지 오브젝트를 살려둘 수 있음
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Execute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Execute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// wParam : NULL
		// Object 를 Dead 상태로 변경
		// 삭제 예정 오브젝트를 모아둔다.

		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{

	}
		break;
	}
}
