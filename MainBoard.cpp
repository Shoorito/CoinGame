#include "MainBoard.h"

void C_MainScene::init()
{
	
}

bool C_MainScene::SceneMain()
{
	if (!C_Scene_Manager::getInstance()->getScene())
	{
		return false;
	}

	C_History_Menu*		pHistory	(nullptr);
	C_Calculator*		pCalculator (nullptr);
	C_Trade_Menu*		pTradeMenu	(nullptr);
	C_ResManagement*	pManager	(nullptr);
	C_CoinManagement*	pCoinManager(nullptr);
	C_ItemManagement*	pItemManager(nullptr);
	C_MainBottom_Menu*	pBottomMenu	(nullptr);
	C_MainTop_Menu*		pTopMenu	(nullptr);
	C_MainBody_Menu*	pBodyMenu	(nullptr);
	C_Share_Management* pShareManager(nullptr);
	C_Window_Management*pWindowManager(nullptr);
	C_Player_Management* pPlayerManager(nullptr);

	pManager		= C_ResManagement::create("ParentFile.txt");
	pItemManager	= C_ItemManagement::create();
	pCoinManager	= C_CoinManagement::create();
	pShareManager	= C_Share_Management::create();
	pPlayerManager	= C_Player_Management::create();

	pHistory	= C_History_Menu::create();
	pBottomMenu = C_MainBottom_Menu::create();
	pTopMenu	= C_MainTop_Menu::create();
	pBodyMenu	= C_MainBody_Menu::create();
	pTradeMenu	= C_Trade_Menu::create();

	pCalculator = C_Calculator::create();
	pWindowManager = C_Window_Management::create();

	pBottomMenu->releaseTemp();
	pTopMenu->releaseTemp();
	pBodyMenu->releaseTemp();
	
    return true;
}