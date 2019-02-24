#pragma once
#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

enum class E_WINDOW
{
	E_NONE = 0,
	E_ONLY_OK = 1,
	E_SELECT = 2,
	E_MAX = 3
};

class C_Message_Window
{
public:
	static C_Message_Window* create();
public:
	virtual bool setWindowType(const int nType);
	virtual void setEnabledWindow(const bool isEnabled);
	virtual void setEnabledTrade(const bool isEnabled, const int nTradeType);
public:
	virtual void setTitle(const std::string& strName);
	virtual void setSubTitle(const std::string& strName);
public:
	virtual inline Layer* getMainLayer() { return m_pMainLayer; }
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createSprite();
	virtual void createLabel();
	virtual void createLayer();
	virtual void createTouchEvent();
	virtual void presetPosition();
	virtual void presetScale();
	virtual void presetPastImage();
	virtual void presetRectList();
	virtual void presetFuncList();
	virtual void addChildList();
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
	virtual void touchOnConfirmMenu();
	virtual void touchOnCancelMenu();
private:
	Sprite* m_arWindow[(int)E_WINDOW::E_MAX]{};
	Sprite* m_pPastTarget;
private:
	Label* m_pTitle;
	Label* m_pSubTitle;
private:
	Layer* m_pMainLayer;
private:
	void(C_Message_Window::*m_arFuncList[(int)E_WINDOW::E_MAX])();
private:
	Rect m_arRectList[(int)E_WINDOW::E_MAX]{};
private:
	std::string m_strTitle;
	std::string m_strSubTitle;
private:
	int m_nType;
	int m_nTradeType;
private:
	bool m_isTrade;
private:
	EventListener* m_pTouchEvent;
private:
	C_Message_Window() {}
	virtual ~C_Message_Window() {}
	C_Message_Window(C_Message_Window&) = delete;
	C_Message_Window operator=(C_Message_Window&) = delete;
};