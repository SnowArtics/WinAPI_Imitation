#pragma once
#include "CScene.h"

class CObject;

class CScene_Test :
    public CScene
{
private:
    //�� ������ � ���� ������ ������ �� �ִ�.
    vector<vector<CObject*> > m_vMap;

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter();
    virtual void Exit();

public:
    vector<char> makeBridgeDirection(int _row, int _column, int _size);
    wstring makeBackgroundName(int _row, int _column);

    void LoadUI(const wstring& _strRelativePath, string _pageName);

public:
    CScene_Test(int _row, int _column);
    ~CScene_Test();
};

