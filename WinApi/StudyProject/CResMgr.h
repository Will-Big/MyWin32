#pragma once

class CTexture;

class CResMgr
{
	SINGLE(CResMgr)
private:
	// �ؽ�ó �̸�, �ؽ�ó ������
	map<wstring, CTexture*> m_mapTex;

private:
	CTexture* FindTexture(const wstring& _strKey);

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

};

