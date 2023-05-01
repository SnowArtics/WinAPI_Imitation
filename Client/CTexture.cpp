#include "pch.h"
#include "CTexture.h"

#include<iostream>
#include <fstream>
#include <Shlwapi.h>

#include "CCore.h"

#pragma comment(lib, "Shlwapi.lib")

void CTexture::Load(const wstring& _strFilePath)
{
	// 1. ��� ���ڿ��� �ùٸ��� Ȯ��
	std::ifstream file(_strFilePath);
	assert(file.good());

	// 2. �̹��� ������ �����ϴ��� Ȯ��
	assert(PathFileExistsW(_strFilePath.c_str()));


	//���Ϸκ��� �ε��� �����ͷ� ��Ʈ�� ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(),IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);
	//��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	//��Ʈ�� ���� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CCore::GetInst()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
	m_dc = CreateCompatibleDC(maindc);

	//���⼭ m_memDC�� m_hBit�� ��������ش�.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	//��Ʈ�� ���� ����
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
