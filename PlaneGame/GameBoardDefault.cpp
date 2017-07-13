#include "stdafx.h"
#include "GameBoardDefault.h"

CGameBoardDefault::CGameBoardDefault(CDataModel* model, CPoint point, int width, int height): CGameBoard(model, point,width,height)
{

}


CGameBoardDefault::~CGameBoardDefault()
{
}

void CGameBoardDefault::draw(CDC * pDC)
{
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkColor(RGB(0, 0, 0));
	CString s;
	s.Format(L"%d", model->getScore());
	pDC->TextOutW(point.x, point.y, L"������" + s);
	s.Format(L"%d", model->getLevel());
	pDC->TextOutW(point.x , point.y + 30, L"�ȼ���" + s);
	s.Format(L"%d", model->getSleepTime());
	pDC->TextOutW(point.x, point.y + 60, L"������ȴ��" + s);

}

//void CGameBoardDefault::update(int n, ...) {
//	va_list pvar;
//	va_start(pvar, n);
//	int t = va_arg(pvar, int);
//	va_end(pvar);
//}