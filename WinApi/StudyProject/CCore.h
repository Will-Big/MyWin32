#pragma once



class CCore
{
	SINGLE(CCore)
private:
	HWND			m_hWnd;			// 메인 윈도우 핸들
	POINT			m_ptResolution;	// 메인 윈도우 해상도
	HDC				m_hDC;			// 메인 윈도우에 Draw 할 DC

	HBITMAP			m_hBit;
	HDC				m_memDC;

	// 자주 사용하는 GDI Object
	HBRUSH			m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN			m_arrPen[(UINT)PEN_TYPE::END];
    // 클래스의 포인터 사용의미 일단 런타임에 생성해야하거나 일반적으로 배열같은거의 크기는 컴파일타임에 결정할 수 없을 때는 포인터를 써야한다.
	// 컴파일타임에 결정된다는 게(바인딩) 이게 많을수록 빠르고(실행처리가 쩍으니) 안정적(컴파일러를 평가를 받은 거니까)이라는 의미라 해석

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};