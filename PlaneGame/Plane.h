#pragma once
#include "GameObject.h"
#include "GamePathArc.h"
#include "GamePathLine.h"
#include "GamePathDefault.h"
#include "Bomb.h"
#include "MyBomb.h"
#include "EnemyBomb.h"
#include "BloodBar.h"
class  CPlane :
	public CGameObject
{
public:
	CPlane(CGameManager* manager, int x = 0, int y = 0, int speed = 6);
	virtual ~CPlane();
	virtual BOOL move(CCommonFun::Direction direct);

	// ͨ�� CGameObject �̳�
	virtual BOOL Collided(POSITION pos)  override = 0;
	// ͨ�� CGameObject �̳�
	virtual BOOL draw(CDC* pDC) override = 0;
protected:
	int speed;
	bool is_fired;
	int blood;
	int team;
	int id;
	int cnt;
	CBloodBar* bloodbar;
public:
	// ���÷ɻ���ʹ�õ�ը��
	virtual BOOL set_bomb(CBomb* bomb);
protected:
	CBomb* bomb;
public:
	// ��������
	virtual BOOL attack(int n) = 0;
	// ͨ�� CGameObject �̳�
	int getHP() const;
	bool setHP(int hp);

};

