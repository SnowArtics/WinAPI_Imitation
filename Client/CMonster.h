#pragma once
#include "CObject.h"

struct tMonInfo
{
    float      fSpeed;           // �ӵ�
    float      fHP;              // ü��
    float      fRecogRange;      // ���� ����
    float      fAttRange;        // ���� ����
    float      fAtt;             // ���ݷ�
    float      fAttSpeed;       //���ݼӵ�
    float      fTime;           //����ӵ�
    float      fDefensive;       //����
    float      fStiffness;        //������ �ִ� ������(��)
};

class AI;

class CMonster :
    public CObject
{
private:
    tMonInfo            m_tInfo;
    AI*                 m_pAI;

    MON_STATE           m_eCurState;//������ ���� ����
    MON_STATE           m_ePrevState;//������ ���� ����

    Vec2                m_vTargetPosition;//���Ͱ� �̵��ؾ��ϴ� ��ġ
    CMonster*           m_vTarget;        //���Ͱ� Ÿ������ ���� ����
    int                 m_iTargetCollision;//���Ͱ� Ÿ������ ���� ���Ϳ� �浹������ 1, �ƴϸ� 0
    int                 m_iDir;//���Ͱ� �ٶ󺸴� ���� ����
    int                 m_iPrevDir;//���Ͱ� �ٶ󺸴� ���� ����

    bool                m_bClicked;//���� ���Ͱ� Ŭ���� �Ǿ�����.
    UINT                m_iType;//0�̸� �ٰŸ�, 1�̸� ���Ÿ�, 2�̸� �ǹ�, -1�̸� worker

    float               m_fWaitTime;//ATT_STATE�� ������ �������ֱ� ���� �ð�

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }

    float GetMonHP() { return m_tInfo.fHP; }
    float GetTime() { return m_tInfo.fTime; }
    float GetAttSpeed() { return m_tInfo.fSpeed; }

    void DecreaseMonHP(float _f) { m_tInfo.fHP -= _f; }

public:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }
    void SetMonCurState(MON_STATE _e) { m_eCurState = _e; }
    void SetMonPrevState(MON_STATE _e) { m_ePrevState = _e; }
    void SetTargetPosition(Vec2 _v) { m_vTargetPosition = _v; }
    void SetTarget(CMonster* _pMon) { m_vTarget = _pMon; }
    void SetTargetCollision(int _i) { m_iTargetCollision = _i; }
    void SetMonDir(int _i) { m_iDir = _i; }
    void SetMonPrevDir(int _i) { m_iPrevDir = _i; }

    MON_STATE GetMonCurState() { return m_eCurState; }
    MON_STATE GetMonPrevState() { return m_ePrevState; }
    Vec2 GetTargetPosition() { return m_vTargetPosition; }
    CMonster* GetTarget() { return m_vTarget; }
    int GetTargetCollision() { return m_iTargetCollision; }
    int GetMonDir() { return m_iDir; }
    int GetMonPrevDir() { return m_iPrevDir; }
    bool GetClicked() { return m_bClicked; }

public:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    //�����͵��� ���ϴ� �ൿ�� ����ѵ�
    //�ִϸ��̼� ������Ʈ�� ���͸��� �޶� ���� �������.
    virtual void update_state();
    virtual void update_move();
    virtual void update_animation();
    virtual void update_gravity();

public:
    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual void MouseRbtnDown();
    virtual void MouseRbtnUp();
    virtual void MouseRbtnClicked();

    CLONE(CMonster);

    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

public:
    CMonster();
    virtual ~CMonster();

    friend class CMonFactory;
};

