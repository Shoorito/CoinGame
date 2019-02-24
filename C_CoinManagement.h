#pragma once
#include "C_Coin.h"
#include "C_FNode.h"
#include "C_FileLoad.h"

class C_CoinManagement
{
public:
	static C_CoinManagement* create();
	static inline C_CoinManagement* getInstance() { return m_pMyPointer; }
public:
	virtual inline C_Coin* getCoin(const int nCoinNum) { return m_vecCoinList.at(nCoinNum); }
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createDummyData();
private:
	virtual void createCoinList();
	virtual void presetFileInfo();
	virtual void presetRoute();
	virtual void presetAllItems();
	virtual void presetAllItemsName();
	virtual void presetAllItemsImage();
	virtual void presetAllItemsValue();
private:
	virtual std::string readText(const std::string & strReadText, int & nPos, const int nMaxLength);
	virtual bool isBlank(const char cTarget);
private:
	static C_CoinManagement* m_pMyPointer;
private:
	std::string m_strRoute;
private:
	std::vector<C_Coin*> m_vecCoinList{};
	std::vector<C_FNode*> m_arImgInfo[2]{};
private:
	C_CoinManagement() {};
	~C_CoinManagement() {};
};