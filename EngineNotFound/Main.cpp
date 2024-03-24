#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include <filesystem>

#include "Action.h"
#include "glm/vec3.hpp"
#include "EngineNotFound.h"
#include "Scene.h"
#include "GameObject.h"
#include "GUI.h"
#include "InputMap.h"
#include "Commands/ActionCommand.h"
#include "Commands/MoveCommand.h"
#include "Components/FPSComp.h"
#include "Components/LivesComp.h"
#include "Components/MoveComp.h"
#include "Components/OrbitComp.h"
#include "Components/PlayerHud.h"
#include "Components/ScoreComp.h"
#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"
#include "Components/SpriteRenderComp.h"
#include "Components/TextRenderComp.h"
#include "Managers/InputManager.h"
#include "Observers/Subject.h"
#include "Widgets/TrashTheCache.h"

namespace fs = std::filesystem;
using namespace enf;

void DemoScene()
{
	auto& scene = SceneManager::Get().GetSceneByName("Demo");

	auto object = scene.AddGameObject("background");
	object->AddComponent<SpriteRenderComp>("background.tga");

	object = scene.AddGameObject("logo", glm::vec3{ 300.f, 80.f, 0.f });
	object->AddComponent<SpriteRenderComp>("logo.tga");

	const auto titleFont = ResourceManager::Get().LoadFont("Lingua.otf", 26);
	const auto fpsFont = ResourceManager::Get().LoadFont("Lingua.otf", 14);

	object = scene.AddGameObject("title", glm::vec3{ 250.f, 20.f, 0.f });
	object->AddComponent<TextRenderComp>(titleFont, "Programming 4 Assignment");

	object = scene.AddGameObject("fps", glm::vec3{ 10.f, 20.f, 0.f });
	object->AddComponent<FPSComp>(fpsFont);

	object = scene.AddGameObject("D-Pad", glm::vec3{ 10.f, 560.f, 0.f });
	object->AddComponent<TextRenderComp>(fpsFont, "Use the D-Pad to move the top cacodemon, X to inflict damage, A and B to pick up pellets");

	object = scene.AddGameObject("WASD", glm::vec3{ 10.f, 600.f, 0.f });
	object->AddComponent<TextRenderComp>(fpsFont, "Use WASD to move the bottom cacodemon, C to inflict damage, Z and X to pick up pellets");

	const auto controllerCacodemon = scene.AddGameObject("Controller Cacodemon", glm::vec3{ 100, 50, 10 });
	controllerCacodemon->AddComponent<SpriteRenderComp>("Cacodemon_96x96.png");
	controllerCacodemon->AddComponent<MoveComp>(200.f);
	{
		const auto livesSubject = controllerCacodemon->AddComponent<LivesComp>(3);
		const auto scoreSubject = controllerCacodemon->AddComponent<ScoreComp>();

		const auto hud = scene.AddGameObject("Player0 hud", glm::vec3{ 10, 75, 100 });
		const auto hudObserver = hud->AddComponent<PlayerHud>(fpsFont, livesSubject->GetLives());
		livesSubject->AddObserver(hudObserver);
		scoreSubject->AddObserver(hudObserver);
	}

	const auto keyboardCacodemon = scene.AddGameObject("Keyboard Cacodemon", glm::vec3{ 100, 150, 10 });
	keyboardCacodemon->AddComponent<SpriteRenderComp>("Cacodemon_96x96.png");
	keyboardCacodemon->AddComponent<MoveComp>(100.f);
	{
		const auto livesSubject = keyboardCacodemon->AddComponent<LivesComp>(3);
		const auto scoreSubject = keyboardCacodemon->AddComponent<ScoreComp>();

		const auto hud = scene.AddGameObject("Player1 hud", glm::vec3{ 10, 150, 100 });
		const auto hudObserver = hud->AddComponent<PlayerHud>(fpsFont, livesSubject->GetLives());
		livesSubject->AddObserver(hudObserver);
		scoreSubject->AddObserver(hudObserver);
	}

	//Controller
	const auto controllerInputMap = InputManager::Get().AddInputMap();
	controllerInputMap->BindAction<MoveUpCommand>(Action::InputState::OnDown, Action::ControllerLayout::GAMEPAD_DPAD_UP);
	controllerInputMap->BindAction<MoveLeftCommand>(Action::InputState::OnDown, Action::ControllerLayout::GAMEPAD_DPAD_LEFT);
	controllerInputMap->BindAction<MoveDownCommand>(Action::InputState::OnDown, Action::ControllerLayout::GAMEPAD_DPAD_DOWN);
	controllerInputMap->BindAction<MoveRightCommand>(Action::InputState::OnDown, Action::ControllerLayout::GAMEPAD_DPAD_RIGHT);
	controllerInputMap->BindAction<TakeDamageCommand>(Action::InputState::OnTrigger, Action::ControllerLayout::GAMEPAD_X);
	controllerInputMap->BindAction<GetPointsCommand>(Action::InputState::OnTrigger, Action::ControllerLayout::GAMEPAD_A, 10);
	controllerInputMap->BindAction<GetPointsCommand>(Action::InputState::OnTrigger, Action::ControllerLayout::GAMEPAD_B, 100);

	const auto keyboardInputMap = InputManager::Get().AddInputMap();
	keyboardInputMap->BindAction<MoveUpCommand>(Action::InputState::OnDown, Action::KeyboardLayout::KEYBOARD_W);
	keyboardInputMap->BindAction<MoveLeftCommand>(Action::InputState::OnDown, Action::KeyboardLayout::KEYBOARD_A);
	keyboardInputMap->BindAction<MoveDownCommand>(Action::InputState::OnDown, Action::KeyboardLayout::KEYBOARD_S);
	keyboardInputMap->BindAction<MoveRightCommand>(Action::InputState::OnDown, Action::KeyboardLayout::KEYBOARD_D);
	keyboardInputMap->BindAction<TakeDamageCommand>(Action::InputState::OnTrigger, Action::KeyboardLayout::KEYBOARD_C);
	keyboardInputMap->BindAction<GetPointsCommand>(Action::InputState::OnTrigger, Action::KeyboardLayout::KEYBOARD_Z, 10);
	keyboardInputMap->BindAction<GetPointsCommand>(Action::InputState::OnTrigger, Action::KeyboardLayout::KEYBOARD_X, 100);

	//TODO: make it so the input map can be copied (try map of values)
	//TODO: What if I want to have some commands without a gameObject?
	InputManager::Get().AddController(controllerCacodemon, controllerInputMap);
	InputManager::Get().AddController(keyboardCacodemon, keyboardInputMap);
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
