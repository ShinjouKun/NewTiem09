#include "Enemy.h"
#include"Input.h"


float RandamValue(float min, float max)
{
	return min + (rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}


Enemy::Enemy(int HP,
	Vector3 pos,
	Vector3 ang,
	ObjectManager * obj,
	shared_ptr<ModelRenderer> m,
	shared_ptr<ParticleManager>p,
	int num,
	mpattern mpattern,
	Vector3 arrivalPos)
	:enemyModel(m),enemyParticle(p)
{
	position = pos;
	angle = ang;
	objM = obj;
	number = num;
	move_pattern = mpattern;
	hp = HP;
	ArrivalPos = arrivalPos;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	death = false;
	objType = ObjectType::ENEMY;
	speed = 0;
	name = "Tank";//名前を登録
	num = to_string(number);//複数用
	numName = name + num;

	enemyModel->AddModel(numName,"Resouse/enemy2.obj","Resouse/enemy2.png");
	//enemyModel->SetAncPoint(numName, Vector3(-2.0f, 0.0f, -2.0f));
	
	ArrivalTime = 0;
	movePoint = Vector3(100, 50, position.z);

	ranMovePoint = Vector3(
		RandamValue(-100, 100),
		RandamValue(0, 10),
		ArrivalPos.z);

	SphereSize = 1.0f; //判定サイズ
}

void Enemy::Update()
{
	position.z -= 1 * speed;

	MovePattern(move_pattern);
	
}

void Enemy::Rend()
{
	DirectXManager::GetInstance()->SetData3D();//モデル用をセット

	enemyModel->Draw(numName,
		Vector3(position.x, position.y, position.z),
		Vector3(0,0,0), Vector3(3, 3, 3));
}

void Enemy::Hit(BaseObject & other)
{
	if (other.GetType() == ObjectType::BULLET)
	{		
		hitFlag = true;
		
		hp = hp - 1;

		if (hp == 0)
		{
			death = true;
		}
	}
	else
	{
		hitFlag = false;
	}

}

void Enemy::MovePattern(mpattern patternnum)
{
	switch (patternnum)
	{
	case mpattern::Fixation:

		shotDamageAmount = 1;
		speed = 0;

		break;

	case mpattern::Tracking_A:
	
		shotDamageAmount = 1;
		Arrival();

		if (!ArrivalFlag) return;
		speed = 0.2f;


		break;

	case mpattern::Tracking_B_LR:

		shotDamageAmount = 2;
		Arrival();

		if (!ArrivalFlag) return;
		speed = 0.2f;

		//　左右移動
		if(!wait)
		{
			if (movetime < 200)movetime++;
			position.x = Easing::ease_out_circ(
				movetime,
				position.x,
				movePoint.x- position.x,
				600);

			if (position.x >= 100) {
				
				movePoint.x = -100;
				wait = true;

			}
			else if(position.x <= -100)
			{
				movePoint.x = 100;
				wait = true;

			}
		}

		if (wait)
		{
			waitTime++;

			if (waitTime == 2) {
				wait = false;
				waitTime = 0;
				movetime = 0;
			}
		}

		break;

	case mpattern::Tracking_B_UB:

		shotDamageAmount = 2;
		Arrival();

		if (!ArrivalFlag) return;
		speed = 0.2f;

		//　上下移動
		if (!wait)
		{
			if (movetime < 200)
				movetime++;

			position.y = Easing::ease_out_sine(
				movetime,
				position.y,
				movePoint.y - position.y,
				400);

			if (position.y >= 50) {

				movePoint.y = 10;
				wait = true;

			}
			else if (position.y <= 10)
			{
				movePoint.y = 50;
				wait = true;

			}
		}	

		if (wait)
		{
			waitTime++;

			if (waitTime == 2) {
				wait = false;
				waitTime = 0;
				movetime = 0;
			}
		}
		break;

	case mpattern::Tracking_C:

		shotDamageAmount = 2;
		Arrival();

		if (!ArrivalFlag) return;
		speed = 0.2f; 
		ranMovePoint.z -= 1 * speed;

		if (!wait)
		{
			if (movetime < 200)movetime++;

			position = Easing::ease_out_expo(
				movetime,
				position,
				ranMovePoint - position,
				400);

			if ((int)position.x == (int)ranMovePoint.x &
				(int)position.y == (int)ranMovePoint.y)
			{
				wait = true;

				ranMovePoint = Vector3(
					RandamValue(-100, 100),
					RandamValue(0, 30),
					position.z);
			}

		}
		if (wait)
		{
			waitTime++;

			if (waitTime == 20) {

				wait = false;
				waitTime = 0;
				movetime = 0;
			}
		}

		break;

	case mpattern::Armor:
		
		shotDamageAmount = 3;

		if (tackletime == 0)
		{

		}

		break;

	case mpattern::Recovery:


		break;

	}
	   
}

void Enemy::Arrival()
{
	if (!ArrivalFlag) {

		if (ArrivalTime < 300) ArrivalTime++;

		position = Easing::ease_in_quint(
			ArrivalTime,
			position,
			(ArrivalPos) - position,
			100);
	}
	if(position.z <= ArrivalPos.z)		//　プレイヤーより後ろ
	{
		ArrivalFlag = true;
	}
	
}


void Enemy::RanPointGenerate(Vector2 min, Vector2 max)
{
	Vector3 point =  Vector3(
		min.x + rand()*(max.x - min.x + 1.0) / (1.0 + RAND_MAX),
		min.y + rand()*(max.y - min.y + 1.0) / (1.0 + RAND_MAX),
		ArrivalPos.z);

}

