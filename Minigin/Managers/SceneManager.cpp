#include "SceneManager.h"
#include "Scene.h"

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

void enf::SceneManager::Render()
{
	for (const auto& scene : m_ScenesPtr)
	{
		scene->Render();
	}
}

enf::Scene& enf::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_ScenesPtr.push_back(scene);
	return *scene;
}