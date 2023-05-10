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
    float      fDefensive;       //����
};

class AI;

class CMonster :
    public CObject
{
private:
    tMonInfo            m_tInfo;
    AI*                 m_pAI;

    MON_STATE       m_eCurState;//������ ���� ����
    MON_STATE       m_ePrevState;//������ ���� ����

    Vec2                m_vTargetPosition;
    int                 m_iDir;//���Ͱ� �ٶ󺸴� ���� ����
    int                 m_iPrevDir;//���Ͱ� �ٶ󺸴� ���� ����

    bool                m_bClicked;//���� ���Ͱ� Ŭ���� �Ǿ�����.

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }

public:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }
    void SetMonCurState(MON_STATE _e) { m_eCurState = _e; }
    void SetMonPrevState(MON_STATE _e) { m_ePrevState = _e; }
    void SetTargetPosition(Vec2 _v) { m_vTargetPosition; }
    void SetMonDir(int _i) { m_iDir = _i; }
    void SetMonPrevDir(int _i) { m_iPrevDir = _i; }

    MON_STATE GetMonCurState() { return m_eCurState; }
    MON_STATE GetMonPrevState() { return m_ePrevState; }
    Vec2 GetTargetPosition() { return m_vTargetPosition; }
    int GetMonDir() { return m_iDir; }
    int GetMonPrevDir() { return m_iPrevDir; }

public:
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

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMonster();
    virtual ~CMonster();

    friend class CMonFactory;
};

