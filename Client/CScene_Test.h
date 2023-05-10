#pragma once
#include "CScene.h"
#include "CMonFactory.h"

class CObject;
class CTexture;
class CBackground;

class CScene_Test :
    public CScene
{
private:
    //�� ������ � ���� ������ ������ �� �ִ�.
    vector<vector<CBackground*> > m_vMap;

    //CBtnUI�� Ŭ���� ���콺 Ŀ���� ����ٴϴ� �ؽ��ĸ� ������ �ؽ���
    CTexture*                   m_pCursorIcon;
    MON_TYPE                    m_eMonType; //���� Ŭ���� �����г��� Ÿ���� ��������
    MON_NAME                    m_eMonName; //���� Ŭ���� ���� �г��� �̸��� ��������
    bool                        m_bTriggerCursor;//���� Ŀ���� ���� Ŀ������

    //�巡�� ���� ����
    Vec2    m_vDragStart;
    Vec2    m_vDragSize;
    bool    m_bDragOn;

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter();
    virtual void Exit();

public:
    const vector<vector<CBackground*> >& GetMaps() { return m_vMap; }

    vector<char> makeBridgeDirection(int _row, int _column, int _size);
    wstring makeBackgroundName(int _row, int _column);

    void LoadUI(const wstring& _strRelativePath, string _pageName);

public:
    void SetCursorIconTex(CTexture* _pTex, MON_TYPE _eMonType, MON_NAME _eMonName);

public:
    CScene_Test(int _row, int _column);
    ~CScene_Test();
};

