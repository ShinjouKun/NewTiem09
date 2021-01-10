#pragma once
#include "BaseObject.h"

class Bass : public BaseObject
{
public:
	Bass();
	~Bass();

	// BaseObject を介して継承されました
	virtual void Init() override;

	virtual void Update() override;

	virtual void Rend() override;

	virtual void Hit(BaseObject & other) override;



private:

};

Bass::Bass()
{
}

Bass::~Bass()
{
}