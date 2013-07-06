#include "Physics2DImage.h"

#ifndef _CHARACTER
#define _CHARACTER

class HitBox;

const int Skill_None_None = 0;
const int Skill_Sword_Front = 1;

const string SkillValueNames[] = {"Skill_None_None",
							"Skill_Sword_Front"};

const string SkillNames[] = {"����",
							"�O���֌���U�艺�낷(��)"};

const string SkillInfo[] = {"�X�L����ݒ肵�܂���B\n�K�v���� : ���� CD : ����",
							"�O���֌���U�艺�낵�܂��B\n�K�v���� : �� CD : ����"};


const int Equipment_None_None = 0;
const int Equipment_Sword_Normal = 1;
const int Equipment_Sword_Flame = 2;

const string EquipmentValueNames[] = {"Equipment_None_None",
							"Equipment_Sword_Normal",
							"Equipment_Sword_Flame"};

const string EquipmentNames[] = {"����",
							"�ʏ팕",
							"����"};

const string EquipmentInfo[] = {"�������g�p���܂���B\n������� : ����",
							"�ʏ팕��p���čU�����s���܂��B\n������� : ��",
							"������p���čU�����s���܂��B\n������� : ��"};

int SearchEquipment();

class Character : public Physics2DImage
{
private:
	
public:
	int MaxHP;
	int HP;
	int State;
	int StateTime;
	int Time;
	static vector<Character*> CharacterList;
	static vector<HitBox> HitBoxList;
	static vector<vector<int>> AnimeGraphs;
	static vector<vector<int>> EquipmentGraphs;

	void InitChara(b2World *World,void* UserData,float Density,float Friction,int MaxHP);
	virtual bool UseSkill(int SkillNumber,int EquipmentNumber);
	virtual void Step(void);
};

#endif