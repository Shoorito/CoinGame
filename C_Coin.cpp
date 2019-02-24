#include "C_Coin.h"

C_Coin * C_Coin::create()
{
	C_Coin* pCoin(nullptr);

	pCoin = new(std::nothrow) C_Coin();

	pCoin->init();
	pCoin->setFuncList();

	return pCoin;
}

void C_Coin::init()
{
	m_nPrice		= 0;
	m_nTPrice		= 0;
	m_nPrePrice		= 0;
	m_nRatePrice	= 0;
	m_fRate			= 0.0f;
	m_strCoinName	= "";
	m_pCoinImg		= nullptr;
	m_pNameImg		= nullptr;
}

bool C_Coin::setPrice(const std::string & strRate)
{
	if (strRate == "")
	{
		return false;
	}

	invertValue(strRate, m_nPrice);

	return true;
}

bool C_Coin::setTPrice(const std::string & strRate)
{
	if (strRate == "")
	{
		return false;
	}

	invertValue(strRate, m_nTPrice);

	return true;
}

bool C_Coin::setPrePrice(const std::string & strPrePrice)
{
	if (strPrePrice == "")
	{
		return false;
	}

	invertValue(strPrePrice, m_nPrePrice);

	return true;
}

void C_Coin::setValues(const std::string arValue[3])
{
	for (int nList(0); nList < 3; nList++)
	{
		(this->*m_arFuncList[nList])(arValue[nList]);
	}
}

bool C_Coin::invertValue(const std::string & strValue, int & nResult)
{
	int nMaxNum(0);
	int nRepeat(0);

	nMaxNum = strValue.size();

	for (int nNumPos(0); nNumPos < nMaxNum; nNumPos++)
	{
		int nNumber(0);

		nNumber = (int)strValue.at(nNumPos) - 48;
		nRepeat = nMaxNum - nNumPos;

		if (nNumber < 0 && nNumber > 9)
		{
			return false;
		}

		for (int nValue(nRepeat - 1); nValue != 0; nValue--)
		{
			nNumber *= 10;
		}

		nResult += nNumber;
	}

	return true;
}

void C_Coin::setFuncList()
{
	m_arFuncList[0] = &C_Coin::setPrice;
	m_arFuncList[1] = &C_Coin::setTPrice;
	m_arFuncList[2] = &C_Coin::setPrePrice;
}
