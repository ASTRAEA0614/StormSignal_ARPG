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


const int Equipment_Sword_Normal = 0;
const int Equipment_Sword_Flame = 1;

const string EquipmentValueNames[] = {"Equipment_Sword_Normal",
							"Equipment_Sword_Flame"};

const string EquipmentNames[] = {"�ʏ팕",
							"����"};

const string EquipmentInfo[] = {"�ʏ팕��p���čU�����s���܂��B\n������� : ��",
							"������p���čU�����s���܂��B\n������� : ��"};


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
	static vector<vector<int>> LoadAnimeGraphs();

	void InitChara(b2World *World,void* UserData,float Density,float Friction,int MaxHP);
	virtual bool UseSkill(int Number);
	virtual void Step(void);
};

#endif