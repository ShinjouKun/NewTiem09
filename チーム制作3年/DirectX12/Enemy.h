#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"ModelRenderer.h"
<<<<<<< HEAD
#include"Player.h"
#include"Easing.h"

=======
#include"ParticleManager.h"
>>>>>>> origin/しんじょーくん
using namespace std;

enum mpattern {

	Fixation,
	Tracking_A,
	Tracking_B,
	Tracking_C,

};

class Enemy :public BaseObject
{

public:
<<<<<<< HEAD
	Enemy(int HP, 
		Vector3 pos,
		Vector3 ang,
		ObjectManager* obj,
		shared_ptr<ModelRenderer>m,
		int number,
		mpattern mpattern,		
		Vector3 appearancePos = Vector3(0, 0, 0));

=======
	Enemy(Vector3 pos,Vector3 ang, ObjectManager* obj, shared_ptr<ModelRenderer>m, shared_ptr<ParticleManager>p,int number);
>>>>>>> origin/しんじょーくん
	~Enemy();
	// BaseObject ����Čp������܂���
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;


	void MovePattern(mpattern patternnum);

	void Appearance();
	
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
<<<<<<< HEAD
	
	bool hitFlag = false;
	mpattern move_pattern;
=======
	bool damge;//�_���[�W
>>>>>>> origin/しんじょーくん

	int hp;
	int time;

	bool AppearanceFlag = false;
	Vector3 AppearancePos; //�o���ꏊ
	//float AppearanceTime; //�o������
};