#include "BottomMenuManager.h"
#include "Scene_Manager.h"
#include "EventManager.h"
#include "ShareKey.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "C_ResManagement.h"
#include "EnumClassList.h"
#include "C_ItemManagement.h"

C_MainBottom_Menu* C_MainBottom_Menu::m_pInstance = nullptr;

C_MainBottom_Menu * C_MainBottom_Menu::create()
{
	if (m_pInstance)
	{
		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_MainBottom_Menu();
	
	m_pInstance->init();
	m_pInstance->mainBoard();

	return m_pInstance;
}

C_MainBottom_Menu* C_MainBottom_Menu::getInstance()
{
	return m_pInstance;
}

void C_MainBottom_Menu::init()
{
	m_strFileRoute	= "";
	m_nPastSprite	= 0;
	m_nSpriteNum	= 0;
	m_nButtonNum	= 0;
	m_pBottomLayer	= nullptr;
}

bool C_MainBottom_Menu::mainBoard()
{
	if (!C_Scene_Manager::getInstance()->getScene())
	{
		return false;
	}

	C_ItemManagement* pManager(nullptr);

	pManager = C_ItemManagement::getInstance();

	pManager->setInfoList((int)E_IMG_TYPE::E_SPRITE, (int)E_FILE_TYPE::E_BOTTOM_MENU, m_vecSpritesInfo);
	pManager->setInfoList((int)E_IMG_TYPE::E_BUTTON, (int)E_FILE_TYPE::E_BOTTOM_MENU, m_vecButtonsInfo);
	
	setFileRoute();
	setBottomItemsNum();
	setBottomPastSelectValue();

	setBottomLayer();

	createSpriteItems();
	createButtonItems();

	pManager->setItemsList(m_vecSpritesInfo, m_vecSpritesList, m_nSpriteNum);
	pManager->setItemsList(m_vecButtonsInfo, m_vecButtonsList, m_nButtonNum);

	pManager->addChildItems(m_vecSpritesList, m_nSpriteNum, m_pBottomLayer);
	pManager->addChildItems(m_vecButtonsList, m_nButtonNum, m_pBottomLayer);

	setBottomItemsAnchor();
	setBottomItemsScale();
	setBottomItemsVisible();
	setBottomItemsPos();

	createTouchEvent();

	return true;
}

void C_MainBottom_Menu::releaseTemp()
{

}

void C_MainBottom_Menu::setEnabled(const bool isEnabled)
{
	m_pTouchEvent->setEnabled(isEnabled);
}

void C_MainBottom_Menu::setBottomItemsNum()
{
	m_nSpriteNum = m_vecSpritesInfo.size();
	m_nButtonNum = m_vecButtonsInfo.size();
}

void C_MainBottom_Menu::setBottomPastSelectValue()
{
	m_nPastSprite = S_KeyStore::nMenuKey - 1;
}

void C_MainBottom_Menu::setFileRoute()
{
	C_ResManagement* pManager(nullptr);

	pManager = C_ResManagement::getInstance();

	m_strFileRoute = pManager->getRoute((int)E_FILE_TYPE::E_BOTTOM_MENU);
}

void C_MainBottom_Menu::setBottomLayer()
{
	Scene* pScene(nullptr);

	pScene = C_Scene_Manager::getInstance()->getScene();

	m_pBottomLayer = C_Layer_Management::createLayer("BottomItemsLayer");
	m_pEndButtonLayer = C_Layer_Management::createColorLayer("End_Button", Color4B::WHITE);

	m_pEndButtonLayer->setContentSize(Size(100.0f, 50.0f));

	pScene->addChild(m_pBottomLayer);
	pScene->addChild(m_pEndButtonLayer);
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

bool C_MainBottom_Menu::touchOnBegan(Touch * pTouch, Event * pUnUsedEvent)
{
	Vec2 vecTouchLocation(Vec2::ZERO);
	Rect recBottomMenu(Rect::ZERO);
	Rect recEndButton(Rect::ZERO);
	Sprite* pSprite(nullptr);

	vecTouchLocation = pTouch->getLocation();
	recBottomMenu = m_vecSpritesList.at(0)->getBoundingBox();
	recEndButton = m_pEndButtonLayer->getBoundingBox();

	if (recBottomMenu.containsPoint(vecTouchLocation))
	{
		m_vecButtonsList.at(m_nPastSprite)->setVisible(false);

		for (int nArrNum((int)E_MENU_TYPE::E_NEWS); nArrNum < (int)E_MENU_TYPE::E_MAX; nArrNum++)
		{
			pSprite = (Sprite*)(m_vecButtonsList.at(nArrNum - 1));
			
			if (pSprite->getBoundingBox().containsPoint(vecTouchLocation))
			{
				pSprite->setVisible(true);

				S_KeyStore::nMenuKey = nArrNum;

				m_nPastSprite = S_KeyStore::nMenuKey - 1;

				CCLOG("MenuCall : " + nArrNum);

				return true;
			}

		}
	}

	if (recEndButton.containsPoint(vecTouchLocation))
	{
		Director::getInstance()->end();
	}

	return false;
}

bool C_MainBottom_Menu::touchOnCanceled(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_MainBottom_Menu::touchOnEnded(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

bool C_MainBottom_Menu::touchOnMoved(Touch * pTouch, Event * pUnUsedEvent)
{
	return false;
}

void C_MainBottom_Menu::createSpriteItems()
{
	for (int nItemNum(0); nItemNum < m_nSpriteNum; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecSpritesInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

void C_MainBottom_Menu::createButtonItems()
{
	for (int nItemNum(0); nItemNum < m_nButtonNum; nItemNum++)
	{
		C_FNode* pNode(nullptr);

		pNode = m_vecButtonsInfo.at(nItemNum);

		C_ItemManagement::getInstance()->createItem(m_strFileRoute, pNode);
	}
}

void C_MainBottom_Menu::setBottomItemsScale()
{
	for (int nList(0); nList < m_nSpriteNum; nList++)
	{
		m_vecSpritesList.at(nList)->setScale(0.5f);
	}

	for (int nList(0); nList < m_nButtonNum; nList++)
	{
		m_vecButtonsList.at(nList)->setScale(0.5f);
	}
}

void C_MainBottom_Menu::setBottomItemsAnchor()
{
	m_vecSpritesList.at(0)->setAnchorPoint(Vec2(0.0f, 0.5f));

	for (int nList(0); nList < m_nButtonNum; nList++)
	{
		m_vecButtonsList.at(nList)->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
}

void C_MainBottom_Menu::setBottomItemsPos()
{
	m_vecSpritesList.at(0)->setPosition(Point(0.0f, 130.0f));

	for (int nList(0); nList < m_nButtonNum; nList++)
	{
		m_vecButtonsList.at(nList)->setPosition(Point(108.0f * (float)(nList), 130.0f));
	}

	m_pEndButtonLayer->setPosition(220.0f, 10.0f);
}

void C_MainBottom_Menu::setBottomItemsVisible()
{
	m_vecSpritesList.at(0)->setVisible(true);
	m_vecButtonsList.at(S_KeyStore::nMenuKey - 1)->setVisible(true);
}