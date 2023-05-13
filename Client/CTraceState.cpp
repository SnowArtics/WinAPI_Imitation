#include "pch.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

#include "AI.h"

void CTraceState::update()
{
	////타겟팅된 플레이어를 쫓아간다.
	//CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	//Vec2 vPlayerPos = pPlayer->GetPos();

	//Vec2 vMonPos = GetMonster()->GetPos();

	//Vec2 vMonDir = vPlayerPos - vMonPos;
	//vMonDir.Normailize();

	//vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	//GetMonster()->SetPos(vMonPos);

	////타겟팅된 몬스터를 쫓아간다.
	if (GetAI()->GetCurTarget() == nullptr)
		return;

	//현재 몬스터가 적대 몬스터와 충돌하는 중이라면,
	if (GetMonster()->GetTargetCollision() == 1) {
		ChangeAIState(GetAI(), MON_STATE::ATT);
		return;
	}

	CMonster* _pCurTarget = GetAI()->GetCurTarget();
	Vec2 vTargetPos = _pCurTarget->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vTargetPos - vMonPos;
	vMonDir.Normailize();

	if (vMonDir.x < 0.f) {
		CMonster* _pMonster = GetMonster();
		_pMonster->SetMonDir(-1);
		_pMonster->SetMonCurState(MON_STATE::TRACE);
	}
	else {
		CMonster* _pMonster = GetMonster();
		_pMonster->SetMonDir(1);
		_pMonster->SetMonCurState(MON_STATE::TRACE);
	}

	vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);
	GetMonster()->SetTarget(_pCurTarget);
	
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)

{
}

CTraceState::~CTraceState()
{
}
