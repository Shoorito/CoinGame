#include "C_Message_Management.h"
#include "C_PlayerManagement.h"
#include "C_CoinManagement.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "C_Stand_Trade.h"
#include "AppointTrade.h"
#include "ShareKey.h"

C_Appoint_Trade* C_Appoint_Trade::m_pMyPointer = nullptr;

C_Appoint_Trade * C_Appoint_Trade::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Appoint_Trade();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Appoint_Trade::updatePrice(const int nType)
{
	C_Coin* pCoin(nullptr);
	float fTradePrice(0.0f);
	float fTradeCount(0.0f);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	if (m_isNowPrice)	{ m_arPriceNum[nType] = pCoin->getPrice(); }
	else				{ m_arPriceNum[nType] = m_arValueBox[nType]->getValue(); }

	m_arCoinNum[nType]  = m_arValueBox[nType + 2]->getValue();
	
	fTradePrice = m_arPriceNum[nType];
	fTradeCount = m_arCoinNum[nType];

	m_arPrice[nType] = (long long)(fTradePrice * fTradeCount);

	m_arPriceLab[nType]->setString(std::to_string(m_arPrice[nType]) + u8"원");

	updateInfo();
}

void C_Appoint_Trade::setCoinType(const int nType)
{
	m_nCoinType = nType;

	updateInfo();
}

void C_Appoint_Trade::tradeCoin(const int nType)
{
	int arSwitch[(int)E_TRADE::E_MAX]{ 0, -1, 1 };
	C_Player_Management* pPlayer(nullptr);
	C_Coin* pCoin				(nullptr);
	long long nPlayerMoney		(0ll);
	long long nTradeMoney		(0ll);
	float fPlayerCoin			(0.0f);
	float fCoinNum				(0.0f);

	pPlayer = C_Player_Management::getInstance();
	pCoin	= C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	nTradeMoney  = m_arPrice[nType] *	 arSwitch[nType];
	fCoinNum	 = m_arCoinNum[nType] * -arSwitch[nType];
	nPlayerMoney = pPlayer->getPlayerMoney();
	fPlayerCoin  = pPlayer->getPlayerCoin(m_nCoinType);

	if (m_arPriceNum[nType] != pCoin->getPrice())
	{
		C_Stand_Trade* pTrade(nullptr);

		pTrade = C_Stand_Trade::getInstance();

		pTrade->addList(m_arPriceNum[nType], m_arCoinNum[nType], m_nCoinType, nType);
		
		if (nType == (int)E_TRADE::E_BUY) { nPlayerMoney += nTradeMoney; }
		else { fPlayerCoin += fCoinNum; }
	}
	else
	{
		if (nType == (int)E_TRADE::E_BUY)
		{ 
			pPlayer->setBuyMoney(pPlayer->getBuyMoney(m_nCoinType) + abs(nTradeMoney), m_nCoinType);
		}
		else
		{
			long long nRemoveMoney(0);

			nRemoveMoney = (long long)(pPlayer->getAvgPrice(m_nCoinType) * fCoinNum);

			pPlayer->setBuyMoney(pPlayer->getBuyMoney(m_nCoinType) - nRemoveMoney, m_nCoinType);
		}

		nPlayerMoney += nTradeMoney; 
		fPlayerCoin += fCoinNum;
	}

	pPlayer->setPlayerCoin(m_nCoinType, fPlayerCoin);
	pPlayer->setPlayerMoney(nPlayerMoney);
	pPlayer->updateAnotherInfo(m_nCoinType);

	updateInfo();
}

void C_Appoint_Trade::setBoxEnabled(E_BOX_TYPE eType, const bool isEnabled)
{
	m_arValueBox[(int)eType]->setEnabledEvent(isEnabled);
}

void C_Appoint_Trade::setAllEnabled(const bool isEnabled)
{
	for (int nBox((int)E_BOX_TYPE::E_BUY_PRICE); nBox < (int)E_BOX_TYPE::E_MAX; nBox++)
	{
		m_arValueBox[nBox]->setEnabledEvent(isEnabled);
	}

	m_pEvent->setEnabled(isEnabled);
	m_pMainLayer->setVisible(isEnabled);
}

void C_Appoint_Trade::setEnabledNowPrice(const bool isEnabled)
{
	C_Coin* pCoin(nullptr);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	if (isEnabled)
	{
		m_arValueBox[(int)E_BOX_TYPE::E_BUY_PRICE]->setNumber(pCoin->getPrice());
		m_arValueBox[(int)E_BOX_TYPE::E_SELL_PRICE]->setNumber(pCoin->getPrice());
		m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->setNumber(0.0f);
		m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->setNumber(0.0f);
	}
	else
	{
		for (int nList((int)E_TRADE::E_BUY); nList < (int)E_TRADE::E_MAX; nList++)
		{
			for (int nBox((int)E_TRADE::E_BUY); nBox < (int)E_TRADE::E_MAX; nBox++)
			{
				m_arValueBox[nList * nBox]->setNumber(0.0f);
			}

			m_arPriceNum[nList] = 0.0;
			m_arCoinNum[nList] = 0.0;
			m_arPrice[nList] = 0;

			m_arPriceLab[nList]->setString(u8"0원");
		}
	}

	m_isNowPrice = isEnabled;
}

void C_Appoint_Trade::init()
{
	m_pBackGround	= nullptr;
	m_pPlayerMoney	= nullptr;
	m_pHoldCoinNum	= nullptr;
	m_pMainLayer	= nullptr;
	m_pEvent		= nullptr;
	m_fPosBorder	= 0.0f;
	m_isNowPrice = false;
}

void C_Appoint_Trade::mainBoard()
{
	createLabel();
	createLayer();
	createValueBox();
	createSprite();
	createRectList();
	createTouchEvent();

	presetItemsOption();
	presetFuncList();
	presetRectList();
	presetBorder();

	addChildItem();
}

void C_Appoint_Trade::createSprite()
{
	m_pBackGround = C_Sprite_Management::createSprite("UI_Items/", "Trade_Limit", "Appoint_Trade_BG");

	m_pBackGround->setVisible(true);
}

void C_Appoint_Trade::createLabel()
{
	m_pPlayerMoney = Label::createWithBMFont("BMFonts/NotoSansKR_SemiLight_25px.fnt", "0");
	m_pHoldCoinNum = Label::createWithBMFont("BMFonts/NotoSansKR_SemiLight_25px.fnt", "0");
	m_arPriceLab[(int)E_TRADE::E_BUY] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", u8"0원");
	m_arPriceLab[(int)E_TRADE::E_SELL] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", u8"0원");
}

void C_Appoint_Trade::createLayer()
{
	m_pMainLayer = C_Layer_Management::createLayer("Appoint_Trade_Main");
}

void C_Appoint_Trade::createValueBox()
{
	for (int nBox((int)E_BOX_TYPE::E_BUY_PRICE); nBox < (int)E_BOX_TYPE::E_MAX; nBox++)
	{
		m_arValueBox[nBox] = C_Value_Box::create(Size(50.0f, 45.0f), 160.0f, 2.0f);
	}
}

void C_Appoint_Trade::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_Appoint_Trade::touchOnBegan, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_Appoint_Trade::touchOnEnded, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_Appoint_Trade::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_Appoint_Trade::touchOnCanceled, this);

	m_pEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_Appoint_Trade::createRectList()
{
	m_arEventArea[(int)E_TRADE_BUTTON::E_SET]   = new(std::nothrow) Rect[(int)E_VALUE_PAD::E_MAX]{};
	m_arEventArea[(int)E_TRADE_BUTTON::E_TRADE] = new(std::nothrow) Rect[(int)E_TRADE::E_MAX]{};
}

void C_Appoint_Trade::presetRectList()
{
	float fWidth(0.0f);
	float fHeight(0.0f);
	float fBasedXpos(0.0f);
	float fBasedYpos(0.0f);
	float fXpos(0.0f);
	Rect* pTradeButton(nullptr);
	Rect* pSetButton(nullptr);

	fWidth  = 57.5f;
	fHeight = 30.0f;

	fBasedXpos = 5.0f;
	fBasedYpos = 210.0f;

	fXpos = fBasedXpos;

	for (int nRect((int)E_VALUE_PAD::E_NONE + 1); nRect < (int)E_VALUE_PAD::E_MAX; nRect++)
	{
		pTradeButton = &m_arEventArea[(int)E_TRADE_BUTTON::E_SET][nRect];

		*pTradeButton = Rect(fXpos, fBasedYpos, fWidth, fHeight);

		fXpos = pTradeButton->getMaxX() + 10.0f;
	}
	
	pSetButton  = &m_arEventArea[(int)E_TRADE_BUTTON::E_TRADE][(int)E_TRADE::E_BUY];

	*pSetButton = Rect(fBasedXpos, 105.0f, 260.0f, 50.0f);

	fWidth = pSetButton->getMaxX();

	pSetButton  = &m_arEventArea[(int)E_TRADE_BUTTON::E_TRADE][(int)E_TRADE::E_SELL];

	*pSetButton = Rect(fWidth + 10.0f, 105.0f, 260.0f, 50.0f);
}

void C_Appoint_Trade::presetBorder()
{
	m_fPosBorder = 155.0f;
}

void C_Appoint_Trade::presetFuncList()
{
	for (int nFunc((int)E_VALUE_PAD::E_NONE + 1); nFunc < (int)E_VALUE_PAD::E_MAX; nFunc++)
	{
		m_arSetupFunc[nFunc] = &C_Appoint_Trade::setTradeValues;
	}
	
	m_arTradeFunc[(int)E_TRADE::E_BUY]  = &C_Appoint_Trade::callTradeWindow;
	m_arTradeFunc[(int)E_TRADE::E_SELL] = &C_Appoint_Trade::callTradeWindow;
}

void C_Appoint_Trade::updateInfo()
{
	C_Player_Management* pPlayer(nullptr);
	std::string strMoneyText("");
	std::string strCoinText("");
	std::string strGetMoney("");
	std::string strGetCoin("");

	pPlayer = C_Player_Management::getInstance();

	strGetMoney  = std::to_string(pPlayer->getPlayerMoney());
	strGetCoin	 = std::to_string(pPlayer->getPlayerCoin(m_nCoinType));
	strMoneyText = u8"현재잔액 : " + strGetMoney;
	
	strCoinText += S_KeyStore::arUseSubName[m_nCoinType];
	strCoinText += u8" : ";
	strCoinText += strGetCoin;

	m_pPlayerMoney->setString(strMoneyText);
	m_pHoldCoinNum->setString(strCoinText);
}

void C_Appoint_Trade::presetItemsOption()
{
	m_pBackGround->setPosition(270.0f, 235.0f);
	m_pPlayerMoney->setPosition(260.0f, 355.5f);
	m_pHoldCoinNum->setPosition(m_pPlayerMoney->getPosition() + Point(270.0f, 0.0f));
	m_arPriceLab[(int)E_TRADE::E_BUY]->setPosition(240.5f, 182.5f);
	m_arPriceLab[(int)E_TRADE::E_SELL]->setPosition(m_arPriceLab[1]->getPosition() + Point(270.0f, 0.0f));
	
	m_arValueBox[(int)E_BOX_TYPE::E_BUY_PRICE]->setPosition(5.0f, 295.0f);
	m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->setPosition(5.0f, 245.0f);
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_PRICE]->setPosition(275.0f, 295.0f);
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->setPosition(275.0f, 245.0f);
	
	m_arValueBox[(int)E_BOX_TYPE::E_BUY_PRICE]->setTrader((int)E_TRADE::E_BUY);
	m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->setTrader((int)E_TRADE::E_BUY);
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_PRICE]->setTrader((int)E_TRADE::E_SELL);
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->setTrader((int)E_TRADE::E_SELL);

	m_arValueBox[(int)E_BOX_TYPE::E_BUY_PRICE]->setTail(u8"원");
	m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->setTail(u8"개");
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_PRICE]->setTail(u8"원");
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->setTail(u8"개");

	m_pBackGround->setScale(0.5f);
	m_arPriceLab[(int)E_TRADE::E_BUY]->setScaleX(0.5f);
	m_arPriceLab[(int)E_TRADE::E_SELL]->setScaleX(0.5f);
	m_arPriceLab[(int)E_TRADE::E_BUY]->setScaleY(0.6f);
	m_arPriceLab[(int)E_TRADE::E_SELL]->setScaleY(0.6f);

	m_pPlayerMoney->setAnchorPoint(Point(1.0f, 0.5f));
	m_pHoldCoinNum->setAnchorPoint(Point(1.0f, 0.5f));
	m_arPriceLab[(int)E_TRADE::E_BUY]->setAnchorPoint(Point(1.0f, 0.5f));
	m_arPriceLab[(int)E_TRADE::E_SELL]->setAnchorPoint(Point(1.0f, 0.5f));

	m_arPriceLab[(int)E_TRADE::E_BUY]->setColor(Color3B(240, 56, 56));
	m_arPriceLab[(int)E_TRADE::E_SELL]->setColor(Color3B(240, 56, 56));
}

void C_Appoint_Trade::addChildItem()
{
	m_pMainLayer->addChild(m_pBackGround);
	m_pMainLayer->addChild(m_pPlayerMoney);
	m_pMainLayer->addChild(m_pHoldCoinNum);
	m_pMainLayer->addChild(m_arPriceLab[(int)E_TRADE::E_BUY]);
	m_pMainLayer->addChild(m_arPriceLab[(int)E_TRADE::E_SELL]);

	for (int nBox((int)E_BOX_TYPE::E_BUY_PRICE); nBox < (int)E_BOX_TYPE::E_MAX; nBox++)
	{
		m_pMainLayer->addChild(m_arValueBox[nBox]->getLayer());
	}
}

bool C_Appoint_Trade::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouch(Vec2::ZERO);
	Rect* pRect(nullptr);

	vecTouch = pTouch->getLocation();

	if (vecTouch.y < m_fPosBorder)
	{
		for (int nListNum((int)E_TRADE::E_BUY); nListNum < (int)E_TRADE::E_MAX; nListNum++)
		{
			pRect = &m_arEventArea[(int)E_TRADE_BUTTON::E_TRADE][nListNum];

			if (pRect->containsPoint(vecTouch))
			{
				(this->*m_arTradeFunc[nListNum])(nListNum);

				return true;
			}
		}
	}
	else
	{
		for (int nListNum((int)E_VALUE_PAD::E_NONE + 1); nListNum < (int)E_VALUE_PAD::E_MAX; nListNum++)
		{
			pRect = &m_arEventArea[(int)E_TRADE_BUTTON::E_SET][nListNum];

			if (pRect->containsPoint(vecTouch))
			{
				(this->*m_arSetupFunc[nListNum])(nListNum);

				return true;
			}
		}
	}

	return false;
}

bool C_Appoint_Trade::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return true;
}

bool C_Appoint_Trade::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Appoint_Trade::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

void C_Appoint_Trade::callTradeWindow(const int nType)
{
	C_Window_Management* pManager(nullptr);
	C_Player_Management* pPlayer(nullptr);
	std::string strTradeInfo("");
	std::string strSubTitle("");
	std::string strTitle("");

	pPlayer  = C_Player_Management::getInstance();
	pManager = C_Window_Management::getInstance();

	if (m_arPriceNum[nType] == 0 || m_arCoinNum[nType] == 0)
	{
		strTitle	= u8"입력 사항 중 '0' 값이 있습니다.";
		strSubTitle = u8"0값은 포함될 수 없습니다.";

		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, strTitle, strSubTitle);
		
		return;
	}

	if ((pPlayer->getPlayerMoney() < m_arPrice[nType + 1]) && (nType + 1 == (int)E_TRADE::E_BUY))
	{
		strTitle	= u8"잔액이 부족합니다.";
		strSubTitle = u8"잔액을 확인하세요.";

		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, strTitle, strSubTitle);

		return;
	}
	else if ((pPlayer->getPlayerCoin(m_nCoinType) < m_arCoinNum[nType + 1]) && (nType + 1 == (int)E_TRADE::E_SELL))
	{
		strTitle	= u8"코인이 부족합니다.";
		strSubTitle = u8"남은 개수를 확인하세요.";

		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, strTitle, strSubTitle);

		return;
	}

	if (nType == (int)E_TRADE::E_BUY)
	{
		strTradeInfo += S_KeyStore::arUseCoinName[m_nCoinType];
		strTradeInfo += " ";
		strTradeInfo += std::to_string(m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->getValue());
		strTradeInfo += u8"개를 개당";
		strTradeInfo += std::to_string((int)m_arPriceNum[nType]);
		strTradeInfo += u8"원에 구입합니다.";
	}
	else
	{
		strTradeInfo += S_KeyStore::arUseCoinName[m_nCoinType];
		strTradeInfo += " ";
		strTradeInfo += std::to_string(m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->getValue());
		strTradeInfo += u8"개를 개당";
		strTradeInfo += std::to_string((int)m_arPriceNum[nType]);
		strTradeInfo += u8"원에 판매합니다.";
	}

	pManager->setEnabledWindow(E_WINDOW::E_SELECT, u8"아래 내용으로 거래가 됩니다.", strTradeInfo);
	pManager->setEnabledTrade(E_WINDOW::E_SELECT, true, nType);
}

void C_Appoint_Trade::setTradeValues(const int nType)
{
	C_Window_Management* pManager(nullptr);
	C_Player_Management* pPlayer(nullptr);
	int nCheck(0);

	nCheck = (nType / 4) + 1;
	pManager = C_Window_Management::getInstance();
	pPlayer  = C_Player_Management::getInstance();

	if (m_arPriceNum[nCheck] == 0)
	{
		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, u8"가격을 설정하세요.", "");

		return;
	}

	if (nType < 4)
	{
		for (int nList(0); nList < 4; nList++)
		{
			if (nType == nList)
			{
				long double dlCount(0.0);

				dlCount = (float)pPlayer->getPlayerMoney() / m_arPriceNum[nCheck];

				dlCount *= (0.25 * ((double)nList + 1.0));

				m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->setNumber(dlCount);

				m_arCoinNum[nCheck] = dlCount;
			}
		}
	}
	else
	{
		for (int nList(4); nList < 8; nList++)
		{
			if (nType == nList)
			{
				long double dlCount(0.0);

				dlCount = pPlayer->getPlayerCoin(m_nCoinType);

				dlCount *= (0.25 * ((double)nList - 3.0f));

				m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->setNumber(dlCount);

				m_arCoinNum[nCheck] = dlCount;
			}
		}
	}
}
