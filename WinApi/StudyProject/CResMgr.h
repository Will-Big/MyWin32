#pragma once

class CRes;
class CTexture;

class CResMgr
{
	SINGLE(CResMgr)
private:
	map<wstring, CRes*> m_mapTex;

private:
	CTexture* FindTexture(const wstring& _strKey);

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

};

