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
	////Player�� ��ġ üũ
	//CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	//Vec2 vPlayerPos = pPlayer->GetPos();

	////������ ���� �ȿ� ������ �������·� ��ȯ
	//CMonster* pMonster = GetMonster();
	//Vec2 vMonPos = pMonster->GetPos();

	//Vec2 vDiff = vPlayerPos - vMonPos;
	//float fLen = vDiff.Length();

	////�÷��̾ ������ �νĹ��� ������ ����
	//if (fLen < pMonster->GetInfo().fRecogRange) {
	//	ChangeAIState(GetAI(), MON_STATE::TRACE);
	//}

	//���� ������ �÷��̾ ������ ������Ʈ�� �޾ƿ�.
	CScene* _pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*> _vP1Mon = ((CScene_Test*)_pCurScene)->GetP1Mon();



	//��� ������Ʈ���� ������� ������ ���� �ȿ� ������ �������·� ��ȯ
	//�� ������Ʈ�� ������� ��.
	//�� ���Ͱ� �ı��� �� ���� ������ ����.
	CMonster* pMonster = GetMonster();

	//������ ������ ����
	//�ִϸ��̼��� ����� IDLE�� ����ϰ���
	pMonster->SetMonDir(1);
	pMonster->SetMonCurState(MON_STATE::IDLE);

	Vec2 vMonPos = pMonster->GetPos();
	for (UINT i = 0; i < _vP1Mon.size(); i++) {
		//�ش� ������Ʈ�� �÷��̾��� ��� ������Ʈ���� ������� ��
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
