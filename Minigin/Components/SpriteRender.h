#pragma once
#include <memory>
#include "RenderComp.h"

namespace enf
{
	class Texture2D;

	class SpriteRenderComp final : public RenderComp
	{
	public:
		SpriteRenderComp(std::shared_ptr<Texture2D> pTexture);

		void Render() override;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};

}
