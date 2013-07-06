#include "Player.h"
#include "Functions.h"
#include "ConstantValue.h"
#include <DxLib.h>

void Player::Initialize(b2World *World,void* UserData,float Density,float Friction,int MaxHP)
{
	InitChara(World,UserData,Density,Friction,MaxHP);

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			SkillSet[i][j][0] = Skill_Sword_Front;
			SkillSet[i][j][1] = 0;
			SkillSet[i][j][2] = 0;
			SkillSet[i][j][3] = 0;
		}
	}

	GetShape()->SetAsBox(12/2/Box_Rate,24/2/Box_Rate);

	GetFixtureDef()->shape = GetShape();
	GetFixtureDef()->density = Density;
	GetFixtureDef()->friction = Friction;

	GetBody()->DestroyFixture(GetFixture());
	GetBody()->CreateFixture(GetFixtureDef());

	Center_x = 64;
	Center_y = 52;

	//スキル設定ウィンドウ作成
	SkillWindow.Initialize(25,25,Screen_Width-50,Screen_Height-50,Black,LightBlack);
	SkillWindow.Visible = false;

	int Length = AnimeGraphs.size();
	for(int i=0;i<Length;i++)
	{
		Image_2D Image;
		Image.Graph.reserve(AnimeGraphs[i].size());
		copy(AnimeGraphs[i].begin(),AnimeGraphs[i].end(),back_inserter(Image.Graph));
		Image.Initialize();
		Image.Anime_Speed = 500;
		SkillImages.push_back(Image);
		
		Window Panel;
		Panel.Initialize(0,0,64,64,Black,LightBlack);
		SkillPanels.push_back(Panel);
	}
}

void Player::Ctrl(void)
{
	//スキルウィンドウトグル
	if(CheckKeyDown(KEY_INPUT_LALT))SkillWindow.Visible = 1 - SkillWindow.Visible;

	//スキル使用中は行動できない
	if(State != Skill_None_None)return;

	b2Vec2 Vect = GetBody()->GetLinearVelocity();

	//移動関連
	if(CheckHitKey(KEY_INPUT_LEFT))
	{
		Vect.x = -MoveSpeed;
		Direction = -1;
	}
	if(CheckHitKey(KEY_INPUT_RIGHT))
	{
		Vect.x = MoveSpeed;
		Direction = 1;
	}
	if(CheckKeyDown(KEY_INPUT_SPACE))Vect.y = -MoveSpeed*2;

	//スキル使用
	int Key[9] = {KEY_INPUT_Q,KEY_INPUT_W,KEY_INPUT_E,
					KEY_INPUT_A,KEY_INPUT_S,KEY_INPUT_D,
					KEY_INPUT_Z,KEY_INPUT_X,KEY_INPUT_C};

	for(int i=0;i<9;i++)
	{
		if(CheckKeyDown(Key[i]))
		{
			UseSkill(SkillSet[i%3][(int)(i/3)][0]);
			SkillSet[i%3][(int)(i/3)][3] = GetNowCount();
		}
	}

	GetBody()->SetLinearVelocity(Vect);
}

void Player::DrawSkillWindow(void)
{
	if(!SkillWindow.Visible)return;

	SkillWindow.ReWindow();
	SkillWindow.SetDrawThisWindow();

	DrawBox(15,10,110,35,Black,false);

	int Length = AnimeGraphs.size();
	for(int i=1;i<Length;i++)
	{
		SkillPanels[i].ReWindow();
		SkillPanels[i].SetDrawThisWindow();

		SkillImages[i].x = SkillPanels[i].GetWidth()/2;
		SkillImages[i].y = SkillPanels[i].GetHeight()/2+24;
		SkillImages[i].Draw(true);
	}

	SkillWindow.SetDrawThisWindow();

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i>0)
			{
				//DrawRotaGraph2(15+j*70+32,50+i*70+32,64,40,1,0,AnimeGraphs[SkillSet[j][i-1][0]][0],true);
				SkillPanels[SkillSet[j][i-1][0]].x = 15+j*70;
				SkillPanels[SkillSet[j][i-1][0]].y = 50+i*70;
				SkillPanels[SkillSet[j][i-1][0]].Draw();
			}
			DrawBox(15+j*70,50+i*70,15+j*70+64,50+i*70+64,Black,false);
		}
	}

	DrawBox(15,330,15+256,390,Black,false);

	SetDrawScreen(DX_SCREEN_BACK);
	SkillWindow.Draw();
}