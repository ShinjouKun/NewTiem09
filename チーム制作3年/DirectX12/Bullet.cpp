#include "Bullet.h"
#include"Matrix4.h"
Bullet::Bullet(Vector3 pos, Vector3 ang, ObjectManager * obj, std::shared_ptr<ModelRenderer> m,ObjectType t,int num)
	:BulletModel(m)
{
	position = pos;
	objM = obj;
	angle = ang;
	setType = t;
	number = num;
}

Bullet::~Bullet()
{
	
}

void Bullet::Init()
{
	SetBulletType();
	name = "Bullet";
	num = to_string(number);
	numName = name + num;
	BulletModel->AddModel(numName,"Resouse/Bullet.obj","Resouse/Bullet.png");
	alive = 0;
	death = false;
	
	SphereSize = 2.0f;
	speed = 1.5f;
}

void Bullet::Update()
{
	
	velocity = Vector3(0, 0, 1);
	velocity *= Matrix4::RotateX(angle.x);
	velocity *= Matrix4::RotateY(angle.y);

	position += velocity * speed;
	alive++;
	if (alive >= 100)
	{
		death = true;
	}
}

void Bullet::Rend()
{
	DirectXManager::GetInstance()->SetData3D();//モデル用をセット
	BulletModel->Draw(numName, Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, 0), Vector3(1, 1, 1));
}

void Bullet::Hit(BaseObject & other)
{
	if (objType == BULLET&& (other.GetType() == ObjectType::ENEMY|| other.GetType() == ObjectType::BOSS || other.GetType() == ObjectType::ENEMYBULLET))
	{
		death = true;
	}
	if (objType == ENEMYBULLET && (other.GetType() == ObjectType::PLAYER || other.GetType() == ObjectType::BULLET))
	{
		death = true;
	}

	
}

void Bullet::SetBulletType()
{
	switch (setType)
	{
	case PLAYER:
		objType = ObjectType::BULLET;//プレイヤーの弾
		break;
	case ENEMY:
	case BOSS:
		objType = ObjectType::ENEMYBULLET;//敵の弾
		break;
	default:
		break;
	}
}
