#include "GamePlay.h"
GamePlay::GamePlay()
{
	
}

GamePlay::~GamePlay()
{
	delete objM;//d—v
}

void GamePlay::StartScene()
{
	/*camera->SetEye(Vector3(0.0f, 6.0f, -90.0f));
	camera->SetTarget(Vector3(0.0f, 6.0f, -100.0f));*/
	objM = new ObjectManager();
	objM->Claer();

	objM->Add(new Player(Vector3(0, 8.0f, -50.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, BaseScene::mSprite));
	//objM->Add(new Enemy(Vector3(0.0f, 6.0f, -120.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 0));
	objM->Add(new Enemy(Vector3(16.0f, 6.0f, -150.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 1));
	objM->Add(new Enemy(Vector3(-24.0f, 6.0f, -150.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 2));


	BaseScene::mModel->AddModel("Sora2", "Resouse/skydome.obj", "Resouse/skydome.jpg");
	BaseScene::mModel->AddModel("Ground2", "Resouse/ground.obj", "Resouse/sougen.jpg");
}

void GamePlay::UpdateScene()
{
	objM->Update();
}

void GamePlay::DrawScene()
{
	DirectXManager::GetInstance()->SetData3D();
	BaseScene::mModel->Draw("Sora2", Vector3(0, 0, -90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
	BaseScene::mModel->Draw("Ground2", Vector3(-20.0f, 4.0f, -90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
	objM->Draw();
}
