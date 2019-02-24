#pragma once
#include "cocos2d.h"
#include "C_Stand_Line.h"
#include "EnumClassList.h"

USING_NS_CC;

enum class E_STAND_RANGE
{
	E_NONE = 0,
	E_MIN = 1,
	E_MAX = 6
};

class C_Stand_Trade
{
public:
	static C_Stand_Trade* create();
	static C_Stand_Trade* getInstance() { return m_pMyPointer; }
	virtual inline Layer* getLayer() { return m_pMainLayer; }
public:
	virtual void setEnabled(const bool isEnabled);
	virtual void updateLineSort(const int nType);
	virtual void addList(const int nPrice, const double dlCount, const int nCoinType, const int nTradeType);
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createLayer();
	virtual void createSprite();
	virtual void createLineList();
	virtual void presetPosition();
	virtual void presetScale();
	virtual void addChildItems();
private:
	C_StandLine* m_arLineList[(int)E_COIN::E_MAX][(int)E_STAND_RANGE::E_MAX]{};
private:
	Layer* m_pMainLayer;
private:
	Sprite* m_pTab;
private:
	int m_arLineNum[(int)E_COIN::E_MAX]{};
private:
	static C_Stand_Trade* m_pMyPointer;
private:
	C_Stand_Trade() {}
	virtual ~C_Stand_Trade() {}
	C_Stand_Trade(C_Stand_Trade&) = delete;
	C_Stand_Trade operator=(C_Stand_Trade&) = delete;
};