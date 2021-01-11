#include "Boss.h"
#include"Bullet.h"
Boss::Boss(Vector3 pos, Vector3 ang, ObjectManager * obj, shared_ptr<ModelRenderer> m, shared_ptr<ParticleManager>p)
	:bossModel(m),bossParticle(p)
{
	position = pos;
	angle = ang;
	objM = obj;
}

Boss::~Boss()
{
}

void Boss::Shot()
{
	objM->Add(new Bullet(Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, angle.z), objM, bossModel, objType, bulletStock));
	ShotCount = 0;
	ShotFlag = false;
}

void Boss::Init()
{
	HP = 100;
	death = false;
	position = Vector3(0.0f, 8.0f, -180.0f);
	SphereSize = 10.0f;
	ShotFlag = false;
	HitFlag = false;
	ShotCount = 0;
	HitCount = 0;
	objType = ObjectType::BOSS;
	bossModel->AddModel("BOSS","Resouse/enemy2.obj", "Resouse/enemy2.png");
	bossParticleBox = make_shared<ParticleEmitterBox>(bossParticle);
	bossParticleBox->LoadAndSet("HIT", "Resouse/Bom.jpg");
	bulletStock = 100;
}

void Boss::Update()
{
	//“–‚½‚è
	if (HitFlag)
	{
		HitCount++;
		if (HitCount >= 30)
		{
			HitCount = 0;
			HitFlag = false;
		}
	}
	//UŒ‚
	
	if (!ShotFlag)
	{
		ShotCount++;
		if (ShotCount >= 100)
		{
			ShotFlag = true;
			Shot();
		}
	}
	//‹…”ãŒÀ‚ðÝ‚¯
	if (bulletStock >= 150)
	{
		bulletStock = 100;
	}
}

void Boss::Rend()
{
	DirectXManager::GetInstance()->SetData3D();
	bossModel->Draw("BOSS", position, angle, Vector3(10, 10, 10));
	if (HitFlag)
	{
		bossParticleBox->EmitterUpdate("HIT", Vector3(position.x, position.y + 8.0f, position.z + 10.0f), angle);
	}
	
}

void Boss::Hit(BaseObject & other)
{
	if (!HitFlag&&other.GetType() == ObjectType::BULLET)
	{
		HP -= 10;
		HitFlag = true;//–³“GŽžŠÔ‚É“ü‚é
	}
}
