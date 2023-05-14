#include "pch.h"
#include "CGuard.h"

//여기 밑으로는 모든 몬스터들이 들고 있어야 할 헤더
#include "CMonster.h"
#include "CCollider.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CAnimation.h"
#include "CRigidBody.h"


void CGuard::update()
{
	MouseOnCheck();
	CMonster::update();
}

void CGuard::render(HDC _dc)
{
	update_animation();

	CMonster::render(_dc);
	
	ViewScale(_dc);
}

void CGuard::update_animation()
{	
	MON_STATE state = GetMonCurState();
	//if (GetMonCurState() == GetMonPrevState() && GetMonDir() == GetMonPrevDir()) {
	//	return;
	//}

	MON_STATE eCurState = GetMonCurState();
	int iDir = GetMonDir();

	switch (eCurState)
	{
	case MON_STATE::IDLE:
		if (iDir == -1)
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		else
			GetAnimator()->Play(L"IDLE_LEFT", true);
		break;
	case MON_STATE::WALK:
		if (iDir == -1)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else
			GetAnimator()->Play(L"WALK_LEFT", true);
		break;
	case MON_STATE::TRACE:
		if (iDir == -1)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else
			GetAnimator()->Play(L"WALK_LEFT", true);
		break;
	case MON_STATE::ATT:
		if (iDir == -1)
			GetAnimator()->Play(L"ATT_RIGHT", true);
		else
			GetAnimator()->Play(L"ATT_LEFT", true);
		break;
	case MON_STATE::TARGET_ATT:
		if (iDir == -1)
			GetAnimator()->Play(L"ATT_RIGHT", true);
		else
			GetAnimator()->Play(L"ATT_LEFT", true);
		break;
	case MON_STATE::DEAD:
		assert(true);
		break;
	}
}

CGuard::CGuard()
{
	//여기 밑으로는 모든 몬스터들이 생성시 구현해야 할 것들

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(40.f, 80.f));
	GetCollider()->SetScale(Vec2(90.0f, 80.f));

	CreateRigidBody();
	GetRigidBody()->SetMass(1.f);

	SetScale(Vec2(90.f, 120.f));

	CreateAnimator();

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"GuardAnimation", L"texture\\guard_animation.png");

	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0.f, 0.f), Vec2(216.f, 216.f), Vec2(216.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 216.f), Vec2(216.f, 216.f), Vec2(216.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"ATT_LEFT", pTex, Vec2(0.f, 432.f), Vec2(216.f, 216.f), Vec2(216.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"ATT_RIGHT", pTex, Vec2(0.f, 648.f), Vec2(216.f, 216.f), Vec2(216.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 864.f), Vec2(216.f, 216.f), Vec2(216.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 1080.f), Vec2(216.f, 216.f), Vec2(216.f, 0.f), 0.2f, 8);

	//애니메이션이 실제 물체의 위치보다 조금 더 우측 하단에 그려지게 함
	CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE_LEFT");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++) {
		pAnim->GetFrame(i).vOffset = Vec2(40.f,20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"IDLE_RIGHT");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++) {
		pAnim->GetFrame(i).vOffset = Vec2(40.f, 20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"WALK_LEFT");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++) {
		pAnim->GetFrame(i).vOffset = Vec2(40.f, 20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"WALK_RIGHT");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++) {
		pAnim->GetFrame(i).vOffset = Vec2(40.f, 20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"ATT_LEFT");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++) {
		pAnim->GetFrame(i).vOffset = Vec2(40.f, 20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"ATT_RIGHT");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++) {
		pAnim->GetFrame(i).vOffset = Vec2(40.f, 20.f);
	}

	GetAnimator()->Play(L"IDLE_LEFT", true);
}

CGuard::~CGuard()
{
}
