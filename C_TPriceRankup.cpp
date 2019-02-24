#include "C_TPriceRankup.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "C_CoinManagement.h"
#include "Korean_UTF8.h"

C_TPrice_Rankup* C_TPrice_Rankup::m_pMyPointer = nullptr;

C_TPrice_Rankup * C_TPrice_Rankup::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_TPrice_Rankup();
	
	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_TPrice_Rankup::init()
{
	m_pMainLayer	= nullptr;
	m_pChart		= nullptr;
	m_pActNode		= nullptr;
}

void C_TPrice_Rankup::mainBoard()
{
	createSpriteItem();
	createLabelItem();
	createLayerItem();

	presetCoinList();
	setRankItem();
	addChildItems();
	presetItemsOption();

	updateRankItem();
}

void C_TPrice_Rankup::createSpriteItem()
{
	m_pChart = C_Sprite_Management::createSprite("UI_Items/", "Volume_Chart",  "Volume_Chart");

	for (int nListNum((int)E_RANK_TYPE::E_FIRST); nListNum < (int)E_RANK_TYPE::E_MAX; nListNum++)
	{
		m_arLogo[nListNum] = Sprite::create();
		m_arInfo[nListNum] = Sprite::create();
	}
}

void C_TPrice_Rankup::createLabelItem()
{
	for (int nListNum((int)E_RANK_TYPE::E_FIRST); nListNum < (int)E_RANK_TYPE::E_MAX; nListNum++)
	{
		m_arNowPrice[nListNum]  = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");
		m_arNowTPrice[nListNum] = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");
	}
}

void C_TPrice_Rankup::createLayerItem()
{
	m_pMainLayer = C_Layer_Management::createLayer("Rankup_MainLayer");

	m_pActNode = Node::create();
}

void C_TPrice_Rankup::presetCoinList()
{
	for (int nCoin((int)E_COIN::E_STANDARD); nCoin < (int)E_COIN::E_MAX; nCoin++)
	{
		m_arCoinList[nCoin] = C_CoinManagement::getInstance()->getCoin(nCoin);
	}
}

void C_TPrice_Rankup::presetItemsOption()
{
	m_pChart->setPosition(0.0f, 0.0f);

	m_pChart->setVisible(true);
	m_pChart->setScale(0.5f);

	for (int nRank((int)E_RANK_TYPE::E_FIRST); nRank < (int)E_RANK_TYPE::E_MAX; nRank++)
	{
		Sprite* pLogo(nullptr);
		Sprite* pInfo(nullptr);
		Label*	pNowPrice(nullptr);
		Label*	pNowTPrice(nullptr);

		pLogo		= m_arLogo[nRank];
		pInfo		= m_arInfo[nRank];
		pNowPrice	= m_arNowPrice[nRank];
		pNowTPrice	= m_arNowTPrice[nRank];

		pLogo->setPosition(-238.5f, 19.5f - (50.0f * (nRank - 1)));
		pInfo->setPosition(pLogo->getPosition() + Point(83.0f, 0.0f));
		pNowPrice->setPosition(pInfo->getPosition() + Point(151.0f, 0.0f));
		pNowTPrice->setPosition(pNowPrice->getPosition() + Point(204.0f, 0.0f));
	
		pLogo->setVisible(true);
		pInfo->setVisible(true);

		pLogo->setScale(0.5f);
		pInfo->setScale(0.5f);
		pNowPrice->setScale(0.7f);
		pNowTPrice->setScale(0.7f);
	}
}

void C_TPrice_Rankup::setRankItem()
{
	C_Coin* pCoin(nullptr);

	soltItem(m_arCoinList, (int)E_COIN::E_STANDARD, (int)E_COIN::E_MAX - 1);

	for (int nRank((int)E_RANK_TYPE::E_FIRST); nRank < (int)E_RANK_TYPE::E_MAX; nRank++)
	{
		pCoin = m_arCoinList[(int)E_COIN::E_MAX - nRank];

		m_arLogo[nRank]->setSpriteFrame(pCoin->getImage()->getSpriteFrame());
		m_arInfo[nRank]->setSpriteFrame(pCoin->getNameImg()->getSpriteFrame());
		m_arNowPrice[nRank]->setString(UTF8(std::to_string(pCoin->getPrice()) + " ¿ø"));
		m_arNowTPrice[nRank]->setString(UTF8(std::to_string(pCoin->getTPrice()) + " ¹é¸¸"));
	}
}

void C_TPrice_Rankup::updateRankItem()
{
	CallFunc* pFunc(nullptr);
	DelayTime* pDelay(nullptr);
	Sequence* pSequance(nullptr);
	Repeat* pRepeat(nullptr);

	pFunc		= CallFunc::create(CC_CALLBACK_0(C_TPrice_Rankup::setRankItem, this));
	pDelay		= DelayTime::create(5.0f);
	pSequance	= Sequence::create(pFunc, pDelay, nullptr);
	pRepeat		= Repeat::create(pSequance, -1);

	m_pActNode->runAction(pRepeat);
}

void C_TPrice_Rankup::addChildItems()
{
	m_pMainLayer->addChild(m_pChart);
	m_pMainLayer->addChild(m_pActNode);

	for (int nItem((int)E_RANK_TYPE::E_FIRST); nItem < (int)E_RANK_TYPE::E_MAX; nItem++)
	{
		m_pMainLayer->addChild(m_arLogo[nItem]);
		m_pMainLayer->addChild(m_arInfo[nItem]);
		m_pMainLayer->addChild(m_arNowPrice[nItem]);
		m_pMainLayer->addChild(m_arNowTPrice[nItem]);
	}
}

void C_TPrice_Rankup::soltItem(C_Coin ** arList, const int nLeft, const int nRight)
{
	C_Coin* pTemp(nullptr);
	int		nLeftpos(0);
	int		nRightpos(0);
	int		nSLeftpos(0);
	int		nSRightpos(0);
	int		nKey(0);

	if (nRight > nLeft)
	{
		nLeftpos	= nLeft;
		nRightpos	= nRight + 1;
		nKey		= arList[nLeft]->getTPrice();

		while (nLeftpos < nRightpos)
		{
			nSLeftpos = nLeftpos + 1;
			nSRightpos = nRightpos - 1;

			while ((arList[nSLeftpos]->getTPrice()) < nKey && (nSLeftpos < nRight)) { nSLeftpos++; }
			while ((arList[nSRightpos]->getTPrice()) > nKey && (nSRightpos > nLeft)) { nSRightpos--; }

			if (nSRightpos > nSLeftpos)
			{
				pTemp = arList[nSLeftpos];
				arList[nSLeftpos] = arList[nSRightpos];
				arList[nSRightpos] = pTemp;
			}

			nLeftpos = nSLeftpos;
			nRightpos = nSRightpos;
		}

		pTemp = arList[nLeft];
		arList[nLeft] = arList[nRightpos];
		arList[nRightpos] = pTemp;

		soltItem(arList, nLeft, nRightpos - 1);
		soltItem(arList, nRightpos + 1, nRight);
	}
}
