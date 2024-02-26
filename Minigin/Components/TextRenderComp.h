#pragma once
#include <memory>
#include <string>

#include "RenderComp.h"

namespace enf
{
	class Font;
	class Texture2D;

	class TextRenderComp final : public RenderComp
	{
	public:
		TextRenderComp(std::string text, std::shared_ptr<Font> pFont);
		~TextRenderComp() override = default;

		TextRenderComp(TextRenderComp&& other) = delete;
		TextRenderComp(const TextRenderComp& other) = delete;
		TextRenderComp& operator=(TextRenderComp&& other) = delete;
		TextRenderComp& operator=(const TextRenderComp& other) = delete;

		void Update() override;
		void Render() override;

	private:
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture{};

		bool m_Dirty;

		void SetText();
	};
}
