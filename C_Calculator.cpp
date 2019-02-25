#include "C_Calculator.h"
#include "Layer_Management.h"
#include "Scene_Manager.h"
#include "Korean_UTF8.h"
#include "ValueBox.h"

C_Calculator * C_Calculator::m_pMyPointer = nullptr;

C_Calculator * C_Calculator::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Calculator();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Calculator::init()
{
	m_pPad_BG		 = nullptr;
	m_pMainLayer	 = nullptr;
	m_pResult		 = nullptr;
	m_pTitle		 = nullptr;
	m_pResultWindow  = nullptr;
	m_pTitleName	 = nullptr;
	m_pTouchEvent	 = nullptr;
	m_pTextConnect   = nullptr;
	m_pConnect		 = nullptr;
	m_recTouchBorder = Rect::ZERO;
	m_strResult		 = "0";
	m_fResult		 = 0.0;
	m_nDotPos		 = 0;
	m_isDot			 = false;
}

void C_Calculator::mainBoard()
{
	createLayer();
	createLabel();
	presetAnchor();
	presetSize();
	presetText();
	presetScale();
	presetPosition();
	presetColor();
	presetBorderRect();
	presetFuncList();
	addChildItems();

	createTouchEvent();

	setEnabled(false);
}

void C_Calculator::createLayer()
{
	m_pMainLayer = C_Layer_Management::createColorLayer("Calculator_BG", Color4B(244, 178, 35, 255));
	m_pTitle = C_Layer_Management::createColorLayer("Calculator_Title", Color4B(23, 30, 47, 255));
	m_pResultWindow = C_Layer_Management::createColorLayer("Calculator_Result", Color4B(23, 30, 47, 255));
	m_pPad_BG = C_Layer_Management::createColorLayer("Calculator_PAD", Color4B(23, 30, 47, 255));

	for (int nPad((int)E_PAD::E_PAD_01); nPad < (int)E_PAD::E_MAX; nPad++)
	{
		std::string strName("");

		strName = "Calculator_PAD_" + std::to_string(nPad);

		m_arPadButton[nPad] = C_Layer_Management::createColorLayer(strName, Color4B::WHITE);
	}
}

void C_Calculator::createLabel()
{
	m_pTitleName = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_pResult	 = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");

	for (int nPad((int)E_PAD::E_PAD_01); nPad < (int)E_PAD::E_MAX - 4; nPad++)
	{
		if ((nPad % 4) != 0)
		{
			m_arPadList[nPad] = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");
		}
	}

	m_arPadList[(int)E_PAD::E_PAD_04] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_arPadList[(int)E_PAD::E_PAD_08] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_arPadList[(int)E_PAD::E_PAD_12] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_arPadList[(int)E_PAD::E_PAD_13] = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");
	m_arPadList[(int)E_PAD::E_PAD_14] = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");
	m_arPadList[(int)E_PAD::E_PAD_15] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
	m_arPadList[(int)E_PAD::E_PAD_16] = Label::createWithBMFont("BMFonts/NotoSansKR_Bold_50px.fnt", "");
}

void C_Calculator::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan	  = CC_CALLBACK_2(C_Calculator::touchOnBegan, this);
	pTouchEvent->onTouchEnded	  = CC_CALLBACK_2(C_Calculator::touchOnEnded, this);
	pTouchEvent->onTouchMoved	  = CC_CALLBACK_2(C_Calculator::touchOnMoved, this);
	pTouchEvent->onTouchCancelled = CC_CALLBACK_2(C_Calculator::touchOnCanceled, this);

	m_pTouchEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_Calculator::addChildItems()
{
	m_pMainLayer->addChild(m_pTitle);
	m_pMainLayer->addChild(m_pResultWindow);
	m_pMainLayer->addChild(m_pPad_BG);
	m_pTitle->addChild(m_pTitleName);
	m_pResultWindow->addChild(m_pResult);

	for (int nList((int)E_PAD::E_PAD_01); nList < (int)E_PAD::E_MAX; nList++)
	{
		m_pPad_BG->addChild(m_arPadButton[nList]);
		m_arPadButton[nList]->addChild(m_arPadList[nList]);
	}

	C_Scene_Manager::getInstance()->getScene()->addChild(m_pMainLayer);
}

void C_Calculator::presetPosition()
{
	m_pMainLayer->setPosition(-104.5f + 270.0f, 400.0f);

	m_pTitle->setPosition(2.0f, 265.0f);
	m_pTitleName->setPosition(102.5f, 8.0f);
	m_pResultWindow->setPosition(m_pTitle->getPosition() + Point(0.0f, -56.0f));
	m_pPad_BG->setPosition(m_pResultWindow->getPosition() + Point(0.0f, -207.0f));
	m_pResult->setPosition(200.0f, 27.0f);

	for (int nYpos(1); nYpos < 5; nYpos++)
	{
		for (int nXpos(1); nXpos < 5; nXpos++)
		{
			m_arPadButton[((nYpos - 1) * 4) + nXpos]->setPositionX((1.0f * nXpos) + (50.0f * (nXpos - 1)));
			m_arPadButton[((nYpos - 1) * 4) + nXpos]->setPositionY(204.0f - (1.0f * (nYpos - 1) + 50.0f * nYpos));
		}
	}

	for (int nButton((int)E_PAD::E_PAD_01); nButton < (int)E_PAD::E_MAX; nButton++)
	{
		m_arPadList[nButton]->setPosition(25.0f, 25.0f);
	}
}

void C_Calculator::presetSize()
{
	m_pTitle->setContentSize(Size(205.0f, 16.0f));
	m_pMainLayer->setContentSize(Size(209.0f, 283.0f));
	m_pResultWindow->setContentSize(Size(205.0f, 54.0f));
	m_pPad_BG->setContentSize(Size(205.0f, 205.0f));

	for (int nPad((int)E_PAD::E_PAD_01); nPad < (int)E_PAD::E_MAX; nPad++)
	{
		m_arPadButton[nPad]->setContentSize(Size(50.0f, 50.0f));
	}
}

void C_Calculator::presetAnchor()
{
	m_pResult->setAnchorPoint(Point(1.0f, 0.5f));
}

void C_Calculator::presetScale()
{
	m_pTitleName->setScale(0.45f);
	m_arPadList[(int)E_PAD::E_PAD_04]->setScale(0.6f);
	m_arPadList[(int)E_PAD::E_PAD_08]->setScale(0.6f);
	m_arPadList[(int)E_PAD::E_PAD_12]->setScale(0.5f);
	m_arPadList[(int)E_PAD::E_PAD_15]->setScale(0.5f);
	m_arPadList[(int)E_PAD::E_PAD_16]->setScale(0.5f);
}

void C_Calculator::presetColor()
{
	for (int nList((int)E_PAD::E_PAD_01); nList < (int)E_PAD::E_MAX; nList++)
	{
		m_arPadList[nList]->setColor(Color3B(23, 30, 47));
	}
}

void C_Calculator::presetText()
{
	int nNumber(0);

	nNumber = (int)E_PAD::E_PAD_01;

	for (int nPad((int)E_PAD::E_PAD_01); nPad < (int)E_PAD::E_MAX - 4; nPad++)
	{
		if ((nPad % 4) != 0)
		{
			m_arPadList[nPad]->setString(std::to_string(nNumber));

			nNumber++;
		}
	}

	m_arPadList[(int)E_PAD::E_PAD_12]->setString(UTF8("취소"));
	m_arPadList[(int)E_PAD::E_PAD_13]->setString(".");
	m_arPadList[(int)E_PAD::E_PAD_14]->setString("0");
	m_arPadList[(int)E_PAD::E_PAD_15]->setString(UTF8("지우기"));
	m_arPadList[(int)E_PAD::E_PAD_16]->setString(UTF8("확인"));

	m_pTitleName->setString(UTF8("Calculator.window"));
	m_pResult->setString(m_strResult);
}

void C_Calculator::presetBorderRect()
{
	Vec2 vecBasicRect(Vec2::ZERO);
	float fBasicXpos(0.0f);
	float fBasicYpos(0.0f);

	m_recTouchBorder = m_pMainLayer->getBoundingBox();

	fBasicXpos = m_pMainLayer->getPositionX();
	fBasicYpos = m_pMainLayer->getPositionY();

	vecBasicRect = Vec2(3.0f + fBasicXpos, 3.0f + fBasicYpos);

	for (int nList((int)E_PAD::E_PAD_01); nList < (int)E_PAD::E_MAX; nList++)
	{
		float fPadXpos(0.0f);
		float fPadYpos(0.0f);

		fPadXpos = m_arPadButton[nList]->getPositionX();
		fPadYpos = m_arPadButton[nList]->getPositionY();

		vecBasicRect = Vec2(2.0f + fBasicXpos + fPadXpos, 2.0f + fBasicYpos + fPadYpos);

		m_arRectList[nList] = Rect(vecBasicRect, Size(50.0f, 50.0f));
	}
}

void C_Calculator::presetFuncList()
{
	int nNumber(0);

	nNumber = (int)E_PAD::E_PAD_01;

	for (int nPad((int)E_PAD::E_PAD_01); nPad < (int)E_PAD::E_MAX - 4; nPad++)
	{
		if ((nPad % 4) != 0)
		{
			m_arFuncList[nPad] = &C_Calculator::inputNumber;

			nNumber++;
		}
	}

	m_arFuncList[(int)E_PAD::E_PAD_04] = &C_Calculator::percentTrade;
	m_arFuncList[(int)E_PAD::E_PAD_08] = &C_Calculator::percentTrade;
	m_arFuncList[(int)E_PAD::E_PAD_12] = &C_Calculator::closeMenu;
	m_arFuncList[(int)E_PAD::E_PAD_16] = &C_Calculator::closeMenu;
	m_arFuncList[(int)E_PAD::E_PAD_15] = &C_Calculator::initNumber;
	m_arFuncList[(int)E_PAD::E_PAD_14] = &C_Calculator::inputZero;
	m_arFuncList[(int)E_PAD::E_PAD_13] = &C_Calculator::addDot;
}

void C_Calculator::inputNumber(const int nNumber)
{
	int nRemove(0);

	for (int nRepeat(0); nRepeat < 2; nRepeat++)
	{
		if (nNumber > (nRepeat + 1) * 4)
		{
			nRemove++;
		}
	}

	if (m_strResult.size() == 1 && m_strResult.at(0) == '0')
	{
		m_strResult = "";
	}
	
	m_strResult += std::to_string(nNumber - nRemove);
}

void C_Calculator::inputZero(const int nNumber)
{
	if (m_strResult.at(0) == '0')
	{
		return;
	}

	m_strResult += '0';
}

void C_Calculator::percentTrade(const int nNumber)
{
}

void C_Calculator::addDot(const int nNumber)
{
	if (m_isDot)
	{
		return;
	}

	m_strResult += '.';
	m_nDotPos = m_strResult.size() - 1;
	m_isDot = true;
}

void C_Calculator::closeMenu(const int nNumber)
{
	if (nNumber == 12)
	{

	}
	else if (nNumber == 16)
	{
		if (m_strResult.size() - 1 == m_nDotPos || m_nDotPos == 0)
		{
			convertInteger();
		}
		else
		{
			convertFloat();
		}

		*m_pConnect = m_fResult;
		m_pTextConnect->setString(std::to_string(m_fResult));
	}

	m_pCallBox->releaseCalculator();

	m_pConnect = nullptr;
	m_pTextConnect = nullptr;
	m_pCallBox = nullptr;

	CCLOG(std::to_string(m_fResult).c_str());
}

void C_Calculator::initNumber(const int nNumber)
{
	m_strResult = "0";
	m_isDot = false;
	m_nDotPos = 0;
	m_fResult = 0.0;
}

void C_Calculator::convertFloat()
{
	int nMaxNum(0);

	nMaxNum = m_strResult.size();

	for (int nList(0); nList < nMaxNum; nList++)
	{
		double dlAdder(0.0);
		
		if (m_strResult.at(nList) == '.')
		{

		}
		else
		{
			dlAdder = (float)((int)(m_strResult.at(nList)) - 48);

			if (m_nDotPos > nList)
			{
				for (int nSquare(0); nSquare < (m_nDotPos - nList - 1); nSquare++)
				{
					dlAdder *= 10.0;
				}
			}
			else if (m_nDotPos < nList)
			{
				for (int nSquare(0); nSquare < (nList - m_nDotPos); nSquare++)
				{
					dlAdder /= 10.0;
				}
			}

			m_fResult += dlAdder;
		}
	}
}

void C_Calculator::convertInteger()
{
	int nMaxNum(0);
	int nMul(0);
	int nResult(0);
	bool isSwitch(true);
	std::string strConvert("");

	nMaxNum = m_strResult.size();

	for (int nList(0); (nList < nMaxNum) && isSwitch; nList++)
	{
		char cText('\0');

		cText = m_strResult.at(nList);

		if (cText != '.')
		{
			strConvert += cText;
		}
		else
		{
			nMaxNum = nList;
			isSwitch = false;
		}
	}

	nMul = 1;

	for (int nList(nMaxNum - 1); nList > -1; nList--)
	{
		int nAdder(0);

		nAdder = (int)(strConvert.at(nList)) - 48;

		nAdder *= nMul;

		nResult += nAdder;

		nMul *= 10;
	}

	m_fResult += (double)nResult;
}

bool C_Calculator::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouch(Vec2::ZERO);

	vecTouch = pTouch->getLocation();

	if (m_recTouchBorder.containsPoint(vecTouch))
	{
		for (int nPad((int)E_PAD::E_PAD_01); nPad < (int)E_PAD::E_MAX; nPad++)
		{
			if (m_arRectList[nPad].containsPoint(vecTouch))
			{
				(this->*m_arFuncList[nPad])(nPad);

				m_pResult->setString(m_strResult);

				return true;
			}
		}
	}

	return false;
}

bool C_Calculator::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Calculator::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_Calculator::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

void C_Calculator::setEnabled(const bool bSwitch)
{
	initNumber(0);

	m_pMainLayer->setVisible(bSwitch);
	m_pTouchEvent->setEnabled(bSwitch);
}

void C_Calculator::setConnect(float* pConnect, Label* pTargetLab, C_Value_Box* pBox)
{
	m_pConnect		= pConnect;
	m_pTextConnect	= pTargetLab;
	m_pCallBox		= pBox;
}