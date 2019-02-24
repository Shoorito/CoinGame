#include "NewsSectionManagement.h"
#include "C_ResManagement.h"
#include "C_ItemManagement.h"
#include "EnumClassList.h"
#include "Layer_Management.h"
#include "Sprite_Management.h"
#include "ClippingNode_Management.h"
#include "ShareKey.h"
#include "EventManager.h"

C_News_Section* C_News_Section::m_pMyPointer = nullptr;

C_News_Section * C_News_Section::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_News_Section();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();
	
	return m_pMyPointer;
}

void C_News_Section::init()
{
	m_nSpriteCount		= 0;
	m_nButtonCount		= 0;
	m_nNowSelectNum		= 0;
	m_fNowTouchedXpos	= 0.0f;
	m_fPastXpos			= 0.0f;
	m_fSection_width	= 0.0f;
	m_fSection_height	= 0.0f;
	m_strFileRoute		= "";
	m_arXposList		= nullptr;
	m_pStencil			= nullptr;
	m_pPastButton		= nullptr;
	m_pClippingNode		= nullptr;
	m_pFirstSection		= nullptr;
	m_pButtonsLayer		= nullptr;
	m_pSpritesLayer		= nullptr;
	m_pItemsLayer		= nullptr;
	m_pSectionLayer		= nullptr;
}

bool C_News_Section::mainBoard()
{
	C_ItemManagement* pManager(nullptr);

	pManager = C_ItemManagement::getInstance();

	pManager->setInfoList((int)E_IMG_TYPE::E_SPRITE, (int)E_FILE_TYPE::E_SECTION_MENU, m_vecSpritesInfo);
	pManager->setInfoList((int)E_IMG_TYPE::E_BUTTON, (int)E_FILE_TYPE::E_SECTION_MENU, m_vecButtonsInfo);

	setItemsCount();
	createSectionLayers();
	createPosList();
	setFileRoute();

	createSpriteItems();
	createButtonItems();

	pManager->setItemsList(m_vecSpritesInfo, m_vecSpritesList, m_nSpriteCount);
	pManager->setItemsList(m_vecButtonsInfo, m_vecButtonsList, m_nButtonCount);

	createStencilNode();
	createBorderGround();

	pManager->addChildItems(m_vecButtonsList, m_nButtonCount, m_pButtonsLayer);
	pManager->addChildItems(m_vecSpritesList, m_nSpriteCount, m_pSpritesLayer);

	setAddchild();

	setSectionPosition();
	setBasedSize();
	setPointList();
	setFirstSection();
	setPastButton();

	setItemsScale();
	setSpritesPosition();
	setButtonsPosition();
	setButtonsLayerPosition();
	setBorderLine();
	setItemsVisible();

	createTouchEvent();
	callSetup();

	return true;
}

void C_News_Section::setPointList()
{
	for (int nListNum(0); nListNum < m_nSpriteCount; nListNum++)
	{
		m_arXposList[nListNum] = -(m_fSection_width * (float)nListNum);
	}
}

void C_News_Section::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	C_Event_Manager::setTagName("News_Section_Event", pTouchEvent);

	pTouchEvent->onTouchBegan = CC_CALLBACK_2(C_News_Section::touchOnBegan, this);
	pTouchEvent->onTouchMoved = CC_CALLBACK_2(C_News_Section::touchOnMoved, this);
	pTouchEvent->onTouchEnded = CC_CALLBACK_2(C_News_Section::touchOnEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_News_Section::setSpritesPosition()
{
	Sprite*	pSprite(nullptr);

	for (int nSpriteCount(0); nSpriteCount < m_nSpriteCount; nSpriteCount++)
	{
		pSprite = m_vecSpritesList.at(nSpriteCount);
		pSprite->setPositionX(m_arXposList[nSpriteCount]);
	}
}

void C_News_Section::setButtonsPosition()
{
	Sprite*	pSprite(nullptr);
	Point   posSetPoint(Point::ZERO);
	int		nSelectedButton(0);

	nSelectedButton = m_nButtonCount / 2;

	for (int nButton(0); nButton < nSelectedButton; nButton++)
	{
		posSetPoint = Point((35.0f * nButton), 15.0f - (m_fSection_height / 2.0f));

		m_vecButtonsList.at(nButton)->setPosition(posSetPoint);
		m_vecButtonsList.at(nButton + nSelectedButton)->setPosition(posSetPoint);
	}

}

void C_News_Section::setAddchild()
{
	m_pItemsLayer->addChild(m_pSpritesLayer);
	m_pItemsLayer->addChild(m_pButtonsLayer);

	m_pClippingNode->addChild(m_pItemsLayer);

	m_pSectionLayer->addChild(m_pBackground);
	m_pSectionLayer->addChild(m_pActionNode);
	m_pSectionLayer->addChild(m_pClippingNode);
}

bool C_News_Section::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouchLocation(Vec2::ZERO);

	vecTouchLocation = pTouch->getLocation();

	if (m_recEventBorder.containsPoint(vecTouchLocation))
	{
		m_fPastXpos			= vecTouchLocation.x;
		m_fNowTouchedXpos	= 0.0f;
		CCLOG("Touched Section");
	}

	return true;
}

bool C_News_Section::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_News_Section::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouchLocation(Vec2::ZERO);

	vecTouchLocation = pTouch->getLocation();

	if (m_recEventBorder.containsPoint(vecTouchLocation))
	{
		float fXLength(0.0f);

		if (vecTouchLocation.x > m_fPastXpos)
		{
			fXLength = vecTouchLocation.x - m_fPastXpos;

			m_pFirstSection->setPositionX(m_pFirstSection->getPosition().x + fXLength);

			m_fNowTouchedXpos += fXLength;

			CCLOG(std::to_string(m_fNowTouchedXpos).c_str()); // 디버그 종료 시 삭제
		}
		else if (vecTouchLocation.x < m_fPastXpos)
		{
			fXLength = m_fPastXpos - vecTouchLocation.x;

			m_pFirstSection->setPositionX(m_pFirstSection->getPosition().x - fXLength);

			m_fNowTouchedXpos -= fXLength;

			CCLOG(std::to_string(m_fNowTouchedXpos).c_str()); // 디버그 종료 시 삭제
		}

		m_fPastXpos = vecTouchLocation.x;

		CCLOG("Moved!");
	}

	return true;
}

bool C_News_Section::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouchLocation(Vec2::ZERO);
	MoveTo* pMoveAct(nullptr);
	float	fMovePoint(0.0f);
	float	fMoveCondition(0.0f);
	int		nButtonNum(0);

	vecTouchLocation = pTouch->getLocation();

	if (m_recEventBorder.containsPoint(vecTouchLocation))
	{
		fMoveCondition = m_fSection_width / 2.0f;

		if ((m_fNowTouchedXpos >= fMoveCondition) && m_nNowSelectNum > 0)
		{
			m_nNowSelectNum--;
		}
		else if ((m_fNowTouchedXpos <= -(fMoveCondition)) && m_nNowSelectNum <= 0)
		{
			m_nNowSelectNum++;
		}

		nButtonNum = (m_nButtonCount / 2) + m_nNowSelectNum;

		fMovePoint = m_arXposList[m_nNowSelectNum];

		pMoveAct = MoveTo::create(0.1f, Point(fMovePoint, 0.0f));

		m_pFirstSection->runAction(pMoveAct);

		m_pPastButton->setVisible(false);

		m_pPastButton = m_vecButtonsList.at(nButtonNum);

		m_pPastButton->setVisible(true);

		CCLOG(std::to_string(m_nNowSelectNum).c_str());
	}

	return true;
}

void C_News_Section::setBasedSize()
{
	m_fSection_width  = m_pStencil->getContentSize().width / 2.0f;
	m_fSection_height = m_pStencil->getContentSize().height / 2.0f;
}

void C_News_Section::setItemsAnchor()
{

}

void C_News_Section::setItemsScale()
{
	for (auto& pSprite : m_vecSpritesList)
	{
		pSprite->setScale(0.5f);
	}

	for (auto& pButton : m_vecButtonsList)
	{
		pButton->setScale(0.5f);
	}

	m_pBackground->setScale(0.5f);
}

void C_News_Section::setItemsVisible()
{
	int nButtonCount(0);

	nButtonCount = m_nButtonCount / 2;

	for (auto& pSprite : m_vecSpritesList)
	{
		pSprite->setVisible(true);
	}

	for (int nButton(0); nButton < nButtonCount; nButton++)
	{
		m_vecButtonsList.at(nButton)->setVisible(true);
	}

	m_pPastButton->setVisible(true);
	m_pStencil->setVisible(true);
}

void C_News_Section::callSetup()
{
	CallFunc*	pCall(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSeq(nullptr);
	Repeat*		pRepeat(nullptr);

	pCall	= CallFunc::create(CC_CALLBACK_0(C_News_Section::setupChainItems, this));
	pDelay	= DelayTime::create(0.01f);
	pSeq	= Sequence::create(pCall, pDelay, nullptr);
	pRepeat = Repeat::create(pSeq, -1);

	m_pActionNode->runAction(pRepeat);
}

void C_News_Section::setupChainItems()
{
	Sprite* pTarget(nullptr);
	float	fBeforePosition(0.0f);

	for (int nItem(1); nItem < m_nSpriteCount; nItem++)
	{
		fBeforePosition = m_vecSpritesList.at(nItem - 1)->getPositionX();
		pTarget			= m_vecSpritesList.at(nItem);

		pTarget->setPositionX(fBeforePosition + m_fSection_width);
	}
}

void C_News_Section::releaseOfTemp()
{

}

void C_News_Section::setFileRoute()
{
	C_ResManagement* pManager(nullptr);

	pManager = C_ResManagement::getInstance();

	m_strFileRoute = pManager->getRoute((int)E_FILE_TYPE::E_SECTION_MENU);
}

void C_News_Section::setItemsCount()
{
	m_nSpriteCount = m_vecSpritesInfo.size();
	m_nButtonCount = m_vecButtonsInfo.size();
}

void C_News_Section::createSpriteItems()
{
	for (int nItemNum(0); nItemNum < m_nSpriteCount; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecSpritesInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

void C_News_Section::createButtonItems()
{
	for (int nItemNum(0); nItemNum < m_nButtonCount; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecButtonsInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

void C_News_Section::createStencilNode()
{
	std::string strCopyFile("");

	strCopyFile	= m_vecSpritesInfo.at(0)->getName();

	m_pStencil = C_Sprite_Management::createSprite(m_strFileRoute, strCopyFile, "Section_Stencil");

	m_pStencil->setScale(0.5f);

	m_pClippingNode = C_ClippingNode_Management::create("SectionCliping", m_pStencil);
}

void C_News_Section::createBorderGround()
{
	C_FNode* pBasedNode(nullptr);

	pBasedNode = m_vecSpritesInfo.at(0);

	m_pBackground = C_Sprite_Management::createSprite(m_strFileRoute, pBasedNode->getName(), "Section_Border");

	m_pBackground->setPosition(270.0f, 765.0f);
}

void C_News_Section::createSectionLayers()
{
	m_pActionNode   = Node::create();
	m_pButtonsLayer = C_Layer_Management::createLayer("Section_Button_Layer");
	m_pSpritesLayer = C_Layer_Management::createLayer("Section_Sprite_Layer");
	m_pItemsLayer	= C_Layer_Management::createLayer("Section_Items_Layer");
	m_pSectionLayer = C_Layer_Management::createLayer(S_KeyStore::strSectionAreaName);
}

void C_News_Section::setBorderLine()
{
	m_recEventBorder = m_pBackground->getBoundingBox();
}
