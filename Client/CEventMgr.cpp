#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "AI.h"

#include "CState.h"
#include "CUIMgr.h"

void CEventMgr::update()
{
	//===================================
	//이전 프레임에서 등록해둔 DeadObject들을 삭제
	//=====================================
	for (size_t i = 0; i < m_vecDead.size(); i++) {
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	//=========
	//Event 처리
	//========

	for (size_t i = 0; i < m_vecEvent.size(); i++) {
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Execute(const tEvent& _eve)
{
	switch (_eve.eEven) {
	case EVENT_TYPE::CREATE_OBJECT:
		//lParam : Object Address
		//wParam : GroupType
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.WParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParam : Object Address
		//wParam : 필요없음

		//Object를 Dead상태로 변경
		//삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam: NextSceneType
		// Scene 변경
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		//포커스 UI 해제(이전 Scene의 UI를 가리키고 있기 때문)
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
	break;

	case EVENT_TYPE::CHANGE_AI_STATE:
		//lParam : AI
		//wParam : Next STATE_TYPE
	{
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.WParam;

		pAI->ChangeState(eNextState);
	}


	break;
	}
}

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}
