#pragma once
#include<memory>
#include"BaseScene.h"
#include"TexRenderer.h"
#include"ModelRenderer.h"
#include"ParticleManager.h"

using namespace std;
class SceneManager
{
public:
	SceneManager(shared_ptr<TexRenderer> sprite,
	shared_ptr<ModelRenderer>model, shared_ptr<ParticleEmitterBox>particle);
	~SceneManager();
	void Update();
	void Draw()const;
private:
	void SetSpriteToScene();
	void SetModelToScene();
	void SetParticleToScene();
	shared_ptr<TexRenderer>mSprite;
	shared_ptr<ModelRenderer>mModel;
	shared_ptr<ParticleEmitterBox>mParticle;

	shared_ptr<BaseScene>mNowScene;
};
