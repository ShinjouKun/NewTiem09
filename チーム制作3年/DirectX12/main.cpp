#include"Windows.h"
#include"d3d12.h"
#include"d3dx12.h"
#include"dxgi1_6.h"
#include"vector"
#include"wrl.h"
//FPS�p
#include<thread>
#include<chrono>

using namespace Microsoft::WRL;
using namespace std;
//���w���C�u����
#include"DirectXMath.h"
using namespace DirectX;
//�V�F�[�_�[�p
#include"d3dcompiler.h"
//DirectXTex
#include"DirectXTex.h"
//�C���v�b�g
#include"Input.h"
//������
#include"DirectXManager.h"
//�X�v���C�g�`��
#include"TexLoader.h"
#include"TexRenderer.h"
//�p�[�e�B�N��
#include"ParticleManager.h"
//���f��
#include"ModelLoader.h"//���[�h�p
#include"ModelRenderer.h"
//�f�o�b�O�X�v���C�g
#include"DebugText.h"
//��
#include"Sound.h"
//�E�B���h�E
#include"Window.h"
//�J����
#include"Camera.h"
//�V�[��
#include"SceneManager.h"
unique_ptr<SceneManager>mScene;//���̃N���X���������|�C���^
//�p�C�v���C��
#include"PipeLine.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
//�f�o�b�O
ComPtr<ID3D12Debug> debugController;

void Debug();//�f�o�b�O

//Main�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//���ݎ������}�C�N���b�Ŋl��
	std::function<long long(void)>currentTimeMicro = []()
	{
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
	};
	int cnt = 0;
	int fps = 60;//60fps�œ��삳����
	long long end = currentTimeMicro();//���ݎ��Ԃ̊l��(1�b = 1000000)
	long long next = end + (1000 * 1000 / fps);//���̍X�V���Ԃ��v�Z
	//�E�B���h�E�N���X
	Window* window = nullptr;
	window = new Window();
	window->CreateGameWindow();
	Debug();//�f�o�b�O�p
	//DXManager
	DirectXManager::GetInstance()->Init(window);
	//�J����
	Camera* camera = new Camera();

	PipeLine* pipeLine = new PipeLine();//�p�C�v���C������
	pipeLine->SetPipeline2D("unti2d");
	pipeLine->SetPipeline3D("unti");
	pipeLine->SetPipelineParticle("untiP");

	TexLoader::GetInstance()->Load("Resouse/hit.png");
	TexLoader::GetInstance()->Load("Resouse/sougen.jpg");
	TexLoader::GetInstance()->Load("Resouse/AIM64.png");
	
	//Player
	ModelLoader::GetInstance()->Load("Resouse/daiza.obj");
	ModelLoader::GetInstance()->Load("Resouse/yoko.obj");
	ModelLoader::GetInstance()->Load("Resouse/taihou.obj");
	//Enemy
	ModelLoader::GetInstance()->Load("Resouse/enemy2.obj");


	ModelLoader::GetInstance()->Load("Resouse/skydome.obj");
	ModelLoader::GetInstance()->Load("Resouse/ground.obj");

	

	
	//�X�v���C�g
	shared_ptr<TexRenderer>sprite = make_shared<TexRenderer>(pipeLine);
	
	//�p�[�e�B�N��
	shared_ptr<ParticleEmitterBox>paricle = make_shared<ParticleEmitterBox>(pipeLine);
	
	//���f��
	shared_ptr<ModelRenderer>model = make_shared<ModelRenderer>(pipeLine);
	
	//�T�E���h
	Sound* sound = new Sound();
	sound->LoadSE("Resouse/endingse.wav");
	sound->Play("Resouse/endingse.wav");
	
	Input* input = new Input();//�C���v�b�g�C���X�^���X����
	input->Init(window->GetHWND());//�C���v�b�g������
	//�V�[��
	mScene = std::make_unique<SceneManager>(sprite, model, paricle);
	while (true)
	{

		if (window->ProcesssMessage()) { break; }//���b�Z�[�W����
		DirectXManager::GetInstance()->Begin();
        //�L�[����
		input->Update();//input		
		//�`��
		mScene->Update();
		mScene->Draw();
		DirectXManager::GetInstance()->End();
		
#pragma region FPS����
		cnt++;//fps�p
		//�d����������������
		std::this_thread::sleep_for(std::chrono::microseconds(5));
		//�ł��邾��60fps�ɕۂ�
		end  = currentTimeMicro();
		if (end < next)
		{
			//�X�V���Ԃ܂őҋ@
			std::this_thread::sleep_for(std::chrono::microseconds(next - end));
			//���̍X�V���Ԃ��v�Z
			next += (1000 * 1000 / fps);
		}
		else
		{
			next = end + (1000 * 1000 / fps);
		}
#pragma endregion
		
	}

	window->DeleateGameWindow();//�Q�[��window�j��
	pipeLine->Clear();
	delete input;
	delete camera;
	delete sound;
	delete pipeLine;
	return 0;
}


void Debug()
{
	
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
}
