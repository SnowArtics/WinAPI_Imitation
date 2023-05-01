#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

//전역함수 호출 시
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);


class CBtnUI :
    public CUI
{
private:
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;

    //Scene 함수포인터를 사용하기 위한 준비
    SCENE_MEMFUNC   m_pSceneFunc;
    CScene*    m_pSceneInst;


public:
    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual void MouseRbtnDown();
    virtual void MouseRbtnUp();
    virtual void MouseRbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) 
    { 
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);


    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

