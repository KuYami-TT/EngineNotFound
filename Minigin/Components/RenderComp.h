#pragma once

#include "Component.h"

namespace enf
{
	class TransformComp;

	class RenderComp : public Component
	{
	public:
		RenderComp() = default;
		~RenderComp() override = default;

		RenderComp(RenderComp&& other) = delete;
		RenderComp(const RenderComp& other) = delete;
		RenderComp& operator=(RenderComp&& other) = delete;
		RenderComp& operator=(const RenderComp& other) = delete;

		void Awake() override;

	protected:
		TransformComp* m_pTransform{};
	};
}