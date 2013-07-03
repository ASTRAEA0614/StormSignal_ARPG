#include <Box2D\Box2D.h>

#ifndef _HITBOX
#define _HITBOX

#include "Character.h"

class HitBox
{
private:
	b2PolygonShape Shape;
	b2Transform Transform;
	Character* Attacker;
	bool Suicide;//�U�������{�l�Ƀ_���[�W�͓��邩�H
	b2Vec2 HitVect;//�q�b�g���ɑ���֗^����x�N�g��
	int Damage;//�_���[�W
	int HitCount;//��������։���q�b�g���邩(-1�Ł�)
	int Duration;//��������
	int Time;
	int StanTime;//�q�b�g���s���s�\����

	vector<b2PolygonShape*> HittedChara;

public:
	void Initialize(b2PolygonShape InputShape,b2Transform InputTransform,Character* InputAttacker,bool SuicideFlag,b2Vec2 InputHitVect,int InputDamage,int InputHitCount,int InputDuration,int InputStanTime);
	bool HitTestShape(Character* Target,b2PolygonShape* TargetShape,b2Transform TargetTrans);
	bool Step();
	Character* GetCharacter(void);
	b2Vec2 GetHitVect(void);
	int GetDamage(void);
	int GetStanTime(void);

	void Draw(void);

};

#endif