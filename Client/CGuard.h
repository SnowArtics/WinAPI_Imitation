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
    //Ŭ���� ������ CMonster���� �� ����

    CLONE(CGuard);

public:
    CGuard();
    ~CGuard();
};

