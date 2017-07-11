#include "stdafx.h"
#include "Plane.h"
#include "resource.h"
#include "GameManager.h"

CPlane::CPlane(CGameManager* manager, int attack_value, int x, int y,int speed, int blood) : CGameObject(manager, x, y, attack_value), speed(speed),blood(blood)
{
	team = 0;
	index = 0;
	cnt = 0;
}
BOOL CPlane::move(CCommonFun::Direction direct) {
	switch (direct)
	{
	case CCommonFun::U:
		point.y -= speed;
		break;
	case CCommonFun::D:
		point.y += speed;
		break;
	case CCommonFun::L:
		point.x -= speed;
		break;
	case CCommonFun::R:
		point.x += speed;
		break;
	default:
		break;
	}
	return TRUE;
}
CPlane::~CPlane()
{
	//ע���ڴ�й©
}



int CPlane::getHP() const
{
	return blood;
}

//��Ѫ��С��0������false;
bool CPlane::setHP(int hp)
{
	blood += hp;
	if (blood <= 0) {
		blood = 0;
		return false;
	}
	return true;
}

