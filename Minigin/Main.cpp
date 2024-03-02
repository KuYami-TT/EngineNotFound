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

	auto object = scene.AddGameObject("background");
	object->AddComponent<SpriteRenderComp>("background.tga");

	
	object = scene.AddGameObject("logo", glm::vec3{ 300, 80, 0 });
	object->AddComponent<SpriteRenderComp>("logo.tga");
	
	object = scene.AddGameObject("title", glm::vec3{ 250, 20, 0 });
	const auto titleFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	object->AddComponent<TextRenderComp>(titleFont, "Programming 4 Assignment");

	object = scene.AddGameObject("fps", glm::vec3{ 10, 20, 0 });
	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	object->AddComponent<FPSComp>(fpsFont);

	//Cacodemons c:<
	const auto cacodemonMain = scene.AddGameObject("Cacodemon_96x96", glm::vec3{ 214, 214, 0 });
	cacodemonMain->AddComponent<SpriteRenderComp>("Cacodemon_96x96.png");

	const auto cacodemon00 = scene.AddGameObject("Cacodemon_72x72");
	cacodemon00->AddComponent<SpriteRenderComp>("Cacodemon_72x72.png");
	cacodemon00->SetParent(cacodemonMain);

	const auto cacodemon01 = scene.AddGameObject("Cacodemon_48x48");
	cacodemon01->AddComponent<SpriteRenderComp>("Cacodemon_48x48.png");
	cacodemon01->SetParent(cacodemon00);
	cacodemon01->SetParent(cacodemonMain);

	const auto cacodemon02 = scene.AddGameObject("cacodemon_36x36");
	cacodemon02->AddComponent<SpriteRenderComp>("Cacodemon_36x36.png");
	cacodemon02->SetParent(cacodemon01);
	cacodemon02->SetParent(cacodemonMain);
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
