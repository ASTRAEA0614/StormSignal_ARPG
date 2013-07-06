#include "Character.h"
#include "Window.h"

#ifndef _PLAYER
#define _PLAYER

const float MoveSpeed = 5.0f;

class Player : public Character
{
private:
	int SkillSet[3][3][4];//x,y,{種類,レベル,経験値,CD}
	vector<int*> SkillList;
	Window SkillWindow;
	vector<Window> SkillPanels;
	vector<Image_2D> SkillImages;
public:
	void Initialize(b2World *World,void* UserData,float Density,float Friction,int MaxHP);
	void Ctrl(void);//操作
	void DrawSkillWindow(void);
};

#endif