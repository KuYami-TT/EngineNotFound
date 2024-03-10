#pragma once

#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Texture2D.h"

namespace enf
{
	class Renderer;

	class RenderComp : public Component
	{
	public:
		RenderComp() = default;
		~RenderComp() override;

		RenderComp(RenderComp&& other) = delete;
		RenderComp(const RenderComp& other) = delete;
		RenderComp& operator=(RenderComp&& other) = delete;
		RenderComp& operator=(const RenderComp& other) = delete;

		void Awake() override;

		[[nodiscard]] inline Texture2D* GetTexturePtr() const { return m_TexturePtr; }
		[[nodiscard]] inline float GetRenderDepth() const { return GetOwner()->GetLocalPos().z; }

	protected:
		Texture2D* m_TexturePtr{};

	private:
		Renderer* m_RendererPtr{};
	};
}
