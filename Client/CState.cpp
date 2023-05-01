#include "pch.h"
#include "CState.h"

#include "CMonster.h"
#include "AI.h"

CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}

CState::CState(MON_STATE _eState)
	: m_eState(_eState)
{
}

CState::~CState()
{
}
