#include "C_Market_Menu.h"
#include "Layer_Management.h"
#include "Scene_Manager.h"
#include "Sprite_Management.h"
#include "C_Message_Management.h"
#include "Korean_UTF8.h"
#include "EventManager.h"
#include "Body_Management.h"
#include "BottomMenuManager.h"
#include "C_Trade_Menu.h"
#include "ShareKey.h"

C_Market_Management* C_Market_Management::m_pMyPointer = nullptr;

C_Market_Management * C_Market_Management::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Market_Management();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Market_Management::setEventEnabled(bool isEnabled)
{
	m_pTouchEvent->setEnabled(isEnabled);
}

void C_Market_Management::init()
{
	m_pMainLayer = nullptr;
	m_pChartLayer = nullptr;
	m_arCoinBorderYpos[0] = 0.0f;
	m_arCoinBorderYpos[1] = 0.0f;
	m_fMovePoint = 0.0f;
	m_fNowTouched = 0.0f;
	m_fPastYpos = 0.0f;
	m_isScroll = false;
}

void C_Market_Management::mainBoard()
{
	createMarketLine();
	createMarketLayer();
	presetLinesOption();
	presetLayerList();
	presetCoinEndPos();
	presetMenuButtonPos();
	createTouchEvent();
}

void C_Market_Management::createMarketLine()
{
	for (int nLineNum((int)E_COIN::E_STANDARD); nLineNum < (int)E_COIN::E_MAX; nLineNum++)
	{
		m_arCoinLine[nLineNum]		= C_Market_Line::create(nLineNum);
		m_arCoinPatcher[nLineNum]	= C_Coin_Patcher::create(nLineNum);
	}
}

void C_Market_Management::createMarketLayer()
{
	m_pMainLayer   = C_Layer_Management::createLayer("Market_Main_Layer");
	m_pChartLayer  = C_Layer_Management::createLayer("Chart_Layer");
}

void C_Market_Management::presetLinesOption()
{
	for (int nLineNum((int)E_COIN::E_STANDARD); nLineNum < (int)E_COIN::E_MAX; nLineNum++)
	{
		float fYpos(0.0f);
		Layer* pLayer(nullptr);

		pLayer = m_arCoinLine[nLineNum]->getMyLayer();

		fYpos = 333.5f - ((float)(nLineNum) * 75.0f);

		pLayer->setPosition(-270.0f, fYpos);
	}
}

void C_Market_Management::presetLayerList()
{
	for (int nLayerNum((int)E_COIN::E_STANDARD); nLayerNum < (int)E_COIN::E_MAX; nLayerNum++)
	{
		m_arLineLayer[nLayerNum] = m_arCoinLine[nLayerNum]->getMyLayer();

		m_pChartLayer->addChild(m_arLineLayer[nLayerNum]);
	}

	m_pMainLayer->addChild(m_pChartLayer);
}

void C_Market_Management::presetCoinEndPos()
{
	m_arCoinBorderYpos[0] = m_pChartLayer->getPositionY() + 53.0f;
	m_arCoinBorderYpos[1] = 0.0f;
}

void C_Market_Management::presetMenuButtonPos()
{
	for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
	{
		m_arMenuPosList[nList] = 855.0f - (75.0f * nList);
	}
}

void C_Market_Management::callTradeWindow()
{
	std::string strMenu("");

	if (m_fMovePoint == 0.0f)
	{
		for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
		{
			strMenu = "Touched Menu";

			CCLOG(strMenu.c_str());
		}
	}
}

void C_Market_Management::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_Market_Management::touchOnBegan, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_Market_Management::touchOnEnded, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_Market_Management::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_Market_Management::touchOnCanceled, this);

	m_pTouchEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

bool C_Market_Management::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	float fTouchYpos(0.0f);
	std::string strTouchPos("");

	fTouchYpos = pTouch->getLocation().y;

	if (fTouchYpos >= 160.0f && fTouchYpos <= 855.0f)
	{
		m_fPastYpos	  = fTouchYpos;
		m_fNowTouched = 0.0f;
		m_fMovePoint  = 0.0f;

		strTouchPos = "Pos : " + std::to_string(fTouchYpos) + " Touch";
		
		CCLOG(strTouchPos.c_str());
	}

	return true;
}

bool C_Market_Management::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	CCLOG("callCancel");
	return false;
}

bool C_Market_Management::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	std::string strTouchPos("");
	 
	m_fNowTouched = pTouch->getLocation().y;

	callTradeWindow();

	if (m_fNowTouched >= 160.0f && m_fNowTouched <= 855.0f)
	{
		if ((m_fNowTouched > m_fPastYpos) && m_pChartLayer->getPositionY() < 53.0f)
		{
			strTouchPos = "Up!" + std::to_string(m_pChartLayer->getPositionY());

			CCLOG(strTouchPos.c_str());

			m_fMovePoint = m_fNowTouched - m_fPastYpos;
			m_pChartLayer->setPositionY(m_pChartLayer->getPosition().y + m_fMovePoint);
		}
		else if ((m_fNowTouched < m_fPastYpos) && m_pChartLayer->getPositionY() > 0.0f)
		{
			strTouchPos = "Down!" + std::to_string(m_pChartLayer->getPositionY());

			CCLOG(strTouchPos.c_str());

			m_fMovePoint = m_fPastYpos - m_fNowTouched;

			m_pChartLayer->setPositionY(m_pChartLayer->getPosition().y - m_fMovePoint);
		}

		m_fPastYpos = m_fNowTouched;
	}

	return true;
}

bool C_Market_Management::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	MoveTo* pMoveAct(nullptr);
	std::string strTouchPos("");
	float fNowTouched(0.0f);

	m_fNowTouched = pTouch->getLocation().y;
	if (m_fNowTouched >= 160.0f && m_fNowTouched <= 855.0f)
	{
		if (m_fMovePoint == 0.0f)
		{
			for (int nList((int)E_COIN::E_STANDARD); nList < (int)E_COIN::E_MAX; nList++)
			{
				fNowTouched = m_fNowTouched - m_pChartLayer->getPositionY();

				if (fNowTouched > m_arMenuPosList[nList])
				{
					strTouchPos = "Touched" + std::to_string(nList) + "Menu";

					setEventEnabled(false);

					C_MainBottom_Menu::getInstance()->setEnabled(false);

					C_Trade_Menu::getInstance()->setEnabled(true, nList);

					CCLOG(strTouchPos.c_str());

					return true;
				}
			}
		}

		float fYLength(0.0f);

		if (m_pChartLayer->getPositionY() > m_arCoinBorderYpos[0])
		{
			pMoveAct = MoveTo::create(0.1f, Vec2(0.0f, m_arCoinBorderYpos[0]));

			m_pChartLayer->runAction(pMoveAct);

			CCLOG(std::to_string(m_pChartLayer->getPositionY()).c_str());
		}
		else if (m_pChartLayer->getPositionY() < m_arCoinBorderYpos[1])
		{
			pMoveAct = MoveTo::create(0.1f, Vec2(0.0f, 0.0f));

			m_pChartLayer->runAction(pMoveAct);

			CCLOG(std::to_string(m_pChartLayer->getPositionY()).c_str());
		}
	}

	return true;
}