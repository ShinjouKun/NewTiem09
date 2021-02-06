#include "Boss.h"
#include"Bullet.h"
#include"Misaile.h"
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
	objM->Add(new Misaile(Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, angle.z), objM, bossModel,bossParticle, objType, bulletStock));
	ShotCount = 0;
	ShotFlag = false;
}

void Boss::Shot2()
{
	objM->Add(new Misaile(Vector3(position.x+10.0f, position.y, position.z), Vector3(angle.x, angle.y, angle.z), objM, bossModel, bossParticle, objType, bulletStock));
	objM->Add(new Misaile(Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, angle.z), objM, bossModel, bossParticle, objType, bulletStock+1));
	objM->Add(new Misaile(Vector3(position.x-10.0f, position.y, position.z), Vector3(angle.x, angle.y, angle.z), objM, bossModel, bossParticle, objType, bulletStock+2));
	ShotCount = 0;
	ShotFlag = false;
}

void Boss::Move()
{
	Count++;
	if (Count<=80)
	{
		position.x -= 1.0f;
	}
	else
	{
		position.x += 1.0f;
		if (Count >= 160)
		{
			Count = 0;
		}
	}
	//UŒ‚
	if (!ShotFlag)
	{
		ShotCount++;
		if (ShotCount >= 120)
		{
			ShotFlag = true;
			Shot();
		}
	}
}

void Boss::Move2()
{
	if (position.x != 0.0f)
	{
		if (position.x >= 0.0f)
		{
			position.x -= 0.2f;
		}
		if (position.x <= 0.0f)
		{
			position.x += 0.2f;
		}
	}
	//UŒ‚
	if (!ShotFlag)
	{
		ShotCount++;
		if (ShotCount >= 100)
		{
			ShotFlag = true;
			Shot2();
		}
	}
}

void Boss::Move3()
{
}

void Boss::Init()
{
	Count = 0;
	HP = 100;
	death = false;
	position = Vector3(40.0f, 10.0f, -180.0f);
	SphereSize = 15.0f;
	ShotFlag = false;
	HitFlag = false;
	ShotCount = 0;
	HitCount = 0;
	objType = ObjectType::BOSS;
	bossModel->AddModel("BOSS","Resouse/boss1.obj", "Resouse/boss1.png");
	bossModel->SetAncPoint("BOSS", Vector3(0.0f,-1.0f, -2.0f));
	bossParticleBox = make_shared<ParticleEmitterBox>(bossParticle);
	bossParticleBox->LoadAndSet("HIT", "Resouse/Bom.jpg");
	bulletStock = 100;
}

void Boss::Update()
{
	if (HP >= 50)
	{
		Move();
	}
	else
	{
		Move2();
	}
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
	if (HP == 0)
	{
		death = true;
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
}

void Boss::Hit(BaseObject & other)
{
	if (!HitFlag&&other.GetType() == ObjectType::BULLET)
	{
		HP -= 10;
		HitFlag = true;//–³“GŽžŠÔ‚É“ü‚é
	}
}
