#pragma once
//
//
////싱글톤 패턴
////객체의 생성을 1개로 제한
////근데 이 객체는 언제 어디서든 모든 파일에서 접근을 할 수 있어야함.
////extern을 사용해서 접근 할 수 있다. 근데 이러면 객체를 여러개를 만들 수 있다.
////즉 객체 생성 방지가 안된다.
////이런것들을 해결할려면 생성자를 private으로 만든다.
////근데 이러면 밖에서 호출이 안된다.
////그런데! 클래스 내부에서는 private를 호출가능하다.
////즉, 객체를 만드는 함수를 클래스내에서 정의해준다.
////함수안에서 객체를 얻는 방법을 하나로 제한하고 그 함수는 객체 하나만 리턴해주는 것이다.
////두번째 문제가 생겼다. 객체를 호출하려면 이미 만들어진 객체가 필요하다.
////근데 객체를 만들려면 함수를 호출해야한다. 로직이 오류가 생긴다.
////이를 해결하려면 객체가 없어도 호출할 수 있는 함수가 필요한데 이것이 바로 static이다.
////객체 없이 어떻게 호출하는 것일까?
////this 키워드가 없기 때문에 호출 할 수 있다. 그런데 this가 없어서 멤버에 접근이 불가능하다.
////그런데 유일하게 접근 가능한 멤버가 있는데 바로 static 변수이다.
//
//class CCore
//{
//private:
//	static CCore* g_pInst;//정적 멤버(데이터) 클래스 내부에서 다 접근이 가능한데, 하나만 있다!
//						//이후 정적 멤버는 반드시 초기화를 해 주어야 한다!! 안하면 에러뜸
//
//public:
//	//정적 멤버함수, 객체없이 호출 가능. 그런데 this 키워드가 없기 때문에,
////멤버 변수나 멤버 함수에 접근할 수 없음.
//	static CCore* GetInstance() {//객체 하나를 얻음
//
//		
//		//최초 호출 된 경우
//		if (nullptr == g_pInst) {
//			g_pInst = new CCore;
//			
//		}
//
//		return g_pInst;//주소값 반환
//	}
//
//	static void Release() {
//		if (nullptr != g_pInst) {
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//};
//
class CTexture;

class CCore {
	//static CCore* GetInstance() {//그냥 생성하고 주소값을 리턴해주면 된다.
	//							//근데 이러면 내가 원할때 해제 해줄 수가 없다.
	//	static CCore core;
	//
	//	return &core;
	//}
	SINGLE(CCore);

private:
	HWND		m_hWnd;			//메인 윈도우 핸들
	POINT		m_ptResolution; //메인 윈도우 해상도
	HDC			m_hDC;		//메인윈도우에 그릴 DC

	CTexture*	m_pMemTex; //백버퍼텍스쳐

	//자주 사용하는 GDI Object
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];

	//메뉴
	HMENU		m_hMenu; //ToolScene에서만 사용

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC		GetMainDC() { return m_hDC; }
	HBRUSH	GetBrush(BRUSH_TYPE _eType) {return m_arrBrush[(UINT)_eType]; }
	HPEN	GetPen(PEN_TYPE _eType) {return m_arrPen[(UINT)_eType]; }

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);
};
//둘중에 어느 방식이 선호될까? 정답은 아무도 몰루~
//수업에서는 요 방식을 쓴다!
//프로젝트의 크기가 그리 크지 않아서.
//반복되니까 매크로로 만들어보자.