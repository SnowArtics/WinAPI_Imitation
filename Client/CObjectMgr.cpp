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

			//���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
			m_pFocusedObject->m_bLbtnDown = false;
		}

		//������ ���콺 üũ
		if (bRbtnTap) {
			m_pFocusedObject->MouseRbtnDown();
			m_pFocusedObject->m_bRbtnDown = true;
		}
		else if (bRbtnAway) {
			m_pFocusedObject->MouseRbtnUp();

			if (m_pFocusedObject->m_bRbtnDown) {
				m_pFocusedObject->MouseRbtnClicked();
			}

			//���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
			m_pFocusedObject->m_bRbtnDown = false;
		}
	}




	////Ŭ���� �����ϰ� ������ ��� ������Ʈ���� ������� �ݺ����� ����
	//for (int i = (int)GROUP_TYPE::BACKGROUND; i < (int)GROUP_TYPE::UI; i++) {
	//	const vector<CObject*>& vecUI = pCurScene->GetGroupObject((GROUP_TYPE)i);

	//	//Ŭ���� �Ǿ����� ���⼭ �˻�
	//	for (size_t i = 0; i < vecUI.size(); i++) {
	//		CObject* pObject = (CObject*)vecUI[i];
	//		if (pObject->IsMouseOn()) {
	//			pObject->MouseOn();

	//			//���ʹ�ư Ŭ����
	//			if (bLbtnTap) {
	//				pObject->MouseLbtnDown();
	//				pObject->m_bLbtnDown = true;
	//			}
	//			else if (bLbtnAway) {
	//				pObject->MouseLbtnUp();

	//				if (pObject->m_bLbtnDown) {
	//					pObject->MouseLbtnClicked();
	//				}
	//				//���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
	//				pObject->m_bLbtnDown = false;
	//			}

	//			//������ ��ư Ŭ����
	//			if (bRbtnTap) {
	//				pObject->MouseRbtnDown();
	//				pObject->m_bRbtnDown = true;
	//			}
	//			else if (bRbtnAway) {
	//				pObject->MouseRbtnUp();

	//				if (pObject->m_bRbtnDown) {
	//					pObject->MouseRbtnClicked();
	//				}
	//				//������ ��ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
	//				pObject->m_bRbtnDown = false;
	//			}
	//		}
	//		else {
	//			//���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
	//			if (bLbtnAway) {
	//				pObject->m_bLbtnDown = false;
	//			}

	//			//������ ��ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
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

	// ���� ��Ŀ�� ������Ʈ�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CObject* pFocusedObject = m_pFocusedObject;

	//���ʹ�ư Tap�� �߻��ߴٴ� ����
	//���ʹ�ư Tap�� �߻��ؾ� ��Ŀ���� �ٲ�.
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
				//���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
				if (bLbtnAway) {
					((CObject*)*iter)->m_bLbtnDown = false;
				}

				//������ ��ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
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

	//���ͳ����� �� �ڷ� ���� ��ü(�������� ���ؼ�)

	return pFocusedObject;
}
