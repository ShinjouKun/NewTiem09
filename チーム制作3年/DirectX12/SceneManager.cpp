#include "SceneManager.h"
#include"Title.h"

SceneManager::SceneManager(shared_ptr<TexRenderer> sprite, shared_ptr<ModelRenderer> model, shared_ptr<ParticleManager>particle)
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
	mParticle->OllUpDate();
	
}

void SceneManager::Draw() const
{
	mNowScene->Draw();
	mParticle->OllDraw();
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
