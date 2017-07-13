#include "stdafx.h"
#include "GameConfig.h"

CGameConfig::CGameConfig(CString file)
{
	std::ifstream config_doc(file, std::ifstream::binary);
	config_doc >> root;
	level_max = root["Levels"].size();
}
//��ȡ��������
Info::BackgroundInfo CGameConfig::GetBackGroundConfig(const int& index ) {
	Json::Value v = root["Backgrounds"];
	ASSERT(index <= v.size());
	v = v[index];
	Info::BackgroundInfo info;
	info.speed = v["speed"].asInt();
	info.BK_ID = v["BK_ID"].asInt();
	return info;
}
//��ȡ·������
Info::PathInfo CGameConfig::GetPathConfig(const int& index) {
	Json::Value v = root["Paths"];
	ASSERT(index <= v.size());
	v = v[index];
	Info::PathInfo info;
	info.id = v["id"].asInt();
	info.Name = v["Name"].asString();
	return info;
}
//��ȡը������
Info::BombInfo  CGameConfig::GetBombConfig(const int& index) {
	Json::Value v = root["Bombs"];
	ASSERT(index <= v.size());
	Info::BombInfo info;
	v = v[index];

	info.id = v["id"].asInt();
	info.Name = v["Name"].asString();
	info.speed = v["speed"].asInt();
	info.attack = v["attack"].asInt();
	info.Hitrate = v["Hitrate"].asDouble();
	Json::Value idinfo = v["pathID"];
	for (int i = 0; i < idinfo.size();i++)
		info.pathID.push_back(idinfo[i].asInt());
	return info;
}
//��ȡ�ɻ�����
Info::PlaneInfo  CGameConfig::GetPlaneConfig(const int& index) {
	Json::Value v = root["MyPlanes"];
	ASSERT(index <= v.size());
	v = v[index];
	Info::PlaneInfo info;
	info.id = v["id"].asInt();
	info.HP = v["HP"].asInt();
	info.speed = v["speed"].asInt();
	info.attack = v["attack"].asInt();
	Json::Value b = v["Bombs"];
	for (int i = 0; i < b.size(); i++) {
		info.bombs.push_back(b[i].asInt());
	}
	return info;
}
//��ȡ�л�����
Info::PlaneInfo  CGameConfig::GetEnemyConfig(const int& index) {
	Json::Value v = root["Enemys"];
	ASSERT(index <= v.size());
	v = v[index];
	Info::PlaneInfo info;
	info.id = v["id"].asInt();
	info.HP = v["HP"].asInt();
	info.speed = v["speed"].asInt();
	info.attack = v["attack"].asInt();
	Json::Value b = v["Bombs"];
	for (int i = 0; i < b.size(); i++) {
		info.bombs.push_back(b[i].asInt());
	}
	return info;
}
//��ȡBOSS���ã�index��1��ʼ
Info::PlaneInfo  CGameConfig::GetBossConfig(const int& index) {
	Json::Value v = root["Bosses"];
	ASSERT(index <= v.size());
	v = v[index];
	Info::PlaneInfo info;
	info.id = v["id"].asInt();
	info.HP = v["HP"].asInt();
	info.speed = v["speed"].asInt();
	info.attack = v["attack"].asInt();
	Json::Value b = v["Bombs"];
	for (int i = 0; i < b.size(); i++) {
		info.bombs.push_back(b[i].asInt());
	}
	return info;
}

//��ȡ�ȼ�����
Info::LevelInfo CGameConfig::GetLevelConfig(int index)
{
	Json::Value levels = root["Levels"]; //��ȡ�ȼ���������
	ASSERT(index - 1 <= levels.size());
	Json::Value &level = levels[index - 1];
	Info::LevelInfo info;
	info.level= level["Level"].asInt();

	info.backinfo = GetBackGroundConfig(level["Background"].asInt());
	info.Score = level["Score"].asInt();
	Json::Value a = level["MyPlaneID"];
	for (int i = 0; i < a.size(); i++) {
		info.myplaneID.push_back(a[i].asInt());
	}
	Json::Value b = level["EnemysID"];
	for (int i = 0; i < b.size(); i++) {
		info.enemyIDs.push_back(b[i].asInt());
	}
	Json::Value bosses = level["BossID"];
	for (int i = 0; i < bosses.size(); i++) {
		info.bossID.push_back(bosses[i].asInt());
		return info;
	}
	return info;
}


CGameConfig::~CGameConfig()
{

}
