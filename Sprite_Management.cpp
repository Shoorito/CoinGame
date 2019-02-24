#include "Sprite_Management.h"

std::map<std::string, Sprite*>* C_Sprite_Management::m_arSpriteList;

void C_Sprite_Management::init()
{
	m_arSpriteList = new(std::nothrow) std::map<std::string, Sprite*>{};
}

Sprite * C_Sprite_Management::createSprite(const std::string strRoute, const std::string strName, const std::string strTagName)
{
	Sprite* pSprite(nullptr);

	pSprite = Sprite::create(strRoute + strName + ".png");

	pSprite->setVisible(false);

	m_arSpriteList->insert(std::make_pair(strTagName, pSprite));

	return pSprite;
}

Sprite * C_Sprite_Management::getSprite(const std::string strTagName)
{
	std::map<std::string, Sprite*>::iterator iterSearch{};

	iterSearch = m_arSpriteList->find(strTagName);

	if (iterSearch != m_arSpriteList->end())
	{
		return (Sprite*)(iterSearch->second);
	}

	return nullptr;
}

void C_Sprite_Management::release()
{
	delete m_arSpriteList;
}
