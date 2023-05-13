#include "pch.h"
#include "CMonster.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"

#include "AI.h"

#include "SelectGDI.h"

#include "CSceneMgr.h"
#include "CScene_Test.h"

#include "CRigidBody.h"

#include "CState.h"
#include "CAttState.h"

#include "CAnimator.h"
#include "CAnimation.h"

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::start()
{

}

void CMonster::update()
{
	m_tInfo.fTime += fDT;

	if (m_tInfo.fTime >= 100000.f)
		m_tInfo.fTime = 0.f;

	if (m_tInfo.fHP <= 0.f) {
		DeleteObject((CObject*)this);
	}

	if (nullptr != m_pAI)
		m_pAI->update();


	if (m_pAI == nullptr) {
		srand(time(nullptr));		

		if (KEY_TAP(KEY::LBTN)) m_bClicked = false;

		m_ePrevState = m_eCurState;
		m_iPrevDir = m_iDir;

		update_move();
		update_state();
		//update_animation()�� �ڽ� ���͵��� ����
	}

}

void CMonster::OnCollision(CCollider* _pOther)
{
	//AI������Ʈ�� �浹���̸�
	if (m_pAI != nullptr) {
		CObject* pOtherObj = _pOther->GetObj();

		if (m_vTarget!=nullptr&&pOtherObj->GetName() == m_vTarget->GetName()) {
			Vec2 vOtherObjPos = pOtherObj->GetPos();
			Vec2 vObjPos = GetPos();

			Vec2 vDir = vOtherObjPos - vObjPos;
			vDir.Normailize();

			if (m_tInfo.fTime >= m_tInfo.fAttSpeed) {
				((CMonster*)pOtherObj)->DecreaseMonHP(m_tInfo.fAtt);

				//��ǥ ����� ��ħ
				CRigidBody* pRigid = ((CMonster*)pOtherObj)->GetRigidBody();
				pRigid->SetVelocity(vDir * m_tInfo.fStiffness);
				if (((CMonster*)pOtherObj)->GetMonHP() <= 0.f) {
					m_vTarget = nullptr;
				}
				m_tInfo.fTime = 0.f;
			}
		}
	}
	else {//�÷��̾��� ������Ʈ�� �浹���̸�
		CObject* pOtherObj = _pOther->GetObj();
		if (m_vTarget != nullptr && pOtherObj->GetName() == m_vTarget->GetName()) {
			if (m_tInfo.fTime >= m_tInfo.fAttSpeed) {
				((CMonster*)pOtherObj)->DecreaseMonHP(m_tInfo.fAtt);
				if (((CMonster*)pOtherObj)->GetMonHP() <= 0.f) {
					m_vTarget = nullptr;
				}
				m_tInfo.fTime = 0.f;
			}
		}
	}

}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	/*CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player") {

	}*/

	//AI������Ʈ�� �浹���̸�
	if (m_pAI != nullptr) {
		CObject* pOtherObj = _pOther->GetObj();

		if (m_vTarget != nullptr && pOtherObj->GetName() == m_vTarget->GetName()) {
			m_iTargetCollision = 1;
		}
	}
	else {//�÷��̾��� ������Ʈ�� �浹���̸�
		CObject* pOtherObj = _pOther->GetObj();
		if (m_vTarget != nullptr && pOtherObj->GetName() == m_vTarget->GetName()) {
			m_iTargetCollision = 1;
		}
	}

}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
	//AI������Ʈ�� �浹���̸�
	if (m_pAI != nullptr) {
		CObject* pOtherObj = _pOther->GetObj();

		if (m_vTarget != nullptr && pOtherObj->GetName() == m_vTarget->GetName()) {
			//ATT_STATE�� ������ �����ϰ� ��.
			UINT iMaxFrm = GetAnimator()->GetCurAnim()->GetMaxFrame();
			int iCurFrm = GetAnimator()->GetCurAnim()->GetCurFrm();
			CAttState* curState = (CAttState*)m_pAI->GetCurState();

			float fWaitTime = (float)(iMaxFrm - 1 - iCurFrm);
			fWaitTime *= 0.2;

			curState->SetWaitTime(fWaitTime);
			curState->SetTime(0.f);

			m_iTargetCollision = 0;
		}
	}
	else {//�÷��̾��� ������Ʈ�� �浹���̸�
		CObject* pOtherObj = _pOther->GetObj();

		if (m_vTarget != nullptr && pOtherObj->GetName() == m_vTarget->GetName()) {

			m_iTargetCollision = 0;
		}
	}
}

void CMonster::render(HDC _dc)
{
	component_render(_dc);

	if (m_pAI == nullptr) {
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

		if (m_bClicked) {
			SelectGDI select1(_dc, PEN_TYPE::GREEN);
			SelectGDI select2(_dc, BRUSH_TYPE::HOLLOW);

			Ellipse(_dc,
				(int)(vRenderPos.x),
				(int)(vRenderPos.y + vScale.x * 0.8f + 20.f),
				(int)(vRenderPos.x + vScale.x),
				(int)(vRenderPos.y + vScale.y + 20.f));
		}
	}
}

void CMonster::update_state()
{
	if(m_vTarget!=nullptr)
		m_vTargetPosition = m_vTarget->GetPos();

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vTargetPos = CCamera::GetInst()->GetRenderPos(m_vTargetPosition);
	//Vec2 vTargetPos = m_vTargetPosition;

	if (abs(vTargetPos.x - vPos.x) < 0.1f && abs(vTargetPos.y - vPos.y) < 0.1f
		&& abs(vTargetPos.x - vPos.x) != 0.f && abs(vTargetPos.y - vPos.y) != 0.f) {
		vTargetPos = vPos;
	}

	//��ǥ ������Ʈ�� �浹���̶��
	if (m_iTargetCollision == 1) {
		if (vTargetPos.x > vPos.x) {
			m_iDir = 1;
			m_eCurState = MON_STATE::ATT;
		}
		else if (vTargetPos.x < vPos.x) {
			m_iDir = -1;
			m_eCurState = MON_STATE::ATT;
		}
		else {
			m_eCurState = MON_STATE::ATT;
		}
	}
	else if (m_vTarget != nullptr) {//��ǥ������Ʈ�� �ִµ� �浹���� �ƴ϶��
		if (vTargetPos.x > vPos.x) {
			m_iDir = 1;
			m_eCurState = MON_STATE::TRACE;
		}
		else if (vTargetPos.x < vPos.x) {
			m_iDir = -1;
			m_eCurState = MON_STATE::TRACE;
		}
		else {
			m_eCurState = MON_STATE::TRACE;
		}
	}
	else {//�ƴ϶��
		//�׳� �̵��ؾ��ϴ� ��ġ�� ���� ����, WALK���·� ��ȯ
		if (vTargetPos.x > vPos.x) {
			m_iDir = 1;
			m_eCurState = MON_STATE::WALK;
		}
		else if (vTargetPos.x < vPos.x) {
			m_iDir = -1;
			m_eCurState = MON_STATE::WALK;
		}
		else if (vTargetPos.y != vPos.y) {
			m_eCurState = MON_STATE::WALK;
		}
		else {
			m_eCurState = MON_STATE::IDLE;
		}
	}


}

void CMonster::update_move()
{
	if (m_vTarget != nullptr)
		m_vTargetPosition = m_vTarget->GetPos();

	CRigidBody* pRigid = GetRigidBody();

	float randomNumber = rand() % 30;

	//Vec2 vPos = GetPos();
	//Vec2 vTargetPos = m_vTargetPosition;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vTargetPos = CCamera::GetInst()->GetRenderPos(m_vTargetPosition);

	////IDLE������ �� �̵��ϰԲ� ��
	//if (m_ePrevState == MON_STATE::IDLE && m_eCurState == MON_STATE::IDLE) {		
	//	if(m_iDir==-1)
	//		m_vTargetPosition = Vec2(vPos.x + randomNumber, vPos.y + randomNumber);
	//	if(m_iDir == 1)
	//		m_vTargetPosition = Vec2(vPos.x - randomNumber, vPos.y - randomNumber);
	//}

	//��ǥ��ġ�� ������ �� ���� ��� �̵���
	if (m_eCurState == MON_STATE::WALK) {
		Vec2 vMovePos = vTargetPos - vPos;
		vMovePos.Normailize();

		vPos.x += m_tInfo.fSpeed * vMovePos.x * fDT;
		vPos.y += m_tInfo.fSpeed * vMovePos.y * fDT;
		
		vPos = CCamera::GetInst()->GetRealPos(vPos);

		SetPos(vPos);
	}
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
	if (m_pAI == nullptr) {
		m_bClicked = true;
	}
}

void CMonster::MouseRbtnDown()
{
	vector<CObject*> p1Mon = ((CScene_Test*)CSceneMgr::GetInst()->GetCurScene())->GetP1Mon();
	for (int i = 0; i < p1Mon.size(); i++) {
		if (((CMonster*)p1Mon[i])->GetClicked()) {
			((CMonster*)p1Mon[i])->SetTarget(this);
		}
	}
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
	, m_vTarget(nullptr)
	, m_iTargetCollision(0)
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
	if (nullptr == m_pAI) {
		CScene_Test* _pCurScene = (CScene_Test*)CSceneMgr::GetInst()->GetCurScene();
		vector<CObject*> _vP1Mon = _pCurScene->GetP1Mon();
		auto index = std::find(_vP1Mon.begin(), _vP1Mon.end(), this);

		if (index == _vP1Mon.end())
			assert(true);
		auto iter = _vP1Mon.erase(index);
	}
}
