#pragma once

#ifdef USE_M2_MODELS

#include "M2/M2_Base_Instance.h"

class ZN_API GameObject
	: public CM2_Base_Instance
{
public:
	GameObject(IScene& Scene, const std::shared_ptr<CM2>& M2Object);
	virtual ~GameObject();
};

#endif