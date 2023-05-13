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
    float      fTime;           //현재속도
    float      fDefensive;       //방어력
    float      fStiffness;        //적에게 주는 경직도(힘)
};

class AI;

class CMonster :
    public CObject
{
private:
    tMonInfo            m_tInfo;
    AI*                 m_pAI;

    MON_STATE           m_eCurState;//몬스터의 현재 상태
    MON_STATE           m_ePrevState;//몬스터의 이전 상태

    Vec2                m_vTargetPosition;//몬스터가 이동해야하는 위치
    CMonster*           m_vTarget;        //몬스터가 타겟팅한 적대 몬스터
    int                 m_iTargetCollision;//몬스터가 타겟팅한 적대 몬스터와 충돌했으면 1, 아니면 0
    int                 m_iDir;//몬스터가 바라보는 현재 방향
    int                 m_iPrevDir;//몬스터가 바라보는 이전 방향

    bool                m_bClicked;//현재 몬스터가 클릭이 되었는지.
    UINT                m_iType;//0이면 근거리, 1이면 원거리, 2이면 건물, -1이면 worker

    float               m_fWaitTime;//ATT_STATE를 강제로 유지해주기 위한 시간

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

    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

public:
    CMonster();
    virtual ~CMonster();

    friend class CMonFactory;
};

