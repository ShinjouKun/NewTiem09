#pragma once
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include <map>
#include <string>
#include<wrl.h>
#include<iostream>
#include<DirectXMath.h>
#include "ModelLoader.h"
#include"Vector4.h"
#include"Matrix4.h"
#include"PipeLine.h"
using namespace DirectX;
using namespace std;
using namespace Microsoft::WRL;

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
struct ConstMap
{
	Vector4 color;
	Matrix4 mat;
	XMFLOAT4 MatAmbinent;
	XMFLOAT4 MatDiffuse;
	XMFLOAT4 MatSpecular;
};
struct DrawData
{
	//定数バッファ
    ComPtr<ID3D12Resource> constBuff;
	Matrix4 matWorld;//ワールド行
	UINT texNum;//テクスチャ番号
	Vector3 ancPoint3D;
	//GPUリソースの生
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ComPtr<ID3D12Resource>vertBuff;
	ComPtr<ID3D12Resource>indexBuff;
};
class ModelRenderer
{
private:
	map<string,OBJData*> datas;//保存用
	DrawData drawData;
	map<string,DrawData>drawDatas;
	//std::map<std::string, std::vector<UINT>>mIndices;
	PipeLine* pipeLine = nullptr;//パイプラインクラスの実体FixMe
	string modelName;
	Matrix4 matProjection;//射影変換行列
	

	//仮置き
	void SetBuffer(OBJData* data);
public:
	ModelRenderer(PipeLine* pipeline);
	~ModelRenderer();

	void AddModel(const string& key,const string& filename,const string& texName);//使うモデルの追加
	void CreateTexture(string filename);//モデル用のテクスチャデータ作成
	void SetMaterial(OBJData* matData);//マテリアルのセット
	void Draw(const string& key,const Vector3& pos,const Vector3& angle, const Vector3& scale);

	//アンカーポイント変更
	void SetAncPoint(const string& key,const Vector3& point);
	
};
