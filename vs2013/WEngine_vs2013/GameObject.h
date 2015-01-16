#ifndef W_GAME_OBJECT_H
#define W_GAME_OBJECT_H

#include "utilities/BitSet.h"

class GameObject
{
public:
	GameObject(unsigned int in_id);

	unsigned int	getId()				const;
	BitSet			getComponentBits()	const;



private:
	unsigned int	m_id;
	BitSet			m_componentBits;
};

#endif