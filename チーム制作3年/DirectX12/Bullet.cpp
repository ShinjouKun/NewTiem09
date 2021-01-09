#include "Bullet.h"
#include"Matrix4.h"
Bullet::Bullet(Vector3 pos, Vector3 ang, ObjectManager * obj, std::shared_ptr<ModelRenderer> m)
	:BulletModel(m)
{
	position = pos;
	objM = obj;
	angle = ang;
}

Bullet::~Bullet()
{
	
}

void Bullet::Init()
{
	BulletModel->AddModel("Bullet","Resouse/Bullet.obj","Resouse/Bullet.png");
	alive = 0;
	death = false;
	objType = ObjectType::BULLET;
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
	BulletModel->Draw("Bullet", Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, 0), Vector3(1, 1, 1));
}

void Bullet::Hit(BaseObject & other)
{
	if (other.GetType() == ObjectType::ENEMY)
	{
		death = true;
	}
}
