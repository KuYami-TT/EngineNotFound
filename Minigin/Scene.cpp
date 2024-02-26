#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace enf;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(std::string name) : m_Name(std::move(name))
{}

void Scene::Add(std::shared_ptr<GameObject> objectPtr)
{
	m_ObjectsPtr.emplace_back(std::move(objectPtr));
}

void Scene::Remove(const std::shared_ptr<GameObject>& objectPtr)
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
		object->Awake();
	}
}

void Scene::FixedUpdate()
{
	for (const auto& object : m_ObjectsPtr)
	{
		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for(const auto& object : m_ObjectsPtr)
	{
		object->Update();
	}
}

void Scene::LateUpdate()
{
	for (const auto& object : m_ObjectsPtr)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_ObjectsPtr)
	{
		object->Render();
	}
}

