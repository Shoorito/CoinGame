#pragma once
#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_Trade_Top_Menu
{
public:
	static C_Trade_Top_Menu* create();
	static inline C_Trade_Top_Menu* getInstance() { return m_pMyPointer; }
public:
	virtual inline Layer* getLayer() { return m_pMainLayer; }
	virtual void setCoinType(const int nCoinType);
	virtual void setEnabeld(const bool isEnabled);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createLayer();
	virtual void createSprite();
	virtual void createLabel();
	virtual void createTouchEvent();
	virtual void callUpdateEvent();
	virtual void presetPosition();
	virtual void presetAnchor();
	virtual void presetScale();
	virtual void presetPrePrice();
	virtual void presetPastTitle();
	virtual void presetRect();
	virtual void addChildItems();
	virtual void updateData();
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	Layer* m_pMainLayer;
private:
	Sprite* m_arTitle[(int)E_COIN::E_MAX];
	Sprite* m_pPastTitle;
private:
	Sprite* m_pBackground;
	Sprite* m_pFavorite;
private:
	Label* m_pNowPrice;
	Label* m_pNetChange;
	Label* m_pLowPrice;
	Label* m_pHighPrice;
	Label* m_pNetChangePer;
private:
	EventListener* m_pTouchEvent;
private:
	Rect m_recReturnButton;
	Rect m_recFavoriteButton;
private:
	int m_nCoinType;
	int m_arPrePrice[(int)E_COIN::E_MAX]{};
	int m_arLowPrice[(int)E_COIN::E_MAX]{};
private:
	static C_Trade_Top_Menu* m_pMyPointer;
private:
	C_Trade_Top_Menu() {}
	virtual ~C_Trade_Top_Menu() {}
	C_Trade_Top_Menu(C_Trade_Top_Menu&) = delete;
	C_Trade_Top_Menu operator=(C_Trade_Top_Menu&) = delete;
};