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

		inline void SetOffset(glm::vec2 offset) { m_Offset = offset; }

		[[nodiscard]] inline Texture2D* GetTexturePtr() const { return m_TexturePtr; }
		[[nodiscard]] inline float GetRenderDepth() const { return GetOwner()->GetLocalPos().z; }
		[[nodiscard]] inline glm::vec2 GetOffset() const { return m_Offset; }

	protected:
		Texture2D* m_TexturePtr{};

	private:
		Renderer* m_RendererPtr{};
		glm::vec2 m_Offset{};
	};
}
