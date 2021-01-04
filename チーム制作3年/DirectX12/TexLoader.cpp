#include "TexLoader.h"
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include"DirectXManager.h"
//DirectXTex
#include"DirectXTex.h"
using namespace DirectX;


namespace {
	const int dataSize = 24;
}
TexLoader::TexLoader()
{
}

TexLoader::~TexLoader()
{
	texList.clear();
}

void TexLoader::Load(string filename)
{
	//WICテクスチャのロード
	wstring wf = wstring(filename.begin(), filename.end());
	const wchar_t *t = wf.c_str();
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	auto result = LoadFromWICFile(
		t,
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	const Image* img = scratchImg.GetImage(0, 0, 0);//生データ抽出
	//リソース設定
	CD3DX12_RESOURCE_DESC textureDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);
	ComPtr<ID3D12Resource>retData;
	//テクスチャ用バッファの作成
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&textureDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,//テクスチャ指定用
		nullptr,
		IID_PPV_ARGS(&retData)
	);
	//テクスチャバッファにデータを転送
	result = retData->WriteToSubresource(
		0,
		nullptr,
		img->pixels,
		(UINT)img->rowPitch,
		(UINT)img->slicePitch
	);
	//追加
	texList.emplace(filename,retData);
}

ComPtr<ID3D12Resource> TexLoader::GetTexList(const string& name)
{
	return texList[name];
}

TexLoader * TexLoader::GetInstance()
{
	static TexLoader instance;
	return &instance;
}

