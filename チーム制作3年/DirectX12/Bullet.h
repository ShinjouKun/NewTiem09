#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"ModelRenderer.h"

class Bullet:public BaseObject
{
public:
	Bullet(Vector3 pos, Vector3 angle, ObjectManager* obj, std::shared_ptr<ModelRenderer>m,ObjectType t,int num);
	~Bullet();

private:
	ObjectManager* objM;
	std::shared_ptr<ModelRenderer>BulletModel;
	Vector3 TargetPos;
	int alive;
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
	//�N�̒e��
	ObjectType setType;
	void SetBulletType();
};
