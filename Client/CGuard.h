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
    //클릭시 같은건 CMonster에서 다 정의

    CLONE(CGuard);

public:
    CGuard();
    ~CGuard();
};

