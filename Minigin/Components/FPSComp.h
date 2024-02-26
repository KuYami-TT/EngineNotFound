#pragma once
#include "Component.h"

namespace enf
{
	class FPSComp final : Component 
	{
		FPSComp() = default;
		~FPSComp() override = default;

		FPSComp(FPSComp&& other);
		FPSComp(const FPSComp& other) = delete;
		FPSComp& operator=(FPSComp&& other) = delete;
		FPSComp& operator=(const FPSComp& other) = delete;
	};
}
