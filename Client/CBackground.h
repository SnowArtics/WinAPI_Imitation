#pragma once
#include "CObject.h"

class CBridge;
class CScene;

class CBackground :
    public CObject
{
private:
    CTexture*                           m_pBackgroundTex;
    map<char, CObject*>       m_mapBridge;//Bridge를 넣을 map
    CScene*                             m_pScene;//Bridge가 속해 있는 씬

    vector<char>                    m_vBridgeDirection;//이 Background가 가질 Bridge의 방향

public:
    void SetTexture(CTexture* _pTex) {
        m_pBackgroundTex = _pTex;
    }

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CBackground);

public:
    CBackground(vector<char> _BridgeDirection, CScene* _Scene);
    CBackground(const CBackground& _origin);
    ~CBackground();
};

