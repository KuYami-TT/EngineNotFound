#pragma once
#include <memory>
#include <string>

#include "RenderComp.h"

namespace enf
{
	class Texture2D;

	class SpriteRenderComp final : public RenderComp
	{
	public:
		SpriteRenderComp(const std::string& filename);
		~SpriteRenderComp() override = default;

		SpriteRenderComp(SpriteRenderComp&& other) = delete;
		SpriteRenderComp(const SpriteRenderComp& other) = delete;
		SpriteRenderComp& operator=(SpriteRenderComp&& other) = delete;
		SpriteRenderComp& operator=(const SpriteRenderComp& other) = delete;

		void Render() override;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
