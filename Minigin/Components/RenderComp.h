#pragma once

#include <memory>

#include "Component.h"
#include "Renderer.h"
#include "TransformComp.h"

namespace enf
{
	class Renderer;
	class TransformComp;

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

		[[nodiscard]] inline float GetRenderDepth() const { return m_TransformPtr->GetPosition().z; }
		[[nodiscard]] inline std::shared_ptr<Texture2D> GetTexturePtr() const { return m_TexturePtr; }
		[[nodiscard]] inline TransformComp* GetTransformPtr() const { return m_TransformPtr; }

	protected:
		std::shared_ptr<Texture2D> m_TexturePtr{};

	private:
		TransformComp* m_TransformPtr{};
		Renderer* m_RendererPtr{};
	};
}
