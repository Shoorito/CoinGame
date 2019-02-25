#pragma once
#pragma warning(disable : 4996)

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum class E_EVENT_TYPE
{
	E_NONE = 0,
	E_DOWN = 1,
	E_UP = 2,
	E_SET = 3,
	E_MAX = 4
};

class C_Value_Box
{
public:
	static C_Value_Box* create(Size szButton, const float fTextLength, const float fLineThick);
public:
	virtual void setEnabledEvent(const bool isEnabled);
	virtual void setPosition(const float fXpos, const float fYpos);
	virtual void setTrader(const int nType);
	virtual void setTail(const std::string& strTail);
	virtual void setNumber(const float fValue);
public:
	virtual inline float getValue() { return m_fMyValue; }
	virtual inline Layer* getLayer() { return m_pMyLayer; }
public:
	virtual void releaseCalculator();
private:
	virtual void init();
	virtual void mainBoard();
private:
	virtual void createLabel();
	virtual void createLayer();
	virtual void createClippingNode();
	virtual void createTouchEvent();
	virtual void presetLabelOption();
	virtual void presetLayerOption();
	virtual void presetPosition();
	virtual void presetRectList();
	virtual void presetAnchor();
	virtual void presetAddList();
	virtual void presetFuncList();
	virtual void addChildItems();
private:
	virtual void addCount(const int nAdd);
	virtual void callCalculator(const int nNoUsed);
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	Size m_szButtonSize;
private:
	void(C_Value_Box::*m_arFuncList[(int)E_EVENT_TYPE::E_MAX])(const int){};
private:
	float m_fTextBarLength;
	float m_fBorderThick;
	float m_fMyValue;
	float m_arAddList[(int)E_EVENT_TYPE::E_MAX - 1]{};
private:
	int m_nTradeType;
private:
	Label* m_arButtonText[(int)E_EVENT_TYPE::E_MAX - 1]{};
	Label* m_pNumberText;
private:
	Layer* m_pMyLayer;
	Layer* m_arBox[(int)E_EVENT_TYPE::E_MAX - 1]{};
	Layer* m_arLine[(int)E_EVENT_TYPE::E_MAX - 1]{};
private:
	ClippingNode* m_pClipNode;
	Scale9Sprite* m_pBox;
private:
	std::string m_strNumber;
	std::string m_strTail;
private:
	Rect m_arRectList[(int)E_EVENT_TYPE::E_MAX]{};
private:
	EventListener* m_pTouchEvent;
private:
	C_Value_Box() {}
	virtual ~C_Value_Box() {}
	C_Value_Box(C_Value_Box&) = delete;
	C_Value_Box operator=(C_Value_Box&) = delete;
};