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
    map<char, CObject*>       m_mapBridge;//Bridge�� ���� map
    CScene*                             m_pScene;//Bridge�� ���� �ִ� ��

    bool                            m_bTriggerCursor;
    MON_TYPE                        m_eMonType;//Ŭ���� ������ ������ Ÿ��
    MON_NAME                        m_eMonName;//Ŭ���� ������ ������ �̸�

    vector<char>                    m_vBridgeDirection;//�� Background�� ���� Bridge�� ����

    int                             m_iOwn; //���� �� ���� �������� �÷��̾�
                                            //0�� ����, 1�� P1, 2�� P2, 3�� P3, 4�� p4

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

