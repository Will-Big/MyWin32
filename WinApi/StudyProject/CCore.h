#pragma once



class CCore
{
	SINGLE(CCore)
private:
	HWND			m_hWnd;			// ���� ������ �ڵ�
	POINT			m_ptResolution;	// ���� ������ �ػ�
	HDC				m_hDC;			// ���� �����쿡 Draw �� DC

	HBITMAP			m_hBit;
	HDC		m_memDC;
    // Ŭ������ ������ ����ǹ� �ϴ� ��Ÿ�ӿ� �����ؾ��ϰų� �Ϲ������� �迭�������� ũ��� ������Ÿ�ӿ� ������ �� ���� ���� �����͸� ����Ѵ�.
	// ������Ÿ�ӿ� �����ȴٴ� ��(���ε�) �̰� �������� ������(����ó���� ½����) ������(�����Ϸ��� �򰡸� ���� �Ŵϱ�)�̶�� �ǹ̶� �ؼ�

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
};