#include "pch.h"
#include "CMonFactory.h"

#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"

#include "CGuard.h"

//몬스터를 생성해서 넣어주고 
CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, MON_NAME _eName, Vec2 _vPos)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f); 

		//AI* pAI = new AI;
		//pAI->AddState(new CIdleState);
		//pAI->AddState(new CTraceState);
		//pAI->SetCurState(MON_STATE::IDLE);

		//pMon->SetAI(pAI);
	}

		break;
	case MON_TYPE::WORKER:



		break;

	case MON_TYPE::MELEE:
	{
		//공격범위는 아직 고민중입니다.
		switch (_eName)
		{
		case MON_NAME::GUARD:
		{
			pMon = new CGuard;
			pMon->SetPos(_vPos);

			tMonInfo info = {};
			info.fSpeed = 100.f;
			info.fHP = 280.f;
			info.fRecogRange = 1.f;
			info.fAttRange = 10.f;
			info.fAtt = 10.f;
			info.fAttSpeed = 0.6f;
			info.fDefensive = 0.f;

			pMon->SetMonInfo(info);

			//모든 오브젝트는 충돌체와 애니메이터와 강체를 들고있음.
			//세부조정은 몬스터마다 다르니 몬스터의 코드에서 조절해 주기.

			pMon->CreateRigidBody();
			pMon->GetRigidBody()->SetMass(1.f);
		}

			break;
		case MON_NAME::HAMMERMAN:
			break;
		case MON_NAME::KNIGHT:
			break;
		case MON_NAME::RED_DRAGON:
			break;
		default:
			assert(true);
		}
	}


		break;

	case MON_TYPE::RANGE:



		break;

	case MON_TYPE::BUILDING:



		break;
	}

	assert(pMon);

	return pMon;
}
