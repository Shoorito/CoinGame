#include "Layer_Management.h"

std::map<std::string, Layer*>* C_Layer_Management::m_arLayerList;

void C_Layer_Management::init()
{
	m_arLayerList = new(std::nothrow) std::map<std::string, Layer*>{};
}

Layer* C_Layer_Management::createLayer(const std::string strName)
{
	Layer* pLayer(nullptr);

	pLayer = Layer::create();

	m_arLayerList->insert(std::make_pair(strName, pLayer));

	CCLOG("CALL_CREATE_LAYER");

	return pLayer;
}

Layer * C_Layer_Management::createColorLayer(const std::string & strName, Color4B colorType)
{
	Layer* pLayer(nullptr);

	pLayer = LayerColor::create(colorType);

	m_arLayerList->insert(std::make_pair(strName, pLayer));

	CCLOG("CALL_CREATE_LAYER");

	return pLayer;
}

Layer * C_Layer_Management::getLayer(const std::string strName)
{
	std::map<std::string, Layer*>::iterator iterSearch{};

	iterSearch = m_arLayerList->find(strName);

	if (iterSearch != m_arLayerList->end())
	{
		return (Layer*)(iterSearch->second);
	}

	return nullptr;
}

void C_Layer_Management::release()
{
	delete m_arLayerList;
}