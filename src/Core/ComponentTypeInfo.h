#ifndef W_COMPONENT_TYPE_INFO_H
#define W_COMPONENT_TYPE_INFO_H

#include <string>
#include <map>
#include <typeinfo>

class ComponentTypeInfo
{
public:
	class Iterator
	{
	public:
		Iterator();

		void next();
		bool hasNext();

		ComponentTypeInfo getCurrent() const;

	private:
		std::map<std::string, ComponentTypeInfo>::iterator m_it;
	};

public:	
	template <typename T>
	static ComponentTypeInfo sGetTypeInfo();

	static int		sGetNbComponentTypes();


	ComponentTypeInfo(const ComponentTypeInfo& in_copy);	

	const int			typeId;
	const int			componentSize;
	const std::string	name;

private:
	static std::map<std::string, ComponentTypeInfo>	s_componentTypes;

	ComponentTypeInfo();
	ComponentTypeInfo(int in_typeId, int in_componentSize, std::string in_name);
};

#endif