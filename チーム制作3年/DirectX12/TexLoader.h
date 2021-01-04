#pragma once
#include"d3dx12.h"
#include"d3d12.h"
#include<string>
#include<iostream>
#include<vector>
#include<unordered_map>
#include"wrl.h"
#include<map>
using namespace std;
using namespace Microsoft::WRL;

class TexLoader
{
public:
	TexLoader();
	~TexLoader();
	void Load(string filename);
	//Get
	ComPtr<ID3D12Resource> GetTexList(const string& name);

	//�C���X�^���X�쐬�@���[�h�N���X�̓V���O���g����
	static TexLoader* GetInstance();
private:
	std::map<string, ComPtr<ID3D12Resource>>texList;//�摜�̃f�[�^���X�g
	
};
