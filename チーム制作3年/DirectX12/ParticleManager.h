#pragma once

#pragma once
#include"d3d12.h"
#include"d3dx12.h"
#include"dxgi1_6.h"
#include<memory>
#include<iostream>
#include<unordered_map>
#include"wrl.h"
#include"vector"
#include<map>
#include<forward_list>
//シェーダー用
#include"d3dcompiler.h"
//DirectXTex
#include"DirectXTex.h"
//ウィンドウ
#include"Window.h"

//数学ライブラリ
#include"DirectXMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

//ローダーとレンダラー
#include"TexLoader.h"
#include"PipeLine.h"
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")
struct ConstBuff
{
	Matrix4 mat;
	Matrix4 matBill;
};
struct VertexParticle
{
	Vector3 pos;//ポジション
	Vector4 color;
	float scale = 1.0f;//サイズ
};
struct DirectVertexP
{
	XMFLOAT3 pos;
};
struct ParticleData//描画用
{
	std::vector<VertexParticle>vertex;
	//GPUリソースの生成
	ComPtr<ID3D12Resource> vertBuff;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	UINT texNum;//テクスチャ番号
	Vector3 ancPoint3D;
};
struct ParticleStateus//パーティクル一粒のステータス
{
	Vector3 pos;//ポジション
	Vector3 vel;//速度
	Vector3 acc;//加速度
	Vector4 color;
	float scale = 1.0f;//サイズ
	//初期スケール
	float sScale = 1.0f;
	//最終スケール
	float eScale = 0.0f;
	int frame = 0;//現在フレーム
	int numFrame = 0;//終了フレーム
};
class ParticleManager
{
public:
	ParticleManager(PipeLine* pipe);
	~ParticleManager();
	void Init();
	void Update();
	void CreateBuff();
	void CreatePlane();//パーティクル用のいたポリ
	void CreateTexture(const string& filename);//テクスチャの適用(いらないかも)
	void CreateParticleData(const string& key,const string& filename);//パーティクル情報を作る
	void DrawParticleBill(const string& key);//全方向ビルボード
	void DrawParticleBillY(const string& key);//Y軸ビルボード

	//パーティクル用リストに追加
	void Add(int life, const Vector3& pos, const Vector3& vel, const Vector3& acc, float sScale, float eScale, const Vector4& color);
private:
	PipeLine* pipeLine = nullptr;//パイプラインクラスの実体FixMe
	ConstBuff*constMap;//定数バッファにデータを転送
	Matrix4 matProjectionP;//射影変換行列
	ParticleData dataP;
	HRESULT result; 
	map<string, ParticleData>particleDatas;//テクスチャのリスト
	//パーティクルリスト
	std::forward_list<ParticleStateus>particles;
	int vertCount = 1024;
};
class TexRenderer;//循環参照を避けたい
class ParticleEmitterBox//パーティクルの発生源
{
public:
	ParticleEmitterBox(PipeLine* pipe);
	~ParticleEmitterBox();
	void LoadAndSet(const string& key,const string& filename);//TexLoaderを呼び出し、TexRenderに渡してバッファをセットする
	void EmitterUpdate(const string& key, const Vector3& pos);//四方に広がる
	void EmitterUpdateUpGas(const string& key, const Vector3& pos);//上に排出される
	void SetPos(Vector3 pos);
private:
	PipeLine* pipeLine = nullptr;//パイプラインクラスの実体FixMe
	Vector3 pos;
	ParticleManager* particle;
	TexRenderer* rend;
};
