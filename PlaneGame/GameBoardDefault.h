#pragma once
#include "GameBoard.h"
class CGameBoardDefault :
	public CGameBoard
{
public:
	CGameBoardDefault(CPoint point, int width, int height);
	virtual ~CGameBoardDefault();

	// ͨ�� CGameBoard �̳�
	virtual void draw(CDC * pDC) override;
	virtual void update(int n , ...) override;
};

