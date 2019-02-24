#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_Trade_Menu
{
public:
	static C_Trade_Menu* create();
	static C_Trade_Menu* getInstance() { return m_pMyPointer; }
public:
	virtual void setEnabled(const bool isEnabled, const int nCoinType);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createLayer();
	virtual void createMenu();
	virtual void addChildItems();
private:
	Sprite* m_pTempSprite;
	Layer* m_pMainLayer;
private:
	static C_Trade_Menu* m_pMyPointer;
private:
	C_Trade_Menu() {}
	virtual ~C_Trade_Menu() {}
	C_Trade_Menu(C_Trade_Menu&) = delete;
	C_Trade_Menu operator=(C_Trade_Menu&) = delete;
};