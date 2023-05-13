#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim; //��� �ֳ׹̿���
	CAnimation*					m_pCurAnim;	//���� ������� �ִϸ��̼�
	CObject*					m_pOwner;	//�ִϸ��̼� ���� ������Ʈ
	bool						m_bRepeat;		//�ݺ��������

public:
	CObject* GetObj() { return m_pOwner; }
	CAnimation* GetCurAnim() { return m_pCurAnim; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);//����° �Ķ���ʹ� �ڸ��� ������.�׹�° �Ķ���ʹ� ����
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

