#include "ClippingNode_Management.h"

std::map<std::string, ClippingNode*>* C_ClippingNode_Management::m_arClippingList;

void C_ClippingNode_Management::init()
{
	m_arClippingList = new(std::nothrow) std::map<std::string, ClippingNode*>{};
}

ClippingNode * C_ClippingNode_Management::create(const std::string strTagName, Sprite* pSizeTarget)
{
	ClippingNode* pClip		(nullptr);
	Sprite*		  pSprite	(nullptr);

	pSprite = pSizeTarget;

	pClip = ClippingNode::create();
	
	pClip->setInverted(false);
	pClip->setStencil(pSprite);

	m_arClippingList->insert(std::make_pair(strTagName, pClip));

	return pClip;
}

ClippingNode * C_ClippingNode_Management::getNode(const std::string strTagName)
{
	std::map<std::string, ClippingNode*>::iterator iterSearch{};

	iterSearch = m_arClippingList->find(strTagName);

	if (iterSearch != m_arClippingList->end())
	{
		return (ClippingNode*)(iterSearch->second);
	}

	return nullptr;
}

void C_ClippingNode_Management::release()
{
	delete m_arClippingList;
}
