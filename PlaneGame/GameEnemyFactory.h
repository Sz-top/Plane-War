#pragma once
#include "GameFactory.h"
#include "EnemyPlane.h"
class CGameEnemyFactory :
	public CGameFactory
{
public:
	CGameEnemyFactory(CGameManager* manager, CLevel* level);
	virtual ~CGameEnemyFactory();
	virtual int getCount();

	virtual CGameObject * createObject(int x, int y) override;

	// ͨ�� CGameFactory �̳�
	virtual CGameObject * createObject(CGameObject * obj) override;
};

