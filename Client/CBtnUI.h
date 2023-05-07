#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

#include "CTexture.h"

//전역함수 호출 시
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);

//몬스터 생성 부분
typedef void(*SPAWN_CREATURE)(DWORD_PTR, DWORD_PTR, DWORD_PTR);

class CBtnUI :
    public CUI
{
private:/*
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;*/

    //Scene 함수포인터를 사용하기 위한 준비
    SCENE_MEMFUNC   m_pSceneFunc;
    CScene*    m_pSceneInst;

    SPAWN_CREATURE  m_pSpawnFunc;
    DWORD_PTR       m_param1;
    DWORD_PTR       m_param2;
    DWORD_PTR       m_param3;

    //버튼을 클릭시 마우스 커서를 따라다니는 텍스쳐를 저장할 텍스쳐
    CTexture*               m_pCursorIcon;
    bool                        m_bTriggerCursor;

public:
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
    
public:
    void SetCursorIconTex(CTexture* _pTex) { m_pCursorIcon = _pTex; }

    //void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) 
    //{ 
    //    m_pFunc = _pFunc;
    //    m_param1 = _param1;
    //    m_param2 = _param2;
    //}

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    void SetClickedCallBack(SPAWN_CREATURE _pFunc, DWORD_PTR _param1, DWORD_PTR _param2, DWORD_PTR _param3) {
        m_pSpawnFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
        m_param3 = _param3;
    }


    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

