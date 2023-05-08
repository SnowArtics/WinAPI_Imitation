#include "pch.h"
#include "CCore.h"

#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "SelectGDI.h"

#include "resource.h"

#include "CSound.h"

//CCore* CCore::g_pInst = nullptr;//������ ������ �����ǰ� ���� ȣ�� �� �ѹ��� �ʱ�ȭ��


//CObject g_obj;

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	
	//�� ������ �ػ󵵿� �°� ���� ���ϴ� ������ ũ�⿡ �°� ������ ũ�� ����
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);
	
	//�޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd);//�ش� �������� dc�� ���´�.

	//���� ���۸� �뵵�� �ؽ��� ������ �����.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	//���� ��� �� �� �� �귯�� ����
	CreateBrushPen();

	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CCollisionMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();

	//g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2),(float) (m_ptResolution.y / 2)));
	//g_obj.SetScale(Vec2(100,100

	/*CResMgr::GetInst()->LoadSound(L"Menu-Theme", L"sound\\Menu-Theme.wav");
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Menu-Theme");

	pNewSound->Play();*/

	//pNewSound->PlayToBGM(true);
	//pNewSound->SetPosition(10.f); // ��з�, �Ҹ� ��ġ ����
	//pNewSound->SetVolume(60.f);

	return S_OK;
}


void CCore::progress()
{

	//Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();


	//Scene Update
	CSceneMgr::GetInst()->update();

	//�浹 üũ
	CCollisionMgr::GetInst()->update();

	//UI �̺�Ʈ üũ
	CUIMgr::GetInst()->update();


	//�׸���
	//DC�� BeginPaint�� EndPaint�� ����ҷ��� �ϴµ�, EndPaint�� ��ȿȭ ������ �������ִ� ������ �Ѵ�.
	//�׷��� EndPaint�� �ۿ��� ���� ������ �����༭ ������ �Ͼ.
	//�׸��� �츮�� �޼����� ���� ����� ������� �ʴ´�.
	//�츮�� �޼����� ��� �׷����Ѵ�.

	//update();
	
	//render();

	//===========
	//Renddering
	//==========
	//ȭ�� Ŭ����
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	//
	//�̺�Ʈ ���� ó��
	//
	CEventMgr::GetInst()->update();

}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);

	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	//hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//red pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID,1,RGB(255,0,0));

	//green pen
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

	//blue pen
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	//sky pen
	m_arrPen[(UINT)PEN_TYPE::SKY] = CreatePen(PS_SOLID, 1, RGB(80, 188, 223));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu() 
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0,0, (long)_vResolution.x, (long)_vResolution.y};
	//SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	//AdjustWindowRectExForDpi(&rt, WS_OVERLAPPEDWINDOW, true, WS_EX_LEFT, 96);

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);	//���� �������� ũ���� ���� ���µ� �츮�� �۾������� �װ� ���� �۾Ƽ� �ξ� ũ�� �������� �Ѵ�.
	//�װ� �����ִ°� �� �Լ���.rt�� ũ�⸦ ���ϰ�, ����� ���ϰ�, �޴��ٰ� �ִٰ� �����Ѵ�.
	//rt�� _Inout_�ε� �����ε� ���⿡ �ְ� �ƿ����ε� ���⿡ �ִ´�.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);//ù��° �Ķ���ͷδ� �������� �ڵ��� �־, �ش� �������� ũ�⸦ �ٲ۴�.

}

//void CCore::update()//��ü���� ������ üũ
//{
//
//	Vec2 vPos = g_obj.GetPos();
//
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD) {
//		vPos.x -= 200.f*fDT;
//	}
//
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD) {
//		vPos.x += 200.f * fDT;
//
//	}
//
//	g_obj.SetPos(vPos);
//
//}

//void CCore::render()//������ ����� �׷���
//{
//	//ȭ�� Clear//��üȭ���� �� ȭ������ �׸��� �Ŀ� �������� �׸���.
//	//������10�� �츮�� ��ҿ� �۾��ϴ� �������� 1�ȼ� �� Ŀ�� �ű⵵ �� ä�����
//	//1�� �߰����ش�.
//	//�ٵ� �̰� �ʹ� ������! 1280*768 = 983040�ε� �̰� �Ź� �׸��°� �ʹ� ��ȿ�����̰�
//	//������ ������?
//	//�̷��� �ȴٸ� ȭ�� ������ ������ ��������.
//	//���߿� �� ���� �̷� ������ ���� ���������̴�.
//	//�Լ� �ϳ��� �׷����� ���� ������ �ʴ´�. �Լ��� ������ ��ũ�� �����.
//	// ���� �Լ����� �׷����� �߰������߿�
//	//�׷����� ���� ���δ�.
//	//�̰� �ذ��ϱ� ���ؼ� ���ʿ� �� �׸��� �װ� �ѹ��� ��������!
//	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
//
//
//	Vec2 vPos = g_obj.GetPos();
//	Vec2 vScale = g_obj.GetScale();
//	Rectangle(m_memDC, 
//		int(vPos.x - vScale.x / 2.f),
//		int(vPos.y - vScale.y / 2.f), 
//		int(vPos.x + vScale.x / 2.f), 
//		int(vPos.y + vScale.y / 2.f));
//
//	//��Ʈ���� �Ѷ��� �̵������ִ� �Լ��� BitBlt�̴�.
//	//�����ض�! BitMap�� �̵������ִ°� �ƴϰ� DC�� �̵������ش�.
//	//�ٵ� �� �۾��� �ϴϱ� �������� ��û ��������.
//	//���� ��� ���� CPU�� �۾��ϰ� �ִµ�, �� �ݺ� ó���� GPU�� �Ѵٸ�
//	//������ �ſ� ����������? �̰� DirectX11���� ����.
//	BitBlt(m_hDC,0,0,m_ptResolution.x,m_ptResolution.y,m_memDC,0,0,SRCCOPY);
//	//��Ʈ ���� ��ǻ�Ϳ� �� �׸��� ��ü�� �� �ű�� ������, ���� ������ ����� ��������̴�.
//	//�׷��Ƿ� Rectangle�� ���� �׷��� �������� ���� �������� �ʴ´�.
//	//�� �̰� �������� ���� ����̴�.
//
//}

CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);//m_hDC�� �ü���� ������ִ� �Ŷ� �ü������ �����ش޶�� ��û�ؾ��Ѵ�.

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i) {
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}