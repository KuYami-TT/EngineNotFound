#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"


namespace enf
{
	class Texture2D;
	class Component;
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

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

	private:
		//std::vector<std::unique_ptr<Component>> m_Components{};

		//todo: each gameobject doenst need a texture
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
	};
}
