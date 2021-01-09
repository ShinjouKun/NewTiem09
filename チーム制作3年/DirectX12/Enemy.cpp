#include "Enemy.h"

Enemy::Enemy(Vector3 pos, Vector3 ang, ObjectManager * obj, shared_ptr<ModelRenderer> m, shared_ptr<ParticleManager>p, int n)
	:enemyModel(m),enemyParticle(p)
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
	damge = false;
	objType = ObjectType::ENEMY;
	speed = 0.3f;
	name = "Tank";//名前を登録
	num = to_string(number);//複数用
	numName = name + num;

	enemyModel->AddModel(numName,"Resouse/enemy2.obj","Resouse/enemy2.png");
	//enemyModel->SetAncPoint(numName, Vector3(-2.0f, 0.0f, -2.0f));
	enemyParticleBox = make_shared<ParticleEmitterBox>(enemyParticle);
	enemyParticleBox->LoadAndSet("Bom","Resouse/Bom.jpg");
	SphereSize = 1.5f;
}

void Enemy::Update()
{
	
}

void Enemy::Rend()
{
	
	DirectXManager::GetInstance()->SetData3D();//モデル用をセット
	enemyModel->Draw(numName, Vector3(position.x, position.y, position.z), Vector3(0,0,0), Vector3(3, 3, 3));
	
	if (!damge)
	{
		enemyParticleBox->EmitterUpdate("Bom", Vector3(position.x, position.y, position.z), Vector3(0.0f, 0.0f, 0.0f));
	}
	
	DirectXManager::GetInstance()->SetData2D();

}

void Enemy::Hit(BaseObject & other)
{
	if (other.GetType() == ObjectType::BULLET)
	{
		damge = true;
	}
}
