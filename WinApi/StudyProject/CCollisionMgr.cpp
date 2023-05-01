#include "pch.h"
#include "CCollisionMgr.h"

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
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 작은 값의 그룹 타입을 행으로
	// 큰 값을 열(비트)로 사용
}

void CCollisionMgr::Reset()
{
}
