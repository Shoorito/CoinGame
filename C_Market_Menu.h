#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MarketLine.h"
#include "EnumClassList.h"
#include "CoinPatcher.h"

USING_NS_CC;
USING_NS_CC_EXT;

class C_Market_Management
{
public:
	static C_Market_Management* create();
	static C_Market_Management* getInstance() { return m_pMyPointer; }
public:
	virtual inline C_Market_Line* getCoinLine(const int nCoinType) { return m_arCoinLine[nCoinType]; }
	virtual inline Layer* getMarketLayer() { return m_pMainLayer; }
	virtual inline Layer* getLineLayer(const int nKeyNum) { return m_arLineLayer[nKeyNum]; }
public:
	virtual void setEventEnabled(const bool isEnabled);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createMarketLine();
	virtual void createMarketLayer();
	virtual void createTouchEvent();
	virtual void presetLinesOption();
	virtual void presetLayerList();
	virtual void presetCoinEndPos();
	virtual void presetMenuButtonPos();
	virtual void callTradeWindow();
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	C_Market_Line* m_arCoinLine[(int)E_COIN::E_MAX]{};
	C_Coin_Patcher* m_arCoinPatcher[(int)E_COIN::E_MAX]{};
	Layer* m_arLineLayer[(int)E_COIN::E_MAX]{};
private:
	EventListener* m_pTouchEvent;
private:
	Layer* m_pChartLayer;
	Layer* m_pMainLayer;
private:
	float m_fPastYpos;
	float m_fNowTouched;
	float m_arMenuPosList[(int)E_COIN::E_MAX]{};
	float m_fMovePoint;
	float m_arCoinBorderYpos[2]{};
private:
	bool m_isScroll;
private:
	static C_Market_Management* m_pMyPointer;
private:
	C_Market_Management() {};
	C_Market_Management(C_Market_Management&) = delete;
	C_Market_Management operator=(C_Market_Management&) = delete;
	virtual ~C_Market_Management() {};
};