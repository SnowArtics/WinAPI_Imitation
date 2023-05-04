#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CEventMgr.h"
#include "CScene_Test.h"

CSceneMgr::CSceneMgr()
	:m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i) {
		if(m_arrScene[i]!=nullptr) delete m_arrScene[i];
	}
}

void CSceneMgr::init()
{
	//씬 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start();
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	m_arrScene[(UINT)SCENE_TYPE::TEST] = new CScene_Test(3,3);
	m_arrScene[(UINT)SCENE_TYPE::TEST]->SetName(L"Test Scene");

	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;

	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TEST];

	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	
	m_pCurScene->finalupdate();

}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	//이벤트로 등록하자
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();
}
