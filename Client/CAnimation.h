#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm {
	Vec2 vLT;//해당 프레임의 LeftTop
	Vec2 vSlice;//해당프레임의 크기
	Vec2 vOffset;
	float fDuration;//해당 프레임이 출력되는 시간
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;//애니메이션이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;//모든프레임정보
	int					m_iCurFrm;//현재 프레임
	float				m_fAccTime;//시간을 누적할 변수

	bool				m_bFinish;//재생끝에 도달한 여부

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

