#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"ModelRenderer.h"
#include"Player.h"
#include"Easing.h"

using namespace std;

enum mpattern {

	Fixation,
	Tracking_A,
	Tracking_B,
	Tracking_C,
	Armor,
	Recovery,

};

class Enemy :public BaseObject
{

public:
	Enemy(int HP, 
		Vector3 pos,
		Vector3 ang,
		ObjectManager* obj,
		shared_ptr<ModelRenderer>m,
		shared_ptr<ParticleManager>p,
		int number,
		mpattern mpattern,
		Vector3 arrivalPos = Vector3(0, 0, 0));

	~Enemy();
	// BaseObject を介して継承されました
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;
	
private:

	void MovePattern(mpattern patternnum); //移動種類

	void Arrival(); //　背後からの出現用

	void RanPointGenerate(Vector2 min,Vector2 max); //　ランダム位置生成
	
private:
	ObjectManager* objM;
	shared_ptr<ModelRenderer>enemyModel;
	shared_ptr<ParticleManager>enemyParticle;

	//複数だす用
	int number = 0;
	string name;//キーワード登録
	string num;//複数用ナンバー
	string numName;//上二つの複合体
	
	bool hitFlag = false;
	mpattern move_pattern;

	int hp;

	int shotDamageAmount = 0; //ダメージ量
	int shotCount; 
	int tackletime = 10;		//タックルタイム

	bool wait = false;			//移動後待ち
	int ArrivalTime;			//出現時間
	bool ArrivalFlag = false;	//出現したか
	Vector3 ArrivalPos;			//出現場所

	Vector3 movePoint;			//移動先
	int movetime = 0;			//移動時間
	int waitTime =0;			//待ち時間

};