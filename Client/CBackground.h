#pragma once
#include "CObject.h"
#include "CMonFactory.h"

class CBridge;
class CScene;

class CBackground :
    public CObject
{
private:
    CTexture*                           m_pBackgroundTex;
    map<char, CObject*>       m_mapBridge;//Bridge를 넣을 map
    CScene*                             m_pScene;//Bridge가 속해 있는 씬

    bool                            m_bTriggerCursor;
    MON_TYPE                        m_eMonType;//클릭시 생성할 몬스터의 타입
    MON_NAME                        m_eMonName;//클릭시 생성할 몬스터의 이름

    vector<char>                    m_vBridgeDirection;//이 Background가 가질 Bridge의 방향

    int                             m_iOwn; //현재 이 맵을 지배중인 플레이어
                                            //0은 몬스터, 1은 P1, 2는 P2, 3은 P3, 4는 p4

public:
    void SetTexture(CTexture* _pTex) {
        m_pBackgroundTex = _pTex;
    }

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    MON_TYPE GetMonType() { return m_eMonType; }
    MON_NAME GetMonName() { return m_eMonName; }

    void SetMonType(MON_TYPE _e) { m_eMonType = _e; }
    void SetMonName(MON_NAME _e) { m_eMonName = _e; }
    void SetTriggerCursor(bool _b) { m_bTriggerCursor = _b; }
    void SetBackgroundOwn(int _i) { m_iOwn = _i; }

public:
    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual void MouseRbtnDown();
    virtual void MouseRbtnUp();
    virtual void MouseRbtnClicked();

    CLONE(CBackground);

public:
    CBackground(vector<char> _BridgeDirection, CScene* _Scene);
    CBackground(const CBackground& _origin);
    ~CBackground();
};

