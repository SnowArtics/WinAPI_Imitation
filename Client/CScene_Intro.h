#pragma once
#include "CScene.h"

#include "CUI.h"

class CScene_Intro :
    public CScene
{
private:
    CUI* m_pPanelUI;
    CUI* m_pUI1;
    CUI* m_pUI2;

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();
    virtual void render(HDC _dc);

public:
    void SetPanelUI(CUI* _p) { m_pPanelUI = _p; }
    void SetUI1(CUI* _p) { m_pUI1 = _p; }
    void SetUI2(CUI* _p) { m_pUI2 = _p; }

    CUI* GetPanelUI() { return m_pPanelUI; }
    CUI* GetUI1() { return m_pUI1; }
    CUI* GetUI2() { return  m_pUI2; }

public:
    CScene_Intro();
    ~CScene_Intro();
};
