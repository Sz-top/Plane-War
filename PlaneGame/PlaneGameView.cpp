
// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PlaneGame.h"
#endif

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_MOVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView(): game_manager(NULL), m_pDC(NULL), m_pMemDC(NULL)
{
	// TODO: �ڴ˴���ӹ������

}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������


void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	InitGame();
	// TODO: �ڴ����ר�ô����/����û���
}
void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CPlaneGameView::InitGame()
{
	CView::OnInitialUpdate();

	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	CRect rect;
	this->GetClientRect(&rect);
	game_manager = new CGameManager(rect.right - rect.left, rect.bottom - rect.top);
	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC, game_manager->getWidth(), game_manager->getHeight());

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	//��������(ս��)
	game_manager->StartGame(true);
	SetTimer(1, 20, NULL);
	
	return TRUE;
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (game_manager->getState() ==  CGameManager::End) {
		KillTimer(1);
		return;
	}
	game_manager->HandleKeyMap();
	game_manager->draw(m_pMemDC);
	game_manager->AI();
	m_pDC->BitBlt(0, 0, game_manager->getWidth(), game_manager->getHeight(), m_pMemDC, 0, 0, SRCCOPY);
	CView::OnTimer(nIDEvent);
}

void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	//delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
	this->KillTimer(1);
	// TODO: �ڴ˴������Ϣ����������
}

void CPlaneGameView::OnMove(int x, int y)
{
	CView::OnMove(x, y);
	//TRACE("Moved");
	// TODO: �ڴ˴������Ϣ����������
}

//BUG:��Ļ����ı���������
void CPlaneGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (game_manager != NULL) {
		CRect rect;
		this->GetClientRect(&rect);
		game_manager->setRect(rect.right - rect.left, rect.bottom - rect.top);
	}


	// TODO: �ڴ˴������Ϣ����������
}

void CPlaneGameView::OnMove(UINT fwSide, LPRECT pRect)
{
	CView::OnMoving(fwSide, pRect);
	//TRACE("Moving\n");

	// TODO: �ڴ˴������Ϣ����������
}
