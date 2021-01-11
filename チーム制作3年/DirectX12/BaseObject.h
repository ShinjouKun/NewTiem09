#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include<cmath>
enum ObjectType//�I�u�W�F�N�g�̃^�O
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
	virtual void Hit(BaseObject& other) = 0;//�q�b�g�ʒm
	virtual Vector3 RotateY(float angle);
	bool StoS_Col(BaseObject& other);//3D���΋������蔻��
	bool BtoB_Col(BaseObject& other);//3D���Δ�
	bool StoP_Col(BaseObject& other,Vector3* inter =nullptr);//3D���Ε���
	//Get�@Set
	virtual ObjectType GetType() { return objType; }
	virtual bool GetDeath() { return death; }
	virtual Vector3 GetPosition() { return position; }
	//AI�p
	size_t GetID()const;
	void SetID(size_t id);
	size_t AiID;//AI�ԍ�
protected:
	ObjectType objType;
	bool death;//����ł��邩
	Vector3 position;
	Vector3 velocity;
    Vector3 angle;
	float speed;
	//���p�̔��a�T�C�Y
	float SphereSize;
	//���ʗp�̃X�e�[�^�X
	float dist;
	//box�p�X�e�[�^�X
	Vector3 max;
	Vector3 min;
	//PI
	const float PI = 3.1415926535897932384626433832795f;

	
};
