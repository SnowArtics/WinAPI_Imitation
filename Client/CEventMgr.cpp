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
	//���� �����ӿ��� ����ص� DeadObject���� ����
	//=====================================
	for (size_t i = 0; i < m_vecDead.size(); i++) {
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	//=========
	//Event ó��
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
		//wParam : �ʿ����

		//Object�� Dead���·� ����
		//�������� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam: NextSceneType
		// Scene ����
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		//��Ŀ�� UI ����(���� Scene�� UI�� ����Ű�� �ֱ� ����)
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
