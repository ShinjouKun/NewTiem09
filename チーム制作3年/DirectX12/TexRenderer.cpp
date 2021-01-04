#include "TexRenderer.h"
#include"Window.h"
#include"TexLoader.h"
#include"DirectXManager.h"


TexRenderer::TexRenderer(PipeLine* pipe)
	:pipeLine(pipe)
{
	Init();
}

TexRenderer::~TexRenderer()
{
}

void TexRenderer::Init()
{
	data.texNum = 300;//FixMe
	matProjection.m[3][0] = -1.0f;
	matProjection.m[3][1] = 1.0f;
	matProjection.m[0][0] = 2.0f / Window::Window_Width;
	matProjection.m[1][1] = -2.0f / Window::Window_Height;
	
}

void TexRenderer::CreateVert()
{
	vertex.clear();
	vertex.resize(4);
	texSize = 100.0f;//初期サイズ
	vertex[0].pos.x = 0.0f;//左下
	vertex[0].pos.y = texSize;
	vertex[0].pos.z = 0.0f;
	vertex[0].uv.x = 0.0f;
	vertex[0].uv.y = 1.0f;

	vertex[1].pos.x = 0.0f;//左上
	vertex[1].pos.y = 0.0f;
	vertex[1].pos.z = 0.0f;
	vertex[1].uv.x = 0.0f;
	vertex[1].uv.y = 0.0f;

	vertex[2].pos.x = texSize;//右下
	vertex[2].pos.y = texSize;
	vertex[2].pos.z = 0.0f;
	vertex[2].uv.x = 1.0f;
	vertex[2].uv.y = 1.0f;

	vertex[3].pos.x = texSize;//右上
	vertex[3].pos.y = 0.0f;
	vertex[3].pos.z = 0.0f;
	vertex[3].uv.x = 1.0f;
	vertex[3].uv.y = 0.0f;
}

void TexRenderer::SetBuffer()
{
	//struct SpriteConstBuffData* constMap = nullptr;
	//頂点バッファ作成
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertex[0])*vertex.size()),//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&data.vertBuff));
	SpriteVert* vertMap;
	//バッファへデータを送信
	result = data.vertBuff->Map(0, nullptr, (void**)&vertMap);
	memcpy(vertMap, vertex.data(), sizeof(vertex[0])*vertex.size());
	data.vertBuff->Unmap(0, nullptr);
	//頂点バッファビュー
	data.vbView.BufferLocation = data.vertBuff->GetGPUVirtualAddress();
	data.vbView.SizeInBytes = sizeof(vertex[0])*vertex.size();
	data.vbView.StrideInBytes = sizeof(vertex[0]);
	//定数バッファ
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(SpriteConstBuffData) + 0xff)&~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&data.constBuff));

	//data.color = Vector4(0, 0, 0, 1);

	result = data.constBuff->Map(0, nullptr, (void**)&constMap);//マッピング
	constMap->color = data.color;
	constMap->mat = matProjection;
	data.constBuff->Unmap(0, nullptr);
}

void TexRenderer::SetUV(const string& name, float left, float top, float right, float bottom, bool inversionX, bool inversionY)
{
	auto d = spriteList[name];
	float Width = d.texSize.x;
	float Height = d.texSize.y;
	float Left = (0.0f, -d.ancPoint.x)*Width;
	float Right = (1.0f - d.ancPoint.x)*Width;
	float Top = (0.0f - d.ancPoint.y)*Height;
	float Bottom = (1.0f - d.ancPoint.y)*Height;
	//反転
	if (inversionX)
	{
		Left = -Left;
		Right = -Right;
	}

	if (inversionY)
	{
		Top = -Top;
		Bottom = -Bottom;
	}

	vertex[0].pos = Vector3(Left, Bottom, 0.0f);
	vertex[1].pos = Vector3(Left, Top, 0.0f);
	vertex[2].pos = Vector3(Right, Bottom, 0.0f);
	vertex[3].pos = Vector3(Right, Top, 0.0f);

	d.texUV = Vector4(left, top, right, bottom);
	vertex[0].uv = Vector2(left, bottom);
	vertex[1].uv = Vector2(left, top);
	vertex[2].uv = Vector2(right, bottom);
	vertex[3].uv = Vector2(right, top);

	SpriteVert* vertMap;
	//バッファへデータを送信
	result = data.vertBuff->Map(0, nullptr, (void**)&vertMap);
	memcpy(vertMap, vertex.data(), sizeof(vertex[0])*vertex.size());
	data.vertBuff->Unmap(0, nullptr);
	spriteList.emplace(name, d);
}

void TexRenderer::SetAncPoint(const string& key,const Vector2& point)
{
	auto d = spriteList[key];
	spriteList.erase(key);
	d.ancPoint = point;
	spriteList.emplace(key, d);
}

void TexRenderer::CreateTexture(const string& name)
{
	UINT descriptorHandleIncrementSize;

	descriptorHandleIncrementSize =
		DirectXManager::GetInstance()->Dev()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	ComPtr<ID3D12Resource> res;
	res = TexLoader::GetInstance()->GetTexList(name);
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = res->GetDesc();//受け取る
	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	//data.texNum = 300;
	DirectXManager::GetInstance()->Dev()->CreateShaderResourceView(res.Get(),
		&srvDesc,
		CD3DX12_CPU_DESCRIPTOR_HANDLE(pipeLine->GetDescripterHeap()->GetCPUDescriptorHandleForHeapStart(),
			data.texNum,
			descriptorHandleIncrementSize));
	
	
}


void TexRenderer::AddTexture(const string& key,const string& filename)
{
	texName = key;//キーワード登録
	//頂点データを画像サイズに書き換え
	data.texSize.x = (float)TexLoader::GetInstance()->GetTexList(filename)->GetDesc().Width;
	data.texSize.y = (float)TexLoader::GetInstance()->GetTexList(filename)->GetDesc().Height;
	CreateVert();
	vertex[0].pos = Vector3(0.0f, data.texSize.y, 0.0f);//左下
	vertex[1].pos = Vector3(0.0f, 0.0f, 0.0f);//左上
	vertex[2].pos = Vector3(data.texSize.x, data.texSize.y, 0.0f);//右下
	vertex[3].pos = Vector3(data.texSize.x, 0.0f, 0.0f);//右上
	data.ancPoint = Vector2(0.0f, 0.0f);
	data.texUV = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	SetBuffer();
	CreateTexture(filename);
	spriteList.emplace(texName,data);//転送
	data.texNum++;//カウントを進める
}

void TexRenderer::Draw(const string& name, const Vector3 & pos, float angle, const Vector2 & size, const Vector4 & color)
{

	SpriteConstBuffData* constMap = nullptr;
	auto d = spriteList[name];
	d.color = color;
	d.texSize = size;
	
	d.matWorld = Matrix4::Identity;
	d.matWorld = Matrix4::createTranslation(Vector3(d.ancPoint.x, d.ancPoint.y, 0.0f));
	d.matWorld *= Matrix4::RotateZ(angle);
	d.matWorld *= Matrix4::createTranslation(pos);
	//行列の転送
	result = d.constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = d.matWorld*matProjection;
	//constMap->color = Vector4(0, 0, 0, 1);
	constMap->color = d.color;
	d.constBuff->Unmap(0, nullptr);
	//頂点バッファセット
	DirectXManager::GetInstance()->CmdList()->IASetVertexBuffers(0, 1, &d.vbView);
	//定数バッファのセット
	DirectXManager::GetInstance()->CmdList()->SetGraphicsRootConstantBufferView(0, d.constBuff->GetGPUVirtualAddress());
	//シェーダリソースビューセット
	DirectXManager::GetInstance()->CmdList()->SetGraphicsRootDescriptorTable(
		1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(pipeLine->GetDescripterHeap()->GetGPUDescriptorHandleForHeapStart(),
			d.texNum,
			DirectXManager::GetInstance()->Dev()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	//描画コマンド
	DirectXManager::GetInstance()->CmdList()->DrawInstanced(vertex.size(), 1, 0, 0);//FixMe
}
