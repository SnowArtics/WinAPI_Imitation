#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim; //모든 애네미에션
	CAnimation*					m_pCurAnim;	//현재 재생중인 애니메이션
	CObject*					m_pOwner;	//애니메이션 소유 오브젝트
	bool						m_bRepeat;		//반복재생여부

public:
	CObject* GetObj() { return m_pOwner; }
	CAnimation* GetCurAnim() { return m_pCurAnim; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);//세번째 파라미터는 자르는 사이즈.네번째 파라미터는 간격
	void LoadAnimation(const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);

	//void OnSize(Vec2 _vSize);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

