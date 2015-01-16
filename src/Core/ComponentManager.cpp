#include "ComponentManager.h"
#include "Component.h"
#include "ComponentTypeInfo.h"
#include "GameObject.h"
#include "EventManager.h"
#include "../Utilities/DynamicMemoryPool.h"



ComponentManager::ComponentManager()
	: m_components(ComponentTypeInfo::sGetNbComponentTypes())
{
	m_components.resize(ComponentTypeInfo::sGetNbComponentTypes());

	ComponentTypeInfo::Iterator it;

	while (it.hasNext())
	{
		ComponentTypeInfo type		= it.getCurrent();

		m_components[type.typeId]	= DynamicMemoryPool(type.componentSize);

		it.next();
	}
}

template <typename T>
T* ComponentManager::addComponent(GameObject* in_gameObject, ComponentTypeInfo in_typeInfo)
{
	Component* component = m_components[in_typeInfo.typeId].get<Component>(in_gameObject->getId());

	component->setGameObjectId(in_gameObject->getId());

	in_gameObject->getComponentBits().set(in_typeInfo.typeId);

	EventManager::Get()->queueEvent(new GameObjectModifiedEvent(in_gameObject->getId()));

	return (T*)component;
}

//template <typename T>
//T* ComponentManager::addComponent(unsigned int in_gameObjectId, ComponentTypeInfo in_typeInfo)
//{
//
//}

//void ComponentManager::removeComponent(Component* in_component)
//{
//	
//}

void ComponentManager::removeComponent(GameObject* in_gameObject, ComponentTypeInfo in_typeInfo)
{
	Component* component = m_components[in_typeInfo.typeId].get<Component>(in_gameObject->getId());

	component->setGameObjectId(INVALID_GAMEOBJECT_ID);

	in_gameObject->getComponentBits().clear(in_typeInfo.typeId);

	EventManager::Get()->queueEvent(new GameObjectModifiedEvent(in_gameObject->getId()));
}

//void ComponentManager::removeComponent(unsigned int in_gameObject, ComponentTypeInfo in_typeInfo)
//{
//
//}