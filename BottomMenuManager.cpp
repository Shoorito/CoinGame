#include "BottomMenuManager.h"
#include "Scene_Manager.h"
#include "EventManager.h"
#include "ShareKey.h"
#include "Sprite_Management.h"
#include "C_ResManagement.h"
#include "EnumClassList.h"
#include "C_ItemManagement.h"

C_MainBottom_Menu* C_MainBottom_Menu::m_pInstance = nullptr;

C_MainBottom_Menu * C_MainBottom_Menu::create(const std::string& strRoute)
{
	if (m_pInstance)
	{
		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_MainBottom_Menu();

	m_pInstance->init();
	m_pInstance->setRoute(strRoute);
	m_pInstance->mainBoard();

	return m_pInstance;
}

void C_MainBottom_Menu::init()
{
	m_strRoute		= "";
	m_nPastButton	= 0;
	m_pMainLayer	= nullptr;
}

bool C_MainBottom_Menu::mainBoard()
{
	Scene* pScene(nullptr);

	pScene = C_Scene_Manager::getInstance()->getScene();

	if (!pScene)
	{
		return false;
	}

	createLayer();
	createSpriteItems();
	createTouchEvent();

	presetPastSelected();
	presetItemsPosition();
	presetItemsAnchor();
	presetItemsScale();
	presetItemsVisible();

	return true;
}

void C_MainBottom_Menu::presetPastSelected()
{
	m_nPastButton = S_KeyStore::nMenuKey;
}

void C_MainBottom_Menu::createLayer()
{
	m_pMainLayer = Layer::create();
} 

void C_MainBottom_Menu::createTouchEvent()
{
	EventListenerTouchOneByOne* pTouchEvent(nullptr);

	pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan		= CC_CALLBACK_2(C_MainBottom_Menu::touchOnBegan, this);
	pTouchEvent->onTouchEnded		= CC_CALLBACK_2(C_MainBottom_Menu::touchOnEnded, this);
	pTouchEvent->onTouchMoved		= CC_CALLBACK_2(C_MainBottom_Menu::touchOnMoved, this);
	pTouchEvent->onTouchCancelled	= CC_CALLBACK_2(C_MainBottom_Menu::touchOnCanceled, this);

	m_pTouchEvent = pTouchEvent;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(pTouchEvent, 1);
}

void C_MainBottom_Menu::createSpriteItems()
{
	for (int nItemNum((int)E_MENU_TYPE::E_NEWS); nItemNum < (int)E_MENU_TYPE::E_MAX; nItemNum++)
	{
		std::string strName("");
		std::string strTag("");

		strName = "Selected_Button_0" + std::to_string(nItemNum);
		strTag = "Bottom_Selected_" + std::to_string(nItemNum);

		m_arSelectedButton[nItemNum] = C_Sprite_Management::createSprite(m_strRoute, strName, strTag);
	}

	m_pMenu_BG = C_Sprite_Management::createSprite(m_strRoute, "MainMenu_Normal", "Bottom_BG");
}

bool C_MainBottom_Menu::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2	vecTouchLocation(Vec2::ZERO);
	Rect	recBottomMenu(Rect::ZERO);
	Sprite* pSprite(nullptr);

	vecTouchLocation = pTouch->getLocation();
	recBottomMenu	 = m_pMenu_BG->getBoundingBox();

	if (recBottomMenu.containsPoint(vecTouchLocation))
	{
		m_arSelectedButton[m_nPastButton]->setVisible(false);

		for (int nArrNum((int)E_MENU_TYPE::E_NEWS); nArrNum < (int)E_MENU_TYPE::E_MAX; nArrNum++)
		{
			pSprite = m_arSelectedButton[nArrNum];
			
			if (pSprite->getBoundingBox().containsPoint(vecTouchLocation))
			{
				pSprite->setVisible(true);

				S_KeyStore::nMenuKey = nArrNum;

				m_nPastButton = S_KeyStore::nMenuKey;

				return true;
			}

		}
	}
	
	return false;
}

void C_MainBottom_Menu::presetItemsScale()
{
	for (int nList((int)E_MENU_TYPE::E_NEWS); nList < (int)E_MENU_TYPE::E_MAX; nList++)
	{
		m_arSelectedButton[nList]->setScale(0.5f);
	}
}

void C_MainBottom_Menu::presetItemsAnchor()
{
	m_pMenu_BG->setAnchorPoint(Vec2(0.0f, 0.5f));

	for (int nList((int)E_MENU_TYPE::E_NEWS); nList < (int)E_MENU_TYPE::E_MAX; nList++)
	{
		m_arSelectedButton[nList]->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
}

void C_MainBottom_Menu::presetItemsPosition()
{
	m_pMenu_BG->setPosition(Point(0.0f, 130.0f));

	for (int nList((int)E_MENU_TYPE::E_NEWS); nList < (int)E_MENU_TYPE::E_MAX; nList++)
	{
		m_arSelectedButton[nList]->setPosition(Point(108.0f * (float)(nList), 130.0f));
	}
}

void C_MainBottom_Menu::presetItemsVisible()
{
	m_pMenu_BG->setVisible(true);
	m_arSelectedButton[S_KeyStore::nMenuKey]->setVisible(true);
}