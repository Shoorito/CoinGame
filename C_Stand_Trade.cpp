#include "C_Stand_Trade.h"
#include "Layer_Management.h"
#include "Sprite_Management.h"

C_Stand_Trade * C_Stand_Trade::m_pMyPointer = nullptr;

C_Stand_Trade * C_Stand_Trade::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Stand_Trade();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Stand_Trade::setEnabled(const bool isEnabled)
{
	m_pMainLayer->setVisible(isEnabled);
}

void C_Stand_Trade::updateLineSort(const int nType)
{
	int nUpdateCount(0);

	for (int nList((int)E_STAND_RANGE::E_NONE); nList < (int)E_STAND_RANGE::E_MAX; nList++)
	{
		C_StandLine* pLine(nullptr);

		pLine = m_arLineList[nType][nList];

		if (pLine->getCoinType() != 0)
		{
			pLine->getLayer()->setPosition(7.5f, 316.5f - (35.0f * (float)nUpdateCount));

			nUpdateCount++;
		}
	}

}

void C_Stand_Trade::addList(const int nPrice, const double dlCount, const int nCoinType, const int nTradeType)
{
	int nLineNum(0);

	if (m_arLineNum[nCoinType] <= (int)E_STAND_RANGE::E_MAX)
	{
		nLineNum = m_arLineNum[nCoinType];

		m_arLineList[nCoinType][nLineNum]->setEnabled(true);
		m_arLineList[nCoinType][nLineNum]->setOrderOption(nPrice, dlCount, nTradeType, nCoinType);

		m_arLineNum[nCoinType]++;
	}

	updateLineSort(nCoinType);
}

void C_Stand_Trade::init()
{
	m_pMainLayer = nullptr;
}

void C_Stand_Trade::mainBoard()
{
	createLayer();
	createSprite();
	createLineList();
	
	presetPosition();
	presetScale();

	addChildItems();
}

void C_Stand_Trade::createLayer()
{
	m_pMainLayer = C_Layer_Management::createLayer("Stand_Trader_Layer");
}

void C_Stand_Trade::createSprite()
{
	m_pTab = C_Sprite_Management::createSprite("UI_Items/", "History_Tab", "History_Tab");

	m_pTab->setVisible(true);
}

void C_Stand_Trade::createLineList()
{
	for (int nCoin((int)E_COIN::E_STANDARD); nCoin < (int)E_COIN::E_MAX; nCoin++)
	{
		for (int nList((int)E_STAND_RANGE::E_NONE); nList < (int)E_STAND_RANGE::E_MAX; nList++)
		{
			m_arLineList[nCoin][nList] = C_StandLine::create();
		}
	}
}

void C_Stand_Trade::presetPosition()
{
	m_pTab->setPosition(270.0f, 355.0f);
}

void C_Stand_Trade::presetScale()
{
	m_pTab->setScale(0.5f);
}

void C_Stand_Trade::addChildItems()
{
	for (int nCoin((int)E_COIN::E_STANDARD); nCoin < (int)E_COIN::E_MAX; nCoin++)
	{
		for (int nList((int)E_STAND_RANGE::E_NONE); nList < (int)E_STAND_RANGE::E_MAX; nList++)
		{
			m_pMainLayer->addChild(m_arLineList[nCoin][nList]->getLayer());
		}
	}

	m_pMainLayer->addChild(m_pTab);
}
