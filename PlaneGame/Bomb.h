#pragma once
#include "GameObject.h"
#include "GamePath.h"
class CBomb :
	public CGameObject
{
protected:
	CPoint point0;
	static CImageList m_Images;
	int speed;
	CGamePath* path;
public:
	CBomb(CGameManager* manager, int x = 0, int y = 0, int speed = 6, double offset = 0);
	virtual ~CBomb();
	BOOL setPoint(CPoint point);
	// ͨ�� CGameObject �̳�
	virtual BOOL Collided() const override;
	virtual BOOL draw(CDC * pDC) override;
	void setPath(CGamePath* path) {
		if (this->path != NULL)
			delete path;
		this->path = path;

	}
	virtual void getPath(int& x, int& y, const int& s);
	// ͨ�� CGameObject �̳�
	 static BOOL LoadImages();

	 // ͨ�� CGameObject �̳�
	 virtual BOOL Initial() override;
protected:
	double offset;
public:
	// ��ȡ��ը����ƫ�ƶ�,���ڸı�ը���켣
	double getOffset() {
		return offset;
	}

	void setOffset(double offset)
	{
		this->offset = offset;
	}
};


