#pragma once

#include "cocos2d.h"
#include "C_FNode.h"

USING_NS_CC;

class C_ItemManagement
{
public:
	static C_ItemManagement* create();
	static C_ItemManagement* getInstance();
public:
	virtual Sprite* createItem(const std::string& strRoute, C_FNode* pTargetNode);
	virtual void setInfoList(const int nUseType, const int nMenuType, std::vector<C_FNode*>& vecResult);
	virtual void setItemsList(const std::vector<C_FNode*>& vecInfo, std::vector<Sprite*>& vecResult, const int nLength);
	virtual void addChildItems(const std::vector<Sprite*>& vecList, const int nLength, Layer* pParent);
private:
	static C_ItemManagement* m_pMyPointer;
private:
	C_ItemManagement() {};
	~C_ItemManagement() {};
	C_ItemManagement(C_ItemManagement&) = delete;
	C_ItemManagement& operator=(C_ItemManagement&) = delete;
};