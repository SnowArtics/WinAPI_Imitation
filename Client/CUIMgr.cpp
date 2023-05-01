#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	bool bRbtnTap = KEY_TAP(KEY::RBTN);
	bool bRbtnAway = KEY_AWAY(KEY::RBTN);

	// 1. Focused UI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI ������, �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI�� �����´�.
	CUI* pTargetUI = GetTargetdUI(m_pFocusedUI);

	if (nullptr != pTargetUI) {
		pTargetUI->MouseOn();

		if (bLbtnTap) {
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway) {
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown) {
				pTargetUI->MouseLbtnClicked();
			}

			//���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
			pTargetUI->m_bLbtnDown = false;
		}

		//������ ���콺 üũ
		if (bRbtnTap) {
			pTargetUI->MouseRbtnDown();
			pTargetUI->m_bRbtnDown = true;
		}
		else if (bRbtnAway) {
			pTargetUI->MouseRbtnUp();

			if (pTargetUI->m_bRbtnDown) {
				pTargetUI->MouseRbtnClicked();
			}

			//���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
			pTargetUI->m_bRbtnDown = false;
		}
	}
	//if (pUI->IsMouseOn()) {//targetedUI���� ���༭ ����.
	//	

	//	//���� ���콺 üũ
	//	
	//}
	//else { targetedUI���� ���༭ ����
	//	//���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
	//	if (bLbtnAway) {
	//		pUI->m_bLbtnDown = false;
	//	}
	//	//�����ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
	//	if (bRbtnAway) {
	//		pUI->m_bRbtnDown = false;
	//	}
	//}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// �̹� ��Ŀ�� ���� ��� or ��Ŀ�� ������û�� ���
	if (m_pFocusedUI == _pUI || nullptr == _pUI) {
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++) {
		if (m_pFocusedUI == *iter) {
			break;
		}
	}

	//���ͳ����� �� �ڷ� ���� ��ü(�������� ���ؼ�)
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}


CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap) {
		return pFocusedUI;
	}

	//���ʹ�ư Tap�� �߻��ߴٴ� ����
	//���ʹ�ư Tap�� �߻��ؾ� ��Ŀ���� �ٲ�.
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end();iter++) {
		if (((CUI*)*iter)->IsMouseOn()) {
			targetiter = iter;
		}		
	}
	//�̹��� Focus�� UI�� ���ٸ�
	if (targetiter == vecUI.end()) {
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	//���ͳ����� �� �ڷ� ���� ��ü(�������� ���ؼ�)
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetdUI(CUI* _pParentUI)
{
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	bool bRbtnTap = KEY_TAP(KEY::RBTN);
	bool bRbtnAway = KEY_AWAY(KEY::RBTN);


	// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;//���� ���Ű��Ƽ� ��������� �ٲ���
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty()) {
		//ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		//ť���� ������ UI�� TargetUI ���� Ȯ��
		//Ÿ�� UI�� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
		if (pUI->IsMouseOn()) {
			if (nullptr != pTargetUI) {
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else {//�ش� UI�� ���콺�� �ö� ���� �ʴٸ�
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); i++) {
			queue.push_back(vecChild[i]);
		}
	}

	if (bLbtnAway) {
		for (size_t i = 0; i < vecNoneTarget.size(); i++) {
			//���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
			vecNoneTarget[i]->m_bLbtnDown = false;
		}		
	}

	//�����ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
	if (bRbtnAway) {
		for (size_t i = 0; i < vecNoneTarget.size(); i++) {
			//���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
			vecNoneTarget[i]->m_bRbtnDown = false;
		}
	}

	return pTargetUI;
}
