#pragma once

#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;

class C_Sprite_Management
{
public:
	static	void	init();
	static	Sprite*	createSprite(const std::string strRoute, const std::string strName, const std::string strTagName);
	static	Sprite*	getSprite(const std::string strTagName);
	static	void	release();
private:
	static	std::map<std::string, Sprite*>* m_arSpriteList;
private:
	C_Sprite_Management() = delete;
	C_Sprite_Management(C_Sprite_Management&) = delete;
	C_Sprite_Management operator=(C_Sprite_Management&) = delete;
};