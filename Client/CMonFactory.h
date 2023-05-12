#pragma once

class CMonster;

enum class MON_TYPE {
	NORMAL,
	WORKER,
	MELEE,
	RANGE,
	BUILDING,
};

enum class MON_NAME {
	STOREHOUSE,
	WORKER,
	FARM,
	WALL,
	GUARD,
	ARCHER,
	AXE_TRHOWER,
	HAMMERMAN,
	KNIGHT,
	HEALER,
	HORSE_ARCHER,
	WIZARD,
	NECROMANCER,
	CATAPULT,
	RED_DRAGON,
	ICE_HUNTER,
};

class CMonFactory
{
public:
	static UINT _iMonNum;

public:
	static CMonster* CreateMonster(MON_TYPE _eType, MON_NAME _eName, Vec2 _vPos);
	static CMonster* CreateAIMonster(MON_TYPE _eType, MON_NAME _eName, Vec2 _vPos);

private:
	CMonFactory(){};
	~CMonFactory() {};
};
