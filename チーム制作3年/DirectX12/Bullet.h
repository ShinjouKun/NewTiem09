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
