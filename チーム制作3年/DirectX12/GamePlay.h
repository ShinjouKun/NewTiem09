#pragma once
#include<memory>
#include"BaseScene.h"
#include"Input.h"
#include"Player.h"
#include"Enemy.h"
#include"Boss.h"
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
	bool GameOver;
	bool GameClear;

	// BaseScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void StartScene() override;

	virtual void UpdateScene() override;

	virtual void DrawScene() override;

	ObjectManager* objM;
	Player* player;//ƒvƒŒƒCƒ„[‚ÌÀ‘Ì¶¬
	Enemy* enemy;
	Boss* boss;
	Camera* camera;
	float x, y, z;
};
