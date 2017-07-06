#pragma once
#include "CommonFun.h"
class CGameManager;
class CGameObject : public CObject
{
public:
	CGameObject(CGameManager* manager, int, int);
	virtual ~CGameObject();
protected:
	CGameManager * manager;
	CPoint point;
	int height;
	int width;
public:
	// ��ȡ�������������
	CRect getRect() const{
		return CRect(point, CPoint(point.x + width, point.y + height));
	}
	// ��ײ����
	virtual BOOL Collided()const = 0;
	// ���ƶ���
	virtual BOOL draw(CDC* pDC) = 0;
	// ��ʼ������
	virtual BOOL Initial() = 0;

};

