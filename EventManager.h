#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_Event_Manager
{
public:
	C_Event_Manager()	= default;
	~C_Event_Manager()	= default;
public:
	static C_Event_Manager* create();
	static void setTagName(const std::string strName, EventListener* pEvent);
public:
	static EventListener* getTagName(const std::string strName);
private:
	static std::unordered_map<std::string, EventListener*> m_EventList;
};