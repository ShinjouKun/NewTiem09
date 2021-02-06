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
	void MisaileMove();//プレイヤーの
	void EnemyMisaileMove();//敵の
	Vector3 TargetPosSet(Vector3 vec);

	ObjectManager* objM;
	std::shared_ptr<ModelRenderer>MisaileModel;
	shared_ptr<ParticleManager>MisaileParticle;
	shared_ptr<ParticleEmitterBox>MisaileParticleBox;
	Vector3 TargetPos;//突撃先
	int alive;
	float speed;
	Sound* sound;
	//複数だす用
	int number = 0;
	string name;//キーワード登録
	string num;//複数用ナンバー
	string numName;//上二つの複合体

	// BaseObject を介して継承されました
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;
	//誰の弾か
	ObjectType setType;
	void SetBulletType();
};
