#pragma once

class CObject;//전방선언 컴파일을 빠르게 하기 위해서

#include "CMonFactory.h"

class CScene
{

private:
	wstring			m_strName;
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];//오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언

	UINT			m_iTileX;//타일 가로 개수
	UINT			m_iTileY;//타일 세로 개수

	CObject*		m_pPlayer; //현재씬의 플레이어

	//접근
	//m_arrObj[(UINT)GROUP_TYPE::END];

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	CObject* GetPlayer() { return m_pPlayer; }

	virtual void start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);

	virtual void Enter() = 0;//해당 씬에 진입시 호출
	virtual void Exit() = 0;//해당 씬을 탈출 시 호출

public:
	inline void AddObject(CObject* _pObj, GROUP_TYPE _eType) {		m_arrObj[(UINT)_eType].push_back(_pObj);	};
	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) {		return m_arrObj[(UINT)_eType];	}
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }


public:
	CScene();
	virtual ~CScene();
};

