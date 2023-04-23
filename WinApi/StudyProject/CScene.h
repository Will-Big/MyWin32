#pragma once

// 전방 선언
class CObject;

// 클래스를 헤더에 구현하면 inline 처리되어서 함수 호출비용이 발생하지 않는다
class CScene
{
private:
	// vector 를 소멸할 필요가 없는 이유는?
	// 명시적으로 작성하지 않아도 멤버변수이기 때문에 vector class 내부에서 알아서 처리해줌
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring				m_strName; // Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	// 순수 가상함수(override 필수)
	virtual void Enter() = 0;	// 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0;	// 해당 Scene 을 탈출 시 호출

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }

public:
	CScene();
	virtual ~CScene(); // virtual 없으면 delete 시 부모쪽의 소멸자만 호출됨
};

