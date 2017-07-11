#include "stdafx.h"
#include "GameMyPlaneFactory.h"
CGameMyPlaneFactory::CGameMyPlaneFactory(CGameManager* manager, CLevel* level) : CGameFactory(manager,level)
{
	//level->getBombInfo(0);
}

CGameMyPlaneFactory::~CGameMyPlaneFactory()
{
}
int CGameMyPlaneFactory::switchObject()
{
	this->index++;
	index %= getCount();
	return index;
}

int CGameMyPlaneFactory::switchNthObject(int index)
{
	if (index > getCount())return -1;
	this->index = index;
	return index;
}
CGameObject * CGameMyPlaneFactory::createObject(CGameObject * obj)
{
	CPlane* plane = (CPlane*)obj;
	plane->setIndex(index);
	return plane;
}
int CGameMyPlaneFactory::getCount()
{
	return level->getLevelInfo().myplaneID.size();
}
CGameObject * CGameMyPlaneFactory::createObject(int x, int y)
{
	Info::LevelInfo lInfo = level->getLevelInfo();
	Info::PlaneInfo info = level->getMyPlaneInfo(lInfo.myplaneID[index]);
	CPlane * plane = new CMyPlane(manager, x, y, info.speed,info.HP, info.attack);
	plane->setIndex(lInfo.myplaneID[index]);
	plane->Initial();
	return plane;
}
