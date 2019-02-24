#pragma once
#include "cocos2d.h"
#include "ShareKey.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "EventManager.h"
#include "C_FNode.h"
#include <vector>

USING_NS_CC;

enum class E_TopMenuItem
{
	E_NONE = 0,
	E_SIDEMENU = 1,
	E_SEARCH = 2
};

class C_MainTop_Menu
{
public:
	static C_MainTop_Menu* create();
private:
	C_MainTop_Menu() {};
	~C_MainTop_Menu(){};
private:
	virtual void init();
	virtual bool mainBoard();
public:
	virtual inline void releaseTemp() {}
private:
	virtual void setItemsCount();
	virtual void createTouchEvent();
	virtual void createSpriteItems();
	virtual void createButtonItems();
	virtual void addChildScene();
private:
	virtual inline void createTopLayer() { m_pTopLayer = C_Layer_Management::createLayer("TopItemsLayer"); }
	virtual inline void setSelectPastValue() { m_nSelectPast = S_KeyStore::nMenuKey; }
private:
	virtual bool touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	virtual void setFileRoute();
	virtual void setTopItemsPosition();
	virtual void setTopItemsAnchor();
	virtual void setTopItemsScale();
	virtual void setTopItemsVisible();
private:
	virtual void callTitleEvent();
	virtual void setupTitle();
private:
	int m_nSpriteCount;
	int m_nButtonCount;
	int	m_nSelectPast;
private:
	std::string	m_strFileRoute;
private:
	std::vector<C_FNode*> m_vecSpritesInfo{};
	std::vector<C_FNode*> m_vecButtonsInfo{};
	std::vector<Sprite*> m_vecSpritesList {};
	std::vector<Sprite*> m_vecButtonsList {};
private:
	Layer*	 m_pTopLayer;
private:
	static C_MainTop_Menu* m_pMyPointer;
};