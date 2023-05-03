#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� : 0 ~ 31, �� : 31 ~ 0
	UINT iRow = (UINT)_eLeft;	// ���� ���� �׷� Ÿ���� ������
	UINT iCol = (UINT)_eRight;	// ū ���� �׷� Ÿ���� ������

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// iCol ��ŭ ��Ʈ �������� �о iRow�� �ֱ�
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// ��ȯ Ÿ���� ������ ������ ������ �ƴ�!
	// ��ȯ�� ����, ������ �����ؼ� �޾ұ⿡ ���������� ��
	// ���� ���� ���� ������ �޾ƾ� ��
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� ���� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü�� ���ų� �ڽŰ� ���� �ּҰ�(�ڱ� �ڽ�)�� ���� ������Ʈ�� ���
			if (vecRight[i]->GetCollider() == nullptr || vecLeft[i] == vecRight[j])
				continue;
			
			// ���� �������� ������ �̿��ؼ�
			// �浹 ������, �浹 ���̾�����, �浹�� ������� Ȯ����
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[i]->GetCollider()))
			{

			}
			else
			{

			}

		}
	}

}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftOffset = _pLeftCol->GetOffsetPos();
	Vec2 vRightOffset = _pRightCol->GetOffsetPos();
	return false;
}
