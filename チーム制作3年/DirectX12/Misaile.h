#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"ModelRenderer.h"
#include"ParticleManager.h"
#include"Sound.h"
class Misaile:public BaseObject
{
public:
	Misaile(Vector3 pos, Vector3 angle, ObjectManager* obj, shared_ptr<ModelRenderer>m, shared_ptr<ParticleManager>p, ObjectType t, int num);
	~Misaile();
private:
	void MisaileMove();//�v���C���[��
	void EnemyMisaileMove();//�G��
	Vector3 TargetPosSet(Vector3 vec);

	ObjectManager* objM;
	std::shared_ptr<ModelRenderer>MisaileModel;
	shared_ptr<ParticleManager>MisaileParticle;
	shared_ptr<ParticleEmitterBox>MisaileParticleBox;
	Vector3 TargetPos;//�ˌ���
	int alive;
	float speed;
	Sound* sound;
	//���������p
	int number = 0;
	string name;//�L�[���[�h�o�^
	string num;//�����p�i���o�[
	string numName;//���̕�����

	// BaseObject ����Čp������܂���
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;
	//�N�̒e��
	ObjectType setType;
	void SetBulletType();
};
