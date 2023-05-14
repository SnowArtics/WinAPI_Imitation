#include "pch.h"
#include "CObjectMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"

#include "CObject.h"

CObjectMgr::CObjectMgr()
{

}

CObjectMgr::~CObjectMgr()
{

}

void CObjectMgr::update()
{
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	bool bRbtnTap = KEY_TAP(KEY::RBTN);
	bool bRbtnAway = KEY_AWAY(KEY::RBTN);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	m_pFocusedObject = GetFocusedObject();

	if (!m_pFocusedObject)
		return;

	if (nullptr != m_pFocusedObject) {
		m_pFocusedObject->MouseOn();

		if (bLbtnTap) {
			m_pFocusedObject->MouseLbtnDown();
			m_pFocusedObject->m_bLbtnDown = true;
		}
		else if (bLbtnAway) {
			m_pFocusedObject->MouseLbtnUp();

			if (m_pFocusedObject->m_bLbtnDown) {
				m_pFocusedObject->MouseLbtnClicked();
			}

			//왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
			m_pFocusedObject->m_bLbtnDown = false;
		}

		//오른쪽 마우스 체크
		if (bRbtnTap) {
			m_pFocusedObject->MouseRbtnDown();
			m_pFocusedObject->m_bRbtnDown = true;
		}
		else if (bRbtnAway) {
			m_pFocusedObject->MouseRbtnUp();

			if (m_pFocusedObject->m_bRbtnDown) {
				m_pFocusedObject->MouseRbtnClicked();
			}

			//왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
			m_pFocusedObject->m_bRbtnDown = false;
		}
	}




	////클릭이 가능하게 설정한 모든 오브젝트들을 대상으로 반복문을 돌림
	//for (int i = (int)GROUP_TYPE::BACKGROUND; i < (int)GROUP_TYPE::UI; i++) {
	//	const vector<CObject*>& vecUI = pCurScene->GetGroupObject((GROUP_TYPE)i);

	//	//클릭이 되었는지 여기서 검사
	//	for (size_t i = 0; i < vecUI.size(); i++) {
	//		CObject* pObject = (CObject*)vecUI[i];
	//		if (pObject->IsMouseOn()) {
	//			pObject->MouseOn();

	//			//왼쪽버튼 클릭시
	//			if (bLbtnTap) {
	//				pObject->MouseLbtnDown();
	//				pObject->m_bLbtnDown = true;
	//			}
	//			else if (bLbtnAway) {
	//				pObject->MouseLbtnUp();

	//				if (pObject->m_bLbtnDown) {
	//					pObject->MouseLbtnClicked();
	//				}
	//				//왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
	//				pObject->m_bLbtnDown = false;
	//			}

	//			//오른쪽 버튼 클릭시
	//			if (bRbtnTap) {
	//				pObject->MouseRbtnDown();
	//				pObject->m_bRbtnDown = true;
	//			}
	//			else if (bRbtnAway) {
	//				pObject->MouseRbtnUp();

	//				if (pObject->m_bRbtnDown) {
	//					pObject->MouseRbtnClicked();
	//				}
	//				//오른쪽 버튼 떼면, 눌렸던 체크를 다시 해제한다.
	//				pObject->m_bRbtnDown = false;
	//			}
	//		}
	//		else {
	//			//왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
	//			if (bLbtnAway) {
	//				pObject->m_bLbtnDown = false;
	//			}

	//			//오른쪽 버튼 떼면, 눌렸던 체크를 다시 해제한다.
	//			if (bRbtnAway) {
	//				pObject->m_bRbtnDown = false;
	//			}
	//		}
	//	}
	//}
}

CObject* CObjectMgr::GetFocusedObject()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	bool bRbtnTap = KEY_TAP(KEY::LBTN);
	bool bRbtnAway = KEY_AWAY(KEY::RBTN);

	// 기존 포커싱 오브젝트를 받아두고 변경되었는지 확인한다.
	CObject* pFocusedObject = m_pFocusedObject;

	//왼쪽버튼 Tap이 발생했다는 전제
	//왼쪽버튼 Tap이 발생해야 포커싱이 바뀜.
	vector<CObject*>& vecObject = pCurScene->GetGroupObjectC((GROUP_TYPE)0);
	vector<CObject*>::iterator targetiter = vecObject.end();
	vector<CObject*>::iterator iter = vecObject.begin();

	vector<CObject*> iterResult;

	for (int i = (int)GROUP_TYPE::BACKGROUND; i < (int)GROUP_TYPE::UI; i++) {
		vecObject = pCurScene->GetGroupObjectC((GROUP_TYPE)i);
		targetiter = vecObject.end();
		iter = vecObject.begin();
		for (; iter != vecObject.end(); iter++) {
			if (((CObject*)*iter)->IsMouseOn()) {
				targetiter = iter;
				iterResult.push_back(*targetiter);
			}
			else {
				//왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
				if (bLbtnAway) {
					((CObject*)*iter)->m_bLbtnDown = false;
				}

				//오른쪽 버튼 떼면, 눌렸던 체크를 다시 해제한다.
				if (bRbtnAway) {
					((CObject*)*iter)->m_bRbtnDown = false;
				}
			}
		}

		if (i == (int)GROUP_TYPE::UI - 1) {
			if (iterResult.size()==0) {
				return nullptr;
			}
		}
	}

	pFocusedObject = (CObject*)iterResult[iterResult.size()-1];

	//벡터내에서 맨 뒤로 순번 교체(렌더링을 위해서)

	return pFocusedObject;
}
