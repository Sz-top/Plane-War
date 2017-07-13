#include "stdafx.h"
#include "GameMyBombFactory.h"


CGameMyBombFactory::CGameMyBombFactory(CGameManager* manager, CLevel* level, int pindex) : CGameFactory(manager, level)
{
	pInfo = level->getMyPlaneInfo(pindex);
	index = 0; //index������Դ����ţ�ͼƬ�����
}

CGameMyBombFactory::~CGameMyBombFactory()
{
}

int CGameMyBombFactory::getCount()
{
	return pInfo.bombs.size();
}
void CGameMyBombFactory::setLevel(CLevel* level, int pindex) {
	CGameFactory::setLevel(level);
	pInfo = level->getMyPlaneInfo(pindex);
}

CGameObject * CGameMyBombFactory::createObject(int x, int y,double offset)
{
	Info::BombInfo info = level->getBombInfo(pInfo.bombs[index]);
	CBomb * bomb = new CMyBomb(manager, x, y, info.speed, offset, info.attack);
	bomb->setIndex(pInfo.bombs[index]);
	bomb->Initial();
	return bomb;
}

CGameObject * CGameMyBombFactory::createObject(CGameObject * obj)
{
	Info::BombInfo info = level->getBombInfo(pInfo.bombs[index]);
	CBomb * bomb = (CBomb*)obj;
	bomb->setIndex(pInfo.bombs[index]);
	return bomb;
}

