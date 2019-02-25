#pragma once
#include "cocos2d.h"
#include "ValueBox.h"
#include "EnumClassList.h"

USING_NS_CC;

enum class E_VALUE_PAD
{
	E_NONE = 0,
	E_PAD = 8,
	E_MAX = 9
};

enum class E_TRADE_BUTTON
{
	E_NONE = 0,
	E_SET = 1,
	E_TRADE = 2,
	E_MAX = 3
};

enum class E_ERROR
{
	E_NONE = 0,
	E_INPUT_ZERO = 1,
	E_COST_LACK = 2,
	E_COIN_LACK = 3,
	E_MAX = 4
};

class C_Appoint_Trade
{
public:
	static C_Appoint_Trade* create();
	static C_Appoint_Trade* getInstance() { return m_pMyPointer; }
	virtual inline Layer* getLayer() { return m_pMainLayer; }
	virtual void updatePrice(const int nType);
	virtual void setCoinType(const int nType);
	virtual void tradeCoin(const int nType);
public:
	virtual void setBoxEnabled(E_BOX_TYPE eType, const bool isEnabled);
	virtual void setAllEnabled(const bool isEnabled);
	virtual void setEnabledNowPrice(const bool isEnabled);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createSprite();
	virtual void createLabel();
	virtual void createLayer();
	virtual void createValueBox();
	virtual void createTouchEvent();
	virtual void createRectList();
	virtual void presetRectList();
	virtual void presetBorder();
	virtual void presetFuncList();
	virtual void updateInfo();
	virtual void presetItemsOption();
	virtual void addChildItem();
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	virtual void callTradeWindow(const int nType);
	virtual void setTradeValues(const int nType);
private:
	Rect* m_arEventArea[(int)E_TRADE::E_MAX]{};
private:
	Label* m_arPriceLab[(int)E_TRADE::E_MAX]{};
	Label* m_pPlayerMoney;
	Label* m_pHoldCoinNum;
private:
	Layer* m_pMainLayer;
private:
	Sprite* m_pBackGround;
private:
	C_Value_Box* m_arValueBox[(int)E_BOX_TYPE::E_MAX]{};
private:
	EventListener* m_pEvent;
private:
	long long m_arPrice[(int)E_TRADE::E_MAX]{};
private:
	float m_arCoinNum[(int)E_TRADE::E_MAX]{};
	float m_arPriceNum[(int)E_TRADE::E_MAX]{};
private:
	int m_nCoinType;
private:
	float m_fPosBorder;
private:
	bool m_isNowPrice;
	bool m_arError;
private:
	void(C_Appoint_Trade::*m_arTradeFunc[(int)E_TRADE::E_MAX])(const int);
	void(C_Appoint_Trade::*m_arSetupFunc[(int)E_VALUE_PAD::E_MAX])(const int);
private:
	static C_Appoint_Trade* m_pMyPointer;
private:
	C_Appoint_Trade() {}
	virtual ~C_Appoint_Trade() {}
	C_Appoint_Trade(C_Appoint_Trade&) = delete;
	C_Appoint_Trade operator=(C_Appoint_Trade&) = delete;
};