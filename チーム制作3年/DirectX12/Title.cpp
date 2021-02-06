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
	camera->SetEye(Vector3(0.0f,6.0f,-90.0f));
	camera->SetTarget(Vector3(0.0f, 6.0f,-100.0f));

	BaseScene::mModel->AddModel("Sora", "Resouse/skydome.obj", "Resouse/skydome.jpg");
	BaseScene::mModel->AddModel("Ground", "Resouse/ground.obj", "Resouse/sougen.jpg");
	BaseScene::mSprite->AddTexture("Title", "Resouse/Title.png");
}

void Title::UpdateScene()
{
	if (Input::KeyDown(DIK_1))
	{
		NextScene(std::make_shared<GamePlay>());
	}
}

void Title::DrawScene()
{
	DirectXManager::GetInstance()->SetData3D();
	BaseScene::mModel->Draw("Sora", Vector3(0,2.0f, -120.0f), Vector3(0, 0.0f, 0), Vector3(5, 5, 5));
	BaseScene::mModel->Draw("Ground", Vector3(-20.0f, 4.0f, -90.0f), Vector3(0,0,0), Vector3(5, 5, 5));
	DirectXManager::GetInstance()->SetData2D();
	BaseScene::mSprite->Draw("Title", Vector3(0, 0, 0), 0.0f, Vector2(1, 1), Vector4(1, 1, 1, 1));
}
