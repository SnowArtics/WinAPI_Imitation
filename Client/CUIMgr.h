#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI*	m_pFocusedUI;

public:
	void update();

	//�ش� UI�� ��� ��Ŀ�� ����
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetTargetdUI(CUI* _pParentUI);//�θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.


};

