#include "C_Message_Management.h"
#include "C_CoinManagement.h"
#include "C_PlayerManagement.h"
#include "AppointTrade.h"
#include "Korean_UTF8.h"
#include "C_Stand_Line.h"
#include "ShareKey.h"
#include <ctime>

C_StandLine * C_StandLine::create()
{
	C_StandLine* pLine(nullptr);

	pLine = new(std::nothrow) C_StandLine();
	
	pLine->init();
	pLine->mainBoard();

	return pLine;
}

void C_StandLine::setEnabled(const bool isEnabled)
{
	m_pEvent->setEnabled(isEnabled);
	m_pMainLayer->setVisible(isEnabled);
}

void C_StandLine::setOrderOption(const int nPrice, const double dlCount, const int nType, const int nCoinType)
{
	std::string strTime("");

	m_nOrderPrice	= nPrice;
	m_dlOrderCount	= dlCount;
	m_nCoinType		= nCoinType;
	m_nOrderType	= nType;

	if (nType == (int)E_TRADE::E_BUY)
	{
		m_pOrderType->setColor(Color3B(55, 212, 0));
		m_pOrderType->setString(UTF8("매수"));
	}
	else if(nType == (int)E_TRADE::E_SELL)
	{
		m_pOrderType->setColor(Color3B(225, 26, 69));
		m_pOrderType->setString(UTF8("매도"));
	}

	loadDayData();

	strTime = getDayData();

	m_pOrderTime->setString(strTime);
	m_pOrderPrice->setString(std::to_string(nPrice));
	m_pOrderValue->setString(std::to_string(dlCount));

	callOrderEvent();
}

void C_StandLine::init()
{
	m_pEvent		= nullptr;
	m_pCancel		= nullptr;
	m_pMainLayer	= nullptr;
	m_pOrderPrice	= nullptr;
	m_pOrderTime	= nullptr;
	m_pOrderType	= nullptr;
	m_pOrderValue	= nullptr;
	m_nCoinType		= 0;
	m_nOrderType	= 0;
	m_nOrderPrice	= 0;
	m_dlOrderCount	= 0.0;
}

void C_StandLine::mainBoard()
{
	createLayer();
	createSprite();
	createLabel();
	createTouchEvent();

	presetPosition();
	presetScale();

	addChildItem();

	resetValue();

	setEnabled(false);
}

void C_StandLine::loadDayData()
{
	time_t timeTest(time(nullptr));

	tm tmNowTime;

	localtime_s(&tmNowTime, &timeTest);

	m_nMonth = tmNowTime.tm_mon + 1;
	m_nDay = tmNowTime.tm_mday;
	m_nHour = tmNowTime.tm_hour;
	m_nMin = tmNowTime.tm_min;
}

void C_StandLine::createLayer()
{
	m_pMainLayer = Layer::create();
}

void C_StandLine::createSprite()
{
	m_pCancel = Sprite::create("UI_Items/Cancel_Button.png");
}

void C_StandLine::createLabel()
{
	m_pOrderPrice = Label::createWithBMFont("BMFonts/NotoSansKR_Regular_30px.fnt", "");
	m_pOrderValue = Label::createWithBMFont("BMFonts/NotoSansKR_Regular_30px.fnt", "");
	m_pOrderTime  = Label::createWithBMFont("BMFonts/NotoSansKR_Regular_30px.fnt", "");
	m_pOrderType  = Label::createWithBMFont("BMFonts/NotoSansKR_Regular_30px.fnt", "");
}

void C_StandLine::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_StandLine::touchOnBegan, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_StandLine::touchOnEnded, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_StandLine::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_StandLine::touchOnCanceled, this);

	m_pEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_StandLine::callOrderEvent()
{
	CallFunc* pFunc(nullptr);
	DelayTime* pDelay(nullptr);
	Sequence* pSeq(nullptr);
	Repeat* pRepeat(nullptr);

	pFunc = CallFunc::create(CC_CALLBACK_0(C_StandLine::checkOrder, this));
	pDelay = DelayTime::create(0.1f);
	pSeq = Sequence::create(pFunc, pDelay, nullptr);
	pRepeat = Repeat::create(pSeq, -1);

	m_pMainLayer->runAction(pRepeat);
}

void C_StandLine::presetPosition()
{
	m_pOrderTime->setPosition(32.5f, 0.0f);
	m_pOrderType->setPosition(m_pOrderTime->getPositionX() + 80.0f, 0.0f);
	m_pOrderPrice->setPosition(m_pOrderType->getPositionX() + 115.25f, 0.0f);
	m_pOrderValue->setPosition(m_pOrderPrice->getPositionX() + 165.0f, 0.0f);

	m_pCancel->setPosition(m_pOrderValue->getPositionX() + 107.25f, 0.0f);
}

void C_StandLine::presetScale()
{
	m_pOrderTime->setScale(0.7f);
	m_pOrderType->setScale(0.7f);
	m_pOrderPrice->setScale(0.7f);
	m_pOrderValue->setScale(0.7f);
	m_pCancel->setScale(0.5f);
}

std::string C_StandLine::getDayData()
{
	int arData[4]{m_nMonth, m_nDay, m_nHour, m_nMin};
	char arSymbol[4]{ '.', ' ', ':', ' ' };
	std::string strResult("");

	for (int nText(0); nText < 4; nText++)
	{
		if (arData[nText] < 10)
		{
			strResult += '0';
		}
		
		strResult += std::to_string(arData[nText]);
		strResult += arSymbol[nText];
	}

	strResult.pop_back();

	return strResult;
}

void C_StandLine::addChildItem()
{
	m_pMainLayer->addChild(m_pCancel);
	m_pMainLayer->addChild(m_pOrderPrice);
	m_pMainLayer->addChild(m_pOrderValue);
	m_pMainLayer->addChild(m_pOrderTime);
	m_pMainLayer->addChild(m_pOrderType);
}

void C_StandLine::resetValue()
{
	m_nCoinType = 0;
	m_nOrderPrice = 0;
	m_nOrderType = 0;
	m_dlOrderCount = 0.0;

	m_pMainLayer->stopAllActions();
}

bool C_StandLine::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Rect recEvent(Rect::ZERO);
	Vec2 vecTouch(Vec2::ZERO);
	float fXpos(0.0f);
	float fYpos(0.0f);
	float fWidth(0.0f);
	float fHeight(0.0f);

	fXpos   = m_pCancel->getBoundingBox().getMinX() + m_pMainLayer->getPositionX();
	fYpos   = m_pCancel->getBoundingBox().getMinY() + m_pMainLayer->getPositionY();
	fWidth  = m_pCancel->getBoundingBox().size.width;
	fHeight = m_pCancel->getBoundingBox().size.height;

	recEvent = Rect(fXpos, fYpos, fWidth, fHeight);
	vecTouch = pTouch->getLocation();

	if (recEvent.containsPoint(vecTouch))
	{
		C_Player_Management* pPlayer(nullptr);

		pPlayer = C_Player_Management::getInstance();

		if (m_nOrderType == (int)E_TRADE::E_BUY)
		{
			pPlayer->setPlayerMoney(pPlayer->getPlayerMoney() + (m_nOrderPrice * m_dlOrderCount));
		}
		else
		{
			pPlayer->setPlayerCoin(m_nCoinType, pPlayer->getPlayerMoney() + m_dlOrderCount);
		}

		C_Appoint_Trade::getInstance()->updatePrice(m_nOrderType);

		resetValue();
		setEnabled(false);

		return true;
	}

	return false;
}

void C_StandLine::checkOrder()
{
	C_Player_Management* pPlayer(nullptr);
	C_Coin* pCoin(nullptr);
	std::string strSubTitle("");
	std::string strTitle("");
	long long int nTradePrice(0);
	int nPrice(0);

	pCoin  = C_CoinManagement::getInstance()->getCoin(m_nCoinType);
	nPrice = pCoin->getPrice();

	if (m_nOrderPrice >= nPrice)
	{
		pPlayer = C_Player_Management::getInstance();

		strTitle += S_KeyStore::arUseCoinName[m_nCoinType] + "의 거래가 완료 되었습니다.";
		strSubTitle += S_KeyStore::arUseSubName[m_nCoinType] + std::to_string(m_dlOrderCount) + "개";

		if (m_nOrderType == (int)E_TRADE::E_BUY)
		{
			double dlTradeCoin(0);

			dlTradeCoin = pPlayer->getPlayerCoin(m_nCoinType) + m_dlOrderCount;
			nTradePrice = (long long int)((double)m_nOrderPrice * m_dlOrderCount);

			pPlayer->setPlayerCoin(m_nCoinType, dlTradeCoin);
			pPlayer->setBuyMoney(pPlayer->getBuyMoney(m_nCoinType) + nTradePrice, m_nCoinType);

			strSubTitle += "구매 완료";
		}
		else
		{
			long long int nTradeMoney(0);

			nTradeMoney = (long long int)(m_dlOrderCount * m_nOrderPrice);
			nTradePrice = (long long int)-((double)m_nOrderPrice * m_dlOrderCount);

			long long llRemoveMoney(0);

			llRemoveMoney = pPlayer->getAvgPrice(m_nCoinType) * m_dlOrderCount;

			pPlayer->setBuyMoney(pPlayer->getBuyMoney(m_nCoinType) - llRemoveMoney, m_nCoinType);

			pPlayer->setPlayerMoney(pPlayer->getPlayerMoney() + nTradeMoney);

			strSubTitle += "판매 완료";
		}

		pPlayer->updateAnotherInfo(m_nCoinType);

		C_Window_Management::getInstance()->setEnabledWindow(E_WINDOW::E_ONLY_OK, UTF8(strTitle), UTF8(strSubTitle));

		resetValue();

		setEnabled(false);
	}
}
