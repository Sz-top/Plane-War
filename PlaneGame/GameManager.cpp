#include "stdafx.h"
#include "GameManager.h" 
CGameManager::CGameManager(int width , int height) : width(width), height(height)
{
	myPlane = NULL;
	NN = 0;
	cnt = 0;
	level = new CLevel(1);
	myplaneFactory = new CGameMyPlaneFactory(this, level);
	enemyplaneFactory = new CGameEnemyFactory(this, level);

	InitLevel(1);
	board = new CGameBoardDefault(CPoint(0,0),width,height);
	model = new CDataModel(board);

	m_ObjList = new CObList[5];
}

//��ʼ���ؿ�
void CGameManager::InitLevel(int index) {
	CMyPlane::LoadImages();
	CMyBomb::LoadImages();
	CEnemyBomb::LoadImages();
	CEnemyPlane::LoadImages();
	if(myPlane)
		delete myPlane;
	info = level->getLevelInfo();
	int my_speed = level->getMyPlaneInfo(info.myplaneID[0]).speed;

	myPlane = (CMyPlane*)myplaneFactory->createObject(width / 2, height / 2);
	//������Ϸ
}

//ʵ������
void CGameManager::LevelUp() {
	int tmp = getLevelInfo().level;
	level = new CLevel(tmp + 1);
	InitLevel(tmp + 1);
}


//������Ϸ
void CGameManager::draw(CDC * m_pMemDC) {
	//TRACE("%d %d\n", game_manager->getWidth(), game_manager->getHeight());
	//m_pMemDC->FillSolidRect(0, 0, getWidth(), getHeight(), RGB(84, 142, 239));
	CDC memdc;
	memdc.CreateCompatibleDC(m_pMemDC);
	//���Ʊ������
	CBitmap   bitmap;
	
	bitmap.LoadBitmap(getLevelInfo().backinfo.BK_ID);   //���IDB_BITMAP1Ҫ�Լ����
	BITMAP bitinfo;
	bitmap.GetBitmap(&bitinfo);
	//CBrush   brush;
	//brush.CreatePatternBrush(&bitmap);
	//CBrush*   pOldBrush = m_pMemDC->SelectObject(&brush);
	memdc.SelectObject(&bitmap);
	m_pMemDC->StretchBlt(0, NN, width, height, &memdc, 0, 0, bitinfo.bmWidth, bitinfo.bmHeight, SRCCOPY);
	m_pMemDC->StretchBlt(0, -height + NN, width, height, &memdc, 0, 0, bitinfo.bmWidth, bitinfo.bmHeight, SRCCOPY);

	//m_pMemDC->Rectangle(0, NN, width, height);  // ��Щ�������Ե���ͼƬ���λ�úʹ�С
	//m_pMemDC->Rectangle(0, -height + NN, width, height);  // ��Щ�������Ե���ͼƬ���λ�úʹ�С
	// m_pMemDC->SelectObject(pOldBrush);
	NN += getLevelInfo().backinfo.speed;
	if ( NN > height) NN = 0;
	//���Ʊ����İ�
	model->push();
	board->draw(m_pMemDC);

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
			if (pBomb->Collided(_mPos, NULL)) {
				delete pBomb;
				pBomb = NULL;
			}
			if (myPlane->Collided(NULL, pBomb) && !is_god) {
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
				if (pBomb->Collided(_mPos1, NULL)) {
					delete pBomb;
					pBomb = NULL;
				}
				if (pPlane->Collided(_mPos, pBomb)) {
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
			if (myPlane->Collided(NULL, pPlane)&&!is_god) {
				delete myPlane;
				myPlane = NULL;
			}
			if (pPlane->Collided(_mPos, myPlane)) {

				delete pPlane;
				pPlane = NULL;
			}
		}
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

}
void CGameManager::AI() {
	cnt++;
	int t = rand() % 60 + 1;
	if (cnt%t == 0) {
		enemyplaneFactory->switchNthObject(rand() % enemyplaneFactory->getCount());
		CEnemyPlane* ep1 = (CEnemyPlane*)enemyplaneFactory->createObject(rand() % this->width, 0);
		this->registerObject(L"enPlane",ep1);
		ep1->attack(5);
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
		//int attack = level->getMyPlaneInfo(getLevelInfo().myplaneID[0]).attack;
		myPlane->attack(5);
	}
	if (GetKeyState('R') & 0x8000?1:0) {
		//int attack = level->getMyPlaneInfo(getLevelInfo().myplaneID[0]).attack;
		myplaneFactory->switchObject();
		myPlane = (CMyPlane*)myplaneFactory->createObject(myPlane);
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

//�����������н����ڴ��ͷ�
CGameManager::~CGameManager()
{
	delete level;
	delete board;
	delete model;
	delete m_ObjList;
	delete myPlane;
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
