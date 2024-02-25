#pragma once
#include <string>
#include <memory>
#include "GameObject.h"

namespace enf
{
	class Font;
	class Texture2D;
	class TextObject final : public GameObject
	{
	public:
		TextObject(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextObject() = default;

		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
