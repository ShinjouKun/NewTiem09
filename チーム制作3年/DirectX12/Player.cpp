#include "Player.h"
#include"Bullet.h"
#include "Input.h"
#include<sstream>

Player::Player(Vector3 pos,
	Vector3 ang,
	ObjectManager * obj,
	shared_ptr<ModelRenderer> m, 
	shared_ptr<ParticleManager>p, 
	shared_ptr<TexRenderer>s)
	:playerModel(m),playerParticle(p),playerSprite(s)
{
	position = pos;
	angle = ang;
	objM = obj;
}

Player::~Player()
{
}

void Player::Shot()
{
	objM->Add(new Bullet(Vector3(position.x, position.y, position.z), Vector3(angle.x, angle.y, angle.z), objM, playerModel));
}

void Player::Init()
{
	//model
	playerModel->AddModel("Taihou", "Resouse/taihou.obj","Resouse/taihou.png");
	playerModel->SetAncPoint("Taihou", Vector3(0.0f, -1.0f, 0.0f));
	playerModel->AddModel("Yoko", "Resouse/yoko.obj", "Resouse/yoko.png");
	playerModel->SetAncPoint("Yoko", Vector3(0.0f, -1.0f, 0.0f));
	playerModel->AddModel("Daiza", "Resouse/daiza.obj", "Resouse/daiza.png");
	playerModel->SetAncPoint("Daiza", Vector3(0.0f, -1.0f, 0.0f));
	playerParticleBox = make_shared<ParticleEmitterBox>(playerParticle);
	playerParticleBox->LoadAndSet("Lazier","Resouse/BlueTile.png");
	playerSprite->AddTexture("Hit", "Resouse/hit.png");
	playerSprite->AddTexture("AIM", "Resouse/AIM64.png");
	playerSprite->SetAncPoint("AIM", Vector2(-32.0f, -32.0f));
	death = false;
	objType = ObjectType::PLAYER;
	SphereSize = 1.0f;
	position = Vector3(0.0f, 6.0f, -90.0f);
	firePos = Vector3(position.x,position.y + 1.5f,position.z);
	angle.x = 20.0f;
	angle.y = 180.0f;
	//AIMPos = Vector3(Window::Window_Width/2,Window::Window_Height/2,0.0f);
	AIMPos = Vector3(position.x,position.y,position.z);
	speed = 0.1f;	
}

void Player::Update()
{
	camera->SetEye(Vector3(position.x, position.y + 6.0f, position.z + 10.0f));
	camera->SetTarget(Vector3(position.x, position.y+6.0f, position.z));

	velocity = Vector3(0,0,0);

#pragma region キー押し処理
	//キー押し処理
	if (Input::KeyState(DIK_UP))
	{
		angle.x += 2.0f;
		AIMPos.y -= 6.0f;
	}
	//上限
	if (angle.x >= 60.0f)
	{
		angle.x = 60.0f;
	}

	if (Input::KeyState(DIK_DOWN))
	{
		angle.x -= 1.0f;
		AIMPos.y += 6.0f;
	}
	//下限
	if (angle.x <= -2.0f)
	{
		angle.x = 0.0f;
	}

	if (Input::KeyState(DIK_RIGHT))
	{
		angle.y -= 1.0f;
		AIMPos.x += 6.0f;
	}
	if (angle.y >= 220.0f)
	{
		angle.y = 220.0f;
	}
	if (Input::KeyState(DIK_LEFT))
	{
		angle.y += 2.0f;
		AIMPos.x -= 6.0f;
	}
	if (angle.y <= 140.0f)
	{
		angle.y = 140.0f;
	}
#pragma endregion

#pragma region ゲームパッド処理

	//　左スティック()

	if (Input::pad_data.lX < 0) {
		angle.y += 2.0f;
		AIMPos.x -= 6.0f;
		if (angle.y >= 220.0f)
		{
			angle.y = 220.0f;
		}
	}

	if (Input::pad_data.lX > 0) {
		angle.y -= 2.0f;
		AIMPos.x += 6.0f;
		
		if (angle.y <= 140.0f)
		{
			angle.y = 140.0f;
		}
	}	

	if (Input::pad_data.lY < 0) {
		angle.x += 2.0f;
		AIMPos.y -= 6.0f;
		if (angle.x <= -2.0f)
		{
			angle.x = 0.0f;
		}
	}
	if (Input::pad_data.lY > 0) {
		angle.x -= 2.0f;
		AIMPos.y += 6.0f;
		if (angle.x >= 60.0f)
		{
			angle.x = 60.0f;
		}
	}

	//　右スティック
	if (Input::pad_data.lZ < 0) {
		camera->CameraMoveEyeVector({ -2.0f,0,0 });

	}
	if (Input::pad_data.lZ > 0) {
		camera->CameraMoveEyeVector({ 2.0f,0,0 });

	}
	if (Input::pad_data.lRz < 0) {
		camera->CameraMoveEyeVector({ 0,2.0f,0 });

	}
	if (Input::pad_data.lRz > 0) {
		camera->CameraMoveEyeVector({ 0,-2.0f,0 });

	}

	if (Input::PushButton(BUTTON_B))
	{
		camera->CameraMoveEyeVector({ 0,180.0f,0 });

	}
	if (Input::PushButton(BUTTON_X))
	{
		position.z -= 1;

	}

	//　ショット
	if (Input::PushButton(BUTTON_A)) {
		Shot();
		shotFlag = true;
		shotcnt = 0;
	}


#pragma endregion


	
	
	if (shotFlag)
	{
		shotcnt++;
		if (shotcnt >= 30)
		{
			shotFlag = false;
		}
	}
	else
	{
	    if(Input::KeyDown(DIK_SPACE))
	    {
		   Shot();
		   shotFlag = true;
		   shotcnt = 0;
	    }
	}

}

void Player::Rend()
{
	
	DirectXManager::GetInstance()->SetData3D();//モデル用をセット
	playerModel->Draw("Taihou", Vector3(position.x, position.y+1.2f, position.z), Vector3(angle.x, angle.y, 0), Vector3(1.5f, 1.5f, 1.5f));
	playerModel->Draw("Yoko", Vector3(position.x, position.y, position.z), Vector3(0, angle.y, 0), Vector3(1.5f, 1.5f, 1.5f));
	playerModel->Draw("Daiza", Vector3(position.x-0.3f, position.y, position.z), Vector3(0, 0, 0), Vector3(1.5f, 1.5f, 1.5f));
	
	
	playerParticleBox->EmitterUpdateUpGas("Lazier", Vector3(firePos.x, firePos.y, firePos.z), Vector3(angle.x, -angle.y, 0.0f));
	DirectXManager::GetInstance()->SetData2D();
	
	if (!hitFlag)
	{
		DirectXManager::GetInstance()->SetData2D();
		playerSprite->Draw("Hit", Vector3(0, 0, 0), 0.0f, Vector2(0, 0), Vector4(1, 1, 1, 1));
		//playerSprite->Draw("AIM", Vector3(100, 100, 0), 0.0f, Vector2(0, 0), Vector4(1, 1, 1, 1));
	}
	
}

void Player::Hit(BaseObject & other)
{
	if (other.GetType() == ObjectType::ENEMY)
	{
		hitFlag = true;
	}
	else
	{
		hitFlag = false;
	}
	
}
