#include "pch.h"
#include "CTexture.h"

#include "CCore.h"


CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit != nullptr);

	// ��Ʈ�ʰ� ������ DC
	// �̰� ������ ����?
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	// �̰� �� ���� �ؾߵ�? ó������ �ȹ����� �ȵ�?
	DeleteObject(hPrevBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::MakeTransparent(UCHAR r, UCHAR g, UCHAR b)
{
	assert(m_hBit != nullptr);

	COLORREF crTransparent = RGB(r, g, b);

	HDC hdcMem, hdcMem2;
	HBITMAP hbmMask;
	BITMAP bm;

	GetObject(m_hBit, sizeof(BITMAP), &bm);
	hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	hdcMem = CreateCompatibleDC(0);
	hdcMem2 = CreateCompatibleDC(0);

	SelectObject(hdcMem, m_hBit);
	SelectObject(hdcMem2, hbmMask);

	SetBkColor(hdcMem, crTransparent);

	BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

	BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);

	m_hBit = hbmMask;
}