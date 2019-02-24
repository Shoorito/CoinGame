#pragma once
#include "cocos2d.h"
#include "C_FNode.h"
#include "ClippingNode_Management.h"
#include "EnumClassList.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class C_MainBody_Menu
{
public:
	static C_MainBody_Menu* create();
	static inline C_MainBody_Menu* getInstance() { return m_pMyPointer; }
private:
			C_MainBody_Menu() {};
	virtual ~C_MainBody_Menu(){};
private:
	virtual void init();
	virtual bool mainBoard();
public:
	virtual void releaseTemp();
	virtual inline Vec2 getBasedPosition() { return m_pBodyClipingNode->getPosition(); }
private:
	virtual void createBodyLayer();
private:
	virtual void createUseItems();
	virtual void createSpriteItems();
	virtual void createButtonItems();
	virtual void addChildScene();
private:
	virtual void setPastSelectedMenu();
	virtual void presetLayerOption();
	virtual void setBodyItemsCount();
	virtual void setBodyItemsRoute();
	virtual void setBodyItemsPosition();
	virtual void setBodyItemsScale();
	virtual void setBodyItemsAnchor();
	virtual void setBodyItemsVisible();
private:
	virtual void setNewsEvent(const bool isEnabled);
	virtual void setMarketEvent(const bool isEnabled);
	virtual void setHistoryEvent(const bool isEnabled);
	virtual void setWorldEvent(const bool isEnabled);
	virtual void setMypageEvent(const bool isEnabled);
private:
	virtual void presetMenuLayer();
	virtual void presetClippingNode();
	virtual void presetEventFuncList();
	virtual void callSetup();
	virtual void setupMenuVisible();
private:
	int m_nPastSelected;
	int	m_nSpriteCount;
	int	m_nButtonCount;
	std::string	m_strFileRoute;
private:
	float m_fPastYpos;
	float m_fNowTouchedYpos;
private:
	std::vector<C_FNode*> m_vecSpritesInfo{};
	std::vector<C_FNode*> m_vecButtonsInfo{};
private:
	std::vector<Sprite*>  m_vecSpritesList{};
	std::vector<Sprite*>  m_vecButtonsList{};
private:
	void(C_MainBody_Menu::*m_arEventFunc[(int)E_MENU_TYPE::E_MAX])(const bool isEnabled);
	void(C_MainBody_Menu::*m_pPastFunc)(const bool isEnabled);
private:
	ClippingNode* m_pBodyClipingNode;
private:
	Sprite* m_pClippingTarget;
private:
	Node* m_pActionNode;
private:
	Layer* m_pBodyLayer;
	Layer* m_pPastLayer;
private:
	Rect m_recEventBorder;
private:
	Layer* m_arMenuLayer[(int)E_MENU_TYPE::E_MAX]{};
private:
	static C_MainBody_Menu* m_pMyPointer;
};