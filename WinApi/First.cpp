#include <Windows.h>


// �ü���� ���� ȣ��Ǵ� ���� ���α׷����� �Լ��� �ݹ�(CallBack) �Լ���� �Ѵ�.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass = (LPSTR)"First";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	
	WndClass.cbClsExtra = 0; // ���� ���� - ������� ���� ��� 0
	WndClass.cbWndExtra = 0; // ���� ���� - ������� ���� ��� 0
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �������� ��� ������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // �� �����찡 ����� ���콺 Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // �� �����찡 ����� �ּ�ȭ�Ǿ��� ��� ��µ� ������
	WndClass.hInstance = hInstance; // �� ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // ������ �޽��� ó�� �Լ� ����
	WndClass.lpszClassName = lpszClass; // ������ Ŭ������ �̸��� ����
	WndClass.lpszMenuName = NULL; // �� ���α׷��� ����� �޴� - ������� ���� ��� NULL
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ ����(����) ũ�Ⱑ ���� �� ���� �ٽ� �׸���
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, "My First Program", WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL); // �޸𸮿� ���μ���(?) ����
	ShowWindow(hWnd, nCmdShow); // ���� ȭ�鿡 ����

	while (GetMessage(&Message, 0, 0, 0)) { // �޼��� Ȯ��(���� ������ �ݺ�)
		TranslateMessage(&Message); // �޼��� ����
		DispatchMessage(&Message); // �޼��� ����
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, CW_USEDEFAULT, CW_USEDEFAULT, "Beautiful Korea", 15);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, "Beautiful Korea", 15);
		EndPaint(hWnd, &ps);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}