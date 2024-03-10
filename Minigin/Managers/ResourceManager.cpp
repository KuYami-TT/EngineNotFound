#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void enf::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

enf::Texture2D* enf::ResourceManager::LoadTexture(const std::string& file)
{
	//const auto fullPath = m_dataPath/file;
	//auto texturePtr = IMG_LoadTexture(Renderer::Get().GetSDLRenderer(), fullPath.string().c_str());
	//if (texturePtr == nullptr)
	//{
	//	throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	//}
	//return std::make_unique<Texture2D>(texturePtr);

	// Check if the texture is already loaded and return it
	if (m_Textures.contains(file))
		return m_Textures.at(file).get();

	// Load new texture
	const auto fullPath = m_dataPath / file;
	auto texturePtr = IMG_LoadTexture(Renderer::Get().GetSDLRenderer(), fullPath.string().c_str());
	if (texturePtr == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());

	m_Textures[file] = std::make_unique<Texture2D>(texturePtr);
	return m_Textures.at(file).get();
}

enf::Font* enf::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	// Check if the font is already loaded and return it
	if (m_Fonts.contains(file))
		return m_Fonts.at(file).get();

	// Load new font
	const auto fullPath = m_dataPath / file;
	m_Fonts[file] = std::make_unique<Font>(fullPath.string(), size);
	return m_Fonts.at(file).get();
}
