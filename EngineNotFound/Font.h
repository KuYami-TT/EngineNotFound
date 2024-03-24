#pragma once
#include <string>

struct _TTF_Font;
namespace enf
{
	/**
	 * Simple RAII wrapper for a _TTF_Font
	 */
	class Font final
	{
	public:
		explicit Font(const std::string& fullPath, int size);
		~Font();

		Font(Font &&) = delete;
		Font(const Font&) = delete;
		Font& operator=(Font&&) = delete;
		Font& operator=(const Font&) = delete;

		_TTF_Font* GetFont() const;

	private:
		_TTF_Font* m_FontPtr;
	};
}
