#include "GameObjectManager.h"
#include "GameObject.h"
#include "EventManager.h"

GameObjectManager::GameObjectManager()
	:m_idPool(), m_gameObjects(10)
{

}

GameObject* GameObjectManager::addGameObject()
{
	unsigned int id = m_idPool.getId();

	if (id >= m_gameObjects.size())
		m_gameObjects.resize(m_gameObjects.size() + id);

	m_gameObjects[id].m_id = id;

	EventManager::Get()->queueEvent(new GameObjectCreatedEvent(id));

	return &m_gameObjects[id];
}

void GameObjectManager::removeGameObject(GameObjectId in_id)
{
	m_destroyed.push_back(in_id);

	EventManager::Get()->queueEvent(new GameObjectDestroyedEvent(in_id));
}

GameObject* GameObjectManager::getGameObject(GameObjectId m_id)
{
	return &m_gameObjects[m_id];
}

void GameObjectManager::update()
{
	for (int i = 0; i < m_destroyed.size(); i++)
	{
		m_gameObjects[m_destroyed[i]].reset();
		m_idPool.recycleId(m_destroyed[i]);
	}

	m_destroyed.clear();
}