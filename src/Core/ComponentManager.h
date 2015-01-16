#ifndef W_COMPONENT_MANAGER_H
#define W_COMPONENT_MANAGER_H

#include "Manager.h"
#include <vector>

class GameObject;
class Component;
class ComponentTypeInfo;
class DynamicMemoryPool;

class ComponentManager : public Manager
{
public:
	ComponentManager();

	template <typename T>
	T* addComponent(GameObject* in_gameObject, ComponentTypeInfo in_typeInfo);

	//template <typename T>
	//T* addComponent(unsigned int in_gameObjectId, ComponentTypeInfo in_typeInfo);

	//void removeComponent(Component* in_component);
	void removeComponent(GameObject* in_gameObject, ComponentTypeInfo in_typeInfo);
	//void removeComponent(unsigned int in_gameObject, ComponentTypeInfo in_typeInfo);

private:
	std::vector<DynamicMemoryPool> m_components;
};

#endif