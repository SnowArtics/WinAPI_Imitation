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
	////Ÿ���õ� �÷��̾ �Ѿư���.
	//CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	//Vec2 vPlayerPos = pPlayer->GetPos();

	//Vec2 vMonPos = GetMonster()->GetPos();

	//Vec2 vMonDir = vPlayerPos - vMonPos;
	//vMonDir.Normailize();

	//vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	//GetMonster()->SetPos(vMonPos);

	////Ÿ���õ� ���͸� �Ѿư���.
	if (GetAI()->GetCurTarget() == nullptr)
		return;

	//���� ���Ͱ� ���� ���Ϳ� �浹�ϴ� ���̶��,
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
