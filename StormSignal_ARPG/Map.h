#include <vector>
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

class Map
{
private:
	vector<string> MapData[14];//�e�L�X�g����ǂݍ��񂾃}�b�v�f�[�^���i�[
	vector<vector<string>> ScriptData;//����u���b�N�p�̃X�N���v�g���i�[
	vector<int> MapChips;//�}�b�v�`�b�v�̉摜
	Player PlayerData;//�v���C���[
	vector<Enemy> EnemyData;//�G�z��
	vector<Object> RigidBodies;//�}�b�v��ɐݒu����Ă���I�u�W�F�N�g�Q
	b2BodyDef GroundBodyDef;//�}�b�v�����蔻��
	b2Body* GroundBody;//�}�b�v�����蔻��
	b2PolygonShape GroundBox;//�}�b�v�����蔻��
	int Width;
public:
	void Initialize(b2World *World);//������
	void LoadMapData(string Pass);//�}�b�v�f�[�^���w��p�X�̃e�L�X�g����ǂݍ���
	void LoadScriptData(string Pass);//�X�N���v�g�f�[�^���w��p�X�̃e�L�X�g����ǂݍ���
	void CreateMap(b2World *World);//�}�b�v�f�[�^����}�b�v�𐶐�����
	void Step();//���t���[���s�������Q
	void Draw();//�}�b�v�A�v���C���[���̕`��
};

#endif