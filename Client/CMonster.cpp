#include "pch.h"
#include "CMonster.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"

#include "AI.h"

#include "SelectGDI.h"

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::update()
{
	if(nullptr!=m_pAI)
		m_pAI->update();

	if (KEY_TAP(KEY::LBTN) || KEY_TAP(KEY::RBTN)) m_bClicked = false;

	update_move();
	update_state();
	//update_animation()는 자식 몬스터들이 해줌
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	/*CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player") {

	}*/
}

void CMonster::render(HDC _dc)
{
	component_render(_dc);

	Vec2 vPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	if (m_bClicked) {
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc,
			(int)(vRenderPos.x - 20.f),
			(int)(vRenderPos.y - 20.f),
			(int)(vRenderPos.x + 20.f),
			(int)(vRenderPos.y + 20.f));
	}
}

void CMonster::update_state()
{
}

void CMonster::update_move()
{
}

void CMonster::update_animation()
{
}

void CMonster::update_gravity()
{
}

void CMonster::MouseOn()
{
}

void CMonster::MouseLbtnDown()
{
}

void CMonster::MouseLbtnUp()
{
}

void CMonster::MouseLbtnClicked()
{
	m_bClicked = true;
}

void CMonster::MouseRbtnDown()
{
}

void CMonster::MouseRbtnUp()
{
}

void CMonster::MouseRbtnClicked()
{
}

CMonster::CMonster()
	: m_tInfo{}
	, m_pAI(nullptr)
	, m_eCurState(MON_STATE::IDLE)
	, m_ePrevState(MON_STATE::IDLE)
	, m_vTargetPosition(Vec2(0.f,0.f))
	, m_iDir(1)
	, m_iPrevDir(1)
	, m_bClicked(false)
{
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI) {
		delete m_pAI;
	}
}
