#pragma once
// Win32API ���� 13ȭ, 6�� 50�� ?

// Ű �Ŵ����� �ʿ��� ����
// 1. ������ ����ȭ - �� �����ӿ��� �߻��� �ϵ鿡 ���� ������ Ű�Է��� ����޾ƾ���
// 2. Ű �Է� �̺�Ʈ�� ��ü������ ����(tap, hold, away)




enum class KEY_STATE
{
	NONE,	// ������ ���� ����,	������ ������ ����
	TAP,	// ���� ����,		������ ������ ����
	HOLD,	// ���� ����,		������ ����
	AWAY,	// ������ ���� ����,	������ ����
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,
	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC,
	LAST, // ENUM �� ��
};

struct tKeyInfo
{
	KEY_STATE	eState; // Ű�� ���� ��
	bool		bPrevPush; // ���� �����ӿ��� ���ȴ��� ����
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

