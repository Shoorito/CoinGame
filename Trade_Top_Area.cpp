#include "Sprite_Management.h"
#include "C_CoinManagement.h"
#include "Trade_Top_Area.h"
#include "C_Trade_Menu.h"

C_Trade_Top_Menu * C_Trade_Top_Menu::m_pMyPointer = nullptr;

C_Trade_Top_Menu * C_Trade_Top_Menu::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Trade_Top_Menu();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Trade_Top_Menu::setCoinType(const int nCoinType)
{
	m_nCoinType = nCoinType;

	m_pPastTitle->setVisible(false);

	m_pPastTitle = m_arTitle[m_nCoinType];
}

void C_Trade_Top_Menu::setEnabeld(const bool isEnabled)
{
	if (isEnabled)
	{
		callUpdateEvent();
	}
	else
	{
		m_pMainLayer->stopAllActions();
	}

	m_pTouchEvent->setEnabled(isEnabled);
	m_pMainLayer->setVisible(isEnabled);
	m_pPastTitle->setVisible(isEnabled);
}

void C_Trade_Top_Menu::init()
{
	m_pMainLayer = nullptr;
}

void C_Trade_Top_Menu::mainBoard()
{
	createLayer();
	createSprite();
	createLabel();
	createTouchEvent();

	presetPosition();
	presetAnchor();
	presetScale();
	presetPrePrice();
	presetRect();
	presetPastTitle();
	
	addChildItems();
}

void C_Trade_Top_Menu::createLayer()
{
	m_pMainLayer = Layer::create();
}

void C_Trade_Top_Menu::createSprite()
{
	std::string strRoute("");

	strRoute = "Trade_Resource/";

	m_pBackground = C_Sprite_Management::createSprite(strRoute, "Trade_Top_BG", "Trade_TopArea_BG");

	m_pBackground->setVisible(true);

	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		std::string strFile("");

		strFile = "Coin_Title_0" + std::to_string(nList);

		m_arTitle[nList] = Sprite::create(strRoute + strFile + ".png");

		m_arTitle[nList]->setVisible(false);
	}

	m_pFavorite = C_Sprite_Management::createSprite("Buttons/", "Favorite_Unselected_icon", "Trade_Favorite");

	m_pFavorite->setVisible(true);
}

void C_Trade_Top_Menu::createLabel()
{
	m_pNowPrice		= Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "");
	m_pNetChange	= Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "");
	m_pLowPrice		= Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "");
	m_pHighPrice	= Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "");
	m_pNetChangePer = Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "");
}

void C_Trade_Top_Menu::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_Trade_Top_Menu::touchOnBegan, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_Trade_Top_Menu::touchOnEnded, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_Trade_Top_Menu::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_Trade_Top_Menu::touchOnCanceled, this);

	m_pTouchEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_Trade_Top_Menu::callUpdateEvent()
{
	CallFunc*	pFunc(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSeq(nullptr);
	Repeat*		pRep(nullptr);

	pFunc = CallFunc::create(CC_CALLBACK_0(C_Trade_Top_Menu::updateData, this));
	pDelay = DelayTime::create(0.3f);
	pSeq = Sequence::create(pFunc, pDelay, nullptr);
	pRep = Repeat::create(pSeq, -1);

	m_pMainLayer->runAction(pRep);
}

void C_Trade_Top_Menu::presetPosition()
{
	m_pBackground->setPosition(0.0f, 750.0f);

	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		m_arTitle[nList]->setPosition(270.0f, 922.5f);
	}
	
	m_pNowPrice->setPosition(270.0f, 880.0f);
	m_pNetChange->setPosition(258.5f, 841.0f);
	m_pFavorite->setPosition(508.5f, 922.5f);
	m_pNetChangePer->setPosition(m_pNetChange->getPosition() + Point(23.0f, 0.0f));
	m_pLowPrice->setPosition(m_pNetChange->getPosition() + Point(0.0f, -33.5f));
	m_pHighPrice->setPosition(m_pNetChangePer->getPosition() + Point(0.0f, -33.5f));
}

void C_Trade_Top_Menu::presetAnchor()
{
	m_pBackground->setAnchorPoint(Vec2(0.0f, 0.0f));
	m_pNetChange->setAnchorPoint(Vec2(1.0f, 0.5f));
	m_pNetChangePer->setAnchorPoint(Vec2(0.0f, 0.5f));
	m_pLowPrice->setAnchorPoint(Vec2(1.0f, 0.5f));
	m_pHighPrice->setAnchorPoint(Vec2(0.0f, 0.5f));
}

void C_Trade_Top_Menu::presetScale()
{
	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		m_arTitle[nList]->setScale(0.5f);
	}

	m_pBackground->setScale(0.5f);
	m_pFavorite->setScale(0.5f);
	
	m_pNowPrice->setScale(0.7f);
	m_pHighPrice->setScale(0.7f);
	m_pLowPrice->setScale(0.7f);
	m_pNetChange->setScale(0.7f);
	m_pNetChangePer->setScale(0.7f);
}

void C_Trade_Top_Menu::presetPrePrice()
{
	C_Coin* pCoin(nullptr);

	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		pCoin = C_CoinManagement::getInstance()->getCoin(nList);

		m_arPrePrice[nList] = pCoin->getPrePrice();
		m_arLowPrice[nList] = pCoin->getPrePrice();
	}
}

void C_Trade_Top_Menu::presetPastTitle()
{
	m_pPastTitle = m_arTitle[(int)E_COIN::E_STANDARD];
}

void C_Trade_Top_Menu::presetRect()
{
	m_recReturnButton = Rect(15.5f, 911.0f, 23.0f, 23.0f);
	m_recFavoriteButton = Rect(496.5f, 911.0f, 24.0f, 23.0f);
}

void C_Trade_Top_Menu::addChildItems()
{
	m_pMainLayer->addChild(m_pBackground);

	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		m_pMainLayer->addChild(m_arTitle[nList]);
	}

	m_pMainLayer->addChild(m_pFavorite);
	m_pMainLayer->addChild(m_pNetChange);
	m_pMainLayer->addChild(m_pNetChangePer);
	m_pMainLayer->addChild(m_pLowPrice);
	m_pMainLayer->addChild(m_pHighPrice);
	m_pMainLayer->addChild(m_pNowPrice);
}

void C_Trade_Top_Menu::updateData()
{
	int nNowPrice(0);
	C_Coin* pCoin(nullptr);
	std::string strNowPrice("");
	std::string strNetChange("");
	std::string strLowPrice("");
	std::string strHighPrice("");
	std::string strNetChangePer("");
	std::string strChangePer("");

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	nNowPrice = pCoin->getPrice();

	if (m_arPrePrice[m_nCoinType] < nNowPrice)
	{
		m_arPrePrice[m_nCoinType] = nNowPrice;
	}
	else if (m_arLowPrice[m_nCoinType] > nNowPrice)
	{
		m_arLowPrice[m_nCoinType] = nNowPrice;
	}

	if (pCoin->getRate() >= 0.0f)
	{
		m_pNetChange->setColor(Color3B(55, 212, 0));
		m_pNetChangePer->setColor(Color3B(55, 212, 0));
	}
	else
	{
		m_pNetChange->setColor(Color3B(225, 26, 69));
		m_pNetChangePer->setColor(Color3B(225, 26, 69));
	}

	strNowPrice = std::to_string(pCoin->getPrice());
	strNetChange = std::to_string(pCoin->getRatePrice());
	strNetChangePer = std::to_string(pCoin->getRate());
	strLowPrice = std::to_string(m_arLowPrice[m_nCoinType]);
	strHighPrice = std::to_string(m_arPrePrice[m_nCoinType]);

	for (int nList(0); nList < (int)strNetChangePer.size() - 4; nList++)
	{
		strChangePer += strNetChangePer.at(nList);
	}

	m_pNowPrice->setString(strNowPrice);
	m_pHighPrice->setString(strHighPrice);
	m_pLowPrice->setString(strLowPrice);
	m_pNetChange->setString(strNetChange);
	m_pNetChangePer->setString(strChangePer + '%');
}

bool C_Trade_Top_Menu::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouch(Vec2::ZERO);

	vecTouch = pTouch->getLocation();

	if (m_recReturnButton.containsPoint(vecTouch))
	{
		C_Trade_Menu::getInstance()->setEnabled(false, (int)E_COIN::E_STANDARD);

		return true;
	}

	return false;
}

bool C_Trade_Top_Menu::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Trade_Top_Menu::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Trade_Top_Menu::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}
