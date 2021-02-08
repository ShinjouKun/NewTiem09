#include "GamePlay.h"
#include"Title.h"

GamePlay::GamePlay()
{
	
}

GamePlay::~GamePlay()
{
	delete objM;//重要
}

void GamePlay::StartScene()
{
	objM = new ObjectManager();
	objM->Claer();
	GameOver = false;              //ゲームオーバー（player死んだとき）
	GameClear = false;				//ゲームクリア  （boss死んだとき）
	objM->Add(new Player(Vector3(0, 8.0f, -50.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, BaseScene::mSprite));
	objM->Add(new Boss(Vector3(0, 0, 0), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle));
	BaseScene::mModel->AddModel("Sora2", "Resouse/skydome.obj", "Resouse/sora.png");
	BaseScene::mModel->AddModel("Ground2", "Resouse/ground.obj", "Resouse/sougen.jpg");
	ClearSound = new Sound();
	ClearSound->LoadBGM("Resouse/GAMECLEAR.wav");
	GameOverSound = new Sound();
	GameOverSound->LoadBGM("Resouse/GAMEOVER.wav");
	BGMsound = new Sound();
	BGMsound->LoadBGM("Resouse/vallery.wav");
	BGMsound->Play("Resouse/vallery.wav");
	BaseScene::mSprite->AddTexture("Clera", "Resouse/GAMECLAR.png");
	BaseScene::mSprite->AddTexture("GameOver", "Resouse/GAMEOVER.png");
}

void GamePlay::UpdateScene()
{
	objM->Update();
	
	
	if (objM->GetPlayerEnd())
	{
		BGMsound->Stop();
		GameOver = true;
		GameOverSound->Play("Resouse/GAMEOVER.wav");
		
		if (Input::KeyDown(DIK_1))
		{
			GameOverSound->Stop();
			NextScene(std::make_shared<Title>());
		}
	}
	if (objM->GetBossEnd())
	{
		BGMsound->Stop();
		GameClear = true;
		ClearSound->Play("Resouse/GAMECLAR.wav");
		if (Input::KeyDown(DIK_1))
		{
			ClearSound->Stop();
			NextScene(std::make_shared<Title>());
		}
	}
}

void GamePlay::DrawScene()
{
	DirectXManager::GetInstance()->SetData3D();
	BaseScene::mModel->Draw("Sora2", Vector3(0, 2.0f, -50.0f), Vector3(0, 0.0f, 0), Vector3(10, 10, 10));
	BaseScene::mModel->Draw("Ground2", Vector3(-20.0f, 4.0f, -90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
	if (GameClear)
	{
		DirectXManager::GetInstance()->SetData2D();
		BaseScene::mSprite->Draw("Clera", Vector3(0, 0, 0), 0.0f, Vector2(1, 1), Vector4(1, 1, 1, 1));
	}
	if (GameOver)
	{
		DirectXManager::GetInstance()->SetData2D();
		BaseScene::mSprite->Draw("GameOver", Vector3(0, 0, 0), 0.0f, Vector2(1, 1), Vector4(1, 1, 1, 1));
	}
	objM->Draw();
}
