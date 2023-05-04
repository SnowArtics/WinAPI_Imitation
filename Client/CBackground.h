#pragma once
#include "CObject.h"
class CBackground :
    public CObject
{
private:
    CTexture* m_pBackgroundTex;

public:
    void SetTexture(CTexture* _pTex) {
        m_pBackgroundTex = _pTex;
    }

private:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CBackground);

public:
    CBackground();
    CBackground(const CBackground& _origin);
    ~CBackground();
};

