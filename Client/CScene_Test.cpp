#include "pch.h"
#include "CScene_Test.h"
#include <locale>

#include "CCore.h"
#include "CCamera.h"

#include "CPathMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CBackground.h"
#include "CBtnUI.h"
#include "CTexture.h"
#include "CPanelUI.h"
#include "SelectGDI.h"

void CScene_Test::update()
{
	CScene::update();

	if (KEY_TAP(KEY::RBTN)) {
		m_bTriggerCursor = false;
		m_pCursorIcon = nullptr;
	}

	//마우스 왼쪽 버튼을 눌렀을 때, 드래그 시작.
	if (KEY_TAP(KEY::LBTN)&&!m_bTriggerCursor) {
		m_vDragStart = MOUSE_POS;
		m_bDragOn = true;
	}
	//마우스 왼쪽 버튼을 계속 누르고 있어야 함.
	if (m_bDragOn && KEY_HOLD(KEY::LBTN)) {
		Vec2 _vPos = MOUSE_POS;
		m_vDragSize = m_vDragStart - _vPos;
		m_bDragOn = true;
	}
	//왼쪽 버튼을 때면 드래그 작동이 끝나고, _vPos 
	if (KEY_AWAY(KEY::LBTN)&&m_bDragOn) {
		m_bDragOn = false;
	}
}

void CScene_Test::render(HDC _dc)
{
	CScene::render(_dc);

	//ButtonPanel을 클릭했을 때
	if (m_bTriggerCursor && m_pCursorIcon) {
		//m_pCursorIcon의 크기를 저장
		UINT iWidth = m_pCursorIcon->Width();
		UINT iHeight = m_pCursorIcon->Height();

		iWidth = m_pCursorIcon->Width();
		iHeight = m_pCursorIcon->Height();

		assert(m_pCursorIcon);

		Vec2 mousePos = MOUSE_POS;

		TransparentBlt(_dc
			, (int)mousePos.x
			, (int)mousePos.y
			, iWidth
			, iHeight
			, m_pCursorIcon->GetDC()
			, 0
			, 0
			, iWidth
			, iHeight
			, RGB(255, 0, 255));
	}

	//현재 드래그 상태일 때
	if (m_bDragOn) {
		PEN_TYPE ePen = PEN_TYPE::SKY;

		SelectGDI p(_dc, ePen);
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

		Rectangle(_dc
			, (int)(m_vDragStart.x)
			, (int)(m_vDragStart.y)
			, (int)(m_vDragStart.x - m_vDragSize.x)
			, (int)(m_vDragStart.y - m_vDragSize.y));
	}
}

void CScene_Test::Enter()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//CObject* pBackground = new CBackground;
	//pBackground->SetName(L"Background");
	//pBackground->SetPos(Vec2(0.f, 0.f));
	//pBackground->SetScale(Vec2(600.f, 600.f));
	//AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	start();
}

void CScene_Test::Exit()
{
}

vector<char> CScene_Test::makeBridgeDirection(int _row, int _column, int _size)
{
	vector<char> directionResult;
	if (_row == 0 && _column == 0) {
		directionResult.push_back('E');
		directionResult.push_back('S');
	}
	else if (_row == 0 && _column == _size) {
		directionResult.push_back('S');
		directionResult.push_back('W');
	}
	else if (_row == _size && _column == 0) {
		directionResult.push_back('E');
		directionResult.push_back('N');
	}
	else if (_row == _size && _column == _size) {
		directionResult.push_back('W');
		directionResult.push_back('N');
	}
	else if (_row == 0 && _column != _size && _column != 0) {
		directionResult.push_back('E');
		directionResult.push_back('S');
		directionResult.push_back('W');
	}
	else if (_row == _size && _column != _size && _column != 0) {
		directionResult.push_back('E');
		directionResult.push_back('W');
		directionResult.push_back('N');
	}
	else if (_row != 0 && _row != _size && _column == 0) {
		directionResult.push_back('E');
		directionResult.push_back('S');
		directionResult.push_back('N');
	}
	else if (_row != 0 && _row != _size && _column == _size) {
		directionResult.push_back('S');
		directionResult.push_back('W');
		directionResult.push_back('N');
	}
	else {
		directionResult.push_back('E');
		directionResult.push_back('S');
		directionResult.push_back('W');
		directionResult.push_back('N');
	}


	return directionResult;
}

wstring CScene_Test::makeBackgroundName(int _row, int _column)
{
	wstring row = std::to_wstring(_row);
	wstring column = std::to_wstring(_column);
	wstring resultName = L"Background";

	resultName += row;
	resultName += column;

	return resultName;
}

void CScene_Test::LoadUI(const wstring& _strRelativePath, string _pageName)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	string str;
	char szBuff[256] = {};

	//여기는 왼쪽 정보패널 적기
	FScanf(szBuff, pFile);
	for (int i = 0; i < 5; i++) {
		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);

		//이게 경로임
		str = szBuff;

		//UI 키값 생성해주기
		string prevUiKey = str.substr(10, str.size() - 10 - 5);
		wstring uiKey;
		uiKey.assign(prevUiKey.begin(), prevUiKey.end());

		//UI 경로값 생성해주기
		str = str.substr(0, str.size() - 1);
		wstring uiRelativePath;
		uiRelativePath.assign(str.begin(), str.end());

		CPanelUI* pPanelUI = new CPanelUI;
		pPanelUI->SetName(uiKey);
		pPanelUI->SetScale(Vec2(85.f, 35.f));
		pPanelUI->SetPos(Vec2(20.f, 35.f*i+20.f));
		//버튼 UI에 이미지 넣어주기
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(uiKey, uiRelativePath);
		pPanelUI->SetTexture(pTex);
		//여기에 버튼 클릭시 행동 넣어주기
		//
		AddObject(pPanelUI, GROUP_TYPE::UI);
	}



	str = str.substr(0, str.size() - 1);
	wstring uiRelativePath;
	uiRelativePath.assign(str.begin(), str.end());

	while (true) {
		FScanf(szBuff, pFile);
		str = szBuff;
		str = str.substr(0, str.size() - 1);
		if (str == _pageName)
			break;
	}

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	//여기에 UI의 개수가 몇개인지 들어옴
	str = szBuff;
	//int로 변환
	int uiCount = std::stoi(str);

	for (int i = 0; i < uiCount; i++) {
		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);

		//이게 경로임
		str = szBuff;

		//UI 키값 생성해주기
		string prevUiKey = str.substr(10, str.size()-10-5);
		wstring uiKey;
		uiKey.assign(prevUiKey.begin(), prevUiKey.end());

		//UI 경로값 생성해주기
		str = str.substr(0,str.size() - 1);
		wstring uiRelativePath;
		uiRelativePath.assign(str.begin(), str.end());

		CBtnUI* pBtnUI = new CBtnUI;
		pBtnUI->SetScale(Vec2(66.f, 56.f));
		pBtnUI->SetPos(Vec2(90.f*i+200.f, 20.f));
		//버튼 UI에 이미지 넣어주기
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(uiKey, uiRelativePath);
		pBtnUI->SetTexture(pTex);
		//여기에 버튼 클릭시 행동 넣어주기
		//
		AddObject(pBtnUI, GROUP_TYPE::UI);

		//마우스 가이드 해줄 아이콘 이미지 로드
		FScanf(szBuff, pFile);

		str = szBuff;
		//UI 키값 생성해주기
		prevUiKey = str.substr(10, str.size() - 10 - 5);
		uiKey.assign(prevUiKey.begin(), prevUiKey.end());

		//UI 경로값 생성해주기
		str = str.substr(0, str.size() - 1);
		uiRelativePath.assign(str.begin(), str.end());

		pTex = CResMgr::GetInst()->LoadTexture(uiKey, uiRelativePath);
		pBtnUI->SetCursorIconTex(pTex);

		pBtnUI->SetClickedCallBack(this, (SCENE_CURSOR_FUNC)&CScene_Test::SetCursorIconTex);
	}

	fclose(pFile);
}

CScene_Test::CScene_Test(int _row, int _column)
	: m_bTriggerCursor(false)
	, m_pCursorIcon(nullptr)
	, m_vDragStart(Vec2(0.f,0.f))
	, m_bDragOn(false)
{
	//m_vMap의 크기를 초기화
	m_vMap.resize(_row);
	for (int i = 0; i < _row; i++) {
		m_vMap[i].resize(_column);
	}
	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _column; j++) {
			vector<char> bridgeDirection = makeBridgeDirection(i, j,_row-1);
			CObject* pBackground = new CBackground(bridgeDirection, this);
			wstring name = makeBackgroundName(i, j);
			pBackground->SetName(name);
			//pBackground->SetPos(Vec2(j * 2045, i * 2048));
			pBackground->SetPos(Vec2(j* 1190, i* 890));
			pBackground->SetScale(Vec2(1050.f, 800.f));
			AddObject(pBackground, GROUP_TYPE::BACKGROUND);
			m_vMap[i][j] = pBackground;
		}
	}

	LoadUI(L"ui\\ui.info", "[page1]");
}

CScene_Test::~CScene_Test()
{
}
