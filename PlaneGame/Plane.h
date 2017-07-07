#pragma once
#include "GameObject.h"
#include "BombRight.h"
#include "GamePathArc.h"
#include "GamePathLine.h"
#include "GamePathDefault.h"
class  CPlane :
	public CGameObject
{
public:
	CPlane(CGameManager* manager, int x = 0, int y = 0, int speed = 6);
	virtual ~CPlane();
	virtual BOOL move(CCommonFun::Direction direct);

	// ͨ�� CGameObject �̳�
	BOOL Collided(POSITION pos)  override;
	// ͨ�� CGameObject �̳�
	virtual BOOL draw(CDC* pDC) override;
protected:
	static CImageList m_Images;
	int speed;
	bool is_fired;
	int blood;
	int team;
	int id;
	int cnt;


public:
	// ���÷ɻ���ʹ�õ�ը��
	virtual BOOL set_bomb(CBomb bomb);
protected:
	CBomb bomb;
public:
	// ��������
	virtual BOOL attack();
	virtual BOOL attack(int n);

	// ͨ�� CGameObject �̳�
	static  BOOL LoadImages();

	// ͨ�� CGameObject �̳�
	virtual BOOL Initial() override;
	virtual int getHP() const;
	virtual bool setHP(int hp);

};

