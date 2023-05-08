#pragma once

class CTexture;

class CResMgr
{
	SINGLE(CResMgr)
private:
	// 텍스처 이름, 텍스처 포인터
	map<wstring, CTexture*> m_mapTex;

private:
	CTexture* FindTexture(const wstring& _strKey);

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

};

