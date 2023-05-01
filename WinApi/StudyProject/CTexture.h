#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    HDC     m_dc;
    HBITMAP m_hBit;
    BITMAP  m_bitInfo;

public:
    void Load(const wstring& _strFilePath);
    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }
    void MakeTransparent(UCHAR r = 255U, UCHAR g = 255U, UCHAR b = 255U);

private:
    CTexture();
    ~CTexture();

    friend class CResMgr;
};

