#pragma once
#include "CScene.h"
#include "CMonFactory.h"

class CObject;
class CTexture;
class CBackground;

class CScene_Test :
    public CScene
{
private:
    //이 맵으로 어떤 행의 지형에 접속할 수 있다.
    vector<vector<CBackground*> > m_vMap;

    //CBtnUI를 클릭시 마우스 커서를 따라다니는 텍스쳐를 저장할 텍스쳐
    CTexture*                   m_pCursorIcon;
    MON_TYPE                    m_eMonType; //현재 클릭한 몬스터패널의 타입이 무엇인지
    MON_NAME                    m_eMonName; //현재 클릭한 몬스터 패널의 이름이 무엇인지
    bool                        m_bTriggerCursor;//현재 커서가 생성 커서인지

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
    const vector<vector<CBackground*> >& GetMaps() { return m_vMap; }

    vector<char> makeBridgeDirection(int _row, int _column, int _size);
    wstring makeBackgroundName(int _row, int _column);

    void LoadUI(const wstring& _strRelativePath, string _pageName);

public:
    void SetCursorIconTex(CTexture* _pTex, MON_TYPE _eMonType, MON_NAME _eMonName);

public:
    CScene_Test(int _row, int _column);
    ~CScene_Test();
};

