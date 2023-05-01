#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm {
	Vec2 vLT;//�ش� �������� LeftTop
	Vec2 vSlice;//�ش��������� ũ��
	Vec2 vOffset;
	float fDuration;//�ش� �������� ��µǴ� �ð�
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;//�ִϸ��̼��� ����ϴ� �ؽ���
	vector<tAnimFrm>	m_vecFrm;//�������������
	int					m_iCurFrm;//���� ������
	float				m_fAccTime;//�ð��� ������ ����

	bool				m_bFinish;//������� ������ ����

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }

	void setFrame(int _iFrameIdx) { 
		m_bFinish = false; 
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep,float _fDuration, UINT _iFrameCount);

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};
