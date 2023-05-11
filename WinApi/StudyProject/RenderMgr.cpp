#include "pch.h"
#include "RenderMgr.h"

#include "CCore.h"

void RenderMgr::init()
{
	
}

void RenderMgr::finalRender(HDC _dc)
{
}

void RenderMgr::renderLayer(LAYER _eLayer, RenderInfo _sInfo)
{
}


RenderMgr::RenderMgr()
	: m_memDC(nullptr)
	, m_arrDC{}
{
}

RenderMgr::~RenderMgr()
{
}
