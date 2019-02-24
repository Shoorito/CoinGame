#include "EventManager.h"

std::unordered_map<std::string, EventListener*> C_Event_Manager::m_EventList;

C_Event_Manager * C_Event_Manager::create()
{
	C_Event_Manager* pEventManager(nullptr);

	pEventManager = new(std::nothrow) C_Event_Manager();

	return pEventManager;
}

void C_Event_Manager::setTagName(const std::string strName, EventListener * pEvent)
{
	m_EventList.insert(std::make_pair(strName, pEvent));
}

EventListener * C_Event_Manager::getTagName(const std::string strName)
{
	for (auto& pList : m_EventList)
	{
		if (pList.first == strName)
		{
			return pList.second;
		}
	}

	MessageBox("Not Found Event\nPlease Re-Check to Your Input Value.", "Not Found!");

	return nullptr;
}
