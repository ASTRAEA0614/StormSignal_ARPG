﻿#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Object.h"

using namespace std;

#ifndef _MAP
#define _MAP

const string Mapchip_Blank = "00";
const string Mapchip_Clay = "01";
const string Mapchip_ClayFloor = "02";
const string Mapchip_Woodbox = "03";
const string Mapchip_Switch1 = "04";
const string Mapchip_Switch2 = "05";

const string Mapchip_TrainingBag = "10";

const string Mapchip_Player = "99";

const string Trigger_Hit = "Hit";
const string Trigger_Hitted = "Hitted";
const string Trigger_Touch = "Touch";
const string Trigger_Flag = "Flag";
const string Trigger_Flagged = "Flagged";

const string Action_Redraw = "Redraw";
const string Action_Flag = "Flag";
const string Action_Delete = "Delete";

class Map
{
private:
	vector<string> MapData[14];//テキストから読み込んだマップデータを格納
	vector<vector<string>> ScriptData;//特殊ブロック用のスクリプトを格納
	vector<b2Fixture*> MapChipFixtures;//特殊ブロック一つ一つの当たり判定
	vector<string> FixtureDataToMapChip;//特殊ブロックとb2Fixtureの紐付
	vector<Image_2D> MapChips;//マップチップの画像
	Player PlayerData;//プレイヤー
	vector<Enemy> EnemyData;//敵配列
	vector<Object> RigidBodies;//マップ上に設置されているオブジェクト群
	b2BodyDef GroundBodyDef;//マップ当たり判定
	b2Body* GroundBody;//マップ当たり判定
	b2PolygonShape GroundBox;//マップ当たり判定
	int Width;
public:
	void Initialize(b2World *World);//初期化
	void LoadMapData(string Pass);//マップデータを指定パスのテキストから読み込む
	void LoadScriptData(string Pass);//スクリプトデータを指定パスのテキストから読み込む
	void CreateMap(b2World *World);//マップデータからマップを生成する
	void Step();//毎フレーム行う処理群
	void Draw();//マップ、プレイヤー等の描画
};

#endif