#include "GamePlay.h"
#include"Title.h"
GamePlay::GamePlay()
{
	
}

GamePlay::~GamePlay()
{
	delete objM;//重要
}

void GamePlay::EnemySponList()
{

	objM->Add(new Enemy(1, Vector3(6.0f, 6.0f, -130.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 10, mpattern::Tracking_B_LR));
	objM->Add(new Enemy(1, Vector3(10.0f, 6.0f, -150.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 9, mpattern::Tracking_B_LR));
	objM->Add(new Enemy(4, Vector3(4.0f, 6.0f, -300.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 8, mpattern::Armor));
	objM->Add(new Enemy(1, Vector3(2.0f, 6.0f, -320.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 5, mpattern::Fixation));
	objM->Add(new Enemy(1, Vector3(-10.0f, 6.0f, -200.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 4, mpattern::Fixation));
	objM->Add(new Enemy(1, Vector3(9.0f, 6.0f, -200.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 3, mpattern::Armor));
	objM->Add(new Enemy(1, Vector3(12.0f, 4.0f, -250.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 2, mpattern::Armor));
	objM->Add(new Enemy(1, Vector3(-12.0f, 4.0f, -180.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 1, mpattern::Armor));
}

void GamePlay::EnemySponList2()
{
	objM->Add(new Enemy(5, Vector3(4.0f, 6.0f, -390.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 15, mpattern::Armor));
	objM->Add(new Enemy(5, Vector3(10.0f, 4.0f, -380.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 14, mpattern::Armor));
	objM->Add(new Enemy(1, Vector3(-2.0f, 4.0f, -360.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 13, mpattern::Fixation));
	objM->Add(new Enemy(1, Vector3(4.0f, 6.0f, -170.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 12, mpattern::Tracking_B_UB));
	objM->Add(new Enemy(1, Vector3(-4.0f, 6.0f, -170.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 11, mpattern::Tracking_B_UB));
}

void GamePlay::EnemySponList3()
{
	objM->Add(new Boss(Vector3(0, 0, 0), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle));
	objM->Add(new Enemy(10, Vector3(0.0f, 6.0f, -510.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 25, mpattern::Armor));
	objM->Add(new Enemy(5, Vector3(4.0f, 4.0f, -530.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 24, mpattern::Armor));
	objM->Add(new Enemy(5, Vector3(-4.0f, 4.0f, -530.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 23, mpattern::Fixation));
	objM->Add(new Enemy(2, Vector3(2.0f, 6.0f, -500.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 22, mpattern::Fixation));
	objM->Add(new Enemy(3, Vector3(-4.0f, 6.0f, -480.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 21, mpattern::Armor));
	objM->Add(new Enemy(3, Vector3(4.0f, 4.0f, -480.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 22, mpattern::Armor));
	objM->Add(new Enemy(1, Vector3(0.0f, 6.0f, -220.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 20, mpattern::Tracking_B_UB));
	objM->Add(new Enemy(2, Vector3(8.0f, 6.0f, -440.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 19, mpattern::Fixation));
	objM->Add(new Enemy(2, Vector3(-10.0f, 4.0f, -460.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 18, mpattern::Fixation));
	objM->Add(new Enemy(1, Vector3(2.0f, 4.0f, -200.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 17, mpattern::Tracking_B_UB));
	
}

void GamePlay::StartScene()
{
	
	objM->Claer();
	fadeFlag = false;
	fadein = false;
	fade = 1.0f;
	BaseScene::mSprite->AddTexture("Fade", "Resouse/fade.png");
	GameOver = false;              //ゲームオーバー（player死んだとき）
	GameClear = false;				//ゲームクリア  （boss死んだとき）
	SpowCnt = 0;
	spowflag = false;
	spowflag2 = false;
	
	EnemySponList();
	objM->Add(new Player(Vector3(0, 8.0f, -50.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, BaseScene::mSprite));
	BaseScene::mModel->AddModel("Sora2", "Resouse/skydome.obj", "Resouse/sora.png");
	BaseScene::mModel->AddModel("Ground2", "Resouse/ground.obj", "Resouse/jimen.png");
	BaseScene::mModel->AddModel("Doukutu", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu2", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu3", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu4", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu5", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu6", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu7", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu8", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
	BaseScene::mModel->AddModel("Doukutu9", "Resouse/doukutu.obj", "Resouse/doukutu.jpg");
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
	if (!fadeFlag)
	{
		fade -= 0.03f;
		if (fade <= 0.0f)
		{
			fadeFlag = true;
		}
	}
	if (!objM->GetPlayerEnd()|| !objM->GetPlayerEnd())
	{
		objM->Update();
	}
	SpowCnt++;
	if (!spowflag&&SpowCnt >= 200)
	{
		EnemySponList2();
		spowflag = true;
	}
	if (!spowflag2&&SpowCnt >= 420)
	{
		EnemySponList3();
		spowflag2 = true;
	}

	if (objM->GetPlayerEnd())
	{
		BGMsound->Stop();
		GameOver = true;
		GameOverSound->Play("Resouse/GAMEOVER.wav");

		if (Input::KeyDown(DIK_1) || Input::PushButton(BUTTON_A))
		{
			fadein = true;
		}
	}
	if (objM->GetBossEnd())
	{
		BGMsound->Stop();
		GameClear = true;
		ClearSound->Play("Resouse/GAMECLAR.wav");
		if (Input::KeyDown(DIK_1) || Input::PushButton(BUTTON_A))
		{
			fadein = true;
		}
	}
	if (fadein)
	{
		fade += 0.01f;
		if (fade >= 1.0f)
		{
			GameOverSound->Stop();
			ClearSound->Stop();
			NextScene(std::make_shared<Title>());
		}
	}
	
}

void GamePlay::DrawScene()
{

	DirectXManager::GetInstance()->SetData3D();

	BaseScene::mModel->Draw("Sora2", Vector3(0, 4.0f, -400.0f), Vector3(0, 0.0f, 0), Vector3(10, 10, 10));
	BaseScene::mModel->Draw("Ground2", Vector3(-20.0f, 4.0f, -90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
	BaseScene::mModel->Draw("Doukutu", Vector3(0.0f, 2.0f, -150.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu2", Vector3(0.0f, 2.0f, -220.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu3", Vector3(0.0f, 2.0f, -280.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu4", Vector3(0.0f, 2.0f, -340.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu5", Vector3(0.0f, 2.0f, -390.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu6", Vector3(0.0f, 2.0f, -430.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu7", Vector3(0.0f, 2.0f, -460.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu8", Vector3(0.0f, 2.0f, -500.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
	BaseScene::mModel->Draw("Doukutu9", Vector3(0.0f, 2.0f, -540.0f), Vector3(0, 90.0f, 0), Vector3(15, 15, 15));
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
	if (!fadeFlag||fadein)
	{
		DirectXManager::GetInstance()->SetData2D();
		BaseScene::mSprite->Draw("Fade", Vector3(0, 0, 0), 0.0f, Vector2(1, 1), Vector4(1, 1, 1, fade));
	}
	
	objM->Draw();
	
}
