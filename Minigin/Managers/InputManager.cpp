#include <SDL.h>

#include "InputManager.h"

#include "InputMap.h"
#include "backends/imgui_impl_sdl2.h"

#include "windows.h"
#include "Xinput.h"

class enf::InputManager::XInputImp final
{
public:
	XInputImp() = default;
	~XInputImp() = default;

	void ControllerInput();

	[[nodiscard]] std::vector<std::unique_ptr<Controller>>& GetControllers() { return m_Controllers; }
	[[nodiscard]] int GetMaxControllers() const { return m_MaxControllers; }

private:
	XINPUT_STATE m_CurrentState{};
	int m_ButtonsPressed{};
	int m_ButtonsReleased{};

	const int m_MaxControllers{ 4 };
	std::vector<std::unique_ptr<Controller>> m_Controllers{};

	void CheckControllerState(DWORD controllerIndex);
	[[nodiscard]] bool IsTriggered(unsigned int button) const;
	[[nodiscard]] bool IsReleased(unsigned int button) const;
	[[nodiscard]] bool IsDown(unsigned int button) const;
};

void enf::InputManager::XInputImp::ControllerInput()
{
	int i{};
	for (const auto& controller : m_Controllers)
	{
		CheckControllerState(i);

		for (const auto& mapped : controller->GetInputMap()->GetMap())
		{
			switch (mapped.first->GetInputState())
			{
			case Action::InputState::OnTrigger:
				{
					if (IsTriggered(static_cast<unsigned int>(mapped.first->GetInput())))
					{
						mapped.second->Execute();
					}
					break;
				}
			case Action::InputState::OnRelease:
				{
					if (IsReleased(static_cast<unsigned int>(mapped.first->GetInput())))
					{
						mapped.second->Execute();
					}
					break;
				}
			case Action::InputState::OnDown:
				{
					if (IsDown(static_cast<unsigned int>(mapped.first->GetInput())))
					{
						mapped.second->Execute();
					}
					break;
				}
			}
		}

		i++;
	}
}

void enf::InputManager::XInputImp::CheckControllerState(DWORD controllerIndex)
{
	XINPUT_STATE previousState;
	CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(controllerIndex, &m_CurrentState);

	const int buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	m_ButtonsPressed = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleased = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool enf::InputManager::XInputImp::IsTriggered(unsigned int button) const
{
	bool result = m_ButtonsPressed & button;
	return result;
}

bool enf::InputManager::XInputImp::IsReleased(unsigned int button) const
{
	return m_ButtonsReleased & button;
}

bool enf::InputManager::XInputImp::IsDown(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

enf::InputManager::InputManager() :
	m_ImplPtr(new XInputImp)
{
}

enf::InputManager::~InputManager() = default;

bool enf::InputManager::ProcessInput()
{
	m_ImplPtr->ControllerInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void enf::InputManager::AddController(GameObject* possessed, InputMap* inputMap)
{
	if (m_ImplPtr->GetControllers().size() >= m_ImplPtr->GetMaxControllers())
	{
		assert(false && "To many controllers have been added");
		return;
	}

	m_ImplPtr->GetControllers().push_back(std::make_unique<Controller>(possessed, inputMap));
}

enf::InputMap* enf::InputManager::AddInputMap()
{
	m_InputMaps.push_back(std::make_unique<InputMap>());
	return m_InputMaps.back().get();
}
