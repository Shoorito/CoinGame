#include "C_News_Menu.h"
#include "EventManager.h"
#include "Layer_Management.h"
#include "NewsSectionManagement.h"
#include "C_TPriceRankup.h"
#include "C_RateRankup.h"

C_News_Management* C_News_Management::m_pMyPointer = nullptr;

C_News_Management * C_News_Management::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_News_Management();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_News_Management::release()
{
}

void C_News_Management::setEventEnabled(const bool isEnabled)
{
	C_Event_Manager::getTagName("News_Section_Event")->setEnabled(isEnabled);
}

void C_News_Management::init()
{
	m_pMenuLayer = nullptr;
	m_pVolumeChart = nullptr;
}

void C_News_Management::mainBoard()
{
	createNewsLayer();
	loadNewsMenu();
	presetNewsLayer();
	presetNewsPosition();
	addChildLayer();
}

void C_News_Management::createNewsLayer()
{
	m_pMenuLayer = C_Layer_Management::createLayer("News_Menu_Layer");
}

void C_News_Management::loadNewsMenu()
{
	C_News_Section* pSection(nullptr);
	C_TPrice_Rankup* pRankupTPrice(nullptr);
	C_Rate_Rankup* pRateRankup(nullptr);

	pSection		= C_News_Section::create();
	pRankupTPrice	= C_TPrice_Rankup::create();
	pRateRankup		= C_Rate_Rankup::create();
}

void C_News_Management::presetNewsLayer()
{
	m_pSectionLayer = C_News_Section::getInstance()->getSectionLayer();
	m_pVolumeChart  = C_TPrice_Rankup::getInstance()->getMainLayer();
	m_pRateChart    = C_Rate_Rankup::getInstance()->getMainLayer();
}

void C_News_Management::presetNewsPosition()
{
	m_pVolumeChart->setPosition(0.0f, 18.0f);
	m_pRateChart->setPosition(m_pVolumeChart->getPosition() + Point(0.0f, -215.0f));
}

void C_News_Management::addChildLayer()
{
	m_pMenuLayer->addChild(m_pSectionLayer);
	m_pMenuLayer->addChild(m_pVolumeChart);
	m_pMenuLayer->addChild(m_pRateChart);
}
