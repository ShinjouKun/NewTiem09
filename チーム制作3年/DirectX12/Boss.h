#pragma once
#include "BaseObject.h"

class Bass : public BaseObject
{
public:
	Bass();
	~Bass();

	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
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