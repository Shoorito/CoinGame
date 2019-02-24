#pragma once

#include "cocos2d.h"
#include "C_FNode.h"
#include <vector>

USING_NS_CC;

class C_News_Section
{
public:
	static C_News_Section* create();
	static  inline C_News_Section* getInstance() { return m_pMyPointer; }
	virtual inline Layer* getSectionLayer()		 { return m_pSectionLayer; }
private:
	virtual void init();
	virtual bool mainBoard();
	virtual void releaseOfTemp();
	virtual void setFileRoute();
	virtual void setItemsCount();
	virtual void createSpriteItems();
	virtual void createButtonItems();
	virtual void createStencilNode();
	virtual void createBorderGround();
	virtual void createSectionLayers();
	virtual void setBorderLine();
	virtual void setBasedSize();
private:
	inline virtual void	createPosList() { m_arXposList = new(std::nothrow) float[m_nSpriteCount]{}; }
private:
	virtual void		createTouchEvent();
	virtual bool		touchOnBegan(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool		touchOnCanceled(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool		touchOnEnded(Touch* pTouch, Event* pUnUsedEvent);
	virtual bool		touchOnMoved(Touch* pTouch, Event* pUnUsedEvent);
private:
	inline virtual void	setFirstSection()
	{
		m_pFirstSection = m_vecSpritesList.at(0);
	}
	inline virtual void setPastButton()
	{
		m_pPastButton = m_vecButtonsList.at(m_nButtonCount / 2);
	}
	inline virtual void setSectionPosition()
	{
		m_pClippingNode->setPosition(0.0f, 242.5f);
	}
	inline virtual void	setButtonsLayerPosition()
	{
		m_pButtonsLayer->setPosition(-17.5f, 0.0f);
	}
private:
	virtual void		setPointList();
	virtual void		setSpritesPosition();
	virtual void		setButtonsPosition();
	virtual void		setItemsAnchor();
	virtual void		setItemsScale();
	virtual void		setItemsVisible();
private:
	virtual void		callSetup();
	virtual void		setAddchild();
	virtual void		setupChainItems();
private:
	C_News_Section() {};
	virtual ~C_News_Section() {};
private:
	Sprite*	m_pFirstSection;
	Sprite* m_pBackground;
	Sprite*	m_pPastButton;
	Sprite*	m_pStencil;
private:
	Node* m_pActionNode;
private:
	std::string	m_strFileRoute;
private:
	std::vector<C_FNode*> m_vecSpritesInfo{};
	std::vector<C_FNode*> m_vecButtonsInfo{};
	std::vector<Sprite*>  m_vecSpritesList{};
	std::vector<Sprite*>  m_vecButtonsList{};
private:
	ClippingNode* m_pClippingNode;
private:
	static C_News_Section* m_pMyPointer;
private:
	Layer* m_pButtonsLayer;
	Layer* m_pSpritesLayer;
	Layer* m_pItemsLayer;
	Layer* m_pSectionLayer;
private:
	Rect m_recEventBorder;
private:
	int	m_nSpriteCount;
	int m_nButtonCount;
	int	m_nNowSelectNum;
private:
	float m_fPastXpos;
	float m_fNowTouchedXpos;
	float m_fSection_width;
	float m_fSection_height;
private:
	float* m_arXposList;
};