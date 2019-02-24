#include "BottomMenuManager.h"
#include "Trade_Bottom_Area.h"
#include "Trade_Top_Area.h"
#include "C_Market_Menu.h"
#include "Scene_Manager.h"
#include "C_Trade_Menu.h"

C_Trade_Menu * C_Trade_Menu::m_pMyPointer = nullptr;

C_Trade_Menu * C_Trade_Menu::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Trade_Menu();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Trade_Menu::setEnabled(const bool isEnabled, const int nCoinType)
{
	C_Trade_Bottom_Menu* pBottomMenu(nullptr);
	C_Trade_Top_Menu* pTopMenu(nullptr);

	if (!isEnabled)
	{
		C_Market_Management::getInstance()->setEventEnabled(!isEnabled);
		C_MainBottom_Menu::getInstance()->setEnabled(!isEnabled);
	}

	pTopMenu = C_Trade_Top_Menu::getInstance();
	pBottomMenu = C_Trade_Bottom_Menu::getInstance();

	pTopMenu->setCoinType(nCoinType);
	pTopMenu->setEnabeld(isEnabled);

	pBottomMenu->setEnabledEvent(isEnabled, nCoinType);

	m_pMainLayer->setVisible(isEnabled);
}

void C_Trade_Menu::init()
{
	m_pMainLayer = nullptr;
	m_pTempSprite = nullptr;
}

void C_Trade_Menu::mainBoard()
{
	createLayer();
	createMenu();

	addChildItems();
}

void C_Trade_Menu::createLayer()
{
	m_pMainLayer = Layer::create();
	m_pTempSprite = Sprite::create("UI_Items/Chart_Temp.png");

	m_pTempSprite->setScale(0.5f);
	m_pTempSprite->setAnchorPoint(Point(0.0f, 0.0f));

	m_pTempSprite->setPosition(0.0f, 410.0f);
}

void C_Trade_Menu::createMenu()
{
	C_Trade_Top_Menu* pTopMenu(nullptr);
	C_Trade_Bottom_Menu* pBottomMenu(nullptr);

	pTopMenu = C_Trade_Top_Menu::create();
	pBottomMenu = C_Trade_Bottom_Menu::create();

	setEnabled(false, (int)E_COIN::E_STANDARD);
}

void C_Trade_Menu::addChildItems()
{
	Scene* pScene(nullptr);
	Layer* pTopLayer(nullptr);
	Layer* pBottomLayer(nullptr);

	pTopLayer = C_Trade_Top_Menu::getInstance()->getLayer();
	pBottomLayer = C_Trade_Bottom_Menu::getInstance()->getLayer();
	pScene = C_Scene_Manager::getInstance()->getScene();

	m_pMainLayer->addChild(pTopLayer);
	m_pMainLayer->addChild(pBottomLayer);
	m_pMainLayer->addChild(m_pTempSprite);

	pScene->addChild(m_pMainLayer);
}
