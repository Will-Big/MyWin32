﻿// StudyProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "StudyProject.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_STUDYPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STUDYPROJECT));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STUDYPROJECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_STUDYPROJECT);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

#define GRID_X 10
#define GRID_Y 10

POINT prevPoint = { -1, -1 };
HRGN lastRegion;

// 창 크기 비례 좌표 조정
void ChangePoint(LPARAM lParam)
{
	static int currWidth, currHeight;
	int prevWidth, prevHeight;

	prevWidth = currWidth;
	prevHeight = currHeight;

	currWidth = LOWORD(lParam);
	currHeight = HIWORD(lParam);

	if (currHeight - prevHeight > 100) return;
	if (currWidth - prevWidth > 100) return;

	int widthDiff = currWidth - prevWidth;
	int heightDiff = currHeight - prevHeight;

	// 색칠된 영역 안을 유지하는지 검사
	if (PtInRegion(lastRegion, 
		prevPoint.x + widthDiff*2, 
		prevPoint.y + heightDiff*2))
	{
		prevPoint.x += widthDiff;
		prevPoint.y += heightDiff;
	}
}

// 그리드 출력
void DrawGrid(HWND hWnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	int xBlock = (rect.right - rect.left) / GRID_X;
	int yBlock = (rect.bottom - rect.top) / GRID_Y;

	if (xBlock <= 0 || yBlock <= 0) return;

	HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(0xff, 0xda, 0xb9));
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	for (int x = rect.left; x < rect.right; x += xBlock)
	{
		for (int y = rect.top; y < rect.bottom; y += yBlock)
		{
			HRGN hrgn = CreateRectRgn(x, y, x + xBlock, y + yBlock);

			if (PtInRegion(hrgn, prevPoint.x, prevPoint.y))
			{
				// 이전 영역 삭제
				if (lastRegion != NULL)
				{
					HRGN tempHrgn = NULL;
					CombineRgn(tempHrgn, lastRegion, NULL, RGN_COPY);
					DeleteObject(tempHrgn);
				}
				
				RECT rc;
				GetRgnBox(hrgn, &rc);
				lastRegion = CreateRectRgnIndirect(&rc);

				SelectObject(hdc, hBrush);
			}
			else
			{
				SelectObject(hdc, hBrushOld);
			}

			Rectangle(hdc, x, y, x + xBlock, y + yBlock);
			DeleteObject(hrgn);
		}
	}

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

// 영역 클릭
void PointGrid(HWND hWnd, LPARAM lParam)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	int xBlock = (rect.right - rect.left) / GRID_X;
	int yBlock = (rect.bottom - rect.top) / GRID_Y;

	prevPoint.x = LOWORD(lParam);
	prevPoint.y = HIWORD(lParam);
}
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
	{
		ChangePoint(lParam);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawGrid(hWnd, hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		PointGrid(hWnd, lParam);
		InvalidateRect(hWnd, nullptr, false);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
