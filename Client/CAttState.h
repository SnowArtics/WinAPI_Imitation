#pragma once
#include "CState.h"
class CAttState :
    public CState
{
private:

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CAttState();
    ~CAttState();
};

