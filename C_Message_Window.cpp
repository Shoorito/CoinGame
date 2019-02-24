#include "C_Message_Window.h"
#include "AppointTrade.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "C_Calculator.h"
#include "Korean_UTF8.h"

C_Message_Window * C_Message_Window::create()
{
	C_Message_Window* pWindow(nullptr);

	pWindow = new(std::nothrow) C_Message_Window();

	pWindow->init();
	pWindow->mainBoard();
	
	return pWindow;
}

void C_Message_Window::init()
{
	m_pMainLayer  = nullptr;
	m_pPastTarget = nullptr;
	m_pTitle	  = nullptr;
	m_pSubTitle	  = nullptr;
	m_nType		  = 0;
	m_strTitle	  = "";
	m_strSubTitle = "";
}

void C_Message_Window::mainBoard()
{
	createSprite();
	createLabel();
	createLayer();
	createTouchEvent();

	presetPastImage();
	presetPosition();
	presetScale();
	presetRectList();
	presetFuncList();

	addChildList();
}

void C_Message_Window::createSprite()
{
	for (int nImage((int)E_WINDOW::E_ONLY_OK); nImage < (int)E_WINDOW::E_MAX; nImage++)
	{
		std::string strName("");
		std::string strTag("");

		strName = "Message_Type_0" + std::to_string(nImage);
		strTag  = "Window_Type_0" + std::to_string(nImage);

		m_arWindow[nImage] = C_Sprite_Management::createSprite("UI_Items/", strName, strTag);
	}
}

void C_Message_Window::createLabel()
{
	m_pTitle	= Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pSubTitle	= Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
}

void C_Message_Window::createLayer()
{
	m_pMainLayer = Layer::create();
}

void C_Message_Window::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_Message_Window::touchOnBegan, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_Message_Window::touchOnEnded, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_Message_Window::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_Message_Window::touchOnCanceled, this);

	m_pTouchEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

bool C_Message_Window::setWindowType(const int nType)
{
	if (nType < (int)E_WINDOW::E_ONLY_OK || nType > (int)E_WINDOW::E_SELECT)
	{
		CCAssert(false, UTF8("지정된 타입이 아닙니다.").c_str());

		return false;
	}

	m_nType = nType;
	
	m_pPastTarget->setVisible(false);

	m_arWindow[nType]->setVisible(true);

	m_pPastTarget = m_arWindow[nType];
	
	return true;
}

void C_Message_Window::setEnabledWindow(const bool isEnabled)
{
	m_pMainLayer->setVisible(isEnabled);
	m_pTouchEvent->setEnabled(isEnabled);
}

void C_Message_Window::setEnabledTrade(const bool isEnabled, const int nTradeType)
{
	m_isTrade = isEnabled;
	m_nTradeType = nTradeType;
}

void C_Message_Window::setTitle(const std::string & strName)
{
	m_strTitle = strName;

	m_pTitle->setString(m_strTitle);
}

void C_Message_Window::setSubTitle(const std::string & strName)
{
	m_strSubTitle = strName;

	m_pSubTitle->setString(m_strSubTitle);
}

void C_Message_Window::presetPosition()
{
	for (int nList((int)E_WINDOW::E_ONLY_OK); nList < (int)E_WINDOW::E_MAX; nList++)
	{
		m_arWindow[nList]->setPosition(270.0f, 550.0f);
	}

	m_pTitle->setPosition(m_arWindow[(int)E_WINDOW::E_ONLY_OK]->getPosition() + Point(0.0f, 45.0f));
	m_pSubTitle->setPosition(m_arWindow[(int)E_WINDOW::E_ONLY_OK]->getPosition() + Point(0.0f, 10.0f));
}

void C_Message_Window::presetScale()
{
	for (int nList((int)E_WINDOW::E_ONLY_OK); nList < (int)E_WINDOW::E_MAX; nList++)
	{
		m_arWindow[nList]->setScale(0.5f);
	}
	m_pTitle->setScale(0.6f);
	m_pSubTitle->setScale(0.5f);
}

void C_Message_Window::presetPastImage()
{
	m_arWindow[(int)E_WINDOW::E_SELECT]->setVisible(false);

	m_pPastTarget = m_arWindow[(int)E_WINDOW::E_ONLY_OK];

	m_pPastTarget->setVisible(true);
}

void C_Message_Window::presetRectList()
{
	float fTargetXpos(0.0f);
	float fTargetYpos(0.0f);

	fTargetXpos = m_arWindow[(int)E_WINDOW::E_ONLY_OK]->getPositionX() - 50.0f;
	fTargetYpos = m_arWindow[(int)E_WINDOW::E_ONLY_OK]->getPositionY() - 55.0f;

	m_arRectList[(int)E_WINDOW::E_NONE] = Rect(fTargetXpos, fTargetYpos, 100.0f, 50.0f);

	fTargetXpos = m_arWindow[(int)E_WINDOW::E_ONLY_OK]->getPositionX() - 122.5f;

	m_arRectList[(int)E_WINDOW::E_ONLY_OK] = Rect(fTargetXpos, fTargetYpos, 100.0f, 50.0f);
	
	fTargetXpos = m_arWindow[(int)E_WINDOW::E_ONLY_OK]->getPositionX() + 22.5f;

	m_arRectList[(int)E_WINDOW::E_SELECT] = Rect(fTargetXpos, fTargetYpos, 100.0f, 50.0f);
}

void C_Message_Window::presetFuncList()
{
	m_arFuncList[(int)E_WINDOW::E_NONE]		= &C_Message_Window::touchOnConfirmMenu;
	m_arFuncList[(int)E_WINDOW::E_ONLY_OK]	= &C_Message_Window::touchOnConfirmMenu;
	m_arFuncList[(int)E_WINDOW::E_SELECT]	= &C_Message_Window::touchOnCancelMenu;
}

void C_Message_Window::addChildList()
{
	for (int nList((int)E_WINDOW::E_ONLY_OK); nList < (int)E_WINDOW::E_MAX; nList++)
	{
		m_pMainLayer->addChild(m_arWindow[nList]);
	}

	m_pMainLayer->addChild(m_pTitle);
	m_pMainLayer->addChild(m_pSubTitle);
}

bool C_Message_Window::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouch(Vec2::ZERO);

	vecTouch = pTouch->getLocation();

	if (m_nType == (int)E_WINDOW::E_ONLY_OK)
	{
		if (m_arRectList[0].containsPoint(vecTouch))
		{
			(this->*m_arFuncList[0])();

			return true;
		}
	}
	else if (m_nType == (int)E_WINDOW::E_SELECT)
	{
		for (int nListNum((int)E_WINDOW::E_ONLY_OK); nListNum < (int)E_WINDOW::E_MAX; nListNum++)
		{
			if (m_arRectList[nListNum].containsPoint(vecTouch))
			{
				(this->*m_arFuncList[nListNum])();

				return true;
			}
		}
	}

	return false;
}

bool C_Message_Window::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Message_Window::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Message_Window::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

void C_Message_Window::touchOnConfirmMenu()
{
	if (m_nType != (int)E_WINDOW::E_ONLY_OK)
	{
		if (m_isTrade == true)
		{
			C_Appoint_Trade* pTrader(nullptr);

			pTrader = C_Appoint_Trade::getInstance();

			pTrader->tradeCoin(m_nTradeType);

			m_isTrade = false;
			m_nTradeType = 0;
		}
	}

	setEnabledWindow(false);
}

void C_Message_Window::touchOnCancelMenu()
{
	setEnabledWindow(false);
}