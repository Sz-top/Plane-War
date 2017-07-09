#include "stdafx.h"
#include "GameManager.h" 
CGameManager::CGameManager(int width , int height) : width(width), height(height)
{
	CLevel v;
	cnt = 0;
	shoot_mode = 1;
	board = new CGameBoardDefault(CPoint(0,0),width,height);
	model = new CDataModel(board);
	m_ObjList = new CObList[5];
	CMyPlane::LoadImages();
	CMyBomb::LoadImages();
	CEnemyBomb::LoadImages();
	CEnemyPlane::LoadImages();
	myPlane = new CMyPlane(this,width/2,height/2,6);
	//������Ϸ
	myPlane->Initial();
}
void CGameManager::draw(CDC * m_pMemDC) {
	//TRACE("%d %d\n", game_manager->getWidth(), game_manager->getHeight());
	//m_pMemDC->FillSolidRect(0, 0, getWidth(), getHeight(), RGB(84, 142, 239));
	
	//���Ʊ������
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BG1);   //���IDB_BITMAP1Ҫ�Լ����
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = m_pMemDC->SelectObject(&brush);
	m_pMemDC->Rectangle(0, 0, width, height);  // ��Щ�������Ե���ͼƬ���λ�úʹ�С
	m_pMemDC->SelectObject(pOldBrush);
	
	//���Ʊ����İ�
	model->push();
	board->draw(m_pMemDC);

	scroll_speed+=1;
	scroll_speed;
	if (myPlane)
		myPlane->draw(m_pMemDC);
	else {
		StopGame();
		return;
	}

	//�����ӵ�/ը��
	POSITION mPos = NULL, _mPos = NULL;
	CObList* list = getList();

	for (mPos = list[enBomb].GetHeadPosition(); (_mPos = mPos) != NULL; ) {
		if (!myPlane) {
			return;
		}
		CEnemyBomb * pBomb = (CEnemyBomb*)list[enBomb].GetNext(mPos);
		CRect tmpRect;
		ASSERT(pBomb);
		if (tmpRect.IntersectRect(&pBomb->getRect(), myPlane->getRect())) {
			if (pBomb->Collided(_mPos)) {
				delete pBomb;
				pBomb = NULL;
			}
			if (myPlane->Collided(NULL) && !is_god) {
				delete myPlane;
				myPlane = NULL;
			}
		}
		if (!pBomb) continue;

		if (is_InRange(pBomb)) {
			this->removeObject(L"enBomb", _mPos);
			delete pBomb;
			pBomb = NULL;
		}
		else
			pBomb->draw(m_pMemDC);
	}

	for (mPos = list[mineBomb].GetHeadPosition(); (_mPos = mPos) != NULL; ) {
		if (!myPlane) {
			return;
		}
		CMyBomb * pBomb = (CMyBomb*)list[mineBomb].GetNext(mPos);
		CRect tmpRect;
		ASSERT(pBomb);
		CRect brect = pBomb->getRect();
		if (!pBomb) continue;

		if (is_InRange(pBomb)) {
			this->removeObject(L"mineBomb", _mPos);
			delete pBomb;
			pBomb = NULL;
		}
		else
			pBomb->draw(m_pMemDC);
	}

	mPos = NULL;
	_mPos = NULL;
	//���Ƶл�����������ײ
	for (mPos = list[enPlane].GetHeadPosition(); (_mPos = mPos) != NULL; ) {
		CEnemyPlane * pPlane = (CEnemyPlane*)list[enPlane].GetNext(mPos);

		pPlane->attack(1);
		ASSERT(pPlane);
		CRect prect = pPlane->getRect();
		int is_exist = 1;
		POSITION mPos1 = NULL, _mPos1 = NULL;
		for (mPos1 = list[mineBomb].GetHeadPosition(); (_mPos1 = mPos1) != NULL; ) {
			CRect tmpRect;
			CMyBomb * pBomb = (CMyBomb*)list[mineBomb].GetNext(mPos1);
			ASSERT(pBomb);
			CRect brect = pBomb->getRect();
			if (tmpRect.IntersectRect(&brect, prect)) {
				if (pBomb->Collided(_mPos1)) {
					delete pBomb;
					pBomb = NULL;
				}
				if (pPlane->Collided(_mPos)) {
					delete pPlane;
					pPlane = NULL;
					break;
				}
				is_exist = 0;
			}

		}
		CRect tmpRect;
		if (!is_exist)
			continue;
		if (!myPlane || !pPlane)continue;
		if (is_InRange(pPlane)) {
			this->removeObject(L"enPlane", _mPos);
			delete pPlane;
			pPlane = NULL;
		}
		else
			pPlane->draw(m_pMemDC);
		if (pPlane && myPlane && tmpRect.IntersectRect(pPlane->getRect(), myPlane->getRect())) {
			if (myPlane->Collided(NULL)&&!is_god) {
				delete myPlane;
				myPlane = NULL;
			}
			if (pPlane->Collided(_mPos)) {

				delete pPlane;
				pPlane = NULL;
			}
		}
	}
}
void CGameManager::AI() {
	cnt++;
	int t = rand() % 20 + 1;
	if (cnt%t == 0) {
		CEnemyPlane* ep1 = new CEnemyPlane(this, rand() % this->width, 0);
		ep1->Initial();
		this->registerObject(L"enPlane",ep1);
		ep1->attack(1);
		cnt = 0;
	}
}
void CGameManager::switchPlane() {

}

void CGameManager::HandleKeyMap()
{
	if (!myPlane)
		return;
	int dir = is_InRange(myPlane);
	if (GetKeyState(VK_LEFT) < 0) {
		if (!(dir & CCommonFun::L))
			myPlane->move(CCommonFun::L);
	}
	if (GetKeyState(VK_RIGHT) < 0) {
		if (!(dir & CCommonFun::R))
			myPlane->move(CCommonFun::R);
	}
	if (GetKeyState(VK_UP) < 0) {
		if (!(dir & CCommonFun::U))
			myPlane->move(CCommonFun::U);
	}
	if (GetKeyState(VK_DOWN) < 0) {
		if (!(dir & CCommonFun::D))
			myPlane->move(CCommonFun::D);
	}
	if (GetKeyState(VK_TAB) < 0) {
		switchPlane();
	}
	if (GetKeyState(VK_SPACE) < 0) {
		myPlane->attack(10);
	}
}
// �ж��Ƿ�����Ļ������
int CGameManager::is_InRange(CGameObject* ob)
{
	int res = 0;
	ASSERT(ob);
	CRect& rect = ob->getRect();
	if (rect.right > width) res |= CCommonFun::R;
	if (rect.left < 0)res |= CCommonFun::L;
	if (rect.top < 0)res |= CCommonFun::U;
	if (rect.bottom > height)res |= CCommonFun::D;
	return res;
}

void CGameManager::setRect(int w, int h)
{
	width = w;
	height = h;
}

CGameManager::~CGameManager()
{
}


CGameManager::GameState CGameManager::getState()
{
	return state;
}

void CGameManager::setState(GameState state)
{
	this->state = state;
}

int CGameManager::getHeight()
{
	return height;
}


int CGameManager::getWidth()
{
	return width;
}

int CGameManager::StartGame(bool is_god)
{
	this->setState(GameState::Start);
	this->is_god = is_god;
	return 0;
}


bool CGameManager::PauseGame()
{
	this->setState(GameState::Pause);
	return false;
}


bool CGameManager::StopGame()
{
	this->setState(GameState::End);
	return false;
}
