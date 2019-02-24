#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_StandLine
{
public:
	static C_StandLine* create();
public:
	virtual inline Layer* getLayer() { return m_pMainLayer; }
	virtual inline int getCoinType() { return m_nCoinType; }
public:
	virtual void setEnabled(const bool isEnabled);
	virtual void setOrderOption(const int nPrice, const double dlCount, const int nOrderType, const int nCoinType);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void loadDayData();
	virtual void createLayer();
	virtual void createSprite();
	virtual void createLabel();
	virtual void createTouchEvent();
	virtual void callOrderEvent();
	virtual void presetPosition();
	virtual void presetScale();
	virtual void addChildItem();
	virtual void resetValue();
private:
	virtual std::string getDayData();
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent) { return false; }
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent) { return false; }
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent) { return false; }
private:
	virtual void checkOrder();
private:
	Sprite* m_pCancel;
private:
	Label* m_pOrderTime;
	Label* m_pOrderType;
	Label* m_pOrderPrice;
	Label* m_pOrderValue;
private:
	Layer* m_pMainLayer;
private:
	EventListener* m_pEvent;
private:
	double m_dlOrderCount;
	int m_nOrderPrice;
	int m_nOrderType;
	int m_nCoinType;
private:
	int m_nMonth;
	int m_nDay;
	int m_nHour;
	int m_nMin;
private:
	C_StandLine() {}
	virtual ~C_StandLine() {}
	C_StandLine(C_StandLine&) = delete;
	C_StandLine operator=(C_StandLine&) = delete;
};