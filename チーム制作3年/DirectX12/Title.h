#pragma once
#include"BaseScene.h"
#include"Input.h"
#include<memory>
#include"Camera.h"
#include"CollisionPrimitive.h"
#include"ModelRenderer.h"
#include"TexRenderer.h"
#include"Player.h"
#include"Enemy.h"
#include"ObjectManager.h"
#include"Sound.h"
class Title:public BaseScene
{
public:
	Title();
	~Title();
	
private:

	// BaseScene ����Čp������܂���
	virtual void StartScene() override;

	virtual void UpdateScene() override;

	virtual void DrawScene() override;

	Camera* camera;	
	ObjectManager* objM;
	Player* player;//�v���C���[�̎��̐���
	Enemy* enemy;

	Vector3 p_pos;
	Sound* sound;
	Sound* se;
	bool fadeFlag;
	float fade;
	int wait;//�{�^���҂�
};
