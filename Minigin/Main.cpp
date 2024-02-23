#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

void load()
{
	auto& scene = enf::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<enf::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<enf::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = enf::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<enf::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif

	enf::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
