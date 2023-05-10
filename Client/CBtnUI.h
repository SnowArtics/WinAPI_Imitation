#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

#include "CTexture.h"
#include "CMonFactory.h"

//�����Լ� ȣ�� ��
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);
typedef void(CScene::*SCENE_CURSOR_FUNC)(CTexture*, MON_TYPE, MON_NAME);

class CBtnUI :
    public CUI
{
private:/*
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;*/

    ////Scene �Լ������͸� ����ϱ� ���� �غ�
    //SCENE_MEMFUNC   m_pSceneFunc;
    //CScene*    m_pSceneInst;
    
    //���� ��ư�� �̸�
    wstring         m_sBtnName;

    //���콺 Ŀ�� �������� ���¸� ������ ���� �ؽ�Ʈ ����
    CTexture* m_pCursorIcon;

    //SceneCursorIcon�� �����ϱ� ���� �Լ������͸� ����� �غ�
    CScene*             m_pSceneInst;
    SCENE_CURSOR_FUNC   m_pSceneCursorIcon;

    MON_TYPE                    m_eMonType; //���� �� �г��� �����г��� Ÿ���� ��������
    MON_NAME                    m_eMonName; //���� �� �г��� ���� �г��� �̸��� ��������   

public:
    virtual void start();
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual void MouseRbtnDown();
    virtual void MouseRbtnUp();
    virtual void MouseRbtnClicked();

    void SetCursorIconTex(CTexture* _pTex) { m_pCursorIcon = _pTex; }
    void SetName(wstring _s) { m_sBtnName = _s; }
    
public:   
    //void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) 
    //{ 
    //    m_pFunc = _pFunc;
    //    m_param1 = _param1;
    //    m_param2 = _param2;
    //}

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    void SetClickedCallBack(CScene* _pScene, SCENE_CURSOR_FUNC _pSceneFunc);

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

