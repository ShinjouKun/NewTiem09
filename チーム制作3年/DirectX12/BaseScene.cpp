#include "BaseScene.h"

BaseScene::BaseScene()
	:mSprite(nullptr),
	mModel(nullptr),
	mParticle(nullptr),
	mNext(nullptr),
	isInit(false)
{
}

BaseScene::~BaseScene()
{
	
}

void BaseScene::Update()
{
	Start();
	UpdateScene();
}

void BaseScene::Draw()
{
	if (!mSprite)
	{
		return;
	}
	if (!mModel)
	{
		return;
	}
	if (!mParticle)
	{
		return;
	}

	DrawScene();
}

void BaseScene::NextScene(std::shared_ptr<BaseScene> next)
{
	mNext = next;
}

std::shared_ptr<BaseScene> BaseScene::GetNextScene() const
{
	return mNext;
}

void BaseScene::SetSprite(std::shared_ptr<TexRenderer> sprite)
{
	mSprite = sprite;
}

void BaseScene::SetModel(std::shared_ptr<ModelRenderer> model)
{
	mModel = model;
}

void BaseScene::SetParticle(shared_ptr<ParticleManager> particle)
{
	mParticle = particle;
}



void BaseScene::Start()
{
	if(!isInit)
	{ 
		 StartScene();
		 isInit = true;
	}
}
