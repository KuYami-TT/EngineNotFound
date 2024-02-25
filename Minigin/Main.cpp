#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include <filesystem>

#include "Minigin.h"
#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "Components/TransformComp.h"
#include "Components/SpriteRenderComp.h"

namespace fs = std::filesystem;

void load()
{
	auto& scene = enf::SceneManager::GetInstance().CreateScene("Demo");

	auto object = std::make_shared<enf::GameObject>();
	object->AddComponent<enf::SpriteRenderComp>("background.tga");
	scene.Add(object);

	object = std::make_shared<enf::GameObject>(glm::vec3{216, 180, 0});
	object->AddComponent<enf::SpriteRenderComp>("logo.tga");
	scene.Add(object);

	//auto font = enf::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<enf::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
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
