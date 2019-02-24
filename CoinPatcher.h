#pragma once
#include <iostream>
#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_Coin_Patcher
{
public:
	static C_Coin_Patcher* create(const int nCoinType); // 본 파일 적용시 create에서 타겟 "Coin"을 정할 수 있다.
private:
	virtual void init();
	virtual void mainBoard();
private:
	virtual inline void presetCoinType(const int nCoinType) { m_nCoinType = nCoinType; }
private:
	virtual void createSetupLayer();
	virtual void presetProfit();
	virtual void callPriceSetup();
	virtual void callTPriceSetup();
	virtual void callGradeSetup();
	virtual void callProfitSetup();
	virtual void setupPrice();
	virtual void setupTPrice();
	virtual void setupProfit();
	virtual void setupPriceCheck();
	virtual void setPriceState();
	virtual void createNode();
	virtual void addNodeChild();
private:
	virtual std::string checkPercent(const std::string& strCheck);
	virtual int			checkProfit(const int nCheckNum);
	virtual bool		checkPriceGrade();
private:
	int m_nCoinType;
	int m_nPriceBorder;
private:
	bool m_isMinusEvent;
private:
	int m_arProfitBorder[(int)E_PROFIT::E_MAX]{};
private:
	Node* m_pPriceUpdateNode;
	Node* m_pTPriceUpdateNode;
	Node* m_pGradeUpdateNode;
	Node* m_pProfitNode;
	Node* m_pProfitUpdateNode;
	Layer* m_pSetupLayer;
private:
			 C_Coin_Patcher() {}
	virtual ~C_Coin_Patcher() {}
};