#include "Title.h"
#include"GamePlay.h"
#include"Collision.h"
#include"TexRenderer.h"

Title::Title():BaseScene()
{
}

Title::~Title()
{
	delete objM;//ちゃんと処理する（最後のシーンで）
}

void Title::StartScene()
{
	objM = new ObjectManager();
	objM->Claer();

	objM->Add(new Player(Vector3(0, 8.0f, -50.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle,BaseScene::mSprite));

	objM->Add(new Enemy(Vector3(0.0f, 6.0f, -120.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, 0));
	objM->Add(new Enemy(Vector3(4.0f, 6.0f, -150.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, 1));
	BaseScene::mModel->AddModel("Sora", "Resouse/skydome.obj", "Resouse/skydome.jpg");
	BaseScene::mModel->AddModel("Ground", "Resouse/ground.obj", "Resouse/sougen.jpg");
}

void Title::UpdateScene()
{
	objM->Update();
}

void Title::DrawScene()
{
	
	DirectXManager::GetInstance()->SetData3D();
	BaseScene::mModel->Draw("Sora", Vector3(0,0,-90.0f), Vector3(0, 0, 0), Vector3(5,5,5));
	BaseScene::mModel->Draw("Ground", Vector3(-20.0f, 4.0f,-90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
	objM->Draw();
}
