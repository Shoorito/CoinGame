#include "C_HoldNode.h"
#include "Layer_Management.h"
#include "ShareKey.h"
#include "C_CoinManagement.h"
#include "Sprite_Management.h"
#include "C_PlayerManagement.h"
#include "Korean_UTF8.h"

C_HoldNode * C_HoldNode::create(const int nCoinType)
{
	C_HoldNode* pNode(nullptr);

	pNode = new(std::nothrow) C_HoldNode();

	pNode->init();
	pNode->m_nType = nCoinType;
	pNode->mainBoard();

	return pNode;
}

void C_HoldNode::setEnabled(const bool isEnabled)
{
	if (isEnabled)
	{
		callUpdate();
	}
	else
	{
		m_pMainLayer->stopAllActions();
	}

	m_pMainLayer->setVisible(isEnabled);
}

void C_HoldNode::init()
{
	m_pMainLayer	 = nullptr;
	m_pLogo			 = nullptr;
	m_pBasicImg		 = nullptr;
	m_pHoldCount	 = nullptr;
	m_pHoldPrice	 = nullptr;
	m_pProfitPrice	 = nullptr;
	m_pProfitPer	 = nullptr;
	m_pAveragePrice  = nullptr;
	m_pValuablePrice = nullptr;
	m_pName			= nullptr;
	m_strName		 = "";
}

void C_HoldNode::mainBoard()
{
	presetName();
	createNodeLayer();
	createSpriteItem();
	createLabelItem();

	addChildItems();

	presetLabelText();
	presetItemsSize();
	presetItemsAnchor();
	presetItemsPosition();

	setEnabled(false);
}

void C_HoldNode::createNodeLayer()
{
	m_pMainLayer = Layer::create();
}

void C_HoldNode::createSpriteItem()
{
	C_Coin* pCoin(nullptr);
	SpriteFrame* pFrame(nullptr);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nType);
	pFrame = pCoin->getImage()->getSpriteFrame();

	m_pLogo = Sprite::createWithSpriteFrame(pFrame);
	m_pBasicImg = Sprite::create("UI_Items/Hold_Node.png");
}

void C_HoldNode::createLabelItem()
{
	m_pHoldCount	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pHoldPrice	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pProfitPrice	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pProfitPer	 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pAveragePrice  = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pValuablePrice = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pName			 = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
}

void C_HoldNode::presetName()
{
	m_strName = UTF8(S_KeyStore::arUseCoinName[m_nType]);
}

void C_HoldNode::presetLabelText()
{
	m_pHoldCount->setString(UTF8("0 개"));
	m_pHoldPrice->setString(UTF8("0 원"));
	m_pProfitPrice->setString(UTF8("0 원"));
	m_pProfitPer->setString(UTF8("0.0%"));
	m_pAveragePrice->setString(UTF8("0 원"));
	m_pValuablePrice->setString(UTF8("0 원"));
	m_pName->setString(m_strName);
}

void C_HoldNode::presetItemsSize()
{
	m_pName->setScale(0.7f);
	m_pLogo->setScale(0.5f);
	m_pBasicImg->setScale(0.5f);
	m_pHoldCount->setScale(0.5f);
	m_pHoldPrice->setScale(0.5f);
	m_pProfitPrice->setScale(0.5f);
	m_pProfitPer->setScale(0.5f);
	m_pAveragePrice->setScale(0.5f);
	m_pValuablePrice->setScale(0.5f);
}

void C_HoldNode::presetItemsAnchor()
{
	m_pLogo->setAnchorPoint(Point(0.0f, 0.5f));
	m_pName->setAnchorPoint(Point(0.0f, 0.5f));
	m_pHoldCount->setAnchorPoint(Point(1.0f, 0.5f));
	m_pHoldPrice->setAnchorPoint(Point(1.0f, 0.5f));
	m_pProfitPrice->setAnchorPoint(Point(1.0f, 0.5f));
	m_pProfitPer->setAnchorPoint(Point(1.0f, 0.5f));
	m_pAveragePrice->setAnchorPoint(Point(1.0f, 0.5f));
	m_pValuablePrice->setAnchorPoint(Point(1.0f, 0.5f));
}

void C_HoldNode::presetItemsPosition()
{
	m_pBasicImg->setPosition(265.0f, 62.0f);
	m_pLogo->setPosition(19.5f, 102.5f);

	m_pName->setPosition(m_pLogo->getPosition() + Point(46.5f, 0.0f));
	m_pHoldCount->setPosition(254.5f, 52.5f);
	m_pHoldPrice->setPosition(m_pHoldCount->getPosition() + Point(0.0f, -32.5f));
	m_pValuablePrice->setPosition(m_pHoldPrice->getPosition() + Point(266.0f, 0.0f));
	m_pAveragePrice->setPosition(m_pValuablePrice->getPosition() + Point(0.0f, 32.5f));
	m_pProfitPer->setPosition(m_pAveragePrice->getPosition() + Point(0.0f, 32.5f));
	m_pProfitPrice->setPosition(m_pProfitPer->getPosition() + Point(0.0f, 32.5f));
}

void C_HoldNode::addChildItems()
{
	m_pMainLayer->addChild(m_pLogo);
	m_pMainLayer->addChild(m_pBasicImg);
	m_pMainLayer->addChild(m_pHoldCount);
	m_pMainLayer->addChild(m_pHoldPrice);
	m_pMainLayer->addChild(m_pProfitPrice);
	m_pMainLayer->addChild(m_pProfitPer);
	m_pMainLayer->addChild(m_pAveragePrice);
	m_pMainLayer->addChild(m_pValuablePrice);
	m_pMainLayer->addChild(m_pName);
}

void C_HoldNode::callUpdate()
{
	CallFunc* pFunc(nullptr);
	DelayTime* pDelay(nullptr);
	Sequence* pSequance(nullptr);
	Repeat* pRepeat(nullptr);

	pFunc = CallFunc::create(CC_CALLBACK_0(C_HoldNode::updateValues, this));
	pDelay = DelayTime::create(0.5f);
	pSequance = Sequence::create(pFunc, pDelay, nullptr);
	pRepeat = Repeat::create(pSequance, -1);

	m_pMainLayer->runAction(pRepeat);
}

void C_HoldNode::updateValues()
{
	long long llProfitPrice(0ll);
	long long llValuablePrice(0ll);
	long long llBuyMoney(0ll);
	long long llAvgPrice(0ll);
	float fProfitPercent(0.0f);
	float fHoldCoin(0.0f);
	std::string strProfitPer("");
	std::string strInvert("");
	C_Coin* pCoin(nullptr);
	C_Player_Management* pPlayer(nullptr);

	pPlayer = C_Player_Management::getInstance();
	pCoin = C_CoinManagement::getInstance()->getCoin(m_nType);

	llProfitPrice	= pPlayer->getProfit(m_nType);
	llValuablePrice	= (int)((float)pCoin->getPrice() * pPlayer->getPlayerCoin(m_nType));
	llAvgPrice		= pPlayer->getAvgPrice(m_nType);
	llBuyMoney		= pPlayer->getBuyMoney(m_nType);
	fProfitPercent  = pPlayer->getProfitPer(m_nType);
	fHoldCoin		= pPlayer->getPlayerCoin(m_nType);
	
	strInvert = std::to_string(abs(fProfitPercent));

	for (int nChar(0); nChar < (int)strInvert.size() - 4; nChar++)
	{
		strProfitPer += strInvert.at(nChar);
	}

	if (llProfitPrice < 0)
	{
		m_pProfitPrice->setColor(Color3B::RED);
		m_pProfitPer->setColor(Color3B::RED);
		m_pProfitPrice->setString(UTF8("▼" + std::to_string(abs(llProfitPrice)) + " 원"));
		m_pProfitPer->setString(UTF8("▼" + strProfitPer + "%"));
	}
	else
	{
		m_pProfitPrice->setColor(Color3B::GREEN);
		m_pProfitPer->setColor(Color3B::GREEN);
		m_pProfitPrice->setString(UTF8("▲" + std::to_string(abs(llProfitPrice)) + " 원"));
		m_pProfitPer->setString(UTF8("▲" + strProfitPer + "%"));
	}

	m_pValuablePrice->setString(UTF8(std::to_string(llValuablePrice) + " 원"));
	m_pAveragePrice->setString(std::to_string(llAvgPrice) + UTF8(" 원"));
	m_pHoldPrice->setString(std::to_string(llBuyMoney) + UTF8(" 원"));
	m_pHoldCount->setString(std::to_string(fHoldCoin) + UTF8(" 개"));
}
