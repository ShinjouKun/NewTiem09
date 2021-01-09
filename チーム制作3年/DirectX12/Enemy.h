#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"ModelRenderer.h"
#include"ParticleManager.h"
using namespace std;

class Enemy :public BaseObject
{
public:
	Enemy(Vector3 pos,Vector3 ang, ObjectManager* obj, shared_ptr<ModelRenderer>m, shared_ptr<ParticleManager>p,int number);
	~Enemy();
	// BaseObject ����Čp������܂���
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;
private:
	ObjectManager* objM;
	shared_ptr<ModelRenderer>enemyModel;
	shared_ptr<ParticleEmitterBox>enemyParticleBox;
	shared_ptr<ParticleManager>enemyParticle;
	//���������p
	int number = 0;
	string name;//�L�[���[�h�o�^
	string num;//�����p�i���o�[
	string numName;//���̕�����
	bool damge;//�_���[�W

};
