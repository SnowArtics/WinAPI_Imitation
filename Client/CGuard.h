#pragma once
#include "CMonster.h"
class CGuard :
    public CMonster
{
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void update_animation();

public:
    virtual void MouseOn() { CMonster::MouseOn(); }

    virtual void MouseLbtnDown() { CMonster::MouseLbtnDown(); };
    virtual void MouseLbtnUp() { CMonster::MouseLbtnUp(); };
    virtual void MouseLbtnClicked() { CMonster::MouseLbtnClicked(); }

    virtual void MouseRbtnDown() { CMonster::MouseRbtnDown(); };
    virtual void MouseRbtnUp() { CMonster::MouseRbtnUp(); };
    virtual void MouseRbtnClicked() { CMonster::MouseRbtnClicked(); };

public:
    //클릭시 같은건 CMonster에서 다 정의

    CLONE(CGuard);

public:
    CGuard();
    ~CGuard();
};

