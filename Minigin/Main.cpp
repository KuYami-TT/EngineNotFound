#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include <filesystem>

#include "glm/vec3.hpp"
#include "Minigin.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components/FPSComp.h"
#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"
#include "Components/SpriteRenderComp.h"
#include "Components/TextRenderComp.h"

namespace fs = std::filesystem;
using namespace enf;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto object = std::make_shared<GameObject>();
	object->AddComponent<SpriteRenderComp>("background.tga");
	scene.Add(object);

	object = std::make_shared<GameObject>(glm::vec3{216, 180, 0});
	object->AddComponent<SpriteRenderComp>("logo.tga");
	scene.Add(object);

	object = std::make_shared<GameObject>(glm::vec3{ 80, 20, 0 });
	const auto titleFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	object->AddComponent<TextRenderComp>(titleFont, "Programming 4 Assignment");
	scene.Add(object);

	object = std::make_shared<GameObject>(glm::vec3{ 0, 20, 0 });
	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	object->AddComponent<FPSComp>(fpsFont);
	scene.Add(object);
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
