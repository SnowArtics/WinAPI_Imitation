#pragma once
#include "CObject.h"

class CBridge;
class CScene;

class CBackground :
    public CObject
{
private:
    CTexture*                           m_pBackgroundTex;
    map<char, CObject*>       m_mapBridge;//Bridge�� ���� map
    CScene*                             m_pScene;//Bridge�� ���� �ִ� ��

    vector<char>                    m_vBridgeDirection;//�� Background�� ���� Bridge�� ����

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

