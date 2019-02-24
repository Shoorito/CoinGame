#pragma once
#include "cocos2d.h"
#include "C_Message_Window.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_Window_Management
{
public:
	static C_Window_Management* create();
	static inline C_Window_Management* getInstance() { return m_pMyPointer; }
public:
	virtual void setEnabledWindow(E_WINDOW eType, const std::string& strTitle, const std::string& strSub);
	virtual void setEnabledTrade(E_WINDOW eType, const bool isTrade, const int nType);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void addChildList();
	virtual void presetWindow();
private:
	C_Message_Window* m_arWindow[(int)E_WINDOW::E_MAX]{};
private:
	static C_Window_Management* m_pMyPointer;
private:
	C_Window_Management() {}
	virtual ~C_Window_Management() {}
	C_Window_Management(C_Window_Management&) = delete;
	C_Window_Management operator=(C_Window_Management&) = delete;
};