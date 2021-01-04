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

class Title:public BaseScene
{
public:
	Title();
	~Title();
	
private:

	// BaseScene を介して継承されました
	virtual void StartScene() override;

	virtual void UpdateScene() override;

	virtual void DrawScene() override;

	Camera* camera;
	ObjectManager* objM;//オブジェクトマネージャー
	Player* player;//プレイヤーの実体生成
	Enemy* enemy;
};
