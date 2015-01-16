#include "GameObject.h"

GameObject::GameObject()
	: m_id(INVALID_GAMEOBJECT_ID), m_componentBits()
{

}

GameObject::GameObject(int in_id)
	: m_id(in_id), m_componentBits()
{

}

GameObject::GameObject(const GameObject& in_copy)
	: m_id(in_copy.m_id), m_componentBits(in_copy.m_componentBits)
{

}

GameObjectId GameObject::getId() const
{
	return m_id;
}

bool GameObject::isActive()	const
{
	return m_id == INVALID_GAMEOBJECT_ID;
}

BitSet GameObject::getComponentBitsCopy() const
{
	return m_componentBits;
}

BitSet&	GameObject::getComponentBits()
{
	return m_componentBits;
}
		
void GameObject::reset()
{
	m_id = INVALID_GAMEOBJECT_ID;
	m_componentBits.clearAll();
}