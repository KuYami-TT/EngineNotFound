#pragma once
#include "Singleton.h"

namespace enf
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
