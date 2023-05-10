#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CGravity.h"
#include "CGravity.h"

void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();



	if (KEY_TAP(KEY::ENTER)){
		SetPos(Vec2(960.f, 340.f));
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	//int iWidth = (int)m_pTex->Width();
	//int iHeight = (int)m_pTex->Height();

	//Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)(iWidth / 2))
	//	, (int)(vPos.y - (float)(iHeight / 2))
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)(iWidth / 2))
	//	, (int)(vPos.y - (float)(iHeight / 2))
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255,0,255));

	//컴포넌트(충돌체, etc...) 가 있는 경우 렌더
	component_render(_dc);

	//밑은 알파블렌드 테스트용 코드
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"FighterTex", L"texture\\Fighter.bmp");

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);

	//float width = (float)pTex->Width();
	//float height = (float)pTex->Height();

	//BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 127;

	//AlphaBlend(_dc
	//	, int(vPos.x - width / 2.f)
	//	, int(vPos.y - height / 2.f)
	//	, int(width), int(height)
	//	, pTex->GetDC()
	//	,0 ,0
	//	, int(width), int(height)
	//	, bf);

}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;

	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(-0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::update_state()
{
	if (KEY_HOLD(KEY::A)) {
		m_iDir = -1;
		if (PLAYER_STATE::JUMP != m_eCurState) {
			m_eCurState = PLAYER_STATE::WALK;
		}
	}
	if (KEY_HOLD(KEY::D)) {
		m_iDir = 1;
		if (PLAYER_STATE::JUMP != m_eCurState) {
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState) {
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP) {
		m_eCurState = PLAYER_STATE::JUMP;

		if (GetRigidBody()) {
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
		}
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A)) {
		pRigid->AddForce(Vec2(-200.f, 0.f));
		//m_eCurState = PLAYER_STATE::WALK;
		if (PLAYER_STATE::JUMP != m_eCurState) {
			m_eCurState = PLAYER_STATE::WALK;
		}
	}
	if (KEY_HOLD(KEY::D)) {
		pRigid->AddForce(Vec2(200.f, 0.f));
		//m_eCurState = PLAYER_STATE::WALK;
		if (PLAYER_STATE::JUMP != m_eCurState) {
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_TAP(KEY::A)) {
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}
	if (KEY_TAP(KEY::D)) {
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir) {
		return;
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if(m_iDir == 1)
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		else
			GetAnimator()->Play(L"IDLE_LEFT", true);
	}
		break;
	case PLAYER_STATE::WALK:
		if (m_iDir == 1)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else
			GetAnimator()->Play(L"WALK_LEFT", true);
		break;
	case PLAYER_STATE::JUMP:
		if (m_iDir == 1)
			GetAnimator()->Play(L"JUMP_RIGHT", true);
		else
			GetAnimator()->Play(L"JUMP_LEFT", true);

		break;

	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	}
}

void CPlayer::update_gravity()
{
	//GetRigidBody()->AddForce(Vec2(0.f,500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == _pOther->GetObj()->GetName()) {
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y) {
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
	//:m_pTex(nullptr)
{
	//Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\industrial_zone.bmp");
	CreateCollider();
	
	GetCollider()->SetOffsetPos(Vec2(0.f, 30.f));
	GetCollider()->SetScale(Vec2(40.0f,40.f));

	CreateRigidBody();

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeft", L"texture\\link_0.bmp");

	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_right.anim");

	/*GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0.f, 130.f), Vec2(120.f, 130.f), Vec2(120.0f, 0.0f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(120.0f, 0.0f), 0.2f, 3);

	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 650.f), Vec2(120.f, 130.f), Vec2(120.0f, 0.0f), 0.2f, 10);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 910.f), Vec2(120.f, 130.f), Vec2(120.0f, 0.0f), 0.2f, 10);

	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pTex, Vec2(0.f, 780.f), Vec2(120.f, 130.f), Vec2(120.0f, 0.0f), 0.2f, 10);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(120.0f, 0.0f), 0.2f, 10);*/

	//애니메이션이 실제 물체의 위치보다 조금 더 위에 그려지게 함
	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE_LEFT");
	//for (UINT i = 0; i < pAnim->GetMaxFrame(); i++) {
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f,-20.f);
	//}

	CreateGravity();

	//애니메이션 저장해보기
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");
	//GetAnimator()->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\player_jump_left.anim");
	//GetAnimator()->FindAnimation(L"JUMP_RIGHT")->Save(L"animation\\player_jump_right.anim");
}

CPlayer::CPlayer(const CPlayer& _origin)
	: CObject(_origin)
	, m_ePrevState(PLAYER_STATE::IDLE)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_iDir(1)
	, m_iPrevDir(1)
	//, m_pTex(_origin.m_pTex)
{
}

CPlayer::~CPlayer()
{
}
