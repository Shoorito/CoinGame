#pragma once
#include "cocos2d.h"
#include "C_HoldNode.h"

USING_NS_CC;

class C_History_Menu
{
public:
	static C_History_Menu* create();
	static inline C_History_Menu* getInstance() { return m_pMyPointer; }
	virtual Layer* getMyLayer() { return m_pMainLayer; }
public:
	virtual void setEnabled(const bool isEnabled);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createSpriteItem();
	virtual void createLabelItem();
	virtual void createMenuLayer();
	virtual void createHoldList();
	virtual void presetSpritesOption();
	virtual void presetLabelsOption();
	virtual void presetInformation();
	virtual void callAction();
	virtual void callNodeList();
	virtual void addChildItems();
	virtual bool isHoldCoin();
private:
	Layer* m_pMainLayer;
private:
	Sprite* m_pPlayerMoney_BG;
	Sprite* m_pHoldCoin_BG;
	Sprite* m_pNotHoldCoin;
private:
	Label* m_pPlayerCredit;
	Label* m_pPlayerMoney;
	Label* m_pAmountMoney;
	Label* m_pNowProfit;
	Label* m_pNowValuable;
	Label* m_pProfitPercent;
private:
	int m_nHoldCount;
private:
	C_HoldNode* m_arHoldNode[(int)E_COIN::E_MAX]{};
	C_HoldNode* m_arNowHoldNode[(int)E_COIN::E_MAX]{};
private:
	static C_History_Menu* m_pMyPointer;
private:
	C_History_Menu() {}
	virtual ~C_History_Menu() {}
	C_History_Menu(C_History_Menu&)	= delete;
	C_History_Menu operator=(C_History_Menu&) = delete;
};