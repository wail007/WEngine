#ifndef W_GAME_OBJECT_H
#define W_GAME_OBJECT_H

#include "../Utilities/BitSet.h"

#define INVALID_GAMEOBJECT_ID -1

typedef int GameObjectId;

class Component;

class GameObject
{
	friend class GameObjectManager;

public:
	GameObject();
	GameObject(int in_id);
	GameObject(const GameObject& in_copy);

	GameObjectId	getId()					const;
	bool			isActive()				const;
	BitSet			getComponentBitsCopy()	const;
	BitSet&			getComponentBits();

	void			reset();

private:
	GameObjectId	m_id;
	BitSet			m_componentBits;
};

#endif