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

//CCore* CCore::g_pInst = nullptr;//데이터 영역에 생성되고 최초 호출 시 한번만 초기화됨


//CObject g_obj;

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	
	//찐 게임의 해상도에 맞게 내가 원하는 게임의 크기에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);
	
	//메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd);//해당 윈도우의 dc를 들고온다.

	//이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	//자주 사용 할 펜 및 브러쉬 생성
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
	//pNewSound->SetPosition(10.f); // 백분률, 소리 위치 설정
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

	//충돌 체크
	CCollisionMgr::GetInst()->update();

	//UI 이벤트 체크
	CUIMgr::GetInst()->update();


	//그리기
	//DC를 BeginPaint와 EndPaint를 사용할려고 하는데, EndPaint는 무효화 영역을 해제해주는 역할을 한다.
	//그런데 EndPaint를 밖에서 쓰면 해제를 못해줘서 문제가 일어남.
	//그리고 우리는 메세지를 쓰는 방식을 사용하지 않는다.
	//우리는 메세지가 없어도 그려야한다.

	//update();
	
	//render();

	//===========
	//Renddering
	//==========
	//화면 클리어
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	//
	//이벤트 지연 처리
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

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);	//실제 윈도우의 크기의 값이 들어가는데 우리의 작업공간은 그것 보다 작아서 훨씬 크게 만들어줘야 한다.
	//그걸 맞춰주는게 이 함수임.rt로 크기를 정하고, 생긴거 정하고, 메뉴바가 있다고 지정한다.
	//rt가 _Inout_인데 인으로도 여기에 넣고 아웃으로도 여기에 넣는다.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);//첫번째 파라미터로는 윈도우의 핸들을 넣어서, 해당 윈도우의 크기를 바꾼다.

}

//void CCore::update()//물체들의 변경점 체크
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

//void CCore::render()//현재의 장면을 그려냄
//{
//	//화면 Clear//전체화면을 흰 화면으로 그리고 후에 나머지를 그린다.
//	//윈도우10은 우리가 평소에 작업하던 공간보다 1픽셀 더 커서 거기도 다 채울려고
//	//1씩 추가해준다.
//	//근데 이건 너무 느리다! 1280*768 = 983040인데 이걸 매번 그리는건 너무 비효율적이고
//	//느리지 않은가?
//	//이렇게 된다면 화면 깜빡임 현상이 심해진다.
//	//나중에 갈 수록 이런 현상은 더욱 심해질것이다.
//	//함수 하나가 그려지는 때는 보이지 않는다. 함수가 끝나고 싱크를 맞춘다.
//	// 여러 함수들이 그려지는 중간과정중에
//	//그려지는 것이 보인다.
//	//이걸 해결하기 위해서 한쪽에 다 그리고 그걸 한번에 가져오자!
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
//	//비트맵을 한땀씩 이동시켜주는 함수가 BitBlt이다.
//	//주의해라! BitMap을 이동시켜주는게 아니고 DC를 이동시켜준다.
//	//근데 이 작업을 하니까 프레임이 엄청 떨어진다.
//	//지금 모든 것을 CPU로 작업하고 있는데, 이 반복 처리를 GPU로 한다면
//	//성능이 매우 빨라지겠지? 이걸 DirectX11에서 배운다.
//	BitBlt(m_hDC,0,0,m_ptResolution.x,m_ptResolution.y,m_memDC,0,0,SRCCOPY);
//	//비트 블릿은 컴퓨터에 뭘 그리든 전체를 다 옮기기 때문에, 지금 프레임 드랍은 고정비용이다.
//	//그러므로 Rectangle을 많이 그려도 프레임이 많이 떨어지지 않는다.
//	//즉 이건 렌더링의 고정 비용이다.
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
	ReleaseDC(m_hWnd, m_hDC);//m_hDC는 운영체제가 만들어주는 거라서 운영체제한테 해제해달라고 요청해야한다.

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i) {
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}