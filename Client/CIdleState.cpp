#include "pch.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CScene_Test.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "AI.h"

void CIdleState::update()
{
	////Player의 위치 체크
	//CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	//Vec2 vPlayerPos = pPlayer->GetPos();

	////몬스터의 범위 안에 들어오면 추적상태로 전환
	//CMonster* pMonster = GetMonster();
	//Vec2 vMonPos = pMonster->GetPos();

	//Vec2 vDiff = vPlayerPos - vMonPos;
	//float fLen = vDiff.Length();

	////플레이어가 몬스터의 인식범위 안으로 진입
	//if (fLen < pMonster->GetInfo().fRecogRange) {
	//	ChangeAIState(GetAI(), MON_STATE::TRACE);
	//}

	//현재 씬에서 플레이어가 소유한 오브젝트를 받아옴.
	CScene* _pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*> _vP1Mon = ((CScene_Test*)_pCurScene)->GetP1Mon();



	//모든 오브젝트들을 대상으로 몬스터의 범위 안에 들어오면 추적상태로 전환
	//한 오브젝트만 대상으로 함.
	//이 몬스터가 파괴될 때 까지 끝까지 따라감.
	CMonster* pMonster = GetMonster();

	//몬스터의 방향은 왼쪽
	//애니메이션의 출력은 IDLE을 출력하게함
	pMonster->SetMonDir(1);
	pMonster->SetMonCurState(MON_STATE::IDLE);

	Vec2 vMonPos = pMonster->GetPos();
	for (UINT i = 0; i < _vP1Mon.size(); i++) {
		//해당 오브젝트와 플레이어의 모든 오브젝트들을 대상으로 함
		Vec2 vDiff = _vP1Mon[i]->GetPos() - vMonPos;
		float fLen = vDiff.Length();

		if (fLen < pMonster->GetInfo().fRecogRange) {
			ChangeAIState(GetAI(), MON_STATE::TRACE);
			GetAI()->SetCurTarget((CMonster*)_vP1Mon[i]);
			break;
		}
	}

}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}

CIdleState::CIdleState()
	:CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}
