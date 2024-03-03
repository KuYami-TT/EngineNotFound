#include "Scene.h"
#include "GameObject.h"

#include <algorithm>


using namespace enf;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(std::string name) : m_Name(std::move(name))
{}

GameObject* Scene::AddGameObject(const std::string& name, const glm::vec3& pos)
{
	m_ObjectsPtr.emplace_back(std::make_unique<GameObject>(name, pos));
	return m_ObjectsPtr.back().get();
}

void Scene::Remove(const std::unique_ptr<GameObject>& objectPtr)
{
	m_ObjectsPtr.erase(std::ranges::remove(m_ObjectsPtr, objectPtr).begin(), m_ObjectsPtr.end());
}

void Scene::RemoveAll()
{
	m_ObjectsPtr.clear();
}

void Scene::Awake()
{
	for (const auto& object : m_ObjectsPtr)
	{
		if(object->IsMarked())
			continue;

		object->Awake();
	}
}

void Scene::FixedUpdate()
{
	for (const auto& object : m_ObjectsPtr)
	{
		if (object->IsMarked())
			continue;

		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for(const auto& object : m_ObjectsPtr)
	{
		if (object->IsMarked())
			continue;

		object->Update();
	}
}

void Scene::LateUpdate()
{
	for (const auto& object : m_ObjectsPtr)
	{
		if (object->IsMarked())
			continue;

		object->LateUpdate();
	}
}

void Scene::CleanUp()
{
	std::erase_if(m_ObjectsPtr,
		[](const std::unique_ptr<GameObject>& object)->bool
		{
			return object->IsMarked();
		});

	for (const auto& object : m_ObjectsPtr) 
	{
		object->CheckToMurder();
	}
}