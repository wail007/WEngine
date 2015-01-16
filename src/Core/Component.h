#ifndef W_COMPONENT_H
#define W_COMPONENT_H


class ComponentTypeInfo;
class GameObject;

class Component
{
	friend class ComponentManager;

public:
	Component(int in_gameObjectId);
	Component(GameObject* in_gameObject);

	virtual ComponentTypeInfo getTypeInfo() const = 0;

	int	getGameObjectId()	const;

protected:
	int m_gameObjectId;

private:
	void setGameObjectId(int in_gameObjectId);
};

#endif