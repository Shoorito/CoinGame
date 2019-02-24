#include "C_History_Menu.h"
#include "C_PlayerManagement.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "Scene_Manager.h"
#include "Korean_UTF8.h"

C_History_Menu* C_History_Menu::m_pMyPointer = nullptr;

C_History_Menu * C_History_Menu::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_History_Menu();
	
	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_History_Menu::setEnabled(const bool isEnabled)
{
	if (isEnabled && !isHoldCoin())
	{
		m_pNotHoldCoin->setVisible(true);
	}
	else
	{
		m_pNotHoldCoin->setVisible(false);
	}
	
	if (isEnabled)
	{
		callAction();
		callNodeList();
	}
	else
	{
		for (int nNode((int)E_COIN::E_STANDARD); nNode < m_nHoldCount; nNode++)
		{
			m_arNowHoldNode[nNode]->setEnabled(false);
			m_arNowHoldNode[nNode] = nullptr;
		}

		m_pMainLayer->stopAllActions();
	}
	
	m_pMainLayer->setVisible(isEnabled);
}

void C_History_Menu::init()
{
	m_pMainLayer		= nullptr;
	m_pPlayerMoney_BG	= nullptr;
	m_pHoldCoin_BG		= nullptr;
	m_pPlayerCredit		= nullptr;
	m_pPlayerMoney		= nullptr;
	m_pAmountMoney		= nullptr;
	m_pNowProfit		= nullptr;
	m_pNowValuable		= nullptr;
	m_pProfitPercent	= nullptr;
	m_pNotHoldCoin		= nullptr;
	m_nHoldCount = 0;
}

void C_History_Menu::mainBoard()
{
	createMenuLayer();
	createSpriteItem();
	createLabelItem();
	createHoldList();

	presetSpritesOption();
	presetLabelsOption();
	presetInformation();

	addChildItems();
}

void C_History_Menu::createSpriteItem()
{
	m_pPlayerMoney_BG	= C_Sprite_Management::createSprite("UI_Items/", "Credit_Info", "Credit_BG");
	m_pHoldCoin_BG		= C_Sprite_Management::createSprite("UI_Items/", "Hold_Coin", "Hold_Coin_BG");
	m_pNotHoldCoin		= Sprite::create("UI_Items/Not_Have_Coin.png");

	m_pHoldCoin_BG->setVisible(true);
	m_pPlayerMoney_BG->setVisible(true);
}

void C_History_Menu::createLabelItem()
{
	m_pPlayerCredit  = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pPlayerMoney	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pAmountMoney	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pNowProfit	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pNowValuable	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pProfitPercent = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
}

void C_History_Menu::createMenuLayer()
{
	m_pMainLayer = C_Layer_Management::createLayer("History_Menu_Layer");
}

void C_History_Menu::createHoldList()
{
	for (int nCoin((int)E_COIN::E_STANDARD); nCoin < (int)E_COIN::E_MAX; nCoin++)
	{
		m_arHoldNode[nCoin] = C_HoldNode::create(nCoin);
	}
}

void C_History_Menu::presetSpritesOption()
{
	m_pHoldCoin_BG->setScale(0.5f);
	m_pPlayerMoney_BG->setScale(0.5f);
	m_pNotHoldCoin->setScale(0.5f);

	m_pPlayerMoney_BG->setAnchorPoint(Point(0.5f, 1.0f));
	m_pHoldCoin_BG->setAnchorPoint(Point(0.5f, 1.0f));

	m_pPlayerMoney_BG->setPosition(0.0f, 359.0f);
	m_pHoldCoin_BG->setPosition(0.0f, 169.0f);
	m_pNotHoldCoin->setPosition(0.0f, -100.0f);
}

void C_History_Menu::presetLabelsOption()
{
	m_pPlayerMoney->setScale(0.7f);
	m_pPlayerCredit->setScale(0.7f);

	m_pProfitPercent->setScale(0.5f);
	m_pNowProfit->setScale(0.5f);
	m_pNowValuable->setScale(0.5f);
	m_pAmountMoney->setScale(0.5f);

	m_pPlayerMoney->setAnchorPoint(Point(0.0f, 0.5f));
	m_pPlayerCredit->setAnchorPoint(Point(0.0f, 0.5f));

	m_pAmountMoney->setAnchorPoint(Point(1.0f, 0.5f));
	m_pNowProfit->setAnchorPoint(Point(1.0f, 0.5f));
	m_pNowValuable->setAnchorPoint(Point(1.0f, 0.5f));
	m_pProfitPercent->setAnchorPoint(Point(1.0f, 0.5f));

	m_pPlayerMoney->setPosition(-254.5f, m_pPlayerMoney_BG->getPositionY() - 90.0f);
	m_pPlayerCredit->setPosition(m_pPlayerMoney->getPosition() + Point(0.0f, -74.0f));

	m_pProfitPercent->setPosition(Point(255.0f, m_pPlayerCredit->getPositionY()));
	m_pNowProfit->setPosition(m_pProfitPercent->getPosition() + Point(0.0f, 37.0f));
	m_pNowValuable->setPosition(m_pNowProfit->getPosition() + Point(0.0f, 37.0f));
	m_pAmountMoney->setPosition(m_pNowValuable->getPosition() + Point(0.0f, 37.0f));
}

void C_History_Menu::presetInformation()
{
	C_Player_Management* pPlayer(nullptr);
	long long llPlayerMoney(0ll);
	long long llPlayerCredit(0ll);
	long long llPlayerBuyPrice(0ll);
	long long llPlayerAppraisal(0ll);
	long long llPlayerProfit(0ll);
	float fPlayerProfitPer(0ll);
	std::string strProfitPer("");
	std::string strConvertPer("");

	pPlayer = C_Player_Management::getInstance();

	for (int nCoin((int)E_COIN::E_STANDARD); nCoin < (int)E_COIN::E_MAX; nCoin++)
	{
		pPlayer->updateAnotherInfo(nCoin);

		llPlayerCredit		+= pPlayer->getAppraisalPrice(nCoin);
		llPlayerBuyPrice	+= pPlayer->getBuyMoney(nCoin);
		llPlayerAppraisal	+= pPlayer->getAppraisalPrice(nCoin);
		llPlayerProfit		+= pPlayer->getProfit(nCoin);
		fPlayerProfitPer	+= pPlayer->getProfitPer(nCoin);
	}

	fPlayerProfitPer	/= 1.0f;
	llPlayerMoney		 = pPlayer->getPlayerMoney();
	llPlayerCredit		+= llPlayerMoney;

	strProfitPer = std::to_string(fPlayerProfitPer);

	for (int nCoin(0); nCoin < (int)strProfitPer.size() - 4; nCoin++)
	{
		strConvertPer += strProfitPer.at(nCoin);
	}

	m_pPlayerMoney->setString(std::to_string(pPlayer->getPlayerMoney()) + UTF8("원"));
	m_pPlayerCredit->setString(std::to_string(llPlayerCredit) + UTF8("원"));
	m_pAmountMoney->setString(std::to_string(llPlayerBuyPrice) + UTF8("원"));
	m_pNowValuable->setString(std::to_string(llPlayerAppraisal) + UTF8("원"));
	m_pNowProfit->setString(std::to_string(llPlayerProfit) + UTF8("원"));
	m_pProfitPercent->setString(strConvertPer + "%");
}

void C_History_Menu::callAction()
{
	CallFunc*	pFunc(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSeq(nullptr);
	Repeat*		pRep(nullptr);

	pFunc = CallFunc::create(CC_CALLBACK_0(C_History_Menu::presetInformation, this));
	pDelay = DelayTime::create(0.5f);
	pSeq = Sequence::create(pFunc, pDelay, nullptr);
	pRep = Repeat::create(pSeq, -1);

	m_pMainLayer->runAction(pRep);
}

void C_History_Menu::callNodeList()
{
	C_Player_Management* pPlayer(nullptr);
	int nPosNum(0);

	pPlayer = C_Player_Management::getInstance();

	for (int nCoin((int)E_COIN::E_STANDARD); nCoin < (int)E_COIN::E_MAX; nCoin++)
	{
		pPlayer->updateAnotherInfo(nCoin);

		if (pPlayer->getPlayerCoin(nCoin) > 0)
		{
			m_arHoldNode[nCoin]->setEnabled(true);

			m_arHoldNode[nCoin]->getMainLayer()->setPosition(-265.0f, -138.0f * nPosNum);
			
			m_arNowHoldNode[nPosNum + 1] = m_arHoldNode[nCoin];

			nPosNum++;
		}
		else
		{
			m_arHoldNode[nCoin]->setEnabled(false);
		}
	}

	m_nHoldCount = nPosNum;
}

void C_History_Menu::addChildItems()
{
	m_pMainLayer->addChild(m_pPlayerMoney_BG);
	m_pMainLayer->addChild(m_pHoldCoin_BG);
	m_pMainLayer->addChild(m_pPlayerCredit);
	m_pMainLayer->addChild(m_pPlayerMoney);
	m_pMainLayer->addChild(m_pAmountMoney);
	m_pMainLayer->addChild(m_pNowProfit);
	m_pMainLayer->addChild(m_pNowValuable);
	m_pMainLayer->addChild(m_pProfitPercent);
	m_pMainLayer->addChild(m_pNotHoldCoin);

	for (int nCoin((int)E_COIN::E_STANDARD); nCoin < (int)E_COIN::E_MAX; nCoin++)
	{
		m_pMainLayer->addChild(m_arHoldNode[nCoin]->getMainLayer());
	}
}

bool C_History_Menu::isHoldCoin()
{
	C_Player_Management* pPlayer(nullptr);
	
	pPlayer = C_Player_Management::getInstance();

	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		int nNum(0);

		nNum = pPlayer->getPlayerCoin(nList);

		if (nNum > 1)
		{
			return true;
		}
	}

	return false;
}
