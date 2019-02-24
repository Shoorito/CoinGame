#include "C_PlayerManagement.h"
#include "C_CoinManagement.h"

C_Player_Management * C_Player_Management::m_pMyPointer = nullptr;

C_Player_Management * C_Player_Management::create()
{
	if (m_pMyPointer)
	{
		MessageBox("Already created : Player_Management", "AlreadyCreated");

		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Player_Management();
	
	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Player_Management::updateAnotherInfo(const int nType)
{
	C_Coin* pCoin(nullptr);
	int nBuyMoney(0);
	int nProfit(0);

	if (m_arBuyMoney[nType] == 0 || m_arPlayerCoinNum[nType] == 0.0f)
	{
		m_arProfit[nType] = 0;
		m_arProfitPer[nType] = 0.0f;
		m_arAvgPrice[nType] = 0;
		m_arAppraisalPrice[nType] = 0;
		m_arBuyMoney[nType] = 0;
		m_arPlayerCoinNum[nType] = 0.0f;

		return;
	}

	pCoin = C_CoinManagement::getInstance()->getCoin(nType);

	nBuyMoney = (float)m_arBuyMoney[nType] / (float)m_arPlayerCoinNum[nType];
	nProfit = pCoin->getPrice() - nBuyMoney;
	
	m_arProfit[nType]			= (long long)((float)nProfit * m_arPlayerCoinNum[nType]);
	m_arProfitPer[nType]		= ((float)nProfit / (float)nBuyMoney) * 100.0f;
	m_arAvgPrice[nType]			= (long long)nBuyMoney;
	m_arAppraisalPrice[nType] = (int)((float)pCoin->getPrice() * m_arPlayerCoinNum[nType]);
}

void C_Player_Management::init()
{
	m_llPlayerMoney	= 0ll;
}

void C_Player_Management::mainBoard()
{
	presetMoney();
}

void C_Player_Management::presetMoney()
{
	m_llPlayerMoney = 10000000000ll;
}

