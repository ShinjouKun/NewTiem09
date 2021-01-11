#include "Enemy.h"
#include"Input.h"

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
	
	time = 0;
	movePoint = Vector2(100, 100);

	SphereSize = 1.0f; //判定サイズ
}

void Enemy::Update()
{
	MovePattern(move_pattern);


	position.z -= 1 * speed;
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

		if (ArrivalFlag)
		{
			speed = 0.2f;
		}

		break;

	case mpattern::Tracking_B:

		shotDamageAmount = 2;
		Arrival();

		if (!ArrivalFlag) return;
		if(!wait)
		{
			if (movetime < 200)movetime++;
			position.x = Easing::ease_out_sine(
				movetime,
				position.x,
				movePoint.x- position.x,
				400);

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

	case mpattern::Tracking_C:

		shotDamageAmount = 2;
		Arrival();

		if (!ArrivalFlag) return;




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

		if (time < 300) time++;
		position = Easing::ease_in_quint(time, position,
			(ArrivalPos) - position, 100);
	}
	if(position.z <= ArrivalPos.z)		//　プレイヤーより後ろ
	{

		ArrivalFlag = true;
	}
	
}

Vector3 Enemy::RanPoint(Vector2 min, Vector2 max)
{
	Vector3 point;

	point =  Vector3(
		rand()*(max.x - min.x + 1.0),
		rand()*(max.y - min.y + 1.0),
		position.z);

	return point;
}

int RandamValue(int min, int max)
{
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

