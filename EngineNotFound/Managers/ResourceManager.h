#pragma once
#include <filesystem>
#include <map>
#include <string>
#include <memory>

#include "Singleton.h"
#include "Texture2D.h"
#include "Font.h"

namespace enf
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::filesystem::path& data);
		enf::Texture2D* LoadTexture(const std::string& file);
		enf::Font* LoadFont(const std::string& file, unsigned int size);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::filesystem::path m_dataPath;

		std::map<std::string, std::unique_ptr<Texture2D>> m_Textures{};
		std::map<std::string, std::unique_ptr<Font>> m_Fonts{};
	};
}
