#include "ShareValue.h"
#include "C_CoinManagement.h"

C_Share_Management* C_Share_Management::m_pMyPointer = nullptr;

C_Share_Management * C_Share_Management::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Share_Management();
	
	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Share_Management::setProfit(const int nType, const int nMinus, const int nState)
{
	m_arMinusBorder[nType] = nMinus;
	m_arStateBorder[nType] = nState;
}

void C_Share_Management::init()
{
}

void C_Share_Management::mainBoard()
{
	presetProfit();
	presetAddList();
	presetBorderPrice();
	presetBorder();
	presetRange();
}

void C_Share_Management::release()
{
}

void C_Share_Management::presetAddList()
{
	m_arAddList[(int)E_ADD_LIST::E_UNDER_1000]		= 1;
	m_arAddList[(int)E_ADD_LIST::E_UNDER_10000]		= 5;
	m_arAddList[(int)E_ADD_LIST::E_UNDER_100000]	= 10;
	m_arAddList[(int)E_ADD_LIST::E_UNDER_1000000]	= 100;
	m_arAddList[(int)E_ADD_LIST::E_UNDER_10000000]	= 1000;
	m_arAddList[(int)E_ADD_LIST::E_UNDER_100000000] = 2000;
}

void C_Share_Management::presetBorderPrice()
{
	m_arBorderList[(int)E_ADD_LIST::E_UNDER_1000]		= 1000;
	m_arBorderList[(int)E_ADD_LIST::E_UNDER_10000]		= 10000;
	m_arBorderList[(int)E_ADD_LIST::E_UNDER_100000]		= 100000;
	m_arBorderList[(int)E_ADD_LIST::E_UNDER_1000000]	= 1000000;
	m_arBorderList[(int)E_ADD_LIST::E_UNDER_10000000]	= 10000000;
	m_arBorderList[(int)E_ADD_LIST::E_UNDER_100000000]	= 100000000;
}

void C_Share_Management::presetRange()
{
	for (int nCoinNum((int)E_COIN::E_STANDARD); nCoinNum < (int)E_COIN::E_MAX; nCoinNum++)
	{
		m_arRangeList[nCoinNum] = S_State_Range::create(0, 99);
	}
}

void C_Share_Management::presetProfit()
{
	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		m_arMinusBorder[nList] = 45;
		m_arStateBorder[nList] = 55;
	}

	m_arProfitList[(int)E_PROFIT::E_MINUS]	= -1;
	m_arProfitList[(int)E_PROFIT::E_STATE]	= 0;
	m_arProfitList[(int)E_PROFIT::E_PLUS]	= 1;
}

void C_Share_Management::presetBorder()
{
	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		int nPrice(0);

		nPrice = C_CoinManagement::getInstance()->getCoin(nList)->getPrice();

		m_arWorstBorder[nList] = (int)((float)nPrice * 0.5f);
	}
}
