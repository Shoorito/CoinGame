#pragma once
#include "cocos2d.h"
#include "C_FNode.h"

USING_NS_CC;

class C_MainBottom_Menu
{
public:
	static C_MainBottom_Menu* create();
	static C_MainBottom_Menu* getInstance();
	virtual void releaseTemp();
public:
	virtual void setEnabled(const bool isEnabled);
private:
			C_MainBottom_Menu()  {};
	virtual ~C_MainBottom_Menu() {};
private:
	virtual void init();
	virtual void createTouchEvent();
	virtual bool mainBoard();
private:
	virtual bool		touchOnBegan	(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool		touchOnCanceled	(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool		touchOnEnded	(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool		touchOnMoved	(Touch* pTouch, Event* pUnUsedEvent);
private:
	virtual void		createSpriteItems();
	virtual void		createButtonItems();
	virtual void		setBottomLayer();
	virtual void		setBottomPastSelectValue();
	virtual void		setFileRoute();
	virtual void		setBottomItemsNum();
	virtual void		setBottomItemsPos();
	virtual void		setBottomItemsAnchor();
	virtual void		setBottomItemsScale();
	virtual void		setBottomItemsVisible();
private:
	static C_MainBottom_Menu* m_pInstance;
private:
	Layer* m_pBottomLayer;
	Layer* m_pEndButtonLayer;
private:
	EventListener* m_pTouchEvent;
private:
	int	m_nPastSprite;
	int m_nSpriteNum;
	int m_nButtonNum;
private:
	std::string m_strFileRoute;
private:
	std::vector<C_FNode*> m_vecSpritesInfo{};
	std::vector<C_FNode*> m_vecButtonsInfo{};
private:
	std::vector<Sprite*> m_vecSpritesList{};
	std::vector<Sprite*> m_vecButtonsList{};
};