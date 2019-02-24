#include "C_ItemManagement.h"
#include "Sprite_Management.h"
#include "C_ResManagement.h"
#include "ShareKey.h"

C_ItemManagement* C_ItemManagement::m_pMyPointer = nullptr;

C_ItemManagement * C_ItemManagement::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}
	
	C_ItemManagement* pManager(nullptr);
	
	pManager = new(std::nothrow) C_ItemManagement();

	m_pMyPointer = pManager;

	return pManager;
}

C_ItemManagement * C_ItemManagement::getInstance()
{
	return m_pMyPointer;
}

Sprite* C_ItemManagement::createItem(const std::string& strRoute, C_FNode* pTargetNode)
{
	std::string strItemName("");
	std::string strItemTag("");
	Sprite* pSprite(nullptr);

	strItemName = pTargetNode->getName();
	strItemTag  = pTargetNode->getTagName();

	pSprite = C_Sprite_Management::createSprite(strRoute, strItemName, strItemTag);

	return pSprite;
}

void C_ItemManagement::setInfoList(const int nUseType, const int nMenuType, std::vector<C_FNode*>& vecResult)
{
	C_ResManagement* pTarget(nullptr);

	pTarget = C_ResManagement::getInstance();

	pTarget->getList(S_KeyStore::arUseType[nUseType], nMenuType, vecResult);
}

void C_ItemManagement::setItemsList(const std::vector<C_FNode*>& vecInfo, std::vector<Sprite*>& vecResult, const int nLength)
{
	std::string strTagName("");

	for (int nListNum(0); nListNum < nLength; nListNum++)
	{
		strTagName = vecInfo.at(nListNum)->getTagName();

		vecResult.push_back(C_Sprite_Management::getSprite(strTagName));
	}
}

void C_ItemManagement::addChildItems(const std::vector<Sprite*>& vecList, const int nLength, Layer* pParent)
{
	Sprite*	pSprite(nullptr);

	for (int nItemNum(0); nItemNum < nLength; nItemNum++)
	{
		pSprite = vecList.at(nItemNum);

		pParent->addChild(pSprite);
	}
}