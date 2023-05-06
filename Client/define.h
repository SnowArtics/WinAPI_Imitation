#pragma once

/*****************
|SINGLETON 매크로|
*****************/
#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
					private:\
						type();\
						~type();\

#define DT CTimeMgr::GetInst()->GetDT();
#define fDT CTimeMgr::GetInst()->GetfDT();

#define CLONE(type) type* Clone() {return new type(*this);}


#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key)==state
#define	KEY_HOLD(key) KEY_CHECK(key,KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key,KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key,KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key,KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f

#define TILE_SIZE 64

enum class GROUP_TYPE {//렌더링 기준이고 충돌 기준임

	DEFAULT,
	BACKGROUND,
	BRIDGE,
	TILE,
	GROUND,
	MONSTER,
	PLAYER,
	PROJ_PLAYER,
	PROJ_MONSTER,

	P1_MELEE_CREATURE,
	P1_RANGE_CREATURE,
	P1_BUILDING,

	P2_MELEE_CREATURE,
	P2_RANGE_CREATURE,
	P2_BUILDING,

	P3_MELEE_CREATURE,
	P3_RANGE_CREATURE,
	P3_BUILDING,

	P4_MELEE_CREATURE,
	P4_RANGE_CREATURE,
	P4_BUILDING,

	UI = 31,
	END = 32,
};


enum class SCENE_TYPE {
	TEST,
	TOOL,
	START,

	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,
	END

};


enum class EVENT_TYPE {
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,




	END,
};

enum class MON_STATE {
	IDLE,//대기
	TRACE,//쫓기
	ATT,	//가까운 상대 공격
	TARGET_ATT,// 지정한 타겟공격
	DEAD,//사망
	END,
};