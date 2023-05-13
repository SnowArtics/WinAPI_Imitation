#pragma once
#include "CState.h"
class CAttState :
    public CState
{
private:
    float m_fTime;
    float m_fWaitTime;

public:
    void SetTime(float _f) { m_fTime = _f; }
    void SetWaitTime(float _f) { m_fWaitTime = _f; }

    float GetTime() { return m_fTime; }
    float GetWaitTime() { return m_fWaitTime; }

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CAttState();
    ~CAttState();
};

