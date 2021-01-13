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
	int alive;//爆発のキーに
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
};