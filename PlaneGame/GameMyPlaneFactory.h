#pragma once
#include "GameFactory.h"

#include "MyPlane.h"
class CGameMyPlaneFactory :
	public CGameFactory
{
protected:
public:

	CGameMyPlaneFactory(CGameManager* manager, CLevel* level);
	virtual ~CGameMyPlaneFactory();

	// ͨ�� CGameFactory �̳�
	virtual CGameObject * createObject(int x, int y) override;

	CGameObject * createObject(CGameObject * obj);

	// ͨ�� CGameFactory �̳�
	virtual int getCount() override;
};

