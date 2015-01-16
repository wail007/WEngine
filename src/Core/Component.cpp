#include "Component.h"
#include "GameObject.h"

Component::Component(int in_gameObjectId)
	: m_gameObjectId(in_gameObjectId)
{

}

Component::Component(GameObject* in_gameObject)
	: m_gameObjectId(in_gameObject->getId())
{

}

int	Component::getGameObjectId() const
{
	return m_gameObjectId;
}

void Component::setGameObjectId(int in_gameObjectId)
{
	m_gameObjectId = in_gameObjectId;
}