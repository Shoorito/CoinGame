#pragma once
#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;

class C_ClippingNode_Management
{
public:
	static void init();
	static ClippingNode* create(const std::string strTagName, Sprite* pSizeTarget);
	static ClippingNode* getNode(const std::string strTagName);
	static void release();
private:
	static	std::map<std::string, ClippingNode*>* m_arClippingList;
private:
	C_ClippingNode_Management()										= delete;
	~C_ClippingNode_Management()									= delete;
	C_ClippingNode_Management(C_ClippingNode_Management&)			= delete;
	C_ClippingNode_Management operator=(C_ClippingNode_Management&) = delete;
};