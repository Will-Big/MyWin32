#include "pch.h"
#include "CKeyMgr.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q', 
	'W', 
	'E', 
	'R', 
	'T', 
	'Y',
	'U', 
	'I', 
	'O', 
	'P',
	'A', 
	'S', 
	'D', 
	'F', 
	'G', 
	'Z', 
	'X', 
	'C',
	'V', 
	'B',
	VK_MENU, 
	VK_LSHIFT, 
	VK_SPACE,
	VK_LCONTROL, 
	VK_RETURN, 
	VK_ESCAPE,
	// LAST
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}


}

void CKeyMgr::update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 키가 눌려있다.
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrevPush)
			{
				// 이전에도 눌려있었다.
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			else
			{
				// 이전에 눌려있지 않았다.
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			m_vecKey[i].bPrevPush = true;
		}
		else
		{
			// 키가 안눌려있다.
			if (m_vecKey[i].bPrevPush)
			{
				// 이전에 눌려있었다.
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else
			{
				// 이전에도 안눌려있었다.
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			m_vecKey[i].bPrevPush = false;
		}

	}
}
