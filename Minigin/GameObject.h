#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"
#include "Component.h"


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
		GameObject() = default;
		virtual ~GameObject();

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

			return reinterpret_cast<ComponentType*>(newComp.get());
		}
		
		template<IComponent ComponentType>
		std::unique_ptr<ComponentType> GetComponent()
		{
			auto it = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component>& type)->bool
				{
					auto pCasted = dynamic_cast<ComponentType*>(type.get());
					return pCasted != nullptr;
				});

			if (it != m_Components.end())
			{
				return std::unique_ptr<ComponentType>(dynamic_cast<ComponentType*>(it->release()));
			}

			return nullptr;
		}
		
		template<IComponent ComponentType>
		bool HasComponent()
		{
			return GetComponent<ComponentType>() != nullptr;
		}

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

	private:
		std::vector<std::unique_ptr<Component>> m_Components{};

		//todo: each gameobject doenst need a texture
		TransformZ m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
	};
}
