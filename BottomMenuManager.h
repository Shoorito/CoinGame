#pragma once
#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_MainBottom_Menu
{
public:
	static C_MainBottom_Menu* create(const std::string& strRoute);
	static inline C_MainBottom_Menu* getInstance() { return m_pInstance; }
public:
	virtual void setEnabled(const bool isEnabled) { m_pTouchEvent->setEnabled(isEnabled); }
public:
	virtual inline Layer* getLayer() { return m_pMainLayer; }
private:
	virtual inline void setRoute(const std::string& strRoute) { m_strRoute = strRoute; }
private:
	virtual void init();
	virtual bool mainBoard();
private:
	virtual bool		touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual inline bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent) { return false; }
	virtual inline bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent)	{ return false; }
	virtual inline bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent)	{ return false; }
private:
	virtual void createSpriteItems();
	virtual void createTouchEvent();
	virtual void createLayer();
	virtual void presetPastSelected();
	virtual void presetItemsPosition();
	virtual void presetItemsAnchor();
	virtual void presetItemsScale();
	virtual void presetItemsVisible();
private:
	C_MainBottom_Menu() {};
	virtual ~C_MainBottom_Menu() {};
	C_MainBottom_Menu(C_MainBottom_Menu&) = delete;
	C_MainBottom_Menu operator=(C_MainBottom_Menu&) = delete;
private:
	static C_MainBottom_Menu* m_pInstance;
private:
	Sprite* m_arSelectedButton[(int)E_MENU_TYPE::E_MAX]{};
	Sprite* m_pMenu_BG;
private:
	Layer* m_pMainLayer;
private:
	EventListener* m_pTouchEvent;
private:
	int	m_nPastButton;
private:
	std::string m_strRoute;
};