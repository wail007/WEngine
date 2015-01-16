#ifndef W_GAME_OBJECT_MANAGER_H
#define W_GAME_OBJECT_MANAGER_H

#include "Manager.h"
#include "GameObject.h"
#include "../Utilities/IdentifierPool.h"
#include <vector>


class GameObjectManager : public Manager
{
public:
	GameObjectManager();

	GameObject*	addGameObject();
	void		removeGameObject(GameObjectId in_id);
	GameObject*	getGameObject(GameObjectId m_id);


	void		update();

private:
	IdentifierPool				m_idPool;
	std::vector<GameObject>		m_gameObjects;
	std::vector<GameObjectId>	m_destroyed;
};

#endif