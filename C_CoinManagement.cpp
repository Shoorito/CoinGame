#include "C_CoinManagement.h"
#include "Sprite_Management.h"
#include "C_ResManagement.h"
#include "C_ItemManagement.h"
#include "C_FNode.h"

C_CoinManagement* C_CoinManagement::m_pMyPointer = nullptr;

C_CoinManagement * C_CoinManagement::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_CoinManagement();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_CoinManagement::init()
{
	m_strRoute = "";
}

void C_CoinManagement::mainBoard()
{
	createDummyData();
	createCoinList();
	presetFileInfo();
	presetRoute();
	presetAllItems();
}

void C_CoinManagement::createDummyData()
{
	C_Coin* pDummy(nullptr);

	pDummy = C_Coin::create();

	m_vecCoinList.push_back(pDummy);
}

void C_CoinManagement::createCoinList()
{
	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		C_Coin* pCoin(nullptr);

		pCoin = C_Coin::create();

		m_vecCoinList.push_back(pCoin);
	}
}

void C_CoinManagement::presetFileInfo()
{
	C_ResManagement::getInstance()->getList("Coin", (int)E_FILE_TYPE::E_COIN, m_arImgInfo[0]);
	C_ResManagement::getInstance()->getList("Sprite", (int)E_FILE_TYPE::E_COIN, m_arImgInfo[1]);
}

void C_CoinManagement::presetRoute()
{
	m_strRoute = C_ResManagement::getInstance()->getRoute((int)E_FILE_TYPE::E_COIN);
}

void C_CoinManagement::presetAllItems()
{
	presetAllItemsName();
	presetAllItemsImage();
	presetAllItemsValue();
}

void C_CoinManagement::presetAllItemsName()
{
	std::string strCoin("");

	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		strCoin = m_arImgInfo[0].at(nList - 1)->getTagName();

		m_vecCoinList.at(nList)->setName(strCoin);
	}
}

void C_CoinManagement::presetAllItemsImage()
{
	std::string strName("");
	std::string strTag("");
	C_Coin* pTarget(nullptr);

	for (int nListNum((int)E_COIN::E_STANDARD); nListNum < (int)E_COIN::E_MAX; nListNum++)
	{
		Sprite* pCoinImg(nullptr);
		Sprite* pNameImg(nullptr);

		pTarget = m_vecCoinList.at(nListNum);

		pCoinImg = C_ItemManagement::getInstance()->createItem(m_strRoute, m_arImgInfo[0].at(nListNum - 1));
		pNameImg = C_ItemManagement::getInstance()->createItem(m_strRoute, m_arImgInfo[1].at(nListNum - 1));

		pTarget->setImg(pCoinImg);
		pTarget->setNameImg(pNameImg);
	}
}

void C_CoinManagement::presetAllItemsValue()
{
	std::vector<C_FNode*> vecCoinValue{};
	std::string strValue("");
	std::string arValue[3]{};

	C_ResManagement::getInstance()->getList("Coin", (int)E_FILE_TYPE::E_COIN_OFFSET, vecCoinValue);

	for (int nListNum((int)E_COIN::E_STANDARD); nListNum < (int)E_COIN::E_MAX; nListNum++)
	{
		int		nPos(0);
		int		nMaxNum(0);
		int		nRatePrice(0);
		float	fRate(0.0f);
		C_Coin* pCoin(nullptr);

		strValue = vecCoinValue.at(nListNum - 1)->getTagName();

		nMaxNum = strValue.size();
		
		pCoin = m_vecCoinList.at(nListNum);

		for (int nValueNum(0); nValueNum < 3; nValueNum++)
		{
			arValue[nValueNum] = readText(strValue, nPos, nMaxNum);
		}

		pCoin->setValues(arValue);
		
		nRatePrice	= (pCoin->getPrice()) - (pCoin->getPrePrice());
		fRate		= (float)nRatePrice / (float)(pCoin->getPrice()) * 100.0f;

		pCoin->setRatePrice(nRatePrice);
		pCoin->setRate(fRate);
	}
}

std::string C_CoinManagement::readText(const std::string & strReadText, int & nPos, const int nMaxLength)
{
	char		cWord('\0');
	bool		bSwitch(true);
	std::string strResult("");

	for (; (nPos < nMaxLength) && (bSwitch); nPos++)
	{
		cWord = strReadText.at(nPos);

		if (isBlank(cWord))
		{
			strResult += cWord;
		}
		else
		{
			bSwitch = false;
		}
	}

	return strResult;
}

bool C_CoinManagement::isBlank(const char cTarget)
{
	char arFilter[4]{' ', '\t', '\"', ','};

	for (int nListNum(0); nListNum < 4; nListNum++)
	{
		if (cTarget == arFilter[nListNum])
		{
			return false;
		}
	}

	return true;
}