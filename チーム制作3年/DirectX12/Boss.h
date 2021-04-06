#pragma once
#include "BaseObject.h"
#include"ObjectManager.h"
#include<memory>
#include"Camera.h"
#include"ModelRenderer.h"
#include"ParticleManager.h"
class Boss : public BaseObject
{
public:
	Boss(Vector3 pos, Vector3 ang, ObjectManager * obj, shared_ptr<ModelRenderer> m, shared_ptr<ParticleManager>p);
	~Boss();

	void Shot();
	void Shot2();
	void Shot3();
	void Stay();
	void Move();//‰Šúmove
	void Move2();//60“
	void Move3();//20ˆÈ‰º
	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;



private:
	ObjectManager* objM;
	shared_ptr<ModelRenderer>bossModel;
	shared_ptr<ParticleManager>bossParticle;
	shared_ptr<ParticleEmitterBox>bossParticleBox;
	Vector3 playerPos;
	int HP;
	bool ShotFlag;
	int ShotCount;
	
	int bulletStock;//’e‚ğ‚¢‚Á‚Ï‚¢‚¾‚·‚½‚ß

	bool HitFlag;//–³“GŠÔ‚Ì‚½‚ß
	int HitCount;
	int Count;
	int FripCount;//‰ñ“]‚ÌØ‚è‘Ö‚¦
	bool stayOff;//‘Ò‹@ƒ‚[ƒVƒ‡ƒ“
	bool firet;//Å‰‚Ì‚İ‚¬‚¢‚Ç‚¤
	int bomCnt;
	bool End;
};
