#include "Title.h"
#include"GamePlay.h"
#include"Collision.h"


Title::Title()
{

}

Title::~Title()
{
	
}

void Title::StartScene()
{
	fade = 0.0f;
	wait = 0;
	camera->SetEye(Vector3(0.0f,6.0f,-90.0f));
	camera->SetTarget(Vector3(0.0f, 6.0f,-100.0f));
	BaseScene::mModel->AddModel("Taihou", "Resouse/taihou.obj", "Resouse/taihou.png");
	BaseScene::mModel->SetAncPoint("Taihou", Vector3(0.0f, -1.0f, 0.0f));
	BaseScene::mModel->AddModel("Yoko", "Resouse/yoko.obj", "Resouse/yoko.png");
	BaseScene::mModel->SetAncPoint("Yoko", Vector3(0.0f, -1.0f, 0.0f));
	BaseScene::mModel->AddModel("Daiza", "Resouse/daiza.obj", "Resouse/daiza.png");
	BaseScene::mModel->SetAncPoint("Daiza", Vector3(0.0f, -1.0f, 0.0f));
	
	BaseScene::mModel->AddModel("Sora", "Resouse/skydome.obj", "Resouse/skydome.jpg");
	BaseScene::mModel->AddModel("Ground", "Resouse/ground.obj", "Resouse/ground.png");
	BaseScene::mSprite->AddTexture("Title", "Resouse/Title.png");
	BaseScene::mSprite->AddTexture("Fade", "Resouse/fade.png");
	sound = new Sound();
	sound->LoadBGM("Resouse/TITLE.wav");
	sound->Play("Resouse/TITLE.wav");
	se = new Sound();
	se->LoadSE("Resouse/Click.wav");
	fadeFlag = false;
}

void Title::UpdateScene()
{
	wait++;
	if (wait>=30&&(Input::KeyDown(DIK_1) || Input::PushButton(BUTTON_A)))
	{
		se->Play("Resouse/Click.wav");
		fadeFlag = true;
	}
	if (fadeFlag)
	{
		fade += 0.01f;
		if (fade >= 1.0f)
		{
			NextScene(std::make_shared<GamePlay>());
			sound->Stop();
		}
	}
}

void Title::DrawScene()
{
	DirectXManager::GetInstance()->SetData3D();
	BaseScene::mModel->Draw("Sora", Vector3(0,2.0f, -120.0f), Vector3(0, 0.0f, 0), Vector3(5, 5, 5));
	BaseScene::mModel->Draw("Ground", Vector3(-20.0f, 4.0f, -90.0f), Vector3(0,0,0), Vector3(5, 5, 5));
	BaseScene::mModel->Draw("Taihou", Vector3(-2.0f, 6.0f, -95.0f), Vector3(20, -45.0f, 0), Vector3(1, 1,1));
	BaseScene::mModel->Draw("Yoko", Vector3(-2.0f, 5.0f, -95.0f), Vector3(0, -45.0f, 0), Vector3(1,1,1));
	BaseScene::mModel->Draw("Daiza", Vector3(-2.0f, 5.0f, -95.0f), Vector3(0, 0.0f, 0), Vector3(1,1,1));

	DirectXManager::GetInstance()->SetData2D();
	BaseScene::mSprite->Draw("Title", Vector3(0, 20, 0), 0.0f, Vector2(1, 1), Vector4(1, 1, 1, 1));
	BaseScene::mSprite->Draw("Fade", Vector3(0, 0, 0), 0.0f, Vector2(1, 1), Vector4(1, 1, 1, fade));
}
