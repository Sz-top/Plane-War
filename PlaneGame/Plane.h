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
	CPlane(CGameManager* manager, int attack_value, int x = 0, int y = 0, int speed = 6, int blood = 300);
	virtual ~CPlane();
	virtual BOOL move(CCommonFun::Direction direct);
	// ͨ�� CGameObject �̳�
	virtual BOOL Collided(POSITION pos, CGameObject* obj)  override = 0;
	// ͨ�� CGameObject �̳�
	virtual BOOL draw(CDC* pDC) override = 0;
protected:
	int speed;
	bool is_fired;
	int blood;
	int team;
	int bomb;
	int index;
	int cnt;
	CBloodBar* bloodbar;
public:
	virtual void setIndex(int index) {
		this->index = index;
	}
	// ���÷ɻ���ʹ�õ�ը��
	virtual BOOL switch_bomb() = 0;
	virtual BOOL switch_nth_bomb() = 0;
protected:
	CBomb* bomb;
public:
	// ��������
	virtual BOOL attack(int n) = 0;
	// ͨ�� CGameObject �̳�
	int getHP() const;
	bool setHP(int hp);
};