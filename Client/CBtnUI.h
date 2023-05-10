#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

#include "CTexture.h"
#include "CMonFactory.h"

//전역함수 호출 시
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

    ////Scene 함수포인터를 사용하기 위한 준비
    //SCENE_MEMFUNC   m_pSceneFunc;
    //CScene*    m_pSceneInst;
    
    //현재 버튼의 이름
    wstring         m_sBtnName;

    //마우스 커서 아이콘의 상태를 가지고 있을 텍스트 변수
    CTexture* m_pCursorIcon;

    //SceneCursorIcon을 조종하기 위한 함수포인터를 사용할 준비
    CScene*             m_pSceneInst;
    SCENE_CURSOR_FUNC   m_pSceneCursorIcon;

    MON_TYPE                    m_eMonType; //현재 이 패널의 몬스터패널의 타입이 무엇인지
    MON_NAME                    m_eMonName; //현재 이 패널의 몬스터 패널의 이름이 무엇인지   

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

