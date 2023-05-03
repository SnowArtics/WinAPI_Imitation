#pragma once
#include "CScene.h"
class CScene_Test :
    public CScene
{
private:

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter();
    virtual void Exit();


public:



public:
    CScene_Test();
    ~CScene_Test();
};

