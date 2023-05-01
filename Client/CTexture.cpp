#include "pch.h"
#include "CTexture.h"

#include<iostream>
#include <fstream>
#include <Shlwapi.h>

#include "CCore.h"

#pragma comment(lib, "Shlwapi.lib")

void CTexture::Load(const wstring& _strFilePath)
{
	// 1. 경로 문자열이 올바른지 확인
	std::ifstream file(_strFilePath);
	assert(file.good());

	// 2. 이미지 파일이 존재하는지 확인
	assert(PathFileExistsW(_strFilePath.c_str()));


	//파일로부터 로딩한 데이터로 비트맵 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(),IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);
	//비트맵과 연결할 DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	//비트맵 정보 저장
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CCore::GetInst()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
	m_dc = CreateCompatibleDC(maindc);

	//여기서 m_memDC와 m_hBit를 연결시켜준다.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	//비트맵 정보 저장
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{

}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}
