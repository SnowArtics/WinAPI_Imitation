#pragma once
#include "CObject.h"

struct tMonInfo
{
    float      fSpeed;           // �ӵ�
    float      fHP;              // ü��
    float      fRecogRange;      // ���� ����
    float      fAttRange;        // ���� ����
    float      fAtt;             // ���ݷ�
};

class AI;

class CMonster :
    public CObject
{
private:
    tMonInfo    m_tInfo;
    AI* m_pAI;

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }

private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }


public:
    virtual void update();/*
    virtual void render(HDC _dc);*/

    CLONE(CMonster);

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};

