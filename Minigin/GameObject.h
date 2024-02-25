#pragma once
#include <string>
#include <memory>
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
	//todo: make gameobject final
	class GameObject
	{
	public:
		GameObject(const glm::vec3& pos = glm::vec3{0, 0, 0});
		virtual ~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Awake();
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render() const;

        template<IComponent ComponentType, typename... TArgs>
        ComponentType* AddComponent(const TArgs&... args)
		{
			assert(!HasComponent<ComponentType>());
		
			auto& newComp = m_Components.emplace_back(std::make_unique<ComponentType>(args...));
			newComp->SetParent(this);
			newComp->Awake();

			return reinterpret_cast<ComponentType*>(newComp.get());
		}
		
		template<IComponent ComponentType>
		ComponentType* GetComponent()
		{
			auto it = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component>& type)->bool
				{
					auto pCasted = dynamic_cast<ComponentType*>(type.get());
					return pCasted != nullptr;
				});

			if (it != m_Components.end())
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
		void CheckMarked();

		void SetTexture(const std::string& filename);

	private:
		std::vector<std::unique_ptr<Component>> m_Components{};

		//todo: each gameobject doenst need a texture
		std::shared_ptr<Texture2D> m_texture{};
	};
}
