#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include<cmath>
enum ObjectType//オブジェクトのタグ
{
	PLAYER,
	ENEMY,
	BULLET,
	GROUND,
	ENEMYBULLET,
	BOSS
};

class BaseObject
{
public:
	BaseObject();
	virtual~BaseObject();
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Rend() = 0;
	virtual void Hit(BaseObject& other) = 0;//ヒット通知
	virtual Vector3 RotateY(float angle);
	bool StoS_Col(BaseObject& other);//3D球対球当たり判定
	bool BtoB_Col(BaseObject& other);//3D箱対箱
	bool StoP_Col(BaseObject& other,Vector3* inter =nullptr);//3D球対平面
	//Get　Set
	virtual ObjectType GetType() { return objType; }
	virtual bool GetDeath() { return death; }
	virtual Vector3 GetPosition() { return position; }
	//AI用
	size_t GetID()const;
	void SetID(size_t id);
	size_t AiID;//AI番号
protected:
	ObjectType objType;
	bool death;//死んでいるか
	Vector3 position;
	Vector3 velocity;
    Vector3 angle;
	float speed;
	//球用の半径サイズ
	float SphereSize;
	//平面用のステータス
	float dist;
	//box用ステータス
	Vector3 max;
	Vector3 min;
	//PI
	const float PI = 3.1415926535897932384626433832795f;

	
};
