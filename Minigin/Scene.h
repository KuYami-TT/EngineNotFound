#pragma once
#include "Managers/SceneManager.h"

namespace enf
{
	class GameObject;
	class Scene final
	{
	public:
		~Scene() = default;

		Scene(Scene&& other) = delete;
		Scene(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;

		void Add(std::shared_ptr<GameObject> objectPtr);
		void Remove(const std::shared_ptr<GameObject>& objectPtr);
		void RemoveAll();

		void Awake();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;
		void CleanUp();

	private:
		explicit Scene(std::string name);

		friend Scene& SceneManager::CreateScene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_ObjectsPtr{};

		static unsigned int m_IdCounter; 
	};
}
