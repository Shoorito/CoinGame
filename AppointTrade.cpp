#include "C_Message_Management.h"
#include "C_PlayerManagement.h"
#include "C_CoinManagement.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "C_Stand_Trade.h"
#include "AppointTrade.h"
#include "Korean_UTF8.h"
#include "ShareKey.h"

C_Appoint_Trade* C_Appoint_Trade::m_pMyPointer = nullptr;

C_Appoint_Trade * C_Appoint_Trade::create()
{
	if (m_pMyPointer)
	{
		CCAssert(m_pMyPointer != nullptr , UTF8("지정 트레이더 메뉴 포인터는 이미 생성되어 있습니다.").c_str());
	}

	m_pMyPointer = new(std::nothrow) C_Appoint_Trade();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Appoint_Trade::updatePrice(const int nType)
{
	C_Coin* pCoin(nullptr);
	double dlTradePrice(0.0);
	double dlTradeCount(0.0);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	if (m_isNowPrice)	{ m_arPriceNum[nType] = pCoin->getPrice(); }
	else				{ m_arPriceNum[nType] = m_arValueBox[nType]->getValue(); }

	m_arCoinNum[nType]  = m_arValueBox[(int)nType + 2]->getValue();
	
	dlTradePrice = m_arPriceNum[nType];
	dlTradeCount = m_arCoinNum[nType];

	m_arPrice[nType] = (long long int)((int)dlTradePrice * dlTradeCount);

	m_arPriceLab[nType]->setString(std::to_string(m_arPrice[nType]) + UTF8("원"));

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
	long long int nPlayerMoney(0);
	long long int nTradeMoney(0);
	double dlPlayerCoin(0.0);
	C_Coin* pCoin(nullptr);
	double dlCoinNum(0.0);

	pPlayer = C_Player_Management::getInstance();
	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	nTradeMoney  = m_arPrice[nType] * arSwitch[nType];
	dlCoinNum	 = m_arCoinNum[nType] * -arSwitch[nType];
	nPlayerMoney = pPlayer->getPlayerMoney();
	dlPlayerCoin = pPlayer->getPlayerCoin(m_nCoinType);

	if (m_arPriceNum[nType] != pCoin->getPrice())
	{
		C_Stand_Trade* pTrade(nullptr);

		pTrade = C_Stand_Trade::getInstance();

		pTrade->addList(m_arPriceNum[nType], m_arCoinNum[nType], m_nCoinType, nType);
		
		if (nType == (int)E_TRADE::E_BUY) { nPlayerMoney += nTradeMoney; }
		else { dlPlayerCoin += dlCoinNum; }
	}
	else
	{
		if (nType == (int)E_TRADE::E_BUY)
		{ 
			pPlayer->setBuyMoney(pPlayer->getBuyMoney(m_nCoinType) + abs(nTradeMoney), m_nCoinType);
		}
		else
		{
			long long llRemoveMoney(0);

			llRemoveMoney = pPlayer->getAvgPrice(m_nCoinType) * dlCoinNum;

			pPlayer->setBuyMoney(pPlayer->getBuyMoney(m_nCoinType) - llRemoveMoney, m_nCoinType);
		}

		nPlayerMoney += nTradeMoney; 
		dlPlayerCoin += dlCoinNum;
	}

	pPlayer->setPlayerCoin(m_nCoinType, dlPlayerCoin);
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
		m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->setNumber(0.0);
		m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->setNumber(0.0);
	}
	else
	{
		for (int nList((int)E_TRADE::E_BUY); nList < (int)E_TRADE::E_MAX; nList++)
		{
			for (int nBox((int)E_TRADE::E_BUY); nBox < (int)E_TRADE::E_MAX; nBox++)
			{
				m_arValueBox[nList * nBox]->setNumber(0.0);
			}

			m_arPriceNum[nList] = 0.0;
			m_arCoinNum[nList] = 0.0;
			m_arPrice[nList] = 0;

			m_arPriceLab[nList]->setString("0원");
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
	m_arPriceLab[(int)E_TRADE::E_BUY] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", UTF8("0원"));
	m_arPriceLab[(int)E_TRADE::E_SELL] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", UTF8("0원"));
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
	m_arEventArea[0] = new(std::nothrow) Rect[8]{};
	m_arEventArea[1] = new(std::nothrow) Rect[2]{};
}

void C_Appoint_Trade::presetRectList()
{
	float fWidth(0.0f);
	float fHeight(0.0f);
	float fBasedXpos(0.0f);
	float fBasedYpos(0.0f);
	float fXpos(0.0f);

	fWidth  = 57.5f;
	fHeight = 30.0f;

	fBasedXpos = 5.0f;
	fBasedYpos = 210.0f;

	fXpos = fBasedXpos;

	for (int nRect(0); nRect < 8; nRect++)
	{
		m_arEventArea[0][nRect] = Rect(fXpos, fBasedYpos, fWidth, fHeight);

		fXpos = m_arEventArea[0][nRect].getMaxX() + 10.0f;
	}
	
	m_arEventArea[1][0] = Rect(fBasedXpos, 105.0f, 260.0f, 50.0f);
	m_arEventArea[1][1] = Rect(m_arEventArea[1][0].getMaxX() + 10.0f, 105.0f, 260.0f, 50.0f);
}

void C_Appoint_Trade::presetBorder()
{
	m_fPosBorder = 155.0f;
}

void C_Appoint_Trade::presetFuncList()
{
	for (int nFunc(0); nFunc < 8; nFunc++)
	{
		m_arSetupFunc[nFunc] = &C_Appoint_Trade::setTradeValues;
	}
	
	m_arTradeFunc[0] = &C_Appoint_Trade::callTradeWindow;
	m_arTradeFunc[1] = &C_Appoint_Trade::callTradeWindow;
}

void C_Appoint_Trade::updateInfo()
{
	C_Player_Management* pPlayer(nullptr);
	std::string strMoneyText("");
	std::string strCoinText("");

	pPlayer = C_Player_Management::getInstance();

	strMoneyText = "현재잔액 : " + std::to_string(pPlayer->getPlayerMoney());
	
	strCoinText += S_KeyStore::arUseSubName[m_nCoinType];
	strCoinText += " : ";
	strCoinText += std::to_string(pPlayer->getPlayerCoin(m_nCoinType));

	m_pPlayerMoney->setString(UTF8(strMoneyText));
	m_pHoldCoinNum->setString(UTF8(strCoinText));
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

	m_arValueBox[(int)E_BOX_TYPE::E_BUY_PRICE]->setTail("원");
	m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->setTail("개");
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_PRICE]->setTail("원");
	m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->setTail("개");

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

	vecTouch = pTouch->getLocation();

	if (vecTouch.y <= m_fPosBorder)
	{
		for (int nListNum(0); nListNum < 2; nListNum++)
		{
			if (m_arEventArea[1][nListNum].containsPoint(vecTouch))
			{
				(this->*m_arTradeFunc[nListNum])(nListNum);

				CCLOG(std::to_string(nListNum).c_str());

				return true;
			}
		}
	}
	else
	{
		for (int nListNum(0); nListNum < 8; nListNum++)
		{
			if (m_arEventArea[0][nListNum].containsPoint(vecTouch))
			{
				(this->*m_arSetupFunc[nListNum])(nListNum);

				CCLOG(std::to_string(nListNum).c_str());

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
	C_Player_Management* pPlayer(nullptr);
	C_Window_Management* pManager(nullptr);
	std::string strTradeInfo("");

	pPlayer = C_Player_Management::getInstance();
	pManager = C_Window_Management::getInstance();

	if (m_arPriceNum[nType + 1] == 0 || m_arCoinNum[nType + 1] == 0)
	{
		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, UTF8("입력 사항 중 '0' 값이 있습니다."), UTF8("0값은 포함될 수 없습니다."));
		
		return;
	}

	if ((pPlayer->getPlayerMoney() < m_arPrice[nType + 1]) && (nType + 1 == (int)E_TRADE::E_BUY))
	{
		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, UTF8("잔액이 부족합니다."), UTF8("잔액을 확인하세요."));

		return;
	}
	else if ((pPlayer->getPlayerCoin(m_nCoinType) < m_arCoinNum[nType + 1]) && (nType + 1 == (int)E_TRADE::E_SELL))
	{
		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, UTF8("코인이 부족합니다."), UTF8("남은 개수를 확인하세요."));

		return;
	}

	if (nType == 0)
	{
		strTradeInfo += S_KeyStore::arUseCoinName[m_nCoinType];
		strTradeInfo += " ";
		strTradeInfo += std::to_string(m_arValueBox[(int)E_BOX_TYPE::E_BUY_COUNT]->getValue());
		strTradeInfo += "개를 개당";
		strTradeInfo += std::to_string((int)m_arPriceNum[nType + 1]);
		strTradeInfo += "원에 구입합니다.";
	}
	else
	{
		strTradeInfo += S_KeyStore::arUseCoinName[m_nCoinType];
		strTradeInfo += " ";
		strTradeInfo += std::to_string(m_arValueBox[(int)E_BOX_TYPE::E_SELL_COUNT]->getValue());
		strTradeInfo += "개를 개당";
		strTradeInfo += std::to_string((int)m_arPriceNum[nType + 1]);
		strTradeInfo += "원에 판매합니다.";
	}

	pManager->setEnabledWindow(E_WINDOW::E_SELECT, UTF8("아래 내용으로 거래가 됩니다."), UTF8(strTradeInfo));
	pManager->setEnabledTrade(E_WINDOW::E_SELECT, true, nType + 1);
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
		pManager->setEnabledWindow(E_WINDOW::E_ONLY_OK, UTF8("가격을 설정하세요."), UTF8(""));

		return;
	}

	if (nType < 4)
	{
		for (int nList(0); nList < 4; nList++)
		{
			if (nType == nList)
			{
				long double dlCount(0.0);

				dlCount = (double)(pPlayer->getPlayerMoney()) / m_arPriceNum[nCheck];

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
