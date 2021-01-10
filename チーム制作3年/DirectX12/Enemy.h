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

};

class Enemy :public BaseObject
{

public:
	Enemy(int HP, 
		Vector3 pos,
		Vector3 ang,
		ObjectManager* obj,
		shared_ptr<ModelRenderer>m,
		int number,
		mpattern mpattern,		
		Vector3 appearancePos = Vector3(0, 0, 0));

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
	std::shared_ptr<ModelRenderer>enemyModel;
	//複数だす用
	int number = 0;
	string name;//キーワード登録
	string num;//複数用ナンバー
	string numName;//上二つの複合体
	
	bool hitFlag = false;
	mpattern move_pattern;

	int hp;
	int time;

	bool AppearanceFlag = false;
	Vector3 AppearancePos; //出現場所
	//float AppearanceTime; //出現時間
};