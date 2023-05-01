#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

//���� Ű���� �츮�� Ű���̶� ��Ī�������
int g_arrVK[(int)KEY::LAST] = {
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	//
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	//
	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,


	VK_LBUTTON,
	VK_RBUTTON,
	//
	//
	//
	//LAST,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; i++) {
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update() {

	//������ ��Ŀ�� �˾Ƴ���
	HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();//���� ��Ŀ�� �Ǿ��ִ� �������� �ڵ��� �˷���
							//��Ŀ�� �� �ֵ��� ���ٸ� 0�� ����.

	if (hWnd != nullptr) {
		for (int i = 0; i < (int)KEY::LAST; i++) {

			//Ű�� �����ִ�.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) {
				if (m_vecKey[i].bPrevPush) {
					//�������� �����־���.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else {
					//������ �ȴ��� �վ���.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else {
				//���� Ű�� �ȴ�������.
				if (m_vecKey[i].bPrevPush) {
					//������ �����ְ� ���� �� ������.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else {
					//�������� ���ݵ� �ȴ����ִ�.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}

		//Mouse ��ġ ���
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

	}
	else {
		//������â�� ��Ŀ���� �� �Ǿ� �ִٸ�

		for (int i = 0; i < (int)KEY::LAST; ++i) {
			m_vecKey[i].bPrevPush = false;
			if (m_vecKey[i].eState == KEY_STATE::TAP|| m_vecKey[i].eState == KEY_STATE::HOLD) {
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY) {
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}



	
}