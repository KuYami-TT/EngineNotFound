#pragma once

#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Renderer.h"

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

		[[nodiscard]] inline float GetRenderDepth() const { return GetOwner()->GetLocalPos().z; }
		[[nodiscard]] inline std::shared_ptr<Texture2D> GetTexturePtr() const { return m_TexturePtr; }

	protected:
		std::shared_ptr<Texture2D> m_TexturePtr{};

	private:
		Renderer* m_RendererPtr{};
	};
}
