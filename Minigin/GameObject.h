#pragma once
#include <string>
#include <memory>
#include "Transform.h"

namespace dae
{
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

		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

	private:
		// todo: each gameobject doenst need a texture
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
	};
}
