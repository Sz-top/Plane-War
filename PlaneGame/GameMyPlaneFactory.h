#pragma once
#include "GameFactory.h"
class CGameMyPlaneFactory :
	public CGameFactory
{
protected:
public:

	CGameMyPlaneFactory(CGameManager* manager, CLevel* level);
	virtual ~CGameMyPlaneFactory();

	// ͨ�� CGameFactory �̳�
	virtual CGameObject * createObject(int x, int y) override;

	// ͨ�� CGameFactory �̳�
	virtual int switchObject() override;
	virtual int switchNthObject(int index) override;
	CGameObject * createObject(CGameObject * obj);

	// ͨ�� CGameFactory �̳�
	virtual int getCount() override;
};

