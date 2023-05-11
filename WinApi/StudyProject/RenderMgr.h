#pragma once
#include "Singleton.h"

enum class LAYER
{
    DEFAULT,
    BACKGROUND,
    OBJECT,
    COLLISION,
    UI,
    END,
};

struct RenderInfo
{
    USHORT a, r, g, b;

};

class RenderMgr : public Singleton<RenderMgr>
{
    friend class Singleton<RenderMgr>;

private:
    HDC     m_memDC;
    HDC     m_arrDC[(UINT)LAYER::END];



public:
    void init();
    void finalRender(HDC _dc);
    void renderLayer(LAYER _eLayer, RenderInfo _sInfo);

private:
    RenderMgr();
    ~RenderMgr();
};

