#pragma once
// Win32API 강의 13화, 6분 50초 ?

// 키 매니저가 필요한 이유
// 1. 프레임 동기화 - 한 프레임에서 발생한 일들에 대해 동일한 키입력을 적용받아야함
// 2. 키 입력 이벤트를 구체적으로 정의(tap, hold, away)




enum class KEY_STATE
{
	NONE,	// 누르지 않은 상태,	이전에 눌리지 않음
	TAP,	// 누른 상태,		이전에 눌리지 않음
	HOLD,	// 누른 상태,		이전에 누름
	AWAY,	// 누르지 않은 상태,	이전에 누름
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,
	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC,
	LAST, // ENUM 의 끝
};

struct tKeyInfo
{
	KEY_STATE	eState; // 키의 상태 값
	bool		bPrevPush; // 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
};

