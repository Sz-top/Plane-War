#pragma once
#include "Level.h"
#include "DataModel.h"
#include "GameBoardDefault.h"
#include "CommonFun.h"
#include "GameObject.h"
#include "Plane.h"
#include "resource.h"
#include "EnemyPlane.h"
#include "MyPlane.h"
#include "GameMyPlaneFactory.h"
#include "GameEnemyFactory.h"

#define enPlane 0
#define enBomb 1
#define minePlane 2
#define mineBomb 3
#define buff 4
using namespace Info;
class CGameManager
{
public:
	enum GameState {
		Start = 1,
		End = 2,
		Pause = 3,
		GodStart = 4
	};
protected:
	CGameMyPlaneFactory* myplaneFactory;
	CGameEnemyFactory* enemyplaneFactory;
protected:
	int NN = 0;
	CDataModel* model;
	CGameBoard* board;
	CMyPlane * myPlane;
	CLevel *level;
	LevelInfo info;
	int is_god;
	GameState state;
	CObList* m_ObjList;
	int height;
	int width;
	int cnt;
public:
	LevelInfo getLevelInfo() { return info; }
	CGameManager(int width = 0, int height = 0);
	void InitLevel(int index);
	void AI();
	void switchPlane();
	void HandleKeyMap();
	// �ж��Ƿ�����Ļ������
	int is_InRange(CGameObject* ob);
	void setRect(int width, int height);
	void registerObject(CString type, CGameObject* ob) {
		if(type == "enBomb")
			m_ObjList[enBomb].AddTail(ob);
		else if (type == "enPlane") {
			m_ObjList[enPlane].AddTail(ob);
		}
		else if (type == "mineBomb") {
			m_ObjList[mineBomb].AddTail(ob);
		}
	}
	void removeObject(CString type, POSITION ob) {
		if (type == "enBomb")
			m_ObjList[enBomb].RemoveAt(ob);
		else if (type == "minePlane") {
			m_ObjList[minePlane].RemoveAt(ob);
		}
		else if (type == "enPlane")
			m_ObjList[enPlane].RemoveAt(ob);
		else if (type == "mineBomb")
			m_ObjList[mineBomb].RemoveAt(ob);
	}
	CObList* getList() {
		return m_ObjList;
	}
	void draw(CDC *m_pMemDC);
	~CGameManager();
//	CPoint point;
public:
	GameState getState();
	void setState(GameState state);

	int getHeight();
	int getWidth();
	int StartGame(bool is_god);
	bool PauseGame();
	void LevelUp();
	bool StopGame();
};
