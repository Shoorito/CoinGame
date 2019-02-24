#pragma once
#include "cocos2d.h"
#include "C_Coin.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_Rate_Rankup
{
public:
	static C_Rate_Rankup* create();
	static inline C_Rate_Rankup* getInstance() { return m_pMyPointer; }
public:
	virtual inline Layer* getMainLayer() { return m_pMainLayer; }
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createSpriteItem();
	virtual void createLabelItem();
	virtual void createLayerItem();
	virtual void presetCoinList();
	virtual void presetItemsOption();
	virtual void setRankItem();
	virtual void updateRankItem();
	virtual void addChildItems();
private:
	virtual void soltItem(C_Coin** arList, const int nLeft, const int nRight);
private:
	virtual std::string checkPercent(const std::string& strCheck);
private:
	Sprite* m_pChart;
	Sprite* m_arLogo[(int)E_RANK_TYPE::E_MAX]{};
	Sprite* m_arInfo[(int)E_RANK_TYPE::E_MAX]{};
private:
	C_Coin* m_arCoinList[(int)E_COIN::E_MAX]{};
private:
	Label* m_arNowPrice[(int)E_RANK_TYPE::E_MAX]{};
	Label* m_arNowRate[(int)E_RANK_TYPE::E_MAX]{};
private:
	Node* m_pActNode;
private:
	Layer* m_pMainLayer;
private:
	static C_Rate_Rankup* m_pMyPointer;
private:
	C_Rate_Rankup() {}
	virtual ~C_Rate_Rankup() {}
	C_Rate_Rankup(C_Rate_Rankup&) = delete;
	C_Rate_Rankup operator=(C_Rate_Rankup&) = delete;
};