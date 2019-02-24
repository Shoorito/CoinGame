#include "Body_Management.h"
#include "Sprite_Management.h"
#include "Scene_Manager.h"
#include "Layer_Management.h"
#include "ShareKey.h"
#include "C_ItemManagement.h"
#include "C_ResManagement.h"
#include "C_News_Menu.h"
#include "C_Market_Menu.h"
#include "EventManager.h"
#include "C_History_Menu.h"

C_MainBody_Menu* C_MainBody_Menu::m_pMyPointer = nullptr;

C_MainBody_Menu * C_MainBody_Menu::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_MainBody_Menu();
	
	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_MainBody_Menu::init()
{
	m_nSpriteCount		= 0;
	m_nButtonCount		= 0;
	m_fNowTouchedYpos	= 0.0f;
	m_fPastYpos			= 0.0f;
	m_strFileRoute		= "";
	m_pBodyLayer		= nullptr;
	m_pClippingTarget	= nullptr;
	m_pBodyClipingNode  = nullptr;
	m_recEventBorder	= Rect::ZERO;
}

bool C_MainBody_Menu::mainBoard()
{
	if (!C_Scene_Manager::getInstance()->getScene())
	{
		return false;
	}

	C_ItemManagement* pManager(nullptr);

	pManager = C_ItemManagement::getInstance();

	pManager->setInfoList((int)E_IMG_TYPE::E_SPRITE, (int)E_FILE_TYPE::E_BODY_MENU, m_vecSpritesInfo);
	pManager->setInfoList((int)E_IMG_TYPE::E_BUTTON, (int)E_FILE_TYPE::E_BODY_MENU, m_vecButtonsInfo);

	createBodyLayer();
	createUseItems();

	setBodyItemsRoute();
	setBodyItemsCount();

	presetMenuLayer();
	presetEventFuncList();
	presetClippingNode();

	createSpriteItems();
	createButtonItems();

	pManager->setItemsList(m_vecSpritesInfo, m_vecSpritesList, m_nSpriteCount);
	pManager->setItemsList(m_vecButtonsInfo, m_vecButtonsList, m_nButtonCount);

	addChildScene();

	setPastSelectedMenu();
	setBodyItemsPosition();
	setBodyItemsScale();
	setBodyItemsAnchor();
	setBodyItemsVisible();
	
	presetLayerOption();
	callSetup();

	return true;
}

void C_MainBody_Menu::releaseTemp()
{

}

void C_MainBody_Menu::createBodyLayer()
{
	m_pBodyLayer = C_Layer_Management::createLayer(S_KeyStore::strBodyAreaName);
}

void C_MainBody_Menu::createUseItems()
{
	m_pActionNode = Node::create();
	C_News_Management::create();
	C_Market_Management::create();
}

void C_MainBody_Menu::createSpriteItems()
{
	for (int nItemNum(0); nItemNum < m_nSpriteCount; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecSpritesInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

void C_MainBody_Menu::createButtonItems()
{
	for (int nItemNum(0); nItemNum < m_nButtonCount; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecButtonsInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

void C_MainBody_Menu::addChildScene()
{
	m_pBodyLayer->addChild(m_vecSpritesList.at(0));
	m_pBodyLayer->addChild(m_pActionNode);
	m_pBodyLayer->addChild(m_arMenuLayer[(int)E_MENU_TYPE::E_NEWS]);
	m_pBodyLayer->addChild(m_arMenuLayer[(int)E_MENU_TYPE::E_MARKET]);
	m_pBodyLayer->addChild(m_arMenuLayer[(int)E_MENU_TYPE::E_HISTORY]);
	m_pBodyLayer->addChild(m_arMenuLayer[(int)E_MENU_TYPE::E_WORLD_NEWS]);
	m_pBodyLayer->addChild(m_arMenuLayer[(int)E_MENU_TYPE::E_MYPAGE]);

	m_pBodyClipingNode->addChild(m_pBodyLayer);
	
	m_arMenuLayer[(int)E_MENU_TYPE::E_MARKET]->addChild(m_vecSpritesList.at(1));
	
	C_Scene_Manager::getInstance()->getScene()->addChild(m_pBodyClipingNode);
}

void C_MainBody_Menu::setPastSelectedMenu()
{
	m_nPastSelected = S_KeyStore::nMenuKey;
	m_pPastLayer = m_arMenuLayer[m_nPastSelected];
	m_pPastFunc  = m_arEventFunc[m_nPastSelected];
}

void C_MainBody_Menu::presetLayerOption()
{
	m_arMenuLayer[(int)E_MENU_TYPE::E_NEWS]->setVisible(true);
	m_arMenuLayer[(int)E_MENU_TYPE::E_MARKET]->setVisible(false);
	m_arMenuLayer[(int)E_MENU_TYPE::E_HISTORY]->setVisible(false);
	m_arMenuLayer[(int)E_MENU_TYPE::E_WORLD_NEWS]->setVisible(false);
	m_arMenuLayer[(int)E_MENU_TYPE::E_MYPAGE]->setVisible(false);

	C_News_Management::getInstance()->setEventEnabled(true);
	C_Market_Management::getInstance()->setEventEnabled(false);
	C_History_Menu::getInstance()->setEnabled(false);
}

void C_MainBody_Menu::setBodyItemsCount()
{
	m_nSpriteCount = m_vecSpritesInfo.size();
	m_nButtonCount = m_vecButtonsInfo.size();
}

void C_MainBody_Menu::setBodyItemsRoute()
{
	C_ResManagement* pManager(nullptr);

	pManager = C_ResManagement::getInstance();

	m_strFileRoute = pManager->getRoute((int)E_FILE_TYPE::E_BODY_MENU);
}

void C_MainBody_Menu::setBodyItemsPosition()
{
	m_vecSpritesList.at(0)->setPosition(0.0f, 0.0f);
	m_vecSpritesList.at(1)->setPosition(0.0f, 349.0f);

	m_pBodyClipingNode->setPosition(270.0f, 522.5f);
}

void C_MainBody_Menu::setBodyItemsScale()
{

}

void C_MainBody_Menu::setBodyItemsAnchor()
{
}

void C_MainBody_Menu::setBodyItemsVisible()
{
	for (int nList(0); nList < m_nSpriteCount; nList++)
	{
		m_vecSpritesList.at(nList)->setVisible(true);
	}
}

void C_MainBody_Menu::setNewsEvent(const bool isEnabled)
{
	C_News_Management::getInstance()->setEventEnabled(isEnabled);
}

void C_MainBody_Menu::setMarketEvent(const bool isEnabled)
{
	C_Market_Management::getInstance()->setEventEnabled(isEnabled);
}

void C_MainBody_Menu::setHistoryEvent(const bool isEnabled)
{
	C_History_Menu::getInstance()->setEnabled(isEnabled);
}

void C_MainBody_Menu::setWorldEvent(const bool isEnabled)
{
}

void C_MainBody_Menu::setMypageEvent(const bool isEnabled)
{
}

void C_MainBody_Menu::presetMenuLayer()
{
	m_arMenuLayer[(int)E_MENU_TYPE::E_NONE]			= nullptr;
	m_arMenuLayer[(int)E_MENU_TYPE::E_NEWS]			= C_News_Management::getInstance()->getNewsLayer();
	m_arMenuLayer[(int)E_MENU_TYPE::E_MARKET]		= C_Market_Management::getInstance()->getMarketLayer();
	m_arMenuLayer[(int)E_MENU_TYPE::E_HISTORY]		= C_History_Menu::getInstance()->getMyLayer();
	m_arMenuLayer[(int)E_MENU_TYPE::E_WORLD_NEWS]	= C_Layer_Management::createLayer("WorldNews_Body_Layer");
	m_arMenuLayer[(int)E_MENU_TYPE::E_MYPAGE]		= C_Layer_Management::createLayer("Mypage_Body_Layer");
}

void C_MainBody_Menu::presetClippingNode()
{
	Sprite* pSprite(nullptr);
	std::string strName("");

	strName = m_vecSpritesInfo.at(0)->getName();

	m_pClippingTarget = C_Sprite_Management::createSprite(m_strFileRoute, strName, "BodyClippingNode");

	m_pClippingTarget->setVisible(true);

	m_pBodyClipingNode = C_ClippingNode_Management::create("BodyLayer_Clipping", m_pClippingTarget);
}

void C_MainBody_Menu::presetEventFuncList()
{
	m_arEventFunc[(int)E_MENU_TYPE::E_NONE]		  = nullptr;
	m_arEventFunc[(int)E_MENU_TYPE::E_NEWS]		  = &C_MainBody_Menu::setNewsEvent;
	m_arEventFunc[(int)E_MENU_TYPE::E_MARKET]	  = &C_MainBody_Menu::setMarketEvent;
	m_arEventFunc[(int)E_MENU_TYPE::E_HISTORY]	  = &C_MainBody_Menu::setHistoryEvent;
	m_arEventFunc[(int)E_MENU_TYPE::E_WORLD_NEWS] = &C_MainBody_Menu::setWorldEvent;
	m_arEventFunc[(int)E_MENU_TYPE::E_MYPAGE]	  = &C_MainBody_Menu::setMypageEvent;

	(this->*m_arEventFunc[(int)E_MENU_TYPE::E_NEWS])(true);
	(this->*m_arEventFunc[(int)E_MENU_TYPE::E_MARKET])(false);
	(this->*m_arEventFunc[(int)E_MENU_TYPE::E_HISTORY])(false);
	(this->*m_arEventFunc[(int)E_MENU_TYPE::E_WORLD_NEWS])(false);
	(this->*m_arEventFunc[(int)E_MENU_TYPE::E_MYPAGE])(false);
}

void C_MainBody_Menu::callSetup()
{
	CallFunc* pFunc(nullptr);
	DelayTime* pDelay(nullptr);
	Sequence* pSequance(nullptr);
	Repeat* pRepeat(nullptr);

	pFunc = CallFunc::create(CC_CALLBACK_0(C_MainBody_Menu::setupMenuVisible, this));
	pDelay = DelayTime::create(0.1f);
	pSequance = Sequence::create(pFunc, pDelay, nullptr);
	pRepeat = Repeat::create(pSequance, -1);

	m_pActionNode->runAction(pRepeat);
}

void C_MainBody_Menu::setupMenuVisible()
{
	if (m_nPastSelected != S_KeyStore::nMenuKey)
	{
		m_pPastLayer->setVisible(false);
		(this->*m_pPastFunc)	(false);

		m_nPastSelected = S_KeyStore::nMenuKey;

		m_pPastLayer = m_arMenuLayer[m_nPastSelected];
		m_pPastFunc  = m_arEventFunc[m_nPastSelected];

		m_pPastLayer->setVisible(true);
		(this->*m_pPastFunc)	(true);
	}
}