#pragma once

// 전방 선언
class CObject;

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring				m_strName; // Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


public:
	CScene();
	virtual ~CScene(); // virtual 없으면 delete 시 부모쪽의 소멸자만 호출됨
};

