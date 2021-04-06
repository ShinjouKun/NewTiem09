#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"Camera.h"
#include"TexRenderer.h"
#include"ModelRenderer.h"
#include"ParticleManager.h"
#include"Track.h"
#include"Sound.h"

using namespace std;
class Player :public BaseObject
{
public:
	Player(Vector3 pos, 
		Vector3 angle,
		ObjectManager* obj,
		shared_ptr<ModelRenderer>m,
		shared_ptr<ParticleManager>p,
		shared_ptr<TexRenderer>s);
	~Player();

	void Shot();
	void BomShot();
	void MisaileShot();
	// BaseObject を介して継承されました
	virtual void Init() override;
	virtual void Update() override;
	virtual void Rend() override;
	virtual void Hit(BaseObject & other) override;

	Vector3 GetPosition() { return position; }

private:
	ObjectManager* objM;
    shared_ptr<ModelRenderer>playerModel;
	shared_ptr<ParticleManager>playerParticle;
	shared_ptr<ParticleEmitterBox>playerParticleBox;
	shared_ptr<TexRenderer>playerSprite;
	Camera* camera;
	//エフェクト発生点
	Vector3 firePos;
	//制御用フラグ
	bool shotFlag =false;
	int shotcnt = 0;
	Vector3 AIMPos;
	//ステータス
	int HP;
	int bulletStock;//弾をいっぱいだすため
	bool HitFlag;//無敵時間のため
	int HitCount;
	Sound* sound;
	float red;
	
};