#pragma once
#include "CObject.h"

struct tMonInfo
{
    float      fSpeed;           // 속도
    float      fHP;              // 체력
    float      fRecogRange;      // 인지 범위
    float      fAttRange;        // 공격 범위
    float      fAtt;             // 공격력
    float      fAttSpeed;       //공격속도
    float      fDefensive;       //방어력
};

class AI;

class CMonster :
    public CObject
{
private:
    tMonInfo            m_tInfo;
    AI*                 m_pAI;

    MON_STATE       m_eCurState;//몬스터의 현재 상태
    MON_STATE       m_ePrevState;//몬스터의 이전 상태

    Vec2                m_vTargetPosition;
    int                 m_iDir;//몬스터가 바라보는 현재 방향
    int                 m_iPrevDir;//몬스터가 바라보는 이전 방향

    bool                m_bClicked;//현재 몬스터가 클릭이 되었는지.

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
    //모든몬스터들이 행하는 행동은 비슷한데
    //애니메이션 업데이트는 몬스터마다 달라서 따로 해줘야함.
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

