#pragma once
#include "cocos2d.h"
#include "ValueBox.h"

USING_NS_CC;

enum class E_PAD
{
	E_NONE	 = 0,
	E_PAD_01 = 1,
	E_PAD_02 = 2,
	E_PAD_03 = 3,
	E_PAD_04 = 4,
	E_PAD_05 = 5,
	E_PAD_06 = 6,
	E_PAD_07 = 7,
	E_PAD_08 = 8,
	E_PAD_09 = 9,
	E_PAD_10 = 10,
	E_PAD_11 = 11,
	E_PAD_12 = 12,
	E_PAD_13 = 13,
	E_PAD_14 = 14,
	E_PAD_15 = 15,
	E_PAD_16 = 16,
	E_MAX	 = 17
};

class C_Calculator
{
public:
	static C_Calculator* create();
	static inline C_Calculator* getInstance() { return m_pMyPointer; }
public:
	virtual inline Layer* getLayer() { return m_pMainLayer; }
	virtual void setEnabled(const bool bSwitch);
	virtual void setConnect(float* pConnect, Label* pTargetLab, C_Value_Box* m_pTarget);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createLayer();
	virtual void createLabel();
	virtual void createTouchEvent();
	virtual void addChildItems();
	virtual void presetPosition();
	virtual void presetSize();
	virtual void presetAnchor();
	virtual void presetScale();
	virtual void presetColor();
	virtual void presetText();
	virtual void presetBorderRect();
	virtual void presetFuncList();
private:
	virtual void inputNumber(const int nNumber);
	virtual void inputZero(const int nNumber);
	virtual void percentTrade(const int nNumber);
	virtual void addDot(const int nNumber);
	virtual void initNumber(const int nNumber);
	virtual void closeMenu(const int nNumber);
	virtual void convertFloat();
	virtual void convertInteger();
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	Layer* m_pMainLayer;
	Layer* m_pTitle;
	Layer* m_pResultWindow;
	Layer* m_pPad_BG;
private:
	Label* m_pTitleName;
	Label* m_pResult;
	Label* m_pTextConnect;
private:
	C_Value_Box* m_pCallBox;
private:
	EventListener* m_pTouchEvent;
private:
	Rect m_recTouchBorder;
private:
	std::string m_strResult;
private:
	float* m_pConnect;
	float m_fResult;
	int m_nDotPos;
private:
	bool m_isDot;
private:
	Layer* m_arPadButton[(int)E_PAD::E_MAX]{};
private:
	Label* m_arPadList[(int)E_PAD::E_MAX]{};
private:
	Rect m_arRectList[(int)E_PAD::E_MAX]{};
private:
	void(C_Calculator::*m_arFuncList[(int)E_PAD::E_MAX])(const int);
private:
	static C_Calculator* m_pMyPointer;
private:
	C_Calculator() {}
	virtual ~C_Calculator() {}
	C_Calculator(C_Calculator&) = delete;
	C_Calculator operator=(C_Calculator&) = delete;

};