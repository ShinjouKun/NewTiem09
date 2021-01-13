#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"Camera.h"
#include"TexRenderer.h"
#include"ModelRenderer.h"
#include"ParticleManager.h"

using namespace std;
class Player :public BaseObject
{
public:
	Player(Vector3 pos, Vector3 angle, ObjectManager* obj,shared_ptr<ModelRenderer>m,shared_ptr<ParticleManager>p,shared_ptr<TexRenderer>s);
	~Player();

	void Shot();
	void BomShot();
	// BaseObject ����Čp������܂���
	virtual void Init() override;
	virtual void Update() override;
	virtual void Rend() override;
	virtual void Hit(BaseObject & other) override;


private:
	ObjectManager* objM;
    shared_ptr<ModelRenderer>playerModel;
	shared_ptr<ParticleManager>playerParticle;
	shared_ptr<ParticleEmitterBox>playerParticleBox;
	shared_ptr<TexRenderer>playerSprite;
	Camera* camera;
	//�G�t�F�N�g�����_
	Vector3 firePos;
	//����p�t���O
	bool shotFlag =false;
	int shotcnt = 0;
	bool hitFlag = false;
	Vector3 AIMPos;
	//�X�e�[�^�X
	int HP;
	bool GameOver = false;
	int bulletStock;//�e�������ς���������
};