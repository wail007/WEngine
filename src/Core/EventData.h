#ifndef W_EVENT_DATA_H
#define W_EVENT_DATA_H

#include <string>
#include "GameObject.h"
#include "../Utilities/RefCounter.h"

typedef unsigned int EventType;

class EventData : public RefCounter
{
public:
	virtual ~EventData(){}

	virtual const EventType&	getEventType()	const = 0;
	virtual std::string			toString()		const = 0;
};



//////////////////////////////////////////////////////////////////

class GameObjectCreatedEvent : public EventData
{
public:
	static EventType Type;

	GameObjectCreatedEvent(GameObjectId in_id) : m_id(in_id){}

	virtual const EventType&	getEventType()		const { return Type; }

	virtual std::string			toString()			const { return "GameObjectCreatedEvent"; }

	GameObjectId				getGameObjectId()	const { return m_id; }

private:
	GameObjectId m_id;
};
EventType GameObjectCreatedEvent::Type = 0xcd924659;

/////////////////////////////////////////////////////////////////

class GameObjectDestroyedEvent : public EventData
{
public:
	static EventType Type;

	GameObjectDestroyedEvent(GameObjectId in_id) : m_id(in_id){}

	virtual const EventType&	getEventType()		const { return Type; }

	virtual std::string			toString()			const { return "GameObjectDestroyedEvent"; }

	GameObjectId				getGameObjectId()	const { return m_id; }

private:
	GameObjectId m_id;
};
EventType GameObjectDestroyedEvent::Type = 0xfad759b;

/////////////////////////////////////////////////////////////////

class GameObjectModifiedEvent : public EventData
{
public:
	static EventType Type;

	GameObjectModifiedEvent(GameObjectId in_id) : m_id(in_id){}

	virtual const EventType&	getEventType()		const { return Type; }

	virtual std::string			toString()			const { return "GameObjectModifiedEvent"; }

	GameObjectId				getGameObjectId()	const { return m_id; }

private:
	GameObjectId m_id;
};
EventType GameObjectModifiedEvent::Type = 0x67605bd2;


#endif