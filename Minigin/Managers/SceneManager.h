#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace enf
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Awake();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
