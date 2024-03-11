#include "SceneManager.h"

#include <stdexcept>

#include "Renderer.h"

void enf::SceneManager::Awake()
{
	for (const auto& scene : m_ScenesPtr)
	{
		scene->Awake();
	}
}

void enf::SceneManager::FixedUpdate()
{
	for (const auto& scene : m_ScenesPtr)
	{
		scene->FixedUpdate();
	}
}

void enf::SceneManager::Update()
{
	Renderer::Get().Update();

	for(const auto& scene : m_ScenesPtr)
	{
		scene->Update();
	}
}

void enf::SceneManager::LateUpdate()
{
	for (const auto& scene : m_ScenesPtr)
	{
		scene->LateUpdate();
	}
}

void enf::SceneManager::CleanUp()
{
	for (const auto& scene : m_ScenesPtr)
	{
		scene->CleanUp();
	}
}

void enf::SceneManager::CreateScene(const std::string& name)
{
	m_ScenesPtr.push_back(std::make_unique<Scene>(name));
}

enf::Scene& enf::SceneManager::GetSceneByName(const std::string& name) const
{
	for (const auto& scene : m_ScenesPtr)
	{
		if (scene->GetName() == name)
		{
			return *scene;
		}
	}
	throw std::runtime_error("Scene not found");
}
