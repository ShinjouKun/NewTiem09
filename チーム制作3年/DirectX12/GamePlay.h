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
#include"Sound.h"
class GamePlay:public BaseScene
{
public:
	GamePlay();
	~GamePlay();
	void EnemySponList();
	void EnemySponList2();
	void EnemySponList3();
private:
	bool GameOver;
	bool GameClear;
	bool spowflag;
	bool spowflag2;
	int SpowCnt;
	// BaseScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void StartScene() override;

	virtual void UpdateScene() override;

	virtual void DrawScene() override;

	ObjectManager* objM = new ObjectManager;
	Player* player;//ƒvƒŒƒCƒ„[‚ÌÀ‘Ì¶¬
	Enemy* enemy;
	Boss* boss;
	Camera* camera;
	Sound* ClearSound;
	Sound* GameOverSound;
	Sound* BGMsound;
	float x, y, z;
	bool fadeFlag;
	float fade;
	bool fadein;
};
