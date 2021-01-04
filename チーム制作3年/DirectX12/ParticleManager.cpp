#include "ParticleManager.h"
#include"Camera.h"
#include"DirectXManager.h"
ParticleManager::ParticleManager(PipeLine* pipe):pipeLine(pipe)
{
	Init();
}

ParticleManager::~ParticleManager()
{
	particleDatas.clear();
}

void ParticleManager::Init()
{
	dataP.texNum = 400;
	matProjectionP = Matrix4::Identity;
	matProjectionP.m[3][0] = -1.0f;
	matProjectionP.m[3][1] = 1.0f;
	matProjectionP.m[0][0] = 2.0f / Window::Window_Width;
	matProjectionP.m[1][1] = -2.0f / Window::Window_Height;
}

void ParticleManager::Update()
{
	Matrix4 matBill = Matrix4::Identity;

	Vector3 zAxis = Vector3::normalize(Camera::target - Camera::eye);
	Vector3 xAxis = Vector3::normalize(Vector3::cross(Camera::up, zAxis));
	Vector3 yAxis = Vector3::normalize(Vector3::cross(zAxis, xAxis));
	float temp[4][4] =
	{
		{xAxis.x,xAxis.y,xAxis.z,0.0f},
		{yAxis.x,yAxis.y,yAxis.z,0.0f},
		{zAxis.x,zAxis.y,zAxis.z,0.0f},
		{0.0f,0.0f,0.0f,1.0f}
	};
	matBill = Matrix4(temp);
	//寿命が尽きたパーティクルの削除
	particles.remove_if([](ParticleStateus& x) {return x.frame >= x.numFrame; });
	//全パーティクル更新
	for (std::forward_list<ParticleStateus>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		//経過フレーム数
		it->frame++;
		//速度に加速度を加算
		it->vel = it->vel + it->acc;
		//速度による移動
		it->pos = it->pos + it->vel;

		//カラー
		//it->color = it->color;
		//スケール
		float f = (float)it->numFrame / it->frame;
		//スケールの線形保管
		it->scale = (it->eScale - it->sScale) / f;
		it->scale += it->sScale;


	}
	//頂点データをバッファへ
	VertexParticle* vertMap = nullptr;
	result = dataP.vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result))
	{
		for (std::forward_list<ParticleStateus>::iterator it = particles.begin(); it != particles.end(); it++)
		{
			vertMap->pos = it->pos;
			vertMap->color = it->color;
			vertMap->scale = it->scale;
			vertMap++;
		}
		dataP.vertBuff->Unmap(0, nullptr);
	}
	//行列の転送
	constMap = nullptr;
	result = dataP.constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = Camera::matView *matProjectionP;
	constMap->matBill = matBill;
	dataP.constBuff->Unmap(0, nullptr);
}

void ParticleManager::CreateBuff()
{
	//頂点バッファ作成
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(dataP.vertex[0])*dataP.vertex.size()),//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&dataP.vertBuff));

	VertexParticle* vertMap = nullptr;
	//バッファへデータを送信
	result = dataP.vertBuff->Map(0, nullptr, (void**)&vertMap);
	memcpy(vertMap, dataP.vertex.data(), sizeof(dataP.vertex[0])* dataP.vertex.size());
	dataP.vertBuff->Unmap(0, nullptr);


	//頂点バッファビュー
	dataP.vbView.BufferLocation = dataP.vertBuff->GetGPUVirtualAddress();
	dataP.vbView.SizeInBytes = sizeof(dataP.vertex[0])*dataP.vertex.size();
	dataP.vbView.StrideInBytes = sizeof(dataP.vertex[0]);


	//定数バッファ
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBuff) + 0xff)&~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&dataP.constBuff));

	XMMATRIX xx = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)Window::Window_Width / Window::Window_Height,
		0.1f, 1000.0f
	);
	result = dataP.constBuff->Map(0, nullptr, (void**)&constMap);//マッピング
	float xxx[4][4] =
	{
		{xx.r[0].m128_f32[0],xx.r[0].m128_f32[1],xx.r[0].m128_f32[2],xx.r[0].m128_f32[3]},
		{xx.r[1].m128_f32[0],xx.r[1].m128_f32[1],xx.r[1].m128_f32[2],xx.r[1].m128_f32[3]},
		{xx.r[2].m128_f32[0],xx.r[2].m128_f32[1],xx.r[2].m128_f32[2],xx.r[2].m128_f32[3]},
		{xx.r[3].m128_f32[0],xx.r[3].m128_f32[1],xx.r[3].m128_f32[2],xx.r[3].m128_f32[3]}
	};

	matProjectionP = Matrix4(xxx);
	constMap->mat = matProjectionP;
	dataP.constBuff->Unmap(0, nullptr);
}

void ParticleManager::CreatePlane()
{
	dataP.vertex.clear();
	dataP.vertex.resize(vertCount);
}

void ParticleManager::CreateTexture(const string& filename)
{
	UINT descriptorHandleIncrementSize;

	descriptorHandleIncrementSize =
		DirectXManager::GetInstance()->Dev()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	ComPtr<ID3D12Resource> res;
	res = TexLoader::GetInstance()->GetTexList(filename);
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = res->GetDesc();//受け取る
	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	
	DirectXManager::GetInstance()->Dev()->CreateShaderResourceView(res.Get(),
		&srvDesc,
		CD3DX12_CPU_DESCRIPTOR_HANDLE(pipeLine->GetDescripterHeap()->GetCPUDescriptorHandleForHeapStart(),
			dataP.texNum,
			descriptorHandleIncrementSize));
}

void ParticleManager::CreateParticleData(const string & key,const string& filename)
{
	string Texname = key;
	CreatePlane();

	std::vector<DirectVertexP>v;
	v.clear();
	v.resize(dataP.vertex.size());
	for (size_t i = 0; i < v.size(); i++)
	{
		v[i].pos.x = dataP.vertex[i].pos.x;
		v[i].pos.y = dataP.vertex[i].pos.y;
		v[i].pos.z = dataP.vertex[i].pos.z;
	}
	v.clear();
	CreateBuff();
	CreateTexture(filename);
	particleDatas.emplace(Texname, dataP);//追加
}

void ParticleManager::DrawParticleBill(const string & key)
{
	auto d = particleDatas[key];
	DirectXManager::GetInstance()->CmdList()->IASetVertexBuffers(0, 1, &d.vbView);
	DirectXManager::GetInstance()->CmdList()->SetGraphicsRootConstantBufferView(0, d.constBuff->GetGPUVirtualAddress());
	//シェーダリソースビューセット
	DirectXManager::GetInstance()->CmdList()->SetGraphicsRootDescriptorTable(
		1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(pipeLine->GetDescripterHeap()->GetGPUDescriptorHandleForHeapStart(),
			d.texNum,
			DirectXManager::GetInstance()->Dev()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));
	DirectXManager::GetInstance()->CmdList()->DrawInstanced((UINT)std::distance(particles.begin(), particles.end()), 1, 0, 0);
}

void ParticleManager::DrawParticleBillY(const string & key)
{
	Matrix4 matBill = Matrix4::Identity;
	auto d = particleDatas[key];

	Vector3 zAxis = Vector3::normalize(Camera::target - Camera::eye);
	Vector3 xAxis = Vector3::normalize(Vector3::cross(Camera::up, zAxis));
	Vector3 yAxis = Vector3::normalize(Camera::up);
	zAxis = Vector3::cross(xAxis, yAxis);
	float temp[4][4] =
	{
		{xAxis.x,xAxis.y,xAxis.z,0.0f},
		{yAxis.x,yAxis.y,yAxis.z,0.0f},
		{zAxis.x,zAxis.y,zAxis.z,0.0f},
		{0.0f,0.0f,0.0f,1.0f}
	};
	matBill = Matrix4(temp);

	//行列の転送
	result = d.constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->matBill = Camera::matView *matProjectionP;
	constMap->matBill = matBill;

	d.constBuff->Unmap(0, nullptr);

	DirectXManager::GetInstance()->CmdList()->IASetVertexBuffers(0, 1, &d.vbView);
	DirectXManager::GetInstance()->CmdList()->SetGraphicsRootConstantBufferView(0, d.constBuff->GetGPUVirtualAddress());
	//シェーダリソースビューセット
	DirectXManager::GetInstance()->CmdList()->SetGraphicsRootDescriptorTable(
		1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(pipeLine->GetDescripterHeap()->GetGPUDescriptorHandleForHeapStart(),
			d.texNum,
			DirectXManager::GetInstance()->Dev()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));
	DirectXManager::GetInstance()->CmdList()->DrawInstanced(d.vertex.size(),1,0,0);
}

void ParticleManager::Add(int life, const Vector3 & pos, const Vector3 & vel, const Vector3 & acc, float sScale, float eScale, const Vector4 & color)
{
	if (std::distance(particles.begin(), particles.end()) >= vertCount)
	{
		return;
	}
	particles.emplace_front();
	ParticleStateus& p = particles.front();
	//値のセット
	p.pos = pos;
	p.vel = vel;
	p.acc = acc;
	p.sScale = sScale;
	p.eScale = eScale;
	p.color = color;
	p.numFrame = life;
}

ParticleEmitterBox::ParticleEmitterBox(PipeLine* pipe):pipeLine(pipe)
{
	particle = new ParticleManager(pipe);
}

ParticleEmitterBox::~ParticleEmitterBox()
{
	delete particle;
}

void ParticleEmitterBox::LoadAndSet(const string& key,const string& filename)
{
	TexLoader::GetInstance()->Load(filename);
	particle->CreateParticleData(key,filename);
}

void ParticleEmitterBox::EmitterUpdate(const string& key, const Vector3& pos)
{
	this->pos = pos;
	for (int i = 0; i < 10; i++)
	{
		const float rndVel = 0.5f;
		Vector3 pVel;
		pVel.x = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;
		pVel.y = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;
		pVel.z = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;

		Vector3 acc;
		const float rndAcc = 0.005f;
		acc.y = -(float)rand() / RAND_MAX * rndAcc;

		//リストに追加
		particle->Add(20, pos, pVel, acc, 5.0f, 0.0f, Vector4(1,1,1,1));
	}
	particle->Update();
	particle->DrawParticleBill(key);
}

void ParticleEmitterBox::EmitterUpdateUpGas(const string & key, const Vector3 & pos)
{
	this->pos = pos;
	for (int i = 0; i < 10; i++)
	{
		const float rndVel = 0.5f;
		Vector3 pVel;
		//pVel.x = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;
		//pVel.y = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;
		pVel.z = (float)rand() / RAND_MAX * rndVel + rndVel / 2.0f;

		Vector3 acc;
		const float rndAcc = 0.005f;
		acc.y = -(float)rand() / RAND_MAX * rndAcc;

		/*Vector3 pCol;
		pCol.x = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;
		pCol.y = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;
		pCol.z = (float)rand() / RAND_MAX * rndVel - rndVel / 2.0f;*/
		//リストに追加
		particle->Add(60, pos, pVel, acc, 1.1f, 0.0f, Vector4(1,1,1,1));
	}
	particle->Update();
	particle->DrawParticleBill(key);
}

void ParticleEmitterBox::SetPos(Vector3 pos)
{
	this->pos = pos;
}
