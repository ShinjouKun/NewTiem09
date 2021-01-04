#pragma once
#include"BaseScene.h"
#include"Input.h"
#include"Player.h"
#include"ObjectManager.h"
#include"Camera.h"
class GamePlay:public BaseScene
{
public:
	GamePlay();
	~GamePlay();

private:


	// BaseScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void StartScene() override;

	virtual void UpdateScene() override;

	virtual void DrawScene() override;

	ObjectManager* objM;
	Player* player;
	Camera* camera;//FixMe sherdPtr‚É
	float x, y, z;
};
