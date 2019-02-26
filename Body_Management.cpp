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

C_MainBody_Menu * C_MainBody_Menu::create(const std::string& strRoute)
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_MainBody_Menu();

	m_pMyPointer->init();
	m_pMyPointer->setRoute(strRoute);
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_MainBody_Menu::init()
{
	m_strRoute			= "";
	m_pMainLayer		= nullptr;
	m_pBackground		= nullptr;
	m_pClipingNode		= nullptr;
	m_recEventBorder	= Rect::ZERO;
}

bool C_MainBody_Menu::mainBoard()
{
	if (!C_Scene_Manager::getInstance()->getScene())
	{
		return false;
	}

	createBodyLayer();
	createSpriteItems();
	createClippingNode();
	createMenu();

	presetEventFuncList();
	presetSelectedMenu();
	presetMenuEnabled();
	presetItemsPosition();
	presetItemsScale();
	presetItemsAnchor();
	presetItemsVisible();

	addChildScene();
	
	callSetup();

	return true;
}

void C_MainBody_Menu::createBodyLayer()
{
	m_pMainLayer = C_Layer_Management::createLayer(S_KeyStore::strBodyAreaName);
}

void C_MainBody_Menu::createMenu()
{
	C_News_Management::create();
	C_Market_Management::create();
	C_History_Menu::create();
}

void C_MainBody_Menu::createSpriteItems()
{
	m_pBackground = C_Sprite_Management::createSprite(m_strRoute, "Body_BG", "Body_Background");
}

void C_MainBody_Menu::addChildScene()
{
	Scene* pScene(nullptr);

	pScene = C_Scene_Manager::getInstance()->getScene();

	m_pMainLayer->addChild(m_pBackground);
	m_pMainLayer->addChild(C_News_Management::getInstance()->getNewsLayer());
	m_pMainLayer->addChild(C_Market_Management::getInstance()->getMarketLayer());
	m_pMainLayer->addChild(C_History_Menu::getInstance()->getMyLayer());

	m_pClipingNode->addChild(m_pMainLayer);
	
	pScene->addChild(m_pClipingNode);
}

void C_MainBody_Menu::presetSelectedMenu()
{
	m_nPastSelected = S_KeyStore::nMenuKey;
	m_pPastFunc		= m_arEventFunc[m_nPastSelected];
}

void C_MainBody_Menu::presetMenuEnabled()
{
	C_News_Management::getInstance()->setEventEnabled(true);
	C_Market_Management::getInstance()->setEventEnabled(false);
	C_History_Menu::getInstance()->setEnabled(false);
}

void C_MainBody_Menu::presetItemsPosition()
{
	m_pClipingNode->setPosition(270.0f, 522.5f); // ClippingNode 위치가 Node자식들에게도 귀속됨.
	m_pBackground->setPosition(0.0f, 0.0f);
}

void C_MainBody_Menu::presetItemsScale()
{

}

void C_MainBody_Menu::presetItemsAnchor()
{
}

void C_MainBody_Menu::presetItemsVisible()
{
	m_pBackground->setVisible(true);
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

void C_MainBody_Menu::createClippingNode()
{
	Sprite* pSprite(nullptr);

	pSprite = Sprite::createWithSpriteFrame(m_pBackground->getSpriteFrame());

	m_pClipingNode = C_ClippingNode_Management::create("Body_Node", pSprite);
}

void C_MainBody_Menu::presetEventFuncList()
{
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

	m_pMainLayer->runAction(pRepeat);
}

void C_MainBody_Menu::setupMenuVisible()
{
	if (m_nPastSelected != S_KeyStore::nMenuKey)
	{
		(this->*m_pPastFunc)(false);

		m_nPastSelected = S_KeyStore::nMenuKey;

		m_pPastFunc  = m_arEventFunc[m_nPastSelected];

		(this->*m_pPastFunc)	(true);
	}
}