#include "ValueBox.h"
#include "C_Calculator.h"
#include "Korean_UTF8.h"
#include "Layer_Management.h"
#include "AppointTrade.h"

C_Value_Box * C_Value_Box::create(Size szButton, const float fTextLength, const float fLineThick)
{
	if (szButton.width < 1.0f || szButton.height < 1.0f || fTextLength < 1.0f || fLineThick < 0.0f)
	{
		CCAssert(false, UTF8("입력한 값이 정해진 값에 비해 작습니다.").c_str());

		return nullptr;
	}

	C_Value_Box* pBox(nullptr);

	pBox = new(std::nothrow) C_Value_Box();
	
	pBox->init();
	pBox->m_fTextBarLength	= fTextLength;
	pBox->m_fBorderThick	= fLineThick;
	pBox->m_szButtonSize	= szButton;
	pBox->mainBoard();

	return pBox;
}

void C_Value_Box::init()
{
	m_szButtonSize		= Size::ZERO;
	m_fTextBarLength	= 0.0f;
	m_fBorderThick		= 0.0f;
	m_fMyValue			= 0.0;
	m_nTradeType		= 0;
	m_strNumber			= "";
	m_strTail			= "";
	m_pTouchEvent		= nullptr;
	m_pMyLayer			= nullptr;
	m_pNumberText		= nullptr;
	m_pBox				= nullptr;
}

void C_Value_Box::mainBoard()
{
	createClippingNode();
	createLabel();
	createLayer();
	createTouchEvent();

	addChildItems();

	presetLabelOption();
	presetLayerOption();
	presetAnchor();
	presetPosition();
	presetRectList();
	presetAddList();
	presetFuncList();
}

void C_Value_Box::setEnabledEvent(const bool isEnabled)
{
	m_pTouchEvent->setEnabled(isEnabled);
	m_pMyLayer->setVisible(isEnabled);
}

void C_Value_Box::setPosition(const float fXpos, const float fYpos)
{
	m_pMyLayer->setPosition(fXpos, fYpos);

	presetRectList();
}

void C_Value_Box::setTrader(const int nType)
{
	m_nTradeType = nType;
}

void C_Value_Box::setTail(const std::string & strTail)
{
	m_strTail = strTail;

	m_pNumberText->setString(UTF8("0" + m_strTail));
}

void C_Value_Box::setNumber(const float fValue)
{
	m_fMyValue = fValue;

	m_strNumber = std::to_string(m_fMyValue);

	m_pNumberText->setString(UTF8(m_strNumber + m_strTail));

	C_Appoint_Trade::getInstance()->updatePrice(m_nTradeType);
}

void C_Value_Box::createLabel()
{
	m_arButtonText[(int)E_EVENT_TYPE::E_DOWN] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", UTF8("◀"));
	m_arButtonText[(int)E_EVENT_TYPE::E_UP] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", UTF8("▶"));
	m_pNumberText = Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "0");
}

void C_Value_Box::createLayer()
{
	Color4B colorPreset(Color4B::WHITE);

	colorPreset = Color4B(76, 84, 98, 255);

	m_pMyLayer  = Layer::create();

	for (int nList((int)E_EVENT_TYPE::E_DOWN); nList < (int)E_EVENT_TYPE::E_MAX - 1; nList++)
	{
		m_arBox[nList]  = LayerColor::create(colorPreset);
		m_arLine[nList] = LayerColor::create(colorPreset);
	}
}

void C_Value_Box::createClippingNode()
{
	Scale9Sprite* pSprite(nullptr);
	Size szClip(Size::ZERO);
	Size szSprite(Size::ZERO);

	szClip   = Size(m_fTextBarLength - 10.0f, m_szButtonSize.height - (m_fBorderThick * 2) - 8);
	szSprite = Size(m_fTextBarLength, m_szButtonSize.height - (m_fBorderThick * 2));

	pSprite = Scale9Sprite::create("UI_Items/Value_Area.png");

	m_pBox = Scale9Sprite::create("UI_Items/Value_Area.png");

	pSprite->setContentSize(szClip);
	m_pBox->setContentSize(szSprite);

	m_pClipNode = ClippingNode::create(pSprite);

	m_pClipNode->setInverted(false);
}

void C_Value_Box::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_Value_Box::touchOnBegan, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_Value_Box::touchOnEnded, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_Value_Box::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_Value_Box::touchOnCanceled, this);

	m_pTouchEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_Value_Box::presetLabelOption()
{
	m_arButtonText[(int)E_EVENT_TYPE::E_DOWN]->setScale(0.6f);
	m_arButtonText[(int)E_EVENT_TYPE::E_UP]->setScale(0.6f);
	m_pNumberText->setScale(0.9f);
}

void C_Value_Box::presetLayerOption()
{
	for (int nList((int)E_EVENT_TYPE::E_DOWN); nList < (int)E_EVENT_TYPE::E_MAX - 1; nList++)
	{
		m_arBox[nList]->setContentSize(m_szButtonSize);
		m_arLine[nList]->setContentSize(Size(m_fTextBarLength, m_fBorderThick));
	}
}

void C_Value_Box::presetPosition()
{
	float fXpos(0.0f);
	float fYpos(0.0f);

	fXpos = ((m_szButtonSize.width * 2.0f) + m_fTextBarLength) / 2.0f;
	fYpos = m_szButtonSize.height / 2.0f;

	m_arBox[(int)E_EVENT_TYPE::E_DOWN]->setPosition(0.0f, 0.0f);
	m_arBox[(int)E_EVENT_TYPE::E_UP]->setPosition(m_szButtonSize.width + m_fTextBarLength, 0.0f);
	m_arLine[(int)E_EVENT_TYPE::E_DOWN]->setPosition(m_szButtonSize.width, 0.0f);
	m_arLine[(int)E_EVENT_TYPE::E_UP]->setPosition(m_szButtonSize.width, m_szButtonSize.height - m_fBorderThick);
	m_arButtonText[(int)E_EVENT_TYPE::E_DOWN]->setPosition(m_szButtonSize / 2.0f);
	m_arButtonText[(int)E_EVENT_TYPE::E_UP]->setPosition(m_szButtonSize / 2.0f);
	
	m_pBox->setPosition(Point(fXpos, fYpos));

	fYpos = (m_szButtonSize.height  - (m_fBorderThick * 2)) / 2.0f;

	m_pClipNode->setPosition(m_fTextBarLength / 2.0f, fYpos);

	m_pNumberText->setPosition((-m_fTextBarLength / 2.0f) + 4.0f, -1.0f);
}

void C_Value_Box::presetRectList()
{
	Rect recTarget(Rect::ZERO);
	float fXpos(0.0f);
	float fYpos(0.0f);
	float fWidth(0.0f);
	float fHeight(0.0f);

	for (int nRect((int)E_EVENT_TYPE::E_DOWN); nRect < (int)E_EVENT_TYPE::E_MAX - 1; nRect++)
	{
		recTarget = m_arBox[nRect]->getBoundingBox();

		fXpos = recTarget.getMinX() + m_pMyLayer->getPositionX();
		fYpos = recTarget.getMinY() + m_pMyLayer->getPositionY();
		fWidth = recTarget.size.width;
		fHeight = recTarget.size.height;

		m_arRectList[nRect] = Rect(fXpos, fYpos, fWidth, fHeight);
	}

	recTarget = m_pBox->getBoundingBox();

	fXpos = recTarget.getMinX() + m_pMyLayer->getPositionX();
	fYpos = recTarget.getMinY() + m_pMyLayer->getPositionY();
	fWidth = recTarget.size.width;
	fHeight = recTarget.size.height;

	m_arRectList[(int)E_EVENT_TYPE::E_SET] = Rect(fXpos, fYpos, fWidth, fHeight);
}

void C_Value_Box::presetAnchor()
{
	m_pNumberText->setAnchorPoint(Point(0.0f, 0.5f));
}

void C_Value_Box::presetAddList()
{
	m_arAddList[(int)E_EVENT_TYPE::E_DOWN]	= -1.0f;
	m_arAddList[(int)E_EVENT_TYPE::E_UP]	= 1.0f;
}

void C_Value_Box::presetFuncList()
{
	m_arFuncList[(int)E_EVENT_TYPE::E_DOWN] = &C_Value_Box::addCount;
	m_arFuncList[(int)E_EVENT_TYPE::E_UP] = &C_Value_Box::addCount;
	m_arFuncList[(int)E_EVENT_TYPE::E_SET] = &C_Value_Box::callCalculator;
}

void C_Value_Box::addChildItems()
{
	for (int nList((int)E_EVENT_TYPE::E_DOWN); nList < (int)E_EVENT_TYPE::E_MAX - 1; nList++)
	{
		m_pMyLayer->addChild(m_arBox[nList]);
		m_pMyLayer->addChild(m_arLine[nList]);
		m_arBox[nList]->addChild(m_arButtonText[nList]);
	}

	m_pBox->addChild(m_pClipNode);
	m_pMyLayer->addChild(m_pBox);
	m_pClipNode->addChild(m_pNumberText);
}

void C_Value_Box::addCount(const int nAdd)
{
	if ((m_fMyValue + m_arAddList[nAdd]) < 0)
	{
		return;
	}

	C_Appoint_Trade* pTrader(nullptr);

	m_fMyValue += m_arAddList[nAdd];

	m_strNumber = std::to_string(m_fMyValue);

	m_pNumberText->setString(m_strNumber + UTF8(m_strTail));

	pTrader = C_Appoint_Trade::getInstance();

	pTrader->updatePrice(m_nTradeType);
}

void C_Value_Box::callCalculator(const int nNoUsed)
{
	C_Calculator* pCalc(nullptr);

	pCalc = C_Calculator::getInstance();
	
	pCalc->setEnabled(true);
	pCalc->setConnect(&m_fMyValue, m_pNumberText, this);

	m_pTouchEvent->setEnabled(false);
}

void C_Value_Box::releaseCalculator()
{
	C_Appoint_Trade* pTrader(nullptr);
	C_Calculator* pCalc(nullptr);

	pCalc = C_Calculator::getInstance();
	pTrader = C_Appoint_Trade::getInstance();

	pTrader->updatePrice(m_nTradeType);

	m_strNumber = std::to_string(m_fMyValue);

	m_pNumberText->setString(m_strNumber + UTF8(m_strTail));

	pCalc->setEnabled(false);
	m_pTouchEvent->setEnabled(true);
}

bool C_Value_Box::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouch(Vec2::ZERO);

	vecTouch = pTouch->getLocation();

	for (int nRect((int)E_EVENT_TYPE::E_DOWN); nRect < (int)E_EVENT_TYPE::E_MAX; nRect++)
	{
		if (m_arRectList[nRect].containsPoint(vecTouch))
		{
			(this->*m_arFuncList[nRect])(nRect);

			return true;
		}
	}

	return true;
}

bool C_Value_Box::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Value_Box::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Value_Box::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}