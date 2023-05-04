#include "pch.h"
#include "CScene_Test.h"

#include "CCore.h"
#include "CCamera.h"

#include "CBackground.h"

void CScene_Test::update()
{
	CScene::update();
}

void CScene_Test::render(HDC _dc)
{
	CScene::render(_dc);
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

CScene_Test::CScene_Test(int _row, int _column)
{
	m_vMap.resize(_row);
	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _column; j++) {
			CObject* pBackground = new CBackground;
			wstring name = L"Background";
			pBackground->SetName(L"Background");
			pBackground->SetPos(Vec2(_column * 2045, _row * 2048));
			pBackground->SetScale(Vec2(600.f, 600.f));
			AddObject(pBackground, GROUP_TYPE::BACKGROUND);
			m_vMap[i].push_back(pBackground);
		}
	}
}

CScene_Test::~CScene_Test()
{
}
