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
>>>>>>> origin/縺励ｓ縺倥ｇ繝ｼ縺上ｓ
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
>>>>>>> origin/縺励ｓ縺倥ｇ繝ｼ縺上ｓ
	~Enemy();
	// BaseObject を介して継承されました
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
	//複数だす用
	int number = 0;
	string name;//キーワード登録
	string num;//複数用ナンバー
	string numName;//上二つの複合体
<<<<<<< HEAD
	
	bool hitFlag = false;
	mpattern move_pattern;
=======
	bool damge;//ダメージ
>>>>>>> origin/縺励ｓ縺倥ｇ繝ｼ縺上ｓ

	int hp;
	int time;

	bool AppearanceFlag = false;
	Vector3 AppearancePos; //出現場所
	//float AppearanceTime; //出現時間
};