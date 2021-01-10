#include "Title.h"
#include"GamePlay.h"
#include"Collision.h"

Title::Title()
{

}

Title::~Title()
{
	delete objM;//�d�v
}

void Title::StartScene()
{
<<<<<<< HEAD
	p_pos = Vector3(0, 8.0f, -50.0f);
=======
	/*camera->SetEye(Vector3(0.0f,6.0f,-90.0f));
	camera->SetTarget(Vector3(0.0f, 6.0f,-100.0f));*/
>>>>>>> origin/しんじょーくん

	objM = new ObjectManager();
	objM->Claer();

<<<<<<< HEAD
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




=======
	objM->Add(new Player(Vector3(0, 8.0f, -50.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, BaseScene::mSprite));
	objM->Add(new Enemy(Vector3(0.0f, 6.0f, -120.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 0));
	objM->Add(new Enemy(Vector3(16.0f, 6.0f, -150.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 1));
	objM->Add(new Enemy(Vector3(-24.0f, 6.0f, -150.0f), Vector3(0, 0, 0), objM, BaseScene::mModel, BaseScene::mParticle, 2));
>>>>>>> origin/しんじょーくん
	BaseScene::mModel->AddModel("Sora", "Resouse/skydome.obj", "Resouse/skydome.jpg");
	BaseScene::mModel->AddModel("Ground", "Resouse/ground.obj", "Resouse/ground.png");
}

void Title::UpdateScene()
{
	objM->Update();
	if (Input::KeyDown(DIK_1))
	{
		NextScene(std::make_shared<GamePlay>());
	}
}

void Title::DrawScene()
{
	DirectXManager::GetInstance()->SetData3D();
<<<<<<< HEAD
	//BaseScene::mModel->Draw("Sora", Vector3(0,0,-90.0f), Vector3(0, 0, 0), Vector3(5,5,5));
	BaseScene::mModel->Draw("Ground", Vector3(-20.0f, 4.0f,-90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
=======
	BaseScene::mModel->Draw("Sora", Vector3(0, 0, -90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
	BaseScene::mModel->Draw("Ground", Vector3(-20.0f, 4.0f, -90.0f), Vector3(0, 0, 0), Vector3(5, 5, 5));
>>>>>>> origin/しんじょーくん
	objM->Draw();
}
