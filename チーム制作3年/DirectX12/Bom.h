#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"ModelRenderer.h"
#include"ParticleManager.h"
class Bom :public BaseObject
{
public:
	Bom(Vector3 pos, Vector3 angle, ObjectManager* obj, shared_ptr<ModelRenderer>m, shared_ptr<ParticleManager>p, int num);
	~Bom();
private:
	ObjectManager* objM;
	std::shared_ptr<ModelRenderer>BomModel;
	shared_ptr<ParticleManager>BomParticle;
	shared_ptr<ParticleEmitterBox>BomParticleBox;
	int alive;//�����̃L�[��
	float speed;

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
};