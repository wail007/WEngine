#include "EventManager.h"
#include <algorithm>

EventManager* EventManager::s_instance = 0;

EventManager* EventManager::Get()
{
	if (s_instance == 0)
	{
		s_instance = new EventManager;
	}

	return s_instance;
}

void EventManager::DeleteInstance()
{
	delete s_instance;
}


EventManager::EventManager()
	: m_activeQueue(0)
{

}

bool EventManager::addListener(const EventListenerDelegate& in_eventDelegate, const EventType& in_type)
{
	std::vector<EventListenerDelegate> v = m_listeners[in_type];

	if (std::find(v.begin(), v.end(), in_eventDelegate) == v.end())
	{
		v.push_back(in_eventDelegate);
		return true;
	}

	return false;
}

bool EventManager::removeListener(const EventListenerDelegate& in_eventDelegate, const EventType& in_type)
{
	std::vector<EventListenerDelegate> v = m_listeners[in_type];

	auto it = std::find(v.begin(), v.end(), in_eventDelegate);

	if ( it != v.end())
	{
		v.erase(it);
		return true;
	}

	return false;
}
	 
bool EventManager::triggerEvent(const EventDataPtr& in_event) const
{
	auto vIt = m_listeners.find(in_event->getEventType());

	if (vIt != m_listeners.end())
	{
		const std::vector<EventListenerDelegate>& v = vIt->second;

		for (auto it = v.begin(); it != v.end(); it++)
		{
			(*it)(in_event);
		}

		return true;
	}

	return false;
}
	
bool EventManager::queueEvent(const EventDataPtr& in_event)
{
	if (m_listeners.find(in_event->getEventType()) != m_listeners.end())
	{
		m_eventQueues[m_activeQueue].push_back(in_event);
		return true;
	}

	return false;
}

bool EventManager::abortEvent(const EventType& in_type)
{
	std::vector<EventDataPtr> v = m_eventQueues[m_activeQueue];

	bool success = false;

	auto it = v.begin();

	while (it != v.end())
	{
		if ((*it)->getEventType() == in_type)
		{
			it = v.erase(it);
			success = true;
			continue;
		}
		it++;
	}

	return success;
}
	
void EventManager::update()
{
	std::vector<EventDataPtr>& eventQueue = m_eventQueues[m_activeQueue];

	m_activeQueue = (m_activeQueue + 1) % 2;

	for (int i = 0; i < eventQueue.size(); i++)
	{
		//An event is not queued if it has no listeners.
		//So the iterator is guaranteed to be valid.
		auto it = m_listeners.find(eventQueue[i]->getEventType());

		for (auto delegateIt = it->second.begin(); delegateIt != it->second.end(); delegateIt++)
		{
			(*delegateIt)(eventQueue[i]);
		}
	}

	eventQueue.clear();
}