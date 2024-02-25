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

		void Render() override;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
