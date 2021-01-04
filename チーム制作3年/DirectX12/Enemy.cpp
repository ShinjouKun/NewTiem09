#include "Enemy.h"

Enemy::Enemy(Vector3 pos, Vector3 ang, ObjectManager * obj, shared_ptr<ModelRenderer> m, int n)
	:enemyModel(m)
{
	position = pos;
	angle = ang;
	objM = obj;
	number = n;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	death = false;
	objType = ObjectType::ENEMY;
	speed = 0.3f;
	name = "Tank";//名前を登録
	num = to_string(number);//複数用
	numName = name + num;

	enemyModel->AddModel(numName,"Resouse/enemy2.obj","Resouse/enemy2.png");
	//enemyModel->SetAncPoint(numName, Vector3(-2.0f, 0.0f, -2.0f));
	
	
	SphereSize = 1.0f;
}

void Enemy::Update()
{
	
}

void Enemy::Rend()
{
	DirectXManager::GetInstance()->SetData3D();//モデル用をセット

	enemyModel->Draw(numName, Vector3(position.x, position.y, position.z), Vector3(0,0,0), Vector3(3, 3, 3));
}

void Enemy::Hit(BaseObject & other)
{
}
