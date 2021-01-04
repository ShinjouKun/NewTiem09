#pragma once
#include"wrl.h"
#include"d3d12.h"
#include"d3dx12.h"
#include"dxgi1_6.h"
#include"vector"
#include<memory>
//シェーダー用
#include"d3dcompiler.h"
//DirectXTex
#include"DirectXTex.h"
#include"Window.h"
//FPS用
#include<thread>
#include<chrono>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;

class PipeLine;

class DirectXManager
{
public:
	DirectXManager();
	~DirectXManager();
	void Init(Window* window);
	void Begin();
	void End();

	void SetData3D();//モデルと3Dオブジェクト用
	void SetData2D();//スプライト用
	void SetDataParticle();//パーティクル用
	static DirectXManager* GetInstance();
	ID3D12Device* Dev()const;
	ID3D12GraphicsCommandList*CmdList()const;

	//FPS管理用
	long long cnt = 0;
	 const int limit = 60;//FPS値
	 int time = currentTime();
	 //現在の時間を獲得する関数
	 long long currentTime();
	 void UpdateFPS();
	 void Update();//全更新
private:
	//初期化用
	HRESULT result;
	ComPtr<ID3D12Device>dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	
	
	//バックバッファの番号獲得
	UINT bbIndex; 
	//デプスステンシルビュー
	ComPtr<ID3D12DescriptorHeap>dsvHeap;
	ComPtr<ID3D12Resource> depthBuffer;

	ComPtr<ID3D12DescriptorHeap> basicDescHeap;
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	//パイプラインクラス
    shared_ptr<PipeLine> pipeLine;
	float r, g, b, a;//色

//定数バッファ初期化
	struct ConstBufferData
	{
		XMFLOAT4 color;//色（RGBA）
		XMMATRIX mat;//3D変換行列
	};

	ConstBufferData* constMap = nullptr;
	ComPtr<ID3D12Resource> constBuff;

};
