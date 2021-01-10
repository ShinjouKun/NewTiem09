#include "Enemy.h"
#include"Input.h"

<<<<<<< HEAD
Enemy::Enemy(int HP,
	Vector3 pos,
	Vector3 ang,
	ObjectManager * obj,
	shared_ptr<ModelRenderer> m,
	int num,
	mpattern mpattern,
	Vector3 appearancePos)
	:enemyModel(m)
=======
Enemy::Enemy(Vector3 pos, Vector3 ang, ObjectManager * obj, shared_ptr<ModelRenderer> m, shared_ptr<ParticleManager>p, int n)
	:enemyModel(m),enemyParticle(p)
>>>>>>> origin/しんじょーくん
{
	position = pos;
	angle = ang;
	objM = obj;
	number = num;
	move_pattern = mpattern;
	hp = HP;
	AppearancePos = appearancePos;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	death = false;
	damge = false;
	objType = ObjectType::ENEMY;
	speed = 0;
	name = "Tank";//���O��o�^
	num = to_string(number);//�����p
	numName = name + num;

	enemyModel->AddModel(numName,"Resouse/enemy2.obj","Resouse/enemy2.png");
	//enemyModel->SetAncPoint(numName, Vector3(-2.0f, 0.0f, -2.0f));
<<<<<<< HEAD
	
	time = 0;
		
	SphereSize = 1.0f; //����T�C�Y
=======
	enemyParticleBox = make_shared<ParticleEmitterBox>(enemyParticle);
	enemyParticleBox->LoadAndSet("Bom","Resouse/Bom.jpg");
	SphereSize = 1.5f;
>>>>>>> origin/しんじょーくん
}

void Enemy::Update()
{
	MovePattern(move_pattern);


	position.z -= 1 * speed;
}

void Enemy::Rend()
{
	
	DirectXManager::GetInstance()->SetData3D();//���f���p���Z�b�g
<<<<<<< HEAD

	enemyModel->Draw(numName,
		Vector3(position.x, position.y, position.z),
		Vector3(0,0,0), Vector3(3, 3, 3));
=======
	enemyModel->Draw(numName, Vector3(position.x, position.y, position.z), Vector3(0,0,0), Vector3(3, 3, 3));
	
	if (!damge)
	{
		enemyParticleBox->EmitterUpdate("Bom", Vector3(position.x, position.y, position.z), Vector3(0.0f, 0.0f, 0.0f));
	}
	
	DirectXManager::GetInstance()->SetData2D();

>>>>>>> origin/しんじょーくん
}

void Enemy::Hit(BaseObject & other)
{
	if (other.GetType() == ObjectType::BULLET)
<<<<<<< HEAD
	{		
		hitFlag = true;
		
		hp = hp - 1;
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

		speed = 0;

		break;

	case mpattern::Tracking_A:
		
		//if (Input::KeyDown(DIK_D)) {
		//	//�@�v���C���[�����
		//	if (position.z > playerPos.z)
		//	{
		//		speed = 0.8f;
		//		/*if (time < 200) time++;
		//		position.z = Easing::ease_in_back(time, position.z,
		//			position.z - (playerPos.z -100), 500);*/
		//	}
		//	
		//}
		//if (position.z < playerPos.z - 80) //�@�v���C���[���O
		//{
		//	speed = 0.1f;
		//}

		//if (!AppearanceFlag) {
		//	if (time < 200) time++;
		//	position.z = Easing::ease_in_quint(time, position.z,
		//		(AppearancePos.z) - position.z, 100);
		//}
		//if (position.z <= AppearancePos.z)		//�@�v���C���[�����
		//{
		//	//speed = 0.8f;
		//
		//	AppearanceFlag = true;
		//}
		//if(AppearanceFlag) //�@�v���C���[���O
		//{
		//	speed = 0.1f;
		//}

		Appearance();

		if (AppearanceFlag) //�@�v���C���[���O
		{
			speed = 0.2f;
		}

		break;

	case mpattern::Tracking_B:

		Appearance();

		break;

	case mpattern::Tracking_C:




		break;

	}

	   
}

void Enemy::Appearance()
{
	if (!AppearanceFlag) {

		if (time < 200) time++;
		position = Easing::ease_in_quint(time, position,
			(AppearancePos) - position, 100);
	}
	if (position.z <= AppearancePos.z)		//�@�v���C���[�����
	{
		//speed = 0.8f;

		AppearanceFlag = true;
	}
	
=======
	{
		damge = true;
	}
>>>>>>> origin/しんじょーくん
}
