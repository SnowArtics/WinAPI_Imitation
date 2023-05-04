#include "pch.h"
#include "CTexture.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <Shlwapi.h>

#include "CCore.h"

#pragma comment(lib, "Shlwapi.lib")

class MyImageDeleter
{
public:
	void operator()(Gdiplus::Image* pImage) const
	{
		pImage->operator delete;
		//delete pImage;
	}
};

class MyBitmapDeleter
{
public:
	void operator()(Bitmap* pBitmap) const
	{
		pBitmap->operator delete;
	}
};

void CTexture::Load(const wstring& _strFilePath)
{
	//GDI
	size_t gdiplusToken = 0;
	GdiplusStartupInput gdiplusStartupInput;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//image.png ������ �̿��Ͽ� ����� ������ �ҷ��� Image��ü�� ����
	//Image* image = Image::FromFile(_strFilePath.c_str(), false);

	//std::unique_ptr<Image> image(Image::FromFile(_strFilePath.c_str(), false));

	//�ҷ��� Image�� Clone�Ͽ� Bitmap ���Ϸ� ��ȯ��, HBITMAP���Ϸ� ��ȯ
	//Bitmap* pBitmap = static_cast<Bitmap*>(image->Clone());
	Bitmap* pBitmap = Bitmap::FromFile(_strFilePath.c_str());
	//std::unique_ptr<Bitmap, MyBitmapDeleter> pBitmap(Bitmap::FromFile(_strFilePath.c_str()));
	assert(pBitmap);
	Status status = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);

	//====================================================================
	// 1. ��� ���ڿ��� �ùٸ��� Ȯ��
	//std::ifstream file(_strFilePath);
	//assert(file.good());

	//// 2. �̹��� ������ �����ϴ��� Ȯ��
	//assert(PathFileExistsW(_strFilePath.c_str()));


	////���Ϸκ��� �ε��� �����ͷ� ��Ʈ�� ����
	//m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(),IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//assert(m_hBit);
	//��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	

	//��Ʈ�� ���� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	
	GdiplusShutdown(gdiplusToken);
}

void CTexture::Loadpng(const wstring& _strFilePath)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// PNG ���� �ε�
	Bitmap* bitmap = Bitmap::FromFile(_strFilePath.c_str(),false);
	assert(bitmap);

	// HBITMAP ��ȯ
	HBITMAP hBitmap;
	bitmap->GetHBITMAP(NULL, &hBitmap);

	GetObject(m_hBit, sizeof(BITMAP), &hBitmap);

	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
	HBITMAP hTempBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hTempBit);
	

	// GDI+ ����
	delete bitmap;
	GdiplusShutdown(gdiplusToken);
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
