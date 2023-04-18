#include <Windows.h>


// 운영체제에 의해 호출되는 응용 프로그램내의 함수를 콜백(CallBack) 함수라고 한다.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass = (LPSTR)"First";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	
	WndClass.cbClsExtra = 0; // 예약 영역 - 사용하지 않을 경우 0
	WndClass.cbWndExtra = 0; // 예약 영역 - 사용하지 않을 경우 0
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 윈도우의 배경 색상을 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 이 윈도우가 사용할 마우스 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 이 윈도우가 사용할 최소화되었을 경우 출력될 아이콘
	WndClass.hInstance = hInstance; // 이 윈도우 클래스를 사용하는 프로그램의 번호
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // 윈도우 메시지 처리 함수 지정
	WndClass.lpszClassName = lpszClass; // 윈도우 클래스의 이름을 정의
	WndClass.lpszMenuName = NULL; // 이 프로그램이 사용할 메뉴 - 사용하지 않을 경우 NULL
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 수직(수평) 크기가 변할 때 마다 다시 그린다
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, "My First Program", WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL); // 메모리에 프로세스(?) 생성
	ShowWindow(hWnd, nCmdShow); // 실제 화면에 띄우기

	while (GetMessage(&Message, 0, 0, 0)) { // 메세지 확인(종료 전까지 반복)
		TranslateMessage(&Message); // 메세지 가공
		DispatchMessage(&Message); // 메세지 전달
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