#include "ModelRenderer.h"
#include"Camera.h"
#include"Window.h"
#include"DirectXManager.h"
#include"TexLoader.h"


ModelRenderer::ModelRenderer(PipeLine* pipeline)
	:pipeLine(pipeline)
{
	drawData.texNum = 0;
	matProjection = Matrix4::Identity;
	matProjection.m[3][0] = -1.0f;
	matProjection.m[3][1] = 1.0f;
	matProjection.m[0][0] = 2.0f / Window::Window_Width;
	matProjection.m[1][1] = -2.0f / Window::Window_Height;
}

ModelRenderer::~ModelRenderer()
{
	datas.clear();
	drawDatas.clear();
}

void ModelRenderer::AddModel(const string& key,const string& filename, const string& texName)
{
	OBJData* data;
	modelName = key;//�L�[���[�h�o�^
	data = &ModelLoader::GetInstance()->GetOBJData(filename);
	SetBuffer(data);//�o�b�t�@�[�̃Z�b�g
	CreateTexture(texName);//���f���p�̃e�N�X�`���f�[�^���Z�b�g
	datas.emplace(modelName,data);//���X�g�ɕۊ�
	drawData.texNum++;
}

void ModelRenderer::CreateTexture(string texName)
{
	UINT descriptorHandleIncrementSize;

	descriptorHandleIncrementSize =
		DirectXManager::GetInstance()->Dev()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	ComPtr<ID3D12Resource> res;
	res = TexLoader::GetInstance()->GetTexList(texName);
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	D3D12_RESOURCE_DESC resDesc = res->GetDesc();//�󂯎��
	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	
	DirectXManager::GetInstance()->Dev()->CreateShaderResourceView(res.Get(),
		&srvDesc,
		CD3DX12_CPU_DESCRIPTOR_HANDLE(pipeLine->GetDescripterHeap()->GetCPUDescriptorHandleForHeapStart(),
			drawData.texNum,
			descriptorHandleIncrementSize));
	
	//drawData.texNum++;
}

void ModelRenderer::SetMaterial(OBJMatM * matData, ConstMap* map)
{
	map->MatAmbinent = XMFLOAT4(matData->Ambient[0], matData->Ambient[1], matData->Ambient[2],1);
	map->MatDiffuse = XMFLOAT4(matData->Diffuse[0], matData->Diffuse[1], matData->Diffuse[2], 1);
	map->MatSpecular = XMFLOAT4(matData->Specular[0], matData->Specular[1], matData->Specular[2], 1);
}

void ModelRenderer::SetBuffer(OBJData* data)
{
	HRESULT result;
	ConstMap* constMap = nullptr;
	//���_�o�b�t�@�쐬
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(data->mesh.vertex[0])*data->mesh.vertex.size()),//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&drawData.vertBuff));
	VertexModel* verts = nullptr;
	

	//index�o�b�t�@�쐬
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(data->mesh.index[0])*data->mesh.index.size()),//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&drawData.indexBuff));

	unsigned short* indexMap = nullptr;

	//�o�b�t�@�փf�[�^�𑗐M
	result = drawData.vertBuff->Map(0, nullptr, (void**)&verts);
	memcpy(verts, data->mesh.vertex.data(), sizeof(data->mesh.vertex[0])* data->mesh.vertex.size());
	drawData.vertBuff->Unmap(0, nullptr);

	//�o�b�t�@�փf�[�^�𑗐M
	result = drawData.indexBuff->Map(0, nullptr, (void**)&indexMap);
	memcpy(indexMap, data->mesh.index.data(), sizeof(data->mesh.index[0])* data->mesh.index.size());
	drawData.indexBuff->Unmap(0, nullptr);

	//���_�o�b�t�@�r���[
	drawData.vbView.BufferLocation = drawData.vertBuff->GetGPUVirtualAddress();
	drawData.vbView.SizeInBytes = sizeof(data->mesh.vertex[0])*data->mesh.vertex.size();
	drawData.vbView.StrideInBytes = sizeof(data->mesh.vertex[0]);
	//index�o�b�t�@�r���[
	drawData.ibView.BufferLocation = drawData.indexBuff->GetGPUVirtualAddress();
	drawData.ibView.Format = DXGI_FORMAT_R16_UINT;
	drawData.ibView.SizeInBytes = sizeof(data->mesh.index[0])* data->mesh.index.size();

	//�萔�o�b�t�@
	result = DirectXManager::GetInstance()->Dev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(DrawData) + 0xff)&~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&drawData.constBuff));

	XMMATRIX xx = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)Window::Window_Width / Window::Window_Height,
		0.1f, 1000.0f
	);
	result = drawData.constBuff->Map(0, nullptr, (void**)&constMap);//�}�b�s���OFixMe
	constMap->color = data->mat.color;
	float xxx[4][4] =
	{
		{xx.r[0].m128_f32[0],xx.r[0].m128_f32[1],xx.r[0].m128_f32[2],xx.r[0].m128_f32[3]},
		{xx.r[1].m128_f32[0],xx.r[1].m128_f32[1],xx.r[1].m128_f32[2],xx.r[1].m128_f32[3]},
		{xx.r[2].m128_f32[0],xx.r[2].m128_f32[1],xx.r[2].m128_f32[2],xx.r[2].m128_f32[3]},
		{xx.r[3].m128_f32[0],xx.r[3].m128_f32[1],xx.r[3].m128_f32[2],xx.r[3].m128_f32[3]}
	};

	matProjection = Matrix4(xxx);
	constMap->mat = matProjection;
	drawData.ancPoint3D = Vector3(0.0f, 0.0f, 0.0f);
	drawData.constBuff->Unmap(0, nullptr);
	drawDatas.emplace(modelName,drawData);
}

void ModelRenderer::Draw(const string& key,const Vector3& pos, const Vector3& angle, const Vector3& scale)
{
		HRESULT result;
		ConstMap* constMap = nullptr;
		
		auto d = drawDatas[key];
		
		d.texNum = d.texNum;//�e�N�X�`���̔ԍ���K�p
		d.matWorld = Matrix4::Identity;
		d.matWorld = Matrix4::createTranslation(d.ancPoint3D);
		d.matWorld *= Matrix4::createScale(scale);
		d.matWorld *= Matrix4::RotateZ(angle.z);
		d.matWorld *= Matrix4::RotateX(angle.x);
		d.matWorld *= Matrix4::RotateY(angle.y);
		d.matWorld *= Matrix4::createTranslation(Vector3(pos.x, pos.y, pos.z));
		
		//�s��̓]��
		result = d.constBuff->Map(0, nullptr, (void**)&constMap);
		constMap->color = d.color;//�F
	//�}�e���A���̓K�p
		SetMaterial(&datas[key]->mat,constMap);	
		constMap->mat = d.matWorld*Camera::matView *matProjection;
		d.constBuff->Unmap(0, nullptr);
		//���_�o�b�t�@�Z�b�g
		DirectXManager::GetInstance()->CmdList()->IASetVertexBuffers(0, 1, &d.vbView);
		DirectXManager::GetInstance()->CmdList()->IASetIndexBuffer(&d.ibView);
		//�萔�o�b�t�@�̃Z�b�g
		DirectXManager::GetInstance()->CmdList()->SetGraphicsRootConstantBufferView(0, d.constBuff->GetGPUVirtualAddress());
		//�V�F�[�_���\�[�X�r���[�Z�b�g
		DirectXManager::GetInstance()->CmdList()->SetGraphicsRootDescriptorTable(
			1,
			CD3DX12_GPU_DESCRIPTOR_HANDLE(
				pipeLine->GetDescripterHeap()->GetGPUDescriptorHandleForHeapStart(),
				d.texNum,
				DirectXManager::GetInstance()->Dev()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));
		//�`��R�}���h
		DirectXManager::GetInstance()->CmdList()->DrawIndexedInstanced(static_cast<UINT>(datas[key]->mesh.index.size()), 1, 0, 0, 0);
	
}

void ModelRenderer::SetAncPoint(const string& key,const Vector3 & point)
{
	auto d = drawDatas[key];
	drawDatas.erase(key);
	d.ancPoint3D = point;
	drawDatas.emplace(key, d);
}

void ModelRenderer::SetColor(const string & key, const Vector4 & c)
{
	auto d = drawDatas[key];
	drawDatas.erase(key);
	d.color = c;
	drawDatas.emplace(key, d);
}
