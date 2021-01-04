#include "SceneManager.h"
#include"Title.h"

SceneManager::SceneManager(shared_ptr<TexRenderer> sprite, shared_ptr<ModelRenderer> model, shared_ptr<ParticleEmitterBox>particle)
	:mSprite(sprite), mModel(model), mParticle(particle),
mNowScene(std::make_shared<Title>())//Å‰‚Íƒ^ƒCƒgƒ‹
{
	SetSpriteToScene();
	SetModelToScene();
	SetParticleToScene();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	mNowScene->Update();
	auto next = mNowScene->GetNextScene();
	if (next)
	{
		mNowScene = next;
		
		SetModelToScene();
		SetParticleToScene();
		SetSpriteToScene();
	}
}

void SceneManager::Draw() const
{
	mNowScene->Draw();
}

void SceneManager::SetSpriteToScene()
{
	mNowScene->SetSprite(mSprite);
}

void SceneManager::SetModelToScene()
{
	mNowScene->SetModel(mModel);
}

void SceneManager::SetParticleToScene()
{
	mNowScene->SetParticle(mParticle);
}
