#pragma once

#include "cocos2d.h"
#include "EnumClassList.h"
#include "ClippingNode_Management.h"

USING_NS_CC;

class C_MainBody_Menu
{
public:
	static C_MainBody_Menu* create(const std::string& strRoute);
	static inline C_MainBody_Menu* getInstance() { return m_pMyPointer; }
public:
	virtual inline Vec2 getBasedPosition() { return m_pClipingNode->getPosition(); }
private:
	virtual inline void setRoute(const std::string& strRoute) { m_strRoute = strRoute; }
private:
	virtual void init();
	virtual bool mainBoard();
private:
	virtual void createMenu();
	virtual void createBodyLayer();
	virtual void createSpriteItems();
	virtual void createClippingNode();
	virtual void addChildScene();
private:
	virtual void presetSelectedMenu();
	virtual void presetMenuEnabled();
	virtual void presetEventFuncList();
	virtual void presetItemsPosition();
	virtual void presetItemsScale();
	virtual void presetItemsAnchor();
	virtual void presetItemsVisible();
private:
	virtual void setNewsEvent(const bool isEnabled);
	virtual void setMarketEvent(const bool isEnabled);
	virtual void setHistoryEvent(const bool isEnabled);
	virtual void setWorldEvent(const bool isEnabled);
	virtual void setMypageEvent(const bool isEnabled);
private:
	virtual void presetMenuEnabled();
	virtual void presetEventFuncList();
	virtual void callSetup();
	virtual void setupMenuVisible();
private:
	C_MainBody_Menu() {};
	virtual ~C_MainBody_Menu() {};
	C_MainBody_Menu(C_MainBody_Menu&) = delete;
	C_MainBody_Menu operator=(C_MainBody_Menu&) = delete;
private:
	int m_nPastSelected;
private:
	std::string	m_strRoute;
private:
	void(C_MainBody_Menu::*m_arEventFunc[(int)E_MENU_TYPE::E_MAX])(const bool isEnabled);
	void(C_MainBody_Menu::*m_pPastFunc)(const bool isEnabled);
private:
	ClippingNode* m_pClipingNode;
private:
	Sprite* m_pBackground;
private:
	Layer* m_pMainLayer;
private:
	Rect m_recEventBorder;
private:
	static C_MainBody_Menu* m_pMyPointer;
};