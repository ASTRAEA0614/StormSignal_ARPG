#include "Image_2D.h"
#include "DxLib.h"

struct Vect
{
	int x;
	int y;
};

void Image_2D::Load(string Pass)
{
	Graph.push_back(LoadGraph(Pass.c_str()));
	SIHandle.push_back(LoadSoftImage(Pass.c_str()));
}

void Image_2D::Unload(void)
{
	int Length = Graph.size();
	for(int i=0;i<Length;i++)
	{
		DeleteGraph(Graph[i]);
		DeleteSoftImage(SIHandle[i]);
	}
	Graph.clear();
	SIHandle.clear();
}

void Image_2D::Initialize(void)
{//������
	int SizeW,SizeH;
	//while(CheckHandleASyncLoad(Graph[0]) && ProcessMessage() == 0){}
	GetGraphSize(Graph[0],&SizeW,&SizeH);
	Visible = true;
	x = 0;
	y = 0;
	Center_x = SizeW / 2;
	Center_y = SizeH / 2;
	Ext = 1.0f;
	Angle = 0.0f;
	
	Anime_Speed = 1;
	Anime_Frame = 0;
	Anime_ShowNum = 0;
}

bool Image_2D::Draw(bool Trans)
{//�`��
	if(Graph.size() > 1)Anime_Frame++;
	if(Anime_Speed <= 0)Anime_Speed = 1;

	if(Visible)DrawRotaGraph2(x,y,Center_x,Center_y,Ext,Angle,Graph[Anime_ShowNum],Trans);

	if((Anime_Frame % Anime_Speed) == 0)Anime_ShowNum++;
	if(Anime_ShowNum >= (int)Graph.size())
	{
		Anime_ShowNum = 0;
		return true;
	}
	return false;
}

int Image_2D::GetAlpha(int X,int Y)
{//�A���t�@�l���擾
	int R,G,B,A;
	GetPixelSoftImage(SIHandle[Anime_ShowNum],X - (x - Center_x),Y - (y - Center_y),&R,&G,&B,&A);
	return A;
}

bool Image_2D::HitTestPoint(int Target_X,int Target_Y,bool Shape)
{//�_�Ƃ̓����蔻��
	int R,G,B,A;
	if(x - Center_x <= Target_X && Target_X <= Center_x + x && y - Center_y <= Target_Y && Target_Y <= Center_y + y)
	{
		if(!Shape)return true;
		else
		{//�摜�����ڒʂ�̔���
			GetPixelSoftImage(SIHandle[Anime_ShowNum],Target_X - (x - Center_x),Target_Y - (y - Center_y),&R,&G,&B,&A);
			if(!A)return false;
			else return true;
		}
	}
	else return false;
}

int Image_2D::HitTestGraph(Image_2D *Target,bool Shape)
{//�摜�Ƃ̓����蔻��
	Vect A1,A2,B1,B2;
	A1.x = x - Center_x;
	A1.y = y - Center_y;
	A2.x = x + Center_x;
	A2.y = y + Center_y;
	B1.x = Target->x - Target->Center_x;
	B1.y = Target->y - Target->Center_y;
	B2.x = Target->x + Target->Center_x;
	B2.y = Target->y + Target->Center_y;

	if(B1.x < A2.x && A2.y > B1.y && B2.x > A1.x && B2.y > A1.y)
	{//��G�c�ȓ����蔻��
		if(!Shape)
		{
			return true;
		}else
		{//�����ڒʂ�̓����蔻��
			int X,Y,Width,Height;
			if(B1.x > A1.x)X = B1.x;
			else X = A1.x;
			if(B1.y > A1.y)Y = B1.y;
			else Y = A1.y;
			if(A2.x < B2.x)Width = A2.x;
			else Width = B2.x;
			if(B2.y > A2.y)Height = A2.y;
			else Height = B2.y;

			for(int i=X;i<Width;i++)
			{
				for(int i2=Y;i2<Height;i2++)
				{
					if(Target->GetAlpha(i,i2) <= 127)continue;
					if(GetAlpha(i,i2) <= 127)continue;
					return true;
				}
			}
			return false;
		}
	}else
	{//����������Ȃ��ꍇ
		return false;
	}
}