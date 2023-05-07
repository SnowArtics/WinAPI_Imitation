#pragma once
#include "CScene.h"

class CObject;
class CTexture;

class CScene_Test :
    public CScene
{
private:
    //�� ������ � ���� ������ ������ �� �ִ�.
    vector<vector<CObject*> > m_vMap;

    //CBtnUI�� Ŭ���� ���콺 Ŀ���� ����ٴϴ� �ؽ��ĸ� ������ �ؽ���
    CTexture*                   m_pCursorIcon;
    bool                        m_bTriggerCursor;

    //�巡�� ���� ����
    Vec2    m_vDragStart;
    Vec2    m_vDragSize;
    bool    m_bDragOn;

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
    void SetCursorIconTex(CTexture* _pTex) {
        m_bTriggerCursor = true;
        m_pCursorIcon = _pTex;
    }

public:
    CScene_Test(int _row, int _column);
    ~CScene_Test();
};

