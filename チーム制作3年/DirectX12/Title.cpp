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
	p_pos = Vector3(0, 8.0f, -50.0f);

	objM = new ObjectManager();
	objM->Claer();

	objM->Add(new Player(p_pos, Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle,BaseScene::mSprite));

	objM->Add(new Enemy(1,Vector3(0.0f, 6.0f, -180.0f),
		Vector3(0, 0, 0), objM,
		BaseScene::mModel,0,
		mpattern::Fixation));

	objM->Add(new Enemy(1, Vector3(8.0f, 6.0f,p_pos.z+20),
		Vector3(0, 0, 0), objM,
		BaseScene::mModel,1,
		mpattern::Tracking_A, 
		Vector3(8.0f,6.0f,p_pos.z -50)));

	objM->Add(new Enemy(1, Vector3(-20.0f, 6.0f, p_pos.z + 20),
		Vector3(0, 0, 0), objM,
		BaseScene::mModel, 2,
		mpattern::Tracking_A,
		Vector3(-10.0f, 20.0f, p_pos.z - 100)));




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
	//BaseScene::mModel->Draw("Sora", Vector3(0,0,-90.0f), Vector3(0, 0, 0), Vector3(5,5,5));
	BaseScene::mModel->Draw("Ground", Vector3(-20.0f, 4.0f,-90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
	objM->Draw();
}
