#include "Trade_Bottom_Area.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "C_Stand_Trade.h"
#include "AppointTrade.h"

C_Trade_Bottom_Menu * C_Trade_Bottom_Menu::m_pMyPointer = nullptr;

C_Trade_Bottom_Menu * C_Trade_Bottom_Menu::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Trade_Bottom_Menu();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Trade_Bottom_Menu::setEnabledEvent(const bool isEnabled, const int nCoinType)
{
	C_Appoint_Trade* pATrade(nullptr);

	pATrade = C_Appoint_Trade::getInstance();

	if (isEnabled)
	{
		pATrade->setCoinType(nCoinType);
	}

	pATrade->setAllEnabled(isEnabled);
	m_pTouchEvent->setEnabled(isEnabled);
	m_pMainLayer->setVisible(isEnabled);
}

void C_Trade_Bottom_Menu::init()
{
	m_pPastButton = nullptr;
	m_pMainLayer  = nullptr;
	m_pBackground = nullptr;
	m_pTouchEvent = nullptr;
	m_isTrade	  = false;
}

void C_Trade_Bottom_Menu::mainBoard()
{
	createLayer();
	createSprite();
	createTradeMenu();
	createTouchEvent();

	presetScale();
	presetVisible();
	presetPosition();
	presetPastMenu();
	presetRectList();
	presetFuncList();

	addChildItems();
}

void C_Trade_Bottom_Menu::createSprite()
{
	for (int nImg((int)E_CHART_MENU::E_APPOINT); nImg < (int)E_CHART_MENU::E_MAX; nImg++)
	{
		std::string strName("");
		std::string strTag("");

		strName = "Chart_Menu_0" + std::to_string(nImg);
		strTag = "Trade_Chart_Button_0" + std::to_string(nImg);

		m_arMenuImg[nImg] = C_Sprite_Management::createSprite("UI_Items/", strName, strTag);
	}

	m_pBackground = C_Sprite_Management::createSprite("UI_Items/", "Trade_Tab", "Trade_Tab_BG");
}

void C_Trade_Bottom_Menu::createLayer()
{
	m_pMainLayer = C_Layer_Management::createLayer("Chart_Menu_Layer");
	m_pBG_Layer = C_Layer_Management::createColorLayer("Chart_Menu_BG", Color4B(25, 33, 52, 255));

	m_pBG_Layer->setContentSize(Size(540.0f, 270.0f));
}

void C_Trade_Bottom_Menu::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_Trade_Bottom_Menu::touchOnBegan, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_Trade_Bottom_Menu::touchOnEnded, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_Trade_Bottom_Menu::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_Trade_Bottom_Menu::touchOnCanceled, this);

	m_pTouchEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_Trade_Bottom_Menu::createTradeMenu()
{
	C_Appoint_Trade::create();
	C_Stand_Trade::create();
}

void C_Trade_Bottom_Menu::presetVisible()
{
	for (int nImg((int)E_CHART_MENU::E_APPOINT); nImg < (int)E_CHART_MENU::E_MAX; nImg++)
	{
		m_arMenuImg[nImg]->setVisible(false);
	}

	m_pBackground->setVisible(true);
	C_Stand_Trade::getInstance()->getLayer()->setVisible(false);
}

void C_Trade_Bottom_Menu::presetScale()
{
	for (int nImg((int)E_CHART_MENU::E_APPOINT); nImg < (int)E_CHART_MENU::E_MAX; nImg++)
	{
		m_arMenuImg[nImg]->setScale(0.5f);
	}
	
	m_pBackground->setScale(0.5f);
}

void C_Trade_Bottom_Menu::presetPosition()
{
	float fXpos(0.0f);
	float fYpos(0.0f);

	fXpos = 90.0f;
	fYpos = 390.0f;

	m_pBackground->setPosition(270.0f, fYpos);
	m_pBG_Layer->setPosition(0.0f, 100.0f);

	for (int nImg((int)E_CHART_MENU::E_APPOINT); nImg < (int)E_CHART_MENU::E_MAX; nImg++)
	{
		Sprite* pTarget(nullptr);

		pTarget = m_arMenuImg[nImg];

		pTarget->setPosition(fXpos, fYpos);

		fXpos += (pTarget->getContentSize().width / 2.0f);
	}
}

void C_Trade_Bottom_Menu::presetPastMenu()
{
	m_pPastButton = m_arMenuImg[(int)E_CHART_MENU::E_APPOINT];

	m_pPastButton->setVisible(true);
}

void C_Trade_Bottom_Menu::presetRectList()
{
	for (int nImg((int)E_CHART_MENU::E_APPOINT); nImg < (int)E_CHART_MENU::E_MAX; nImg++)
	{
		m_arRectList[nImg] = m_arMenuImg[nImg]->getBoundingBox();
	}
}

void C_Trade_Bottom_Menu::presetFuncList()
{
	m_arFuncList[(int)E_CHART_MENU::E_APPOINT] = &C_Trade_Bottom_Menu::changeMode;
	m_arFuncList[(int)E_CHART_MENU::E_MARKET_PRICE] = &C_Trade_Bottom_Menu::changeMode;
	m_arFuncList[(int)E_CHART_MENU::E_NOT_TRADE] = &C_Trade_Bottom_Menu::changeMenu;
}

void C_Trade_Bottom_Menu::addChildItems()
{
	C_Appoint_Trade* pAppoint(nullptr);
	C_Stand_Trade* pStand(nullptr);

	pAppoint = C_Appoint_Trade::getInstance();
	pStand = C_Stand_Trade::getInstance();

	m_pMainLayer->addChild(m_pBackground);
	m_pMainLayer->addChild(m_pBG_Layer);

	for (int nImg((int)E_CHART_MENU::E_APPOINT); nImg < (int)E_CHART_MENU::E_MAX; nImg++)
	{
		m_pMainLayer->addChild(m_arMenuImg[nImg]);
	}

	m_pMainLayer->addChild(pAppoint->getLayer());
	m_pMainLayer->addChild(pStand->getLayer());
}

void C_Trade_Bottom_Menu::changeMode(const int nType)
{
	C_Appoint_Trade* pTrader(nullptr);
	C_Stand_Trade* pStand(nullptr);

	pTrader = C_Appoint_Trade::getInstance();
	pStand  = C_Stand_Trade::getInstance();

	pTrader->getLayer()->setVisible(true);
	pStand->setEnabled(false);

	if (!m_isTrade)
	{
		pTrader->setAllEnabled(true);

		m_isTrade = true;
	}

	if (nType == (int)E_CHART_MENU::E_APPOINT)
	{
		pTrader->setBoxEnabled(E_BOX_TYPE::E_BUY_PRICE, true);
		pTrader->setBoxEnabled(E_BOX_TYPE::E_SELL_PRICE, true);
		pTrader->setEnabledNowPrice(false);
	}
	else if (nType == (int)E_CHART_MENU::E_MARKET_PRICE)
	{
		pTrader->setBoxEnabled(E_BOX_TYPE::E_BUY_PRICE, false);
		pTrader->setBoxEnabled(E_BOX_TYPE::E_SELL_PRICE, false);
		pTrader->setEnabledNowPrice(true);
	}
}

void C_Trade_Bottom_Menu::changeMenu(const int nType)
{
	C_Appoint_Trade* pTrader(nullptr);
	C_Stand_Trade* pStand(nullptr);

	pTrader = C_Appoint_Trade::getInstance();
	pStand  = C_Stand_Trade::getInstance();

	m_isTrade = false;

	pTrader->setAllEnabled(false);

	pStand->setEnabled(true);

	pTrader->setEnabledNowPrice(false);
}

bool C_Trade_Bottom_Menu::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouch(Vec2::ZERO);

	vecTouch = pTouch->getLocation();

	for (int nRect((int)E_CHART_MENU::E_APPOINT); nRect < (int)E_CHART_MENU::E_MAX; nRect++)
	{
		if (m_arRectList[nRect].containsPoint(vecTouch))
		{
			m_pPastButton->setVisible(false);

			m_pPastButton = m_arMenuImg[nRect];

			m_pPastButton->setVisible(true);

			(this->*m_arFuncList[nRect])(nRect);
			
			return true;
		}
	}

	return false;
}

bool C_Trade_Bottom_Menu::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Trade_Bottom_Menu::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Trade_Bottom_Menu::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}
