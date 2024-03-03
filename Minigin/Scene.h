#pragma once
#include "GameObject.h"
#include "Managers/SceneManager.h"

namespace enf
{
	class Scene final
	{
	public:
		~Scene() = default;

		Scene(Scene&& other) = delete;
		Scene(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;

		GameObject* AddGameObject(const ::std::string& name, const glm::vec3& pos = glm::vec3{ 0, 0, 0 });
		void Remove(const std::unique_ptr<GameObject>& objectPtr);
		void RemoveAll();

		void Awake();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void CleanUp();

	private:
		explicit Scene(std::string name);

		friend Scene& SceneManager::CreateScene(const std::string& name);

		std::string m_Name;
		std::vector <std::unique_ptr<GameObject>> m_ObjectsPtr{};

		static unsigned int m_IdCounter; 
	};
}
