#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Component.h"
#include "glm/vec3.hpp"

namespace enf
{
	template<typename ComponentType>
	concept IComponent = requires(ComponentType c)
	{
		{ std::derived_from<ComponentType, Component> };
	};

	class Texture2D;
	class GameObject final
	{
	public:
		GameObject(const std::string& name, const glm::vec3& pos = glm::vec3{0, 0, 0});
		~GameObject() = default;

		GameObject(GameObject&& other) = delete;
		GameObject(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;

		void Awake();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

        template<IComponent ComponentType, typename... TArgs>
        ComponentType* AddComponent(const TArgs&... args)
		{
			if (HasComponent<ComponentType>())
				return nullptr;
		
			auto& newCompPtr = m_ComponentsPtr.emplace_back(std::make_unique<ComponentType>(args...));
			newCompPtr->SetParent(this);
			newCompPtr->Awake();

			return reinterpret_cast<ComponentType*>(newCompPtr.get());
		}
		
		template<IComponent ComponentType>
		ComponentType* GetComponent()
		{
			auto it = std::ranges::find_if(m_ComponentsPtr, [](const std::unique_ptr<Component>& type)->bool
				{
					auto pCastedPtr = dynamic_cast<ComponentType*>(type.get());
					return pCastedPtr != nullptr;
				});

			if (it != m_ComponentsPtr.end())
			{
				return dynamic_cast<ComponentType*>(it->get());
			}

			return nullptr;
		}
		
		template<IComponent ComponentType>
		bool HasComponent()
		{
			return GetComponent<ComponentType>() != nullptr;
		}

		//Delete components that are marked for deletion 
		void CheckToMurder();

	private:
		std::string m_Name{};
		std::vector<std::unique_ptr<Component>> m_ComponentsPtr{};
	};
}
