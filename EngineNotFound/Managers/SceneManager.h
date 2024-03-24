#pragma once
#include <vector>
#include <string>
#include <memory>

#include "InputMap.h"
#include "Singleton.h"
#include "Scene.h"

namespace enf
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(const std::string& name);

		[[nodiscard]] Scene& GetSceneByName(const std::string& name) const;

		void Awake();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void CleanUp();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::unique_ptr<Scene>> m_ScenesPtr;
	};
}
