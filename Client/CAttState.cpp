#include "pch.h"
#include "CAttState.h"

#include "CMonster.h"
#include "AI.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

void CAttState::update()
{
	CMonster* _pMon = GetMonster();

	CMonster* _pCurTarget = GetAI()->GetCurTarget();
	Vec2 vTargetPos = _pCurTarget->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vTargetPos - vMonPos;
	vMonDir.Normailize();

	if (vMonDir.x < 0.f) {
		CMonster* _pMonster = GetMonster();
		_pMonster->SetMonDir(-1);
		_pMonster->SetMonCurState(MON_STATE::ATT);
	}
	else {
		CMonster* _pMonster = GetMonster();
		_pMonster->SetMonDir(1);
		_pMonster->SetMonCurState(MON_STATE::ATT);
	}

	if (m_fTime <= m_fWaitTime) {
		m_fTime += fDT;
		return;
	}

	if (_pMon->GetTarget() == nullptr) {
		ChangeAIState(GetAI(), MON_STATE::IDLE);
		return;
	}

	if (_pMon->GetTargetCollision() == 0) {
		ChangeAIState(GetAI(), MON_STATE::TRACE);
		return;
	}
}

void CAttState::Enter()
{
}

void CAttState::Exit()
{
}

CAttState::CAttState()
	: CState(MON_STATE::ATT)
	, m_fTime(0.f)
{
}

CAttState::~CAttState()
{
}
