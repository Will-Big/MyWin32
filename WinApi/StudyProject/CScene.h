#pragma once

// ���� ����
class CObject;

// Ŭ������ ����� �����ϸ� inline ó���Ǿ �Լ� ȣ������ �߻����� �ʴ´�
class CScene
{
private:
	// vector �� �Ҹ��� �ʿ䰡 ���� ������?
	// ��������� �ۼ����� �ʾƵ� ��������̱� ������ vector class ���ο��� �˾Ƽ� ó������
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName; // Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	// ���� �����Լ�(override �ʼ�)
	virtual void Enter() = 0;	// �ش� Scene �� ���� �� ȣ��
	virtual void Exit() = 0;	// �ش� Scene �� Ż�� �� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }

public:
	CScene();
	virtual ~CScene(); // virtual ������ delete �� �θ����� �Ҹ��ڸ� ȣ���
};

