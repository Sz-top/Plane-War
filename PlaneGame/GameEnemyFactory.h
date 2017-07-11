#pragma once
#include "GameFactory.h"
class CGameEnemyFactory :
	public CGameFactory
{
public:
	CGameEnemyFactory(CGameManager* manager, CLevel* level);
	virtual ~CGameEnemyFactory();

	virtual int getCount();

	// ͨ�� CGameFactory �̳�
	virtual int switchObject() override;
	virtual int switchNthObject(int index) override;
	virtual CGameObject * createObject(int x, int y) override;
};

