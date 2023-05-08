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

	//Ŭ���� �����ϰ� ������ ��� ������Ʈ���� ������� �ݺ����� ����
	for (int i = (int)GROUP_TYPE::BACKGROUND; i < (int)GROUP_TYPE::UI; i++) {
		const vector<CObject*>& vecUI = pCurScene->GetGroupObject((GROUP_TYPE)i);

		//Ŭ���� �Ǿ����� ���⼭ �˻�
		for (size_t i = 0; i < vecUI.size(); i++) {
			CObject* pObject = (CObject*)vecUI[i];
			if (pObject->IsMouseOn()) {
				pObject->MouseOn();

				//���ʹ�ư Ŭ����
				if (bLbtnTap) {
					pObject->MouseLbtnDown();
					pObject->m_bLbtnDown = true;
				}
				else if (bLbtnAway) {
					pObject->MouseLbtnUp();

					if (pObject->m_bLbtnDown) {
						pObject->MouseLbtnClicked();
					}
					//���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
					pObject->m_bLbtnDown = false;
				}

				//������ ��ư Ŭ����
				if (bRbtnTap) {
					pObject->MouseRbtnDown();
					pObject->m_bRbtnDown = true;
				}
				else if (bRbtnAway) {
					pObject->MouseRbtnUp();

					if (pObject->m_bRbtnDown) {
						pObject->MouseRbtnClicked();
					}
					//������ ��ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
					pObject->m_bRbtnDown = false;
				}
			}
			else {
				//���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
				if (bLbtnAway) {
					pObject->m_bLbtnDown = false;
				}

				//������ ��ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
				if (bRbtnAway) {
					pObject->m_bRbtnDown = false;
				}
			}



		}



	}
}
