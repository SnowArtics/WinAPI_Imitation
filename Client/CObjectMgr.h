#pragma once

class CObject;

class CObjectMgr
{
	SINGLE(CObjectMgr);
private:
	CObject* m_pFocusedObject;

public:
	void update();

private:
	
};

