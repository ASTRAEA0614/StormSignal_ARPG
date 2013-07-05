#include "Character.h"
#include "Window.h"

#ifndef _PLAYER
#define _PLAYER

const float MoveSpeed = 5.0f;

class Player : public Character
{
private:
	int SkillSet[3][3][4];//x,y,{���,���x��,�o���l,CD}
	vector<int*> SkillList;
	Window SkillWindow;
public:
	void Initialize(b2World *World,void* UserData,float Density,float Friction,int MaxHP);
	void Ctrl(void);//����
	void DrawSkillWindow(void);
};

#endif