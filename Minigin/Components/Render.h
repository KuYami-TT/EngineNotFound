#pragma once
#include "Component.h"

namespace enf
{
	class TransformComp;

	class RenderComp : public Component
	{
	public:
		void Awake() override;

	protected:
		TransformComp* m_TransformPtr{};
	};
}