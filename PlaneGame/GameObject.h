#pragma once
#include "CommonFun.h"
class CGameManager;
class CGameObject : public CObject
{
public:
	CGameObject(CGameManager* manager, int, int, int);
	virtual ~CGameObject();
protected:
	int index;
	CGameManager * manager;
	CPoint point;
	int attack_value;
	int height;
	int width;
public:

	virtual int get_attack() {
		return attack_value;
	}
	// ��ȡ�������������
	CRect getRect() const{
		return CRect(point, CPoint(point.x + width, point.y + height));
	}
	virtual void setIndex(int index) {
		this->index = index;
	}
	// ��ײ����
	virtual BOOL Collided(POSITION pos, CGameObject *obj) = 0;
	// ���ƶ���
	virtual BOOL draw(CDC* pDC) = 0;
	// ��ʼ������
	virtual BOOL Initial() = 0;

};

