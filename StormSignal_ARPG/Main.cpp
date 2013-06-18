#include "Includes.h"
#include "Font.h"

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

	//��A�N�e�B�u���ł��������s��
	SetAlwaysRunFlag(true);

	Font Fonts;

	//���C�����[�v
	while( ProcessMessage() == 0)
	{
		ScreenTimer(0,RefreshRate);

		Fonts.DrawString(Screen_Width / 2,100,5,1,"STORMSIGNAL ARPG","Font/Big_Red",DrawString_Center);

		ScreenTimer(1,RefreshRate);
	}
	DxLib_End();
	return 0;
}