#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI*	m_pFocusedUI;

public:
	void update();

	//해당 UI를 즉시 포커스 해줌
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetTargetdUI(CUI* _pParentUI);//부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 변환한다.


};

