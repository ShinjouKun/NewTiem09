#include "Bom.h"

Bom::Bom(Vector3 pos, Vector3 ang, ObjectManager * obj, shared_ptr<ModelRenderer> m, shared_ptr<ParticleManager> p, int num)
	:BomModel(m),BomParticle(p)
{
	position = pos;
	objM = obj;
	angle = ang;
	number = num;
}

Bom::~Bom()
{
}

void Bom::Init()
{
	name = "BOM";
	num = to_string(number);
	numName = name + num;
	BomModel->AddModel(numName, "Resouse/Bullet.obj", "Resouse/Bullet.png");
	BomParticleBox = make_shared<ParticleEmitterBox>(BomParticle);
	BomParticleBox->LoadAndSet("Bom", "Resouse/Bom.jpg");
	alive = 0;
	death = false;

	SphereSize = 2.0f;
	speed = 0.7f;
}

void Bom::Update()
{
	velocity = Vector3(0, 0, 1);
	velocity *= Matrix4::RotateX(angle.x);
	velocity *= Matrix4::RotateY(angle.y);

	position += velocity * speed;
	alive++;
	if (alive >= 100)
	{
		SphereSize += 0.3f;
		if (SphereSize >= 8.0f)
		{
			death = true;
		}
	}
}

void Bom::Rend()
{
	DirectXManager::GetInstance()->SetData3D();//モデル用をセット
	BomModel->Draw(numName, Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, 0), Vector3(1, 1, 1));
}

void Bom::Hit(BaseObject & other)
{
	if (other.GetType() == ObjectType::ENEMY || other.GetType() == ObjectType::BOSS || other.GetType() == ObjectType::ENEMYBULLET)
	{
		BomParticleBox->EmitterUpdate("Bom", Vector3(position.x, position.y, position.z), angle);
		death = true;
	}
}
