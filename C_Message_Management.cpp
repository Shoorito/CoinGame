#include "C_Message_Management.h"
#include "Scene_Manager.h"
#include "EnumClassList.h"
#include "Korean_UTF8.h"

C_Window_Management * C_Window_Management::m_pMyPointer = nullptr;

C_Window_Management * C_Window_Management::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Window_Management();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_Window_Management::setEnabledWindow(E_WINDOW eType, const std::string& strTitle, const std::string& strSub)
{
	C_Message_Window* pWindow(nullptr);

	pWindow = m_arWindow[(int)eType];

	pWindow->setEnabledWindow(true);
	pWindow->setWindowType((int)eType);
	pWindow->setTitle(strTitle);
	pWindow->setSubTitle(strSub);
}

void C_Window_Management::setEnabledTrade(E_WINDOW eType, const bool isTrade, const int nType)
{
	C_Message_Window* pWindow(nullptr);

	pWindow = m_arWindow[(int)eType];

	pWindow->setEnabledTrade(isTrade, nType);
}

void C_Window_Management::init()
{
}

void C_Window_Management::mainBoard()
{
	presetWindow();
	addChildList();
}

void C_Window_Management::addChildList()
{
	C_Scene_Manager* pManager(nullptr);
	Scene* pScene(nullptr);

	pManager = C_Scene_Manager::getInstance();

	pScene = pManager->getScene();

	for (int nListNum((int)E_WINDOW::E_ONLY_OK); nListNum < (int)E_WINDOW::E_MAX; nListNum++)
	{
		Layer* pLayer(nullptr);

		pLayer = m_arWindow[nListNum]->getMainLayer();

		pScene->addChild(pLayer);
	}
}

void C_Window_Management::presetWindow()
{
	m_arWindow[(int)E_WINDOW::E_NONE]	 = nullptr;
	m_arWindow[(int)E_WINDOW::E_ONLY_OK] = C_Message_Window::create();
	m_arWindow[(int)E_WINDOW::E_SELECT]  = C_Message_Window::create();

	for (int nListNum((int)E_WINDOW::E_ONLY_OK); nListNum < (int)E_WINDOW::E_MAX; nListNum++)
	{
		m_arWindow[nListNum]->setEnabledWindow(false);
	}
}
