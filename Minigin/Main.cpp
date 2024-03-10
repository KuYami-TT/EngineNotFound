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
#include "Components/OrbitComp.h"
#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"
#include "Components/SpriteRenderComp.h"
#include "Components/TextRenderComp.h"

namespace fs = std::filesystem;
using namespace enf;

void DemoScene()
{
	auto& scene = SceneManager::Get().GetSceneByName("Demo");

	auto object = scene.AddGameObject("background");
	object->AddComponent<SpriteRenderComp>("background.tga");

	object = scene.AddGameObject("logo", glm::vec3{ 300.f, 80.f, 0.f });
	object->AddComponent<SpriteRenderComp>("logo.tga");

	object = scene.AddGameObject("title", glm::vec3{ 250.f, 20.f, 0.f });
	const auto titleFont = ResourceManager::Get().LoadFont("Lingua.otf", 26);
	object->AddComponent<TextRenderComp>(titleFont, "Programming 4 Assignment");

	object = scene.AddGameObject("fps", glm::vec3{ 10.f, 20.f, 0.f });
	const auto fpsFont = ResourceManager::Get().LoadFont("Lingua.otf", 20);
	object->AddComponent<FPSComp>(fpsFont);

	//Cacodemons c:<
	const auto pivotPoint = scene.AddGameObject("pivot", glm::vec3{ 300.f, 214.f, 10.f });

	const auto cacodemonMain = scene.AddGameObject("Cacodemon_96x96");
	cacodemonMain->SetParent(pivotPoint);
	cacodemonMain->AddComponent<SpriteRenderComp>("Cacodemon_96x96.png");
	cacodemonMain->AddComponent<OrbitComp>(0.5f, 40.f)->SetAngle(112.f);

	const auto cacodemon00 = scene.AddGameObject("Cacodemon_72x72");
	cacodemon00->SetParent(cacodemonMain);
	cacodemon00->AddComponent<SpriteRenderComp>("Cacodemon_72x72.png");
	cacodemon00->AddComponent<OrbitComp>(-1.f, 200.f)->SetAngle(45.f);

	const auto cacodemon01 = scene.AddGameObject("Cacodemon_48x48");
	cacodemon01->SetParent(cacodemon00);
	cacodemon01->AddComponent<SpriteRenderComp>("Cacodemon_48x48.png");
	cacodemon01->AddComponent<OrbitComp>(6.f, 80.f)->SetAngle(240.f);

	const auto cacodemon02 = scene.AddGameObject("cacodemon_36x36");
	cacodemon02->SetParent(cacodemon01);
	cacodemon02->AddComponent<SpriteRenderComp>("Cacodemon_36x36.png");
	cacodemon02->AddComponent<OrbitComp>(12.f, 40.f)->SetAngle(85.f);
}

void load()
{
	SceneManager::Get().CreateScene("Demo");

	DemoScene();
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
