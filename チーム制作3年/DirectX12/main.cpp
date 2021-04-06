#include"Windows.h"
#include"d3d12.h"
#include"d3dx12.h"
#include"dxgi1_6.h"
#include"vector"
#include"wrl.h"
//FPS用
#include<thread>
#include<chrono>

using namespace Microsoft::WRL;
using namespace std;
//数学ライブラリ
#include"DirectXMath.h"
using namespace DirectX;
//シェーダー用
#include"d3dcompiler.h"
//DirectXTex
#include"DirectXTex.h"
//インプット
#include"Input.h"
//初期化
#include"DirectXManager.h"
//スプライト描画
#include"TexLoader.h"
#include"TexRenderer.h"
//パーティクル
#include"ParticleManager.h"
//モデル
#include"ModelLoader.h"//ロード用
#include"ModelRenderer.h"
//デバッグスプライト
#include"DebugText.h"
//音
#include"Sound.h"
//ウィンドウ
#include"Window.h"
//カメラ
#include"Camera.h"
//シーン
#include"SceneManager.h"
unique_ptr<SceneManager>mScene;//このクラスだけが持つポインタ
//パイプライン
#include"PipeLine.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
//デバッグ
ComPtr<ID3D12Debug> debugController;

void Debug();//デバッグ

//Main関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//現在時刻をマイクロ秒で獲得
	std::function<long long(void)>currentTimeMicro = []()
	{
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
	};
	int cnt = 0;
	int fps = 60;//60fpsで動作させる
	long long end = currentTimeMicro();//現在時間の獲得(1秒 = 1000000)
	long long next = end + (1000 * 1000 / fps);//次の更新時間を計算
	//ウィンドウクラス
	Window* window = nullptr;
	window = new Window();
	window->CreateGameWindow();
	Debug();//デバッグ用
	//DXManager
	DirectXManager::GetInstance()->Init(window);
	//カメラ
	Camera* camera = new Camera();

	PipeLine* pipeLine = new PipeLine();//パイプライン生成
	pipeLine->SetPipeline2D("unti2d");
	pipeLine->SetPipeline3D("unti");
	pipeLine->SetPipelineParticle("untiP");

	TexLoader::GetInstance(pipeLine)->Load("Resouse/hit.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/jimen.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/sora.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/sougen.jpg");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/Title.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/TaihouLife.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/stone.jpg");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/GAMECLAR.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/GAMEOVER.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/fade.png");
	TexLoader::GetInstance(pipeLine)->Load("Resouse/damage.png");
	//Player
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/daiza.obj");
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/yoko.obj");
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/taihou.obj");
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/L2.obj");
	//トンネル
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/doukutu.obj");
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/doukutu2.obj");
	//Enemy
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/enemy2.obj");
	//BOSS
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/boss1.obj");
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/boss1_core1.obj");
	//Bullet
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/Bullet.obj");
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/misail.obj");
	

	ModelLoader::GetInstance(pipeLine)->Load("Resouse/skydome.obj");
	ModelLoader::GetInstance(pipeLine)->Load("Resouse/ground.obj");

	//スプライト
	shared_ptr<TexRenderer>sprite = make_shared<TexRenderer>(pipeLine);
	
	//パーティクル
	shared_ptr<ParticleManager>paricle = make_shared<ParticleManager>(pipeLine);
	
	//モデル
	shared_ptr<ModelRenderer>model = make_shared<ModelRenderer>(pipeLine);
	
	//サウンド
	
	Input* input = new Input();//インプットインスタンス生成
	input->Init(window->GetHWND());//インプット初期化
	input->InitGamepad(window->GetHWND());
	//シーン
	mScene = std::make_unique<SceneManager>(sprite, model, paricle);
	while (true)
	{

		if (window->ProcesssMessage()) { break; }//メッセージ処理
		DirectXManager::GetInstance()->Begin();
        //キー入力
		input->Update();//input		
		input->UpdateGamepad();
		//描画
		mScene->Update();
		mScene->Draw();
		DirectXManager::GetInstance()->End();
		
#pragma region FPS処理
		cnt++;//fps用
		//重い処理があった時
		std::this_thread::sleep_for(std::chrono::microseconds(5));
		//できるだけ60fpsに保つ
		end  = currentTimeMicro();
		if (end < next)
		{
			//更新時間まで待機
			std::this_thread::sleep_for(std::chrono::microseconds(next - end));
			//次の更新時間を計算
			next += (1000 * 1000 / fps);
		}
		else
		{
			next = end + (1000 * 1000 / fps);
		}
#pragma endregion
		
	}

	window->DeleateGameWindow();//ゲームwindow破棄
	pipeLine->Clear();
	delete input;
	delete camera;
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
