// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"

#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.//재정의 해줌//
HWND        g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
//wchar_t를 재정의한게 WCHAR임//

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//함수 전방선언함//
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



//_In_, _In_opt_는 지역변수 앞에 적어줌으로써 용도를 정의해줄 수 있다.
//SAL(소스코드주석언어) 라고 한다.
//모든 인스턴스에 다는 것보단 약속된 키워드를 다는게 더 편하잖나?
//_In_은 받는 인스턴스, _In_opt는 부가적으로 받는거다.(그래서 밑에 딱히 필요없다고 정의한다.)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,//프로그램 첫 진입 함수이다.
                                                //hInstance는 실행된 프로세스의 시작 주소이다.(가상메모리의)
                     _In_opt_ HINSTANCE hPrevInstance,//나보다 이전에 실행된 프로세스의 시작 주소.
                                                    //옛날에는 이 hPrevInstance로 현재 프로세스의 주소를
                                                //받아야만 했는데, 윈도우가 가상 메모리를 사용함으로써
                                                //각 프로세스별로 구별된 메모리 공간을 할당받기 때문에
                                                //모든 프로세스의 hInstance값은 똑같을 수 있고,
                                                //hPrevInstance는 필요 없어졌다.
                     _In_ LPWSTR    lpCmdLine,//명령프롬프트로 프로그램을 실행하면 추가적인 인자로
                                            //문자열을 받을 수 있다.ex) 옵션 같은거
                     _In_ int       nCmdShow)
{
    //메모리릭(누수) 찾기
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(402);
    _CrtDumpMemoryLeaks();

    SetProcessDPIAware();

    UNREFERENCED_PARAMETER(hPrevInstance);//이 파라미터는 쓰이지 않는다
    UNREFERENCED_PARAMETER(lpCmdLine);//이 파라미터는 쓰이지 않는다.

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.//전역변수로 선언한 szTitle, szWindowClass에 문자열을 로드함.
    //리소스 뷰의 StringTable에서 문자열을 받아온다.
    //Resource.h의 헤더에보면 숫자로 #define되어 있다.
    //즉, LoadStringW에서 해당 값의 텍스트를 불러와라가 된다.
    LoadStringW(hInstance, IDS_APP_TITLE/*103*/, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT/*109*/, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);//가보자
    //이 함수는 그냥 윈도우에 정보를 등록한다,
    //여기에 등록한 정보대로 창을 생성한다.

    // 애플리케이션 초기화를 수행합니다:
    //InitInstance는 윈도우의 창을 만들어주는 일을 한다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{1920,1080}))) {
        MessageBox(nullptr, L"Core 객체 초기화 실패",L"ERROR",MB_OK);
        return FALSE;
    };

    //밑의 변수에는 단축키 정보가 들어가 있음.
    //리소스뷰의 Accelator에 존재한다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    //SetTimer(g_hWnd, 0, 0, nullptr);//g_hWnd에 타이머 부탁, ID는 0, 멈추지않고 계속 실행
    //이 함수로 프로시져를 발생시켜서 메세지를 계속 보냄.

    //MSG의 구조체를 까보면 msg.hwnd가 존재하는데, 해당 윈도우가 어떤 윈도우인지에 대한 정보 또한 존재한다.

    // 기본 메시지 루프입니다:
    //윈도우에는 메세지 큐라는게 해당 프로그램에 존재한다.
    //윈도우안에는 다양한 프로세스들이 존재하는데, 윈도우는 현재 포커싱이 되어 있는 프로그램한테 우선적으로 메세지큐의 신호들을 전달해준다.
    //예를 들어, 그림판을 쓰고 있는데, 클릭을 하면 그림판에 우선적으로 클릭 신호를 넘기는 것이다.
    //이 GetMessage는 그 메세지 큐에서 나한테 전달된 정보가 있는지 꺼내보는 것이다.

    //또다른 GetMessage의 특징이 있는데,
    //메세지큐에 아무것도 없다고 이 반복문이 종료되지 않는다. 메세지큐에서 메세지 확인할때까지 기다린다.
    //msg.message==WM_QUIT인경우 false를 반환하고 -> 프로그램이 종료된다.
    //즉 메세지 반응 프로그램이다.
    //근데 게임은 우리가 가만히 있어도 동작해야한다. 즉 바꿔야한다.
    //while (GetMessage(&msg, nullptr, 0, 0))//msg의 주소값을 던져서 msg의 구조체에 값을 채워준다.
    //{

    //    //이 조건문에서 hAccelTable를 참조해서 단축키가 들어가있는지 채크해준다.
    //    //해당 단축기를 쓰면 맞는 메세지가 뜬다.
    //    //그래서 저 테이블 단축키를 쓰는게 아니라면 딱히 밑에 껄 쓸 필요가 없긴 하다.
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);//알맞은 윈도우한테 메세지를 던지고 해당 윈도우의 프로시져가 처리한다.//프로시져측으로 가보자.
    //        DispatchMessage(&msg);
    //    }
    //}

    //KillTimer(g_hWnd,0);

    //메세지 큐의 문제는 메세지가 들어올때까지 계속 기다리고 있다.
    //이를 해결하기 위해서 WM_TIMER를 강제로 발생시키는데, 이것 또한 문제가 많다.
    //그래서 이 메세지를 기다리는 구조를 갖다 버리고 다른 방법을 사용해 보자.


    while (true) {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        //메세지를 몰래 보다. 라는 뜻이다.
        //메세지가 있으면 있는거 반환하고 없으면 없는대로 계속 반환한다.
        //뒤에 파라미터를 하나 더 주는데, 메세지를 보고
        //메세지를 없앨지 안 없앨지 넣어줄 수 있다.
        //픽 메세지는 메세지유무와 관계없이 반환한다.
        //픽 메세지는 반환이 어떻게 정해질까?
        //픽 메세지도 똑같이 True와 False를 반환하는데, 언제 이렇게 반환값이 구분될까?
        //반환되었을 때 메시지가 있으면 True, 없으면 False를 반환한다.
        //즉, while문 조건으로 넣을 수 는 없다.
        //그래서 if문 안에 넣어준다.

            if (WM_QUIT == msg.message) break;//만약에 message가 WM_QUIT일 때 while문 종료
            //이 상태가 기존의 GetMessage와 똑같은 상태이다.

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        }
        //메세지가 발생하지 않는 대부분의 시간
        else {
            //메세지가 없는 동안 호출
            //그렇다면 왜 메세지가 없는동안 시스템을 돌리려고 할까? 얼마나 효율이 나길래?
            //테스트를 해보면 많아도 메세지의 비율은 전체 처리 비율의 0.01퍼센트를 넘어가지 않는다.
            //즉 나머지 0.99가 놀고 있는 것이다. 이걸 사용해야 한다.

            //밑으로 게임 코드를 적는다.
            //디자인 패턴(설계 유형)을 먼저 제작해보자.
            //디자인 패턴은 유형이기 때문에 알면 좋은 그런것이다.
            //근데 싱글톤 패턴은 무조건 알아야 한다!!!
            CCore::GetInst()->progress();


            
        }

    }
    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;//밑으로 WNDCLASSEXW의 구조체를 채우고 있다.

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;//각윈도우는 해당 윈도우에서 발생하는 메세지를 처리해주는 무언가를 만들어주는데 그게 프로시져다.
                                    //여기서 윈도우에 프로시져를 등록하고 자신만의 프로시져를 처리한다.
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_CLIENT);//윈도우의 메뉴바를 가리킴
    wcex.lpszClassName  = szWindowClass;//이 구조체의 세팅 키값을 지정한다,
                                        //키값으로 윈도우의 정보를 찾는다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);//이건 윈도우에서 제공해주는 함수라서
                                    //선언만 볼 수 있고, 정확한 구조를 알 수 없다.
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
   SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);


   //여기서 szWindowClass와 szTitle로 윈도우를 만들어준다.
   //szWindowClass로 키값을 등록했는데 CreateWindowW에서 szWindowClass키값으로
   //윈도우에 정보세팅한 값을 불러와서 윈도우를 생성한다.
   //CreateWindowW시 해당 윈도우의 아이디가 HWND에 저장된다.
   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   //g_hWnd = CreateWindowEx(0, szWindowClass, szTitle,
   //    WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU,
   //    0, 0, 640, 480, NULL, NULL, hInstance, NULL);


   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//#include <vector>
//
//using namespace std;
//
//struct tObjInfo {
//
//    POINT g_ptObjPos;
//    POINT g_ptObjScale;
//
//};
//
//vector<tObjInfo> g_vecInfo;
//
//
//POINT g_ptLT;//좌 상단 좌표
//POINT g_ptRB;//우 하단 좌표
//
//bool blbtnDown = false;

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//메시지가 마우스 클릭인경우 lparam에 추가로 정보가 들어오고, 키 다운인경우 무슨 키인지 wParam에 들어온다.
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_MENU_TILE:
            {
                INT_PTR iRet = DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);

                if (iRet == IDOK) {

                }
            }
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT://여기를 만져봥.쓰윽쓰윽
                    //무효화영역(invalidate)이 발생한 경우 WM_PAINT가 발생한다.
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);//DeviceContext라는 그리기 관련된 요소를 생성해서 ID 값을 HDC에 반환해준다.
            //HDC까보면 int하나 들고 있는 구조체임. 다른 핸들도 다 까보면 int만 들고 있음. 그렇다면 왜 이름을 다 나눌까?
            //이름을 안 나누면 머가 먼지 헷갈리니까 다 나눈거다.
            // 그리고자하는 hWnd를 받아서 그린다.
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            //윈도우 핸들/ㅎㅎ
            //윈도우 좌표/ㅎㅎ
            //HDC ?/ㅎㅎ

            //DC란 윈도우에 그리기 위한 도구들(펜, 브러시 등)의 총 집합체이다.
            //즉 이 함수는, 이 hdc를 사용해서 그린다는 거고 hdc를 만들때 hWnd로 dc의 목적지를 정해주었다.
            //근데 DC를 정해준게 없는데, 이 때는 Default 펜을 쓴다(black)
            //브러쉬는 기본 브러쉬 (white)를 쓴다. 내부는 하얀색으로, 브러쉬로 칠해져있다.

            //직접 펜을 만들어보자 그리고 DC에 지급하자.
            //HPEN hRedPen = CreatePen(PS_SOLID,1,RGB(255,0,0));
            //HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);//hdc의 펜을 바꾼다.
            //                                                    //SelectObject가 매우 범용적인 함수라서 HPEN, 처럼 지정해서 반환할 수 없다.
            //                                                    //그래서 void*함수로 만들어놓고 타입캐스팅하게 해놓는다.
            //                                                    //반환시 기존에 사용된 펜이 나온다.

            //HBRUSH hBlueBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);//자주 쓰는 펜이나 브러쉬같은경우에 미리 만들어 놓은게 있다. 그걸 쓴다.
            //                                     //이 경우 직접 만들어 쓴게 아니고 얻어다 쓴거라서 DELETE하지 않는다.
            //HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            //if (blbtnDown) {
                //Rectangle(hdc,1820, 980, 1920,1080);
            //}

            //for (size_t i = 0; i < g_vecInfo.size(); i++) {
            //    Rectangle(hdc,
            //        g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x/2,
            //        g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2,
            //        g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2,
            //        g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            //}

            //SelectObject(hdc, hDefaultPen);//hdc의 펜을 Default펜으로 바꾼다.
            //SelectObject(hdc, hDefaultBrush);

            //DeleteObject(hRedPen);//필요없어진 hRedPen을 삭제한다.
            //DeleteObject(hBlueBrush);


            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
    {
        //switch (wParam)
        //{
        //case VK_UP:
        //    //g_ptObjPos.y-=10;//여기까지만 하면 움직이지 않는다. 무효화 영역을 임의로 설정해줘서 WM_PAINT를 실행시켜야 한다.
        //    InvalidateRect(hWnd, nullptr, true);//무효화 영역을 강제로 발생시킨다. 즉, WM_PAINT를 발생 시킨다.
        //                                        //발생한 윈도우를 지정하고, nullptr을 하면 무효화 영역이 발생한 영역을 전체영역으로 가정한다.
        //                                        //false를 두면 기존의 그림을 지우지 않는다.
        //    break;

        //case VK_DOWN:
        //    //g_ptObjPos.y+=10;
        //    InvalidateRect(hWnd, nullptr, true);
        //    break;

        //case VK_RIGHT:
        //    //g_ptObjPos.x += 10;
        //    InvalidateRect(hWnd, nullptr, true);           
        //    break;

        //case VK_LEFT:
        //    //g_ptObjPos.x -= 10;
        //    InvalidateRect(hWnd, nullptr, true);
        //    break;

        //}
    }
        break;


    case WM_LBUTTONDOWN://마우스 버튼이 눌렸을때 어디를 클릭했냐?
    {
        ////lparam에 우측 2바이트에는 x좌표 좌측 2바이트에는 y좌표가 들어가서 나온다.
        ////밑에서 비트 연산자로 x좌표 y좌표 자름
        //g_ptLT.x = LOWORD(lParam);//마우스 x좌표
        //g_ptLT.y = HIWORD(lParam);//마우스 y좌표

        //blbtnDown = true;
    }
        break;

    case WM_MOUSEMOVE:
    {
        //g_ptRB.x = LOWORD(lParam);//마우스 x좌표
        //g_ptRB.y = HIWORD(lParam);//마우스 y좌표
        //InvalidateRect(hWnd, nullptr, true);
    }
        break;

    case WM_LBUTTONUP:
    {

        //tObjInfo info = {};//
        //info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        //info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        //info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        //info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        //g_vecInfo.push_back(info);

        //blbtnDown = false;
        //InvalidateRect(hWnd, nullptr, true);

    }

        break;


    case WM_TIMER://타이머가 작동될때마다 여기 스크립트가 실행




        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
