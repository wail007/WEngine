#ifndef W_EVENT_MANAGER_H
#define W_EVENT_MANAGER_H

#include "EventData.h"
#include "../Utilities/StrongPtr.h"
#include "../Utilities/Delegate.h"
#include <map>
#include <vector>

typedef StrongPtr<EventData>			EventDataPtr;
typedef Delegate<void, EventDataPtr>	EventListenerDelegate;

class EventManager
{
public:
	static EventManager*	Get();
	static void				DeleteInstance();

	bool addListener(const EventListenerDelegate& in_eventDelegate, const EventType& in_type);
	bool removeListener(const EventListenerDelegate& in_eventDelegate, const EventType& in_type);

	bool triggerEvent(const EventDataPtr& in_event) const;

	bool queueEvent(const EventDataPtr& in_event);
	bool abortEvent(const EventType& in_type);

	void update();

private:
	static EventManager* s_instance;

	EventManager();

	std::map<EventType, std::vector<EventListenerDelegate> >	m_listeners;
	std::vector<EventDataPtr>									m_eventQueues[2];
	unsigned int												m_activeQueue;

};

#endif