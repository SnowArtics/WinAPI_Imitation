#pragma once
//
//
////�̱��� ����
////��ü�� ������ 1���� ����
////�ٵ� �� ��ü�� ���� ��𼭵� ��� ���Ͽ��� ������ �� �� �־����.
////extern�� ����ؼ� ���� �� �� �ִ�. �ٵ� �̷��� ��ü�� �������� ���� �� �ִ�.
////�� ��ü ���� ������ �ȵȴ�.
////�̷��͵��� �ذ��ҷ��� �����ڸ� private���� �����.
////�ٵ� �̷��� �ۿ��� ȣ���� �ȵȴ�.
////�׷���! Ŭ���� ���ο����� private�� ȣ�Ⱑ���ϴ�.
////��, ��ü�� ����� �Լ��� Ŭ���������� �������ش�.
////�Լ��ȿ��� ��ü�� ��� ����� �ϳ��� �����ϰ� �� �Լ��� ��ü �ϳ��� �������ִ� ���̴�.
////�ι�° ������ �����. ��ü�� ȣ���Ϸ��� �̹� ������� ��ü�� �ʿ��ϴ�.
////�ٵ� ��ü�� ������� �Լ��� ȣ���ؾ��Ѵ�. ������ ������ �����.
////�̸� �ذ��Ϸ��� ��ü�� ��� ȣ���� �� �ִ� �Լ��� �ʿ��ѵ� �̰��� �ٷ� static�̴�.
////��ü ���� ��� ȣ���ϴ� ���ϱ�?
////this Ű���尡 ���� ������ ȣ�� �� �� �ִ�. �׷��� this�� ��� ����� ������ �Ұ����ϴ�.
////�׷��� �����ϰ� ���� ������ ����� �ִµ� �ٷ� static �����̴�.
//
//class CCore
//{
//private:
//	static CCore* g_pInst;//���� ���(������) Ŭ���� ���ο��� �� ������ �����ѵ�, �ϳ��� �ִ�!
//						//���� ���� ����� �ݵ�� �ʱ�ȭ�� �� �־�� �Ѵ�!! ���ϸ� ������
//
//public:
//	//���� ����Լ�, ��ü���� ȣ�� ����. �׷��� this Ű���尡 ���� ������,
////��� ������ ��� �Լ��� ������ �� ����.
//	static CCore* GetInstance() {//��ü �ϳ��� ����
//
//		
//		//���� ȣ�� �� ���
//		if (nullptr == g_pInst) {
//			g_pInst = new CCore;
//			
//		}
//
//		return g_pInst;//�ּҰ� ��ȯ
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
	//static CCore* GetInstance() {//�׳� �����ϰ� �ּҰ��� �������ָ� �ȴ�.
	//							//�ٵ� �̷��� ���� ���Ҷ� ���� ���� ���� ����.
	//	static CCore core;
	//
	//	return &core;
	//}
	SINGLE(CCore);

private:
	HWND		m_hWnd;			//���� ������ �ڵ�
	POINT		m_ptResolution; //���� ������ �ػ�
	HDC			m_hDC;		//���������쿡 �׸� DC

	CTexture*	m_pMemTex; //������ؽ���

	//���� ����ϴ� GDI Object
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];

	//�޴�
	HMENU		m_hMenu; //ToolScene������ ���

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
//���߿� ��� ����� ��ȣ�ɱ�? ������ �ƹ��� ����~
//���������� �� ����� ����!
//������Ʈ�� ũ�Ⱑ �׸� ũ�� �ʾƼ�.
//�ݺ��Ǵϱ� ��ũ�η� ������.