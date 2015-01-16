#include "ComponentTypeInfo.h"

////////////////////////////////////////////////////////////////////////////////

std::map<std::string, ComponentTypeInfo> ComponentTypeInfo::s_componentTypes;

////////////////////////////////////////////////////////////////////////////////

ComponentTypeInfo::Iterator::Iterator()
	: m_it(s_componentTypes.begin())
{

}

void ComponentTypeInfo::Iterator::next()
{
	m_it++;
}

bool ComponentTypeInfo::Iterator::hasNext()
{
	return m_it != s_componentTypes.end();
}

ComponentTypeInfo ComponentTypeInfo::Iterator::getCurrent() const
{
	return m_it->second;
}

////////////////////////////////////////////////////////////////////////////////

ComponentTypeInfo::ComponentTypeInfo(int in_typeId, int in_componentSize, std::string in_name)
	: typeId(in_typeId), name(in_name), componentSize(in_componentSize)
{

}

ComponentTypeInfo::ComponentTypeInfo(const ComponentTypeInfo& in_copy)
	: typeId(in_copy.typeId), name(in_copy.name), componentSize(in_copy.componentSize)
{

}

template <typename T>
ComponentTypeInfo ComponentTypeInfo::sGetTypeInfo()
{
	static int nextId = 0;

	std::string n = typeid(T).name;

	Iterator it = s_componentTypes.find(n);

	if (it != s_componentTypes.end())
		return it->second;

	return (s_componentTypes[n] = ComponentTypeInfo(nextId++, sizeof(T), n));
}

int ComponentTypeInfo::sGetNbComponentTypes()
{
	return s_componentTypes.size();
}
