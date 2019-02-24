#pragma once
#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_Player_Management
{
public:
	static C_Player_Management* create();
	static inline C_Player_Management* getInstance() { return m_pMyPointer; }
public:
	virtual inline long long getPlayerMoney() { return m_llPlayerMoney; }
	virtual inline long long getBuyMoney(const int nType) { return m_arBuyMoney[nType]; }
	virtual inline long long getProfit(const int nType) { return m_arProfit[nType]; }
	virtual inline long long getAvgPrice(const int nType) { return m_arAvgPrice[nType]; }
	virtual inline long long getAppraisalPrice(const int nType) { return m_arAppraisalPrice[nType]; }
public:
	virtual inline float getPlayerCoin(const int nType) { return m_arPlayerCoinNum[nType]; }
	virtual inline float getProfitPer(const int nType) { return m_arProfitPer[nType]; }
public:
	virtual inline void setPlayerMoney(const long long llPrice) { m_llPlayerMoney = llPrice; }
	virtual inline void setPlayerCoin(const int nType, const float fCoin) { m_arPlayerCoinNum[nType] = fCoin; }
	virtual inline void setBuyMoney(const long long llPrice, const int nType) { m_arBuyMoney[nType] = llPrice; }
	virtual void updateAnotherInfo(const int nType);
private:
	virtual void init();
	virtual void mainBoard();
private:
	virtual void presetMoney();
private:
	float m_arPlayerCoinNum[(int)E_COIN::E_MAX]{};
	float m_arProfitPer[(int)E_COIN::E_MAX]{};
private:
	long long m_llPlayerMoney;
	long long m_arBuyMoney[(int)E_COIN::E_MAX]{};
	long long m_arProfit[(int)E_COIN::E_MAX]{};
	long long m_arAvgPrice[(int)E_COIN::E_MAX]{};
	long long m_arAppraisalPrice[(int)E_COIN::E_MAX]{};
private:
	static C_Player_Management* m_pMyPointer;
private:
	C_Player_Management() {}
	~C_Player_Management() {}
	C_Player_Management(C_Player_Management&) = delete;
	C_Player_Management operator=(C_Player_Management&) = delete;
};