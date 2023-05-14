#pragma once
#include "CObject.h"

class CTexture;

class CBack :
    public CObject
{
private:
    CTexture* m_pBackgroundTex;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetTexture(CTexture* _pTex) { m_pBackgroundTex = _pTex; }
    CTexture* GetTexture() { m_pBackgroundTex; }

    CLONE(CBack);
public:
    CBack();
    ~CBack();
};

