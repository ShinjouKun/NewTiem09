#pragma once
#include"ObjectManager.h"
#include"BaseObject.h"
#include<memory>
#include"ModelRenderer.h"
#include"Player.h"
#include"Easing.h"

using namespace std;

enum mpattern {

	Fixation,//��_
	Tracking_A,//�ǔ��^�P�i��납�炭��j
	Tracking_B_LR,//���E�ړ��ǔ�
	Tracking_B_UB,//�㉺�ړ�����
	Tracking_C,//ranndamu
	Armor,//���b�^�˂�����ł���z
	Recovery,//�|���Ɖ�

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
	// BaseObject ����Čp������܂���
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;
	
	void SetPlayerPos(Vector3 player) { pos_P = player; };

private:

	void MovePattern(mpattern patternnum); //�ړ����

	void Arrival(); //�@�w�ォ��̏o���p

	void RanPointGenerate(Vector2 min,Vector2 max); //�@�����_���ʒu����
	
	bool Wait(float waittime);

	void Shot();

private:
	ObjectManager* objM;
	shared_ptr<ModelRenderer>enemyModel;
	shared_ptr<ParticleManager>enemyParticle;

	//���������p
	int number = 0;
	string name;//�L�[���[�h�o�^
	string num;//�����p�i���o�[
	string numName;//���̕�����
	
	bool hitFlag = false;
	mpattern move_pattern;

	int hp;

	int shotDamageAmount = 0; //�_���[�W��
	int shotCount; 
	int tackletime = 150;		//�^�b�N���^�C��

	bool wait = false;			//�ړ���҂�
	int ArrivalTime;			//�o������
	bool ArrivalFlag = false;	//�o��������
	Vector3 ArrivalPos;			//�o���ꏊ

	bool movePermet = false;

	Vector3 movePoint;			//�ړ���
	Vector3 ranMovePoint;		//�ړ���
	int movetime = 0;			//�ړ�����
	int waitTime = 0;			//�҂�����

	Vector3 dist;
	Vector3 pos_P; //�v���C���[�̃|�W�V����

	const int StartMovingDist = 60; //�ړ��J�n�����F�A�[�}�[�^�C�v�p
	const int finishTime = 0;
	bool ShotFlag;
	int ShotCount;

	int bulletStock;//�e�������ς���������
};