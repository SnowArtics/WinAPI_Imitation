#pragma once
#include "CScene.h"

class CObject;
class CTexture;

class CScene_Test :
    public CScene
{
private:
    //이 맵으로 어떤 행의 지형에 접속할 수 있다.
    vector<vector<CObject*> > m_vMap;

    //CBtnUI를 클릭시 마우스 커서를 따라다니는 텍스쳐를 저장할 텍스쳐
    CTexture*                   m_pCursorIcon;
    bool                        m_bTriggerCursor;

    //드래그 시작 지점
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

