#pragma once
#include <memory>
#include <string>

#include "RenderComp.h"
#include "Font.h"

namespace enf
{
	class TextRenderComp final : public RenderComp
	{
	public:
		TextRenderComp(Font* fontPtr, std::string text = {});
		~TextRenderComp() override = default;

		TextRenderComp(TextRenderComp&& other) = delete;
		TextRenderComp(const TextRenderComp& other) = delete;
		TextRenderComp& operator=(TextRenderComp&& other) = delete;
		TextRenderComp& operator=(const TextRenderComp& other) = delete;

		void Update() override;

		void SetText(const std::string& text);

	private:
		std::string m_Text;
		Font* m_FontPtr;
		std::unique_ptr<Texture2D> m_TextTexturePtr{};
		bool m_Dirty;
	};
}
