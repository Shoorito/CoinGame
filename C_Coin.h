#pragma once
#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_Coin
{
public:
	static C_Coin* create();
public:
	virtual inline Sprite* getImage()		{ return m_pCoinImg; }
	virtual inline Sprite* getNameImg()		{ return m_pNameImg; }
public:
	virtual inline int getPrice()		 { return m_nPrice; }
	virtual inline int getTPrice()		 { return m_nTPrice; }
	virtual inline int getPrePrice()	 { return m_nPrePrice; }
	virtual inline int getRatePrice()	 { return m_nRatePrice; }
	virtual inline float getRate()		 { return m_fRate; }
	virtual inline std::string getName() { return m_strCoinName; }
public:
	virtual inline void setName(const std::string& strName) { m_strCoinName = strName; };
	virtual inline void setPrice(const int nPrice)			{ m_nPrice = nPrice; }
	virtual inline void setTPrice(const int nTPrice)		{ m_nTPrice = nTPrice; }
	virtual inline void setPrePrice(const int nPrePrice)	{ m_nPrePrice = nPrePrice; }
	virtual inline void setRatePrice(const int nRatePrice)  { m_nRatePrice = nRatePrice; }
	virtual inline void setRate(const float fRate)			{ m_fRate = fRate; }
	virtual inline void setImg(Sprite* pImg)				{ m_pCoinImg = pImg; }
	virtual inline void setNameImg(Sprite* pImg)			{ m_pNameImg = pImg; }
public:
	virtual void setValues(const std::string arValue[3]);
private:
	virtual bool invertValue(const std::string& strValue, int& nResult);
private:
	virtual bool setPrice(const std::string & strPrice);
	virtual bool setTPrice(const std::string & strTPrice);
	virtual bool setPrePrice(const std::string& strPrePrice);
private:
	virtual void init();
	virtual void setFuncList();
private:
	bool(C_Coin::*m_arFuncList[3])(const std::string&);
private:
	int m_nPrice;
	int m_nTPrice;
	int m_nPrePrice;
	int m_nRatePrice;
private:
	float m_fRate;
private:
	Sprite* m_pCoinImg;
	Sprite* m_pNameImg;
private:
	std::string m_strCoinName;
};