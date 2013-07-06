#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "Box2D/Box2D.h"
#include "DebugDraw.h"
#include "DxLib.h"
#include "Functions.h"
#include "ConstantValue.h"
#include "Font.h"
#include "Player.h"
#include "Enemy.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine, int nCmdShow )
{
	//�E�B���h�E���[�h��ύX����
	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);

	//��ʃ��[�h
	SetGraphMode(Screen_Width,Screen_Height,32);

	//�w�i�F�𔒂ɐݒ�
	SetBackgroundColor(255,255,255);

	//�A���`�G�C���A�X�ݒ�
	//SetFullSceneAntiAliasingMode(4,3);

	//�^�C�g��
	SetMainWindowText("StormSignal ARPG");

	//���������M����҂��Ȃ�
	SetWaitVSyncFlag(false);

	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		 return -1;	// �G���[���N�����璼���ɏI��
	}

	//Alt�AF10���̃|�[�Y�𖳌���
	SetSysCommandOffFlag(true);

	//��A�N�e�B�u���ł��������s��
	SetAlwaysRunFlag(true);

	//BOX2D
	b2Vec2 Gravity(0.f,9.8f);
	b2World World(Gravity);

	float32 TimeStep = 1.0f / (float)RefreshRate;
	int32 VelocityIterations = 6;
	int32 PositionIterations = 2;

	DebugDraw DebugDraw;
	DebugDraw.SetFlags(0xff);
	World.SetDebugDraw(&DebugDraw);

	//�n��
	b2BodyDef GroundBodyDef;
	GroundBodyDef.position.Set(96.f,Screen_Height/Box_Rate);
	b2Body* GroundBody = World.CreateBody(&GroundBodyDef);
	GroundBody->SetUserData("Ground");
	b2PolygonShape GroundBox;
	GroundBox.SetAsBox(96.f,1.5f);
	GroundBody->CreateFixture(&GroundBox,0.f);

	Player Player;
	Player.Load("Image/Chara/None.png");
	Player.Initialize(&World,"Player",1,1,100);

	Enemy PunchingBag;
	PunchingBag.Load("Font/Big_Green/A.png");
	PunchingBag.Initialize(&World,"Enemy",1,1,100);

	Font Fonts;

	int Scene = TrainingMode;


	//���C�����[�v
	while( ProcessMessage() == 0)
	{
		ScreenTimer(0,RefreshRate);

		switch(Scene)
		{
			case Title:
			{
				#pragma region �^�C�g��

				Fonts.DrawString(Screen_Width / 2,Screen_Height/5,5,1,"STORMSIGNAL ARPG","Font/Big_Red",DrawString_Center);

				Fonts.DrawString(Screen_Width / 2,Screen_Height*0.6,5,1,"PRESS ENTER KEY","Font/Big_Red",DrawString_Center);

				break;
				#pragma endregion
			}
			case ModeSelect:
			{
				#pragma region ���[�h�Z���N�g

				Fonts.DrawString(Screen_Width / 2,100,5,1,"STORMSIGNAL ARPG","Font/Big_Red",DrawString_Center);

				break;
				#pragma endregion
			}
			case StoryMode:
			{
				#pragma region �X�g�[���[���[�h

				Fonts.DrawString(Screen_Width / 2,100,5,1,"STORMSIGNAL ARPG","Font/Big_Red",DrawString_Center);

				break;
				#pragma endregion
			}
			case ArcadeMode:
			{
				#pragma region �A�[�P�[�h���[�h

				Fonts.DrawString(Screen_Width / 2,100,5,1,"STORMSIGNAL ARPG","Font/Big_Red",DrawString_Center);

				break;
				#pragma endregion
			}
			case TrainingMode:
			{
				#pragma region �g���[�j���O���[�h

				Fonts.DrawString(Screen_Width / 2,100,5,1,"TRAINING","Font/Big_Red",DrawString_Center);

				Player.Ctrl();
				Player.Step();
				Player.Draw(true);

				PunchingBag.Step();
				PunchingBag.Draw(true);

				Player.StepSkillWindow();

				World.Step(TimeStep, VelocityIterations, PositionIterations);
				World.DrawDebugData();

				break;
				#pragma endregion
			}
			case OptionMode:
			{
				#pragma region �I�v�V����

				Fonts.DrawString(Screen_Width / 2,100,5,1,"STORMSIGNAL ARPG","Font/Big_Red",DrawString_Center);

				break;
				#pragma endregion
			}

		}
		

		ScreenTimer(1,RefreshRate);
	}
	DxLib_End();
	return 0;
}