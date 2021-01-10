#pragma once
#include<memory>
#include"BaseScene.h"
#include"Input.h"
#include"Player.h"
#include"Enemy.h"
#include"ObjectManager.h"
#include"Camera.h"
#include"ModelRenderer.h"
#include"TexRenderer.h"
#include"ParticleManager.h"
class GamePlay:public BaseScene
{
public:
	GamePlay();
	~GamePlay();

private:


	// BaseScene ����Čp������܂���
	virtual void StartScene() override;

	virtual void UpdateScene() override;

	virtual void DrawScene() override;

	ObjectManager* objM;
	Player* player;//�v���C���[�̎��̐���
	Enemy* enemy;
	Camera* camera;
	float x, y, z;
};
