#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_Market_Line
{
public:
	static C_Market_Line* create(const int nCoinType);
public:
	virtual inline Layer* getMyLayer() { return m_pLineLayer; }
	virtual inline Label* getMyRate() { return m_pRate; }
	virtual inline Label* getMyRatePrice() { return m_pRatePrice; }
private:
	virtual void init();
	virtual void mainBoard();
private:
	virtual void presetImage();
	virtual void createUpdateNode();
	virtual void createLabel();
	virtual void createLayer();
	virtual void addChildItems(); // 실제 엔진에서 사용되지 않음.
	virtual void updateList();
private:
	virtual void setupPriceValue();
private:
	virtual inline void presetCoinOption(const int nCoinType) { m_nCoinType = nCoinType; }
	virtual void presetSpriteOption();
	virtual void presetLabelOption();
private:
	Sprite* m_pCoinImg;
	Sprite* m_pNameImg;
	Sprite* m_pFavorite[2];
	Sprite* m_pLine;
private:
	Label* m_pPrice;
	Label* m_pTPrice;
	Label* m_pRate;
	Label* m_pRatePrice;
private:
	Layer* m_pLineLayer; // 실제 엔진 접속시 "태깅" 기능을 이용해 사용.
private:
	Node* m_pUpdateNode;
private:
	bool m_isFavorite;
	int  m_nCoinType;
private:
			 C_Market_Line() {};
	virtual ~C_Market_Line() {};
	C_Market_Line(C_Market_Line&)			= delete;
	C_Market_Line operator=(C_Market_Line&) = delete;
};