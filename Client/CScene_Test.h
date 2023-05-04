#pragma once
#include "CScene.h"
class CScene_Test :
    public CScene
{
private:
    vector<vector<CObject*> > m_vMap;

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter();
    virtual void Exit();

public:
    

public:
    CScene_Test(int _row, int _column);
    ~CScene_Test();
};

