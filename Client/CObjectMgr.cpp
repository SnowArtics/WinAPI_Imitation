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

	//클릭이 가능하게 설정한 모든 오브젝트들을 대상으로 반복문을 돌림
	for (int i = (int)GROUP_TYPE::BACKGROUND; i < (int)GROUP_TYPE::UI; i++) {
		const vector<CObject*>& vecUI = pCurScene->GetGroupObject((GROUP_TYPE)i);

		//클릭이 되었는지 여기서 검사
		for (size_t i = 0; i < vecUI.size(); i++) {
			CObject* pObject = (CObject*)vecUI[i];
			if (pObject->IsMouseOn()) {
				pObject->MouseOn();

				//왼쪽버튼 클릭시
				if (bLbtnTap) {
					pObject->MouseLbtnDown();
					pObject->m_bLbtnDown = true;
				}
				else if (bLbtnAway) {
					pObject->MouseLbtnUp();

					if (pObject->m_bLbtnDown) {
						pObject->MouseLbtnClicked();
					}
					//왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
					pObject->m_bLbtnDown = false;
				}

				//오른쪽 버튼 클릭시
				if (bRbtnTap) {
					pObject->MouseRbtnDown();
					pObject->m_bRbtnDown = true;
				}
				else if (bRbtnAway) {
					pObject->MouseRbtnUp();

					if (pObject->m_bRbtnDown) {
						pObject->MouseRbtnClicked();
					}
					//오른쪽 버튼 떼면, 눌렸던 체크를 다시 해제한다.
					pObject->m_bRbtnDown = false;
				}
			}
			else {
				//왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
				if (bLbtnAway) {
					pObject->m_bLbtnDown = false;
				}

				//오른쪽 버튼 떼면, 눌렸던 체크를 다시 해제한다.
				if (bRbtnAway) {
					pObject->m_bRbtnDown = false;
				}
			}



		}



	}
}
