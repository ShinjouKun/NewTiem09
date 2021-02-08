#include "Misaile.h"


Misaile::Misaile(Vector3 pos, Vector3 ang, ObjectManager * obj, shared_ptr<ModelRenderer> m, shared_ptr<ParticleManager> p, ObjectType t, int num)
	:MisaileModel(m),MisaileParticle(p)
{
	position = pos;
	objM = obj;
	angle = ang;
	setType = t;
	number = num;
}

Misaile::~Misaile()
{
}

void Misaile::MisaileMove()
{
	velocity = Vector3(0, 0, -1);
	for (auto& t : objM->getUseList())
	{
		if (t->GetType() == ObjectType::ENEMY||t->GetType() == ObjectType::BOSS)
		{
			TargetPos = t->GetPosition();
			velocity = TargetPosSet(velocity);
		}
	}
	
	velocity *= Matrix4::RotateX(angle.x);
	velocity *= Matrix4::RotateY(angle.y);

	position -= velocity * speed;
	
}

void Misaile::EnemyMisaileMove()
{
	velocity = Vector3(0, 0, 1);
	for (auto& t : objM->getUseList())
	{
		if (t->GetType() == ObjectType::PLAYER)
		{
			TargetPos = t->GetPosition();
			velocity = TargetPosSet(velocity);
		}
	}
	
	velocity *= Matrix4::RotateX(angle.x);
	velocity *= Matrix4::RotateY(angle.y);

	position += velocity * speed;
}

Vector3 Misaile::TargetPosSet(Vector3 vec)
{
	Vector3 v = TargetPos - position;
	return v.normal();
}

void Misaile::Init()
{
	SetBulletType();
	name = "Bullet";
	num = to_string(number);
	numName = name + num;
	MisaileModel->AddModel(numName, "Resouse/misail.obj", "Resouse/misail.png");
	MisaileParticleBox = make_shared<ParticleEmitterBox>(MisaileParticle);
	MisaileParticleBox->LoadAndSet("Bom", "Resouse/Bom.jpg");
	alive = 0;
	death = false;

	SphereSize = 2.0f;
	speed = 0.5f;
	sound = new Sound();
	sound->LoadSE("Resouse/bom.wav");
}

void Misaile::Update()
{
	switch (objType)
	{
	case BULLET:
		MisaileMove();
		break;
	case ENEMYBULLET:
		EnemyMisaileMove();
		break;
	default:
		break;
	}
	EnemyMisaileMove();
	alive++;
	if (alive >= 150)
	{
	  death = true;
	}
}

void Misaile::Rend()
{
	DirectXManager::GetInstance()->SetData3D();//モデル用をセット
	MisaileModel->Draw(numName, Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, angle.z), Vector3(2, 2, 2));
}

void Misaile::Hit(BaseObject & other)
{
	if (objType == BULLET && (other.GetType() == ObjectType::ENEMY || other.GetType() == ObjectType::BOSS || other.GetType() == ObjectType::ENEMYBULLET))
	{
		MisaileParticleBox->EmitterUpdate("Bom", Vector3(position.x, position.y, position.z), angle);
	    sound->Play("Resouse/bom.wav");
		death = true;
	}
	if (objType == ENEMYBULLET && (other.GetType() == ObjectType::PLAYER || other.GetType() == ObjectType::BULLET))
	{
		MisaileParticleBox->EmitterUpdate("Bom", Vector3(position.x, position.y, position.z), angle);
		sound->Play("Resouse/bom.wav");
		death = true;
	}
}

void Misaile::SetBulletType()
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
