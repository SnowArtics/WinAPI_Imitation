#pragma once
#include "CObject.h"
class CBridge :
    public CObject
{
private:
    CTexture* m_pBridgeTex;
    char m_iDirection;

public:
    void SetTexture(CTexture* _pTex) {
        m_pBridgeTex = _pTex;
    }

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual void MouseRbtnDown();
    virtual void MouseRbtnUp();
    virtual void MouseRbtnClicked();

    CLONE(CBridge);

public:
    void DrawTransparentImage(HDC hdc, int x, int y, int cx, int cy, HBITMAP hBitmap, COLORREF transparentColor, int alpha);

public:
    CBridge(char _direction);
    CBridge(const CBridge& _origin);
    ~CBridge();
};

