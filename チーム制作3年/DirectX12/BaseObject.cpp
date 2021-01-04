#include "BaseObject.h"
#include"Matrix4.h"
BaseObject::BaseObject()
{
}

BaseObject::~BaseObject()
{
}

Vector3 BaseObject::RotateY(float angle)
{
	Vector3 v;
	
	angle = angle + 45.0f;
	angle = angle * PI / 180.0f;

	float sin = sinf(angle);
	float cos = cosf(angle);

	float x = cos + sin;
	float z = -(sin)+cos;

	v = Vector3(x,0.0f,z);
	return v;
}

bool BaseObject::StoS_Col(BaseObject & other)
{
	//半径の中心点がモデルの原点に依存しているので注意せよ
	float length = Vector3((position - other.position)).Length();
	float radSam = SphereSize + other.SphereSize;
	if (length <= radSam)
	{
		return true;
	}
	return false;
}

bool BaseObject::BtoB_Col(BaseObject & other)
{

	if (position.x > other.max.x)return false;
	if (max.x < other.position.x)return false;

	if (position.y > other.max.y)return false;
	if (max.y < other.position.y)return false;

	if (position.z > other.max.z)return false;
	if (max.z < other.position.z)return false;

	return true;//衝突!
}

bool BaseObject::StoP_Col(BaseObject & other,Vector3* inter)
{
	float length = Vector3::dot(position, other.position);
	float disSam = length - other.dist;

	if (fabsf(disSam)>SphereSize)
	{
		return false;
	}
	if (inter)
	{
		*inter = -disSam * position + other.position;
	}
	return true;
}

size_t BaseObject::GetID() const
{
	return AiID;
}

void BaseObject::SetID(size_t id)
{

	AiID = id;
}
