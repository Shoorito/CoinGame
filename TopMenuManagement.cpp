#include "TopMenuManagement.h"
#include "C_ResManagement.h"
#include "C_ItemManagement.h"
#include "Scene_Manager.h"

C_MainTop_Menu* C_MainTop_Menu::m_pMyPointer = nullptr;

C_MainTop_Menu * C_MainTop_Menu::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_MainTop_Menu();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_MainTop_Menu::init()
{
	m_nSelectPast		= 0;
	m_nSpriteCount		= 0;
	m_nButtonCount		= 0;
	m_strFileRoute		= "";
	m_pTopLayer			= nullptr;
}

bool C_MainTop_Menu::mainBoard()
{
	if (!C_Scene_Manager::getInstance()->getScene())
	{
		return false;
	}

	C_ItemManagement* pManager(nullptr);

	pManager = C_ItemManagement::getInstance();

	pManager->setInfoList((int)E_IMG_TYPE::E_SPRITE, (int)E_FILE_TYPE::E_TOP_MENU, m_vecSpritesInfo);
	pManager->setInfoList((int)E_IMG_TYPE::E_BUTTON, (int)E_FILE_TYPE::E_TOP_MENU, m_vecButtonsInfo);

	createTopLayer();
	setFileRoute();
	setItemsCount();
	setSelectPastValue();
	
	createSpriteItems();
	createButtonItems();

	pManager->setItemsList(m_vecSpritesInfo, m_vecSpritesList, m_nSpriteCount);
	pManager->setItemsList(m_vecButtonsInfo, m_vecButtonsList, m_nButtonCount);

	pManager->addChildItems(m_vecSpritesList, m_nSpriteCount, m_pTopLayer);
	pManager->addChildItems(m_vecButtonsList, m_nButtonCount, m_pTopLayer);

	setTopItemsAnchor();
	setTopItemsScale();
	setTopItemsPosition();
	setTopItemsVisible();

	addChildScene();

	createTouchEvent();
	callTitleEvent();

	return true;
}

void C_MainTop_Menu::addChildScene()
{
	C_Scene_Manager::getInstance()->getScene()->addChild(m_pTopLayer);
}

void C_MainTop_Menu::setItemsCount()
{
	m_nSpriteCount = m_vecSpritesInfo.size();
	m_nButtonCount = m_vecButtonsInfo.size();
}

void C_MainTop_Menu::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	C_Event_Manager::setTagName((std::string)("TopTouchEvent"), (EventListener*)(pTouchEvent));

	pTouchEvent->onTouchBegan		= CC_CALLBACK_2(C_MainTop_Menu::touchOnBegan,		this);
	pTouchEvent->onTouchEnded		= CC_CALLBACK_2(C_MainTop_Menu::touchOnEnded,		this);
	pTouchEvent->onTouchMoved		= CC_CALLBACK_2(C_MainTop_Menu::touchOnMoved,		this);
	pTouchEvent->onTouchCancelled	= CC_CALLBACK_2(C_MainTop_Menu::touchOnCanceled,	this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority((EventListener*)(pTouchEvent), 1);
}

void C_MainTop_Menu::createSpriteItems()
{
	for (int nItemNum(0); nItemNum < m_nSpriteCount; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecSpritesInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

void C_MainTop_Menu::createButtonItems()
{
	for (int nItemNum(0); nItemNum < m_nButtonCount; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecButtonsInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

bool C_MainTop_Menu::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouchLocation(Vec2::ZERO);
	Rect recBottomMenu(Rect::ZERO);

	vecTouchLocation = pTouch->getLocation();

	for (int nVecList(0); nVecList < m_nButtonCount; nVecList++)
	{
		if (m_vecButtonsList.at(nVecList)->getBoundingBox().containsPoint(vecTouchLocation))
		{

		}
	}

	return true;
}

bool C_MainTop_Menu::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_MainTop_Menu::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_MainTop_Menu::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

void C_MainTop_Menu::setFileRoute()
{
	C_ResManagement* pManager(nullptr);

	pManager = C_ResManagement::getInstance();

	m_strFileRoute = pManager->getRoute((int)E_FILE_TYPE::E_TOP_MENU);
}

void C_MainTop_Menu::setTopItemsPosition()
{
	m_vecButtonsList.at((int)E_TopMenuItem::E_SIDEMENU - 1)->setPosition(31.5f, 922.5f);
	m_vecButtonsList.at((int)E_TopMenuItem::E_SEARCH - 1)->setPosition(506.0f, 922.5f);

	for (int nSpriteNum(0); nSpriteNum < m_nSpriteCount; nSpriteNum++)
	{
		m_vecSpritesList.at(nSpriteNum)->setPosition(270.0f, 922.5f);
	}
}

void C_MainTop_Menu::setTopItemsAnchor()
{

}

void C_MainTop_Menu::setTopItemsScale()
{
	for (int nSpriteNum(0); nSpriteNum < m_nSpriteCount; nSpriteNum++)
	{
		m_vecSpritesList.at(nSpriteNum)->setScale(0.5f);
	}

	m_vecButtonsList.at((int)E_TopMenuItem::E_SEARCH - 1)->setScale(0.5f);
}

void C_MainTop_Menu::setTopItemsVisible()
{
	m_vecSpritesList.at(0)->setVisible(true);
	m_vecSpritesList.at(m_nSelectPast)->setVisible(true);

	for (int nButtonNum(0); nButtonNum < m_nButtonCount; nButtonNum++)
	{
		m_vecButtonsList.at(nButtonNum)->setVisible(true);
	}
}

void C_MainTop_Menu::callTitleEvent()
{
	CallFunc*	pCallFunc	(nullptr);
	DelayTime*	pDelay		(nullptr);
	Sequence*	pSeq		(nullptr);
	Repeat*		pRep		(nullptr);

	pCallFunc	= CallFunc::create(CC_CALLBACK_0(C_MainTop_Menu::setupTitle, this));
	pDelay		= DelayTime::create((float)(0.05f));
	pSeq		= Sequence::create(pCallFunc, pDelay, nullptr);
	pRep		= Repeat::create(pSeq, -1);

	m_pTopLayer->runAction(pRep);
}

void C_MainTop_Menu::setupTitle()
{
	if (m_nSelectPast != S_KeyStore::nMenuKey)
	{
		m_vecSpritesList.at(m_nSelectPast)->setVisible(false);

		m_nSelectPast = S_KeyStore::nMenuKey;

		m_vecSpritesList.at(m_nSelectPast)->setVisible(true);
	}
}
