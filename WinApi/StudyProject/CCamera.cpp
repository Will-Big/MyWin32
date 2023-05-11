#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}

		
	}

	CalDiff();
}

void CCamera::CalDiff()
{
	Vec2 vResoultion = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResoultion / 2.f;

	m_vDiff = m_vLookAt - vCenter;
}
