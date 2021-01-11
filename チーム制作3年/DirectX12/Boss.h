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
	// BaseObject ����Čp������܂���
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;



private:
	ObjectManager* objM;
	shared_ptr<ModelRenderer>bossModel;
	shared_ptr<ParticleManager>bossParticle;
	shared_ptr<ParticleEmitterBox>bossParticleBox;
	int HP;
	bool ShotFlag;
	int ShotCount;
	bool HitFlag;//���G���Ԃ̂���
	int HitCount;
	int bulletStock;//�e�������ς���������
};
