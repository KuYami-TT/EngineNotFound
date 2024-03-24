#include <SDL.h>

#include "InputManager.h"

#include <ranges>

#include "InputMap.h"
#include "SDL_egl.h"
#include "backends/imgui_impl_sdl2.h"
#include "Commands/GameObjectCommand.h"

bool enf::InputManager::ProcessInput()
{
	const Uint8* keyboardStatePtr = SDL_GetKeyboardState(nullptr);

	for (auto&& controller : m_Controllers)
	{
		controller->HandleControllerInput();

		for (const auto& context : controller->GetInputMap()->GetKeyboardMap())
		{
			switch (context.first->GetInputState())
			{
			case Action::InputState::OnDown:
				if (keyboardStatePtr[EngineButtonToSDL_Scanecode(context.first->GetKeyboardInput())])
				{
					context.second->Execute();
				}
				break;
			}
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		}

		for (auto&& controller : m_Controllers)
		{
			for (const auto& context : controller->GetInputMap()->GetKeyboardMap())
			{
				switch (context.first->GetInputState())
				{
				case Action::InputState::OnTrigger:
					if (e.type == static_cast<Uint32>(SDL_KEYDOWN))
					{
						if (e.key.repeat) return true;

						if (e.key.keysym.sym == EngineButtonToSDL_KeyCode(context.first->GetKeyboardInput()))
							context.second->Execute();
					}
					break;
				case Action::InputState::OnRelease:
					if (e.type == static_cast<Uint32>(SDL_KEYUP))
					{
						if (e.key.keysym.sym == EngineButtonToSDL_KeyCode(context.first->GetKeyboardInput()))
							context.second->Execute();
					}
					break;
				}
			}
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void enf::InputManager::AddController(GameObject* possessed, InputMap* inputMap)
{
	if (m_Controllers.size() >= m_MaxControllers)
	{
		assert(false && "To many controllers have been added");
		return;
	}

	for (auto& command : inputMap->GetControllerMap() | std::views::values)
	{
		if (dynamic_cast<GameObjectCommand*>(command.get()))
		{
			dynamic_cast<GameObjectCommand*>(command.get())->SetPossessed(possessed);
		}
	}

	for (auto& command : inputMap->GetKeyboardMap() | std::views::values)
	{
		if (dynamic_cast<GameObjectCommand*>(command.get()))
		{
			dynamic_cast<GameObjectCommand*>(command.get())->SetPossessed(possessed);
		}
	}
	
	m_Controllers.push_back(std::make_unique<Controller>(possessed, inputMap, static_cast<int>(m_Controllers.size())));
}

enf::InputMap* enf::InputManager::AddInputMap()
{
	m_InputMaps.push_back(std::make_unique<InputMap>());
	return m_InputMaps.back().get();
}

SDL_KeyCode enf::InputManager::EngineButtonToSDL_KeyCode(Action::KeyboardLayout button)
{
	switch (button)
	{
	case Action::KeyboardLayout::KEYBOARD_Q:			return SDLK_q;
	case Action::KeyboardLayout::KEYBOARD_W:			return SDLK_w;
	case Action::KeyboardLayout::KEYBOARD_E:			return SDLK_e;
	case Action::KeyboardLayout::KEYBOARD_R:			return SDLK_r;
	case Action::KeyboardLayout::KEYBOARD_T:			return SDLK_t;
	case Action::KeyboardLayout::KEYBOARD_Y:			return SDLK_y;
	case Action::KeyboardLayout::KEYBOARD_U:			return SDLK_u;
	case Action::KeyboardLayout::KEYBOARD_I:			return SDLK_i;
	case Action::KeyboardLayout::KEYBOARD_O:			return SDLK_o;
	case Action::KeyboardLayout::KEYBOARD_P:			return SDLK_p;
	case Action::KeyboardLayout::KEYBOARD_A:			return SDLK_a;
	case Action::KeyboardLayout::KEYBOARD_S:			return SDLK_s;
	case Action::KeyboardLayout::KEYBOARD_D:			return SDLK_d;
	case Action::KeyboardLayout::KEYBOARD_F:			return SDLK_f;
	case Action::KeyboardLayout::KEYBOARD_G:			return SDLK_g;
	case Action::KeyboardLayout::KEYBOARD_H:			return SDLK_h;
	case Action::KeyboardLayout::KEYBOARD_J:			return SDLK_j;
	case Action::KeyboardLayout::KEYBOARD_K:			return SDLK_k;
	case Action::KeyboardLayout::KEYBOARD_L:			return SDLK_l;
	case Action::KeyboardLayout::KEYBOARD_Z:			return SDLK_z;
	case Action::KeyboardLayout::KEYBOARD_X:			return SDLK_x;
	case Action::KeyboardLayout::KEYBOARD_C:			return SDLK_c;
	case Action::KeyboardLayout::KEYBOARD_V:			return SDLK_v;
	case Action::KeyboardLayout::KEYBOARD_B:			return SDLK_b;
	case Action::KeyboardLayout::KEYBOARD_N:			return SDLK_n;
	case Action::KeyboardLayout::KEYBOARD_M:			return SDLK_m;
	case Action::KeyboardLayout::KEYBOARD_1:			return SDLK_1;
	case Action::KeyboardLayout::KEYBOARD_2:			return SDLK_2;
	case Action::KeyboardLayout::KEYBOARD_3:			return SDLK_3;
	case Action::KeyboardLayout::KEYBOARD_4:			return SDLK_4;
	case Action::KeyboardLayout::KEYBOARD_5:			return SDLK_5;
	case Action::KeyboardLayout::KEYBOARD_6:			return SDLK_6;
	case Action::KeyboardLayout::KEYBOARD_7:			return SDLK_7;
	case Action::KeyboardLayout::KEYBOARD_8:			return SDLK_8;
	case Action::KeyboardLayout::KEYBOARD_9:			return SDLK_9;
	case Action::KeyboardLayout::KEYBOARD_0:			return SDLK_0;
	case Action::KeyboardLayout::KEYBOARD_RETURN:		return SDLK_RETURN;
	case Action::KeyboardLayout::KEYBOARD_ESCAPE:		return SDLK_ESCAPE;
	case Action::KeyboardLayout::KEYBOARD_BACKSPACE:	return SDLK_BACKSPACE;
	case Action::KeyboardLayout::KEYBOARD_TAB:			return SDLK_TAB;
	case Action::KeyboardLayout::KEYBOARD_SPACE:		return SDLK_SPACE;
	default: return SDLK_UNKNOWN;
	}
}

SDL_Scancode enf::InputManager::EngineButtonToSDL_Scanecode(Action::KeyboardLayout button)
{
	switch (button)
	{
	case Action::KeyboardLayout::KEYBOARD_Q:			return SDL_SCANCODE_Q;
	case Action::KeyboardLayout::KEYBOARD_W:			return SDL_SCANCODE_W;
	case Action::KeyboardLayout::KEYBOARD_E:			return SDL_SCANCODE_E;
	case Action::KeyboardLayout::KEYBOARD_R:			return SDL_SCANCODE_R;
	case Action::KeyboardLayout::KEYBOARD_T:			return SDL_SCANCODE_T;
	case Action::KeyboardLayout::KEYBOARD_Y:			return SDL_SCANCODE_Y;
	case Action::KeyboardLayout::KEYBOARD_U:			return SDL_SCANCODE_U;
	case Action::KeyboardLayout::KEYBOARD_I:			return SDL_SCANCODE_I;
	case Action::KeyboardLayout::KEYBOARD_O:			return SDL_SCANCODE_O;
	case Action::KeyboardLayout::KEYBOARD_P:			return SDL_SCANCODE_P;
	case Action::KeyboardLayout::KEYBOARD_A:			return SDL_SCANCODE_A;
	case Action::KeyboardLayout::KEYBOARD_S:			return SDL_SCANCODE_S;
	case Action::KeyboardLayout::KEYBOARD_D:			return SDL_SCANCODE_D;
	case Action::KeyboardLayout::KEYBOARD_F:			return SDL_SCANCODE_F;
	case Action::KeyboardLayout::KEYBOARD_G:			return SDL_SCANCODE_G;
	case Action::KeyboardLayout::KEYBOARD_H:			return SDL_SCANCODE_H;
	case Action::KeyboardLayout::KEYBOARD_J:			return SDL_SCANCODE_J;
	case Action::KeyboardLayout::KEYBOARD_K:			return SDL_SCANCODE_K;
	case Action::KeyboardLayout::KEYBOARD_L:			return SDL_SCANCODE_L;
	case Action::KeyboardLayout::KEYBOARD_Z:			return SDL_SCANCODE_Z;
	case Action::KeyboardLayout::KEYBOARD_X:			return SDL_SCANCODE_X;
	case Action::KeyboardLayout::KEYBOARD_C:			return SDL_SCANCODE_C;
	case Action::KeyboardLayout::KEYBOARD_V:			return SDL_SCANCODE_V;
	case Action::KeyboardLayout::KEYBOARD_B:			return SDL_SCANCODE_B;
	case Action::KeyboardLayout::KEYBOARD_N:			return SDL_SCANCODE_N;
	case Action::KeyboardLayout::KEYBOARD_M:			return SDL_SCANCODE_M;
	case Action::KeyboardLayout::KEYBOARD_1:			return SDL_SCANCODE_1;
	case Action::KeyboardLayout::KEYBOARD_2:			return SDL_SCANCODE_2;
	case Action::KeyboardLayout::KEYBOARD_3:			return SDL_SCANCODE_3;
	case Action::KeyboardLayout::KEYBOARD_4:			return SDL_SCANCODE_4;
	case Action::KeyboardLayout::KEYBOARD_5:			return SDL_SCANCODE_5;
	case Action::KeyboardLayout::KEYBOARD_6:			return SDL_SCANCODE_6;
	case Action::KeyboardLayout::KEYBOARD_7:			return SDL_SCANCODE_7;
	case Action::KeyboardLayout::KEYBOARD_8:			return SDL_SCANCODE_8;
	case Action::KeyboardLayout::KEYBOARD_9:			return SDL_SCANCODE_9;
	case Action::KeyboardLayout::KEYBOARD_0:			return SDL_SCANCODE_0;
	case Action::KeyboardLayout::KEYBOARD_RETURN:		return SDL_SCANCODE_RETURN;
	case Action::KeyboardLayout::KEYBOARD_ESCAPE:		return SDL_SCANCODE_ESCAPE;
	case Action::KeyboardLayout::KEYBOARD_BACKSPACE:	return SDL_SCANCODE_BACKSPACE;
	case Action::KeyboardLayout::KEYBOARD_TAB:			return SDL_SCANCODE_TAB;
	case Action::KeyboardLayout::KEYBOARD_SPACE:		return SDL_SCANCODE_SPACE;
	default: return SDL_SCANCODE_UNKNOWN;
	}
}