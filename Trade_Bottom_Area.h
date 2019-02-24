#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class E_CHART_MENU
{
	E_NONE = 0,
	E_APPOINT = 1,
	E_MARKET_PRICE = 2,
	E_NOT_TRADE = 3,
	E_MAX = 4
};

class C_Trade_Bottom_Menu
{
public:
	static C_Trade_Bottom_Menu* create();
	static inline C_Trade_Bottom_Menu* getInstance() { return m_pMyPointer; }
	virtual inline Layer* getLayer() { return m_pMainLayer; }
public:
	virtual void setEnabledEvent(const bool isEnabled, const int nCoinType);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createSprite();
	virtual void createLayer();
	virtual void createTouchEvent();
	virtual void createTradeMenu();
	virtual void presetVisible();
	virtual void presetScale();
	virtual void presetPosition();
	virtual void presetPastMenu();
	virtual void presetRectList();
	virtual void presetFuncList();
	virtual void addChildItems();
private:
	virtual void changeMode(const int nType);
	virtual void changeMenu(const int nType);
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	Sprite* m_arMenuImg[(int)E_CHART_MENU::E_MAX]{};
	Sprite* m_pBackground;
	Sprite* m_pPastButton;
private:
	Layer* m_pMainLayer;
	Layer* m_pBG_Layer;
private:
	Rect m_arRectList[(int)E_CHART_MENU::E_MAX]{};
private:
	void(C_Trade_Bottom_Menu::*m_arFuncList[(int)E_CHART_MENU::E_MAX])(const int);
private:
	EventListener* m_pTouchEvent;
private:
	bool m_isTrade;
private:
	static C_Trade_Bottom_Menu* m_pMyPointer;
private:
	C_Trade_Bottom_Menu() {}
	virtual ~C_Trade_Bottom_Menu() {}
	C_Trade_Bottom_Menu(C_Trade_Bottom_Menu&) = delete;
	C_Trade_Bottom_Menu operator=(C_Trade_Bottom_Menu&) = delete;
};