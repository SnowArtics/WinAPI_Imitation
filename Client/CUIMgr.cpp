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

	// 1. Focused UI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI를 가져온다.
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

			//왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
			pTargetUI->m_bLbtnDown = false;
		}

		//오른쪽 마우스 체크
		if (bRbtnTap) {
			pTargetUI->MouseRbtnDown();
			pTargetUI->m_bRbtnDown = true;
		}
		else if (bRbtnAway) {
			pTargetUI->MouseRbtnUp();

			if (pTargetUI->m_bRbtnDown) {
				pTargetUI->MouseRbtnClicked();
			}

			//왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
			pTargetUI->m_bRbtnDown = false;
		}
	}
	//if (pUI->IsMouseOn()) {//targetedUI에서 해줘서 안함.
	//	

	//	//왼쪽 마우스 체크
	//	
	//}
	//else { targetedUI에서 해줘서 안함
	//	//왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
	//	if (bLbtnAway) {
	//		pUI->m_bLbtnDown = false;
	//	}
	//	//오른쪽버튼 떼면 눌렸던 체크를 다시 해제한다
	//	if (bRbtnAway) {
	//		pUI->m_bRbtnDown = false;
	//	}
	//}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// 이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
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

	//벡터내에서 맨 뒤로 순번 교체(렌더링을 위해서)
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}


CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap) {
		return pFocusedUI;
	}

	//왼쪽버튼 Tap이 발생했다는 전제
	//왼쪽버튼 Tap이 발생해야 포커싱이 바뀜.
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end();iter++) {
		if (((CUI*)*iter)->IsMouseOn()) {
			targetiter = iter;
		}		
	}
	//이번에 Focus된 UI가 없다면
	if (targetiter == vecUI.end()) {
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	//벡터내에서 맨 뒤로 순번 교체(렌더링을 위해서)
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


	// 1. 부모 UI 포함, 모든 자식들을 검사한다.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;//자주 쓸거같아서 정적멤버로 바꿔줌
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty()) {
		//큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		//큐에서 꺼내온 UI가 TargetUI 인지 확인
		//타겟 UI들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn()) {
			if (nullptr != pTargetUI) {
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else {//해당 UI에 마우스가 올라가 있지 않다면
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); i++) {
			queue.push_back(vecChild[i]);
		}
	}

	if (bLbtnAway) {
		for (size_t i = 0; i < vecNoneTarget.size(); i++) {
			//왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
			vecNoneTarget[i]->m_bLbtnDown = false;
		}		
	}

	//오른쪽버튼 떼면 눌렸던 체크를 다시 해제한다
	if (bRbtnAway) {
		for (size_t i = 0; i < vecNoneTarget.size(); i++) {
			//왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
			vecNoneTarget[i]->m_bRbtnDown = false;
		}
	}

	return pTargetUI;
}
