#pragma once
#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_HoldNode
{
public:
	static C_HoldNode* create(const int nCoinType);
public:
	virtual inline Layer* getMainLayer() { return m_pMainLayer; }
public:
	virtual void setEnabled(const bool isEnabled);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createNodeLayer();
	virtual void createSpriteItem();
	virtual void createLabelItem();
	virtual void presetName();
	virtual void presetLabelText();
	virtual void presetItemsPosition();
	virtual void presetItemsSize();
	virtual void presetItemsAnchor();
	virtual void addChildItems();
	virtual void callUpdate();
	virtual void updateValues();
private:
	Layer* m_pMainLayer;
private:
	Sprite* m_pLogo;
	Sprite* m_pBasicImg;
private:
	Label* m_pName;
	Label* m_pHoldCount;
	Label* m_pHoldPrice;
	Label* m_pProfitPrice;
	Label* m_pProfitPer;
	Label* m_pAveragePrice;
	Label* m_pValuablePrice;
private:
	std::string m_strName;
private:
	int m_nType;
private:
	C_HoldNode() {}
	virtual ~C_HoldNode() {}
	C_HoldNode(C_HoldNode&) = delete;
	C_HoldNode operator=(C_HoldNode&) = delete;
};