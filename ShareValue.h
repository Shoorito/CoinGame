#pragma once
#include <iostream>
#include "StateRange.h"
#include "EnumClassList.h"

class C_Share_Management
{
public:
	static C_Share_Management* create();
	static inline C_Share_Management* getInstance() { return m_pMyPointer; }
public:
	virtual void setProfit(const int nType, const int nMinus, const int nState);
public:
	virtual inline int	 getAddNum(const int nType)		 { return m_arAddList[nType]; }
	virtual inline int	 getBorderNum(const int nType)	 { return m_arBorderList[nType]; }
	virtual inline int	 getMinusBorder(const int nType) { return m_arMinusBorder[nType]; }
	virtual inline int	 getStateBorder(const int nType) { return m_arStateBorder[nType]; }
	virtual inline int	 getProfitNum(const int nType)	 { return m_arProfitList[nType]; }
	virtual inline int	 getWorstBorder(const int nType) { return m_arWorstBorder[nType]; }
public:
	virtual inline S_State_Range* getRange(const int nType) { return m_arRangeList[nType]; }
private:
	virtual void init();
	virtual void mainBoard();
	virtual void release();
private:
	virtual void presetAddList();
	virtual void presetBorderPrice();
	virtual void presetRange();
	virtual void presetProfit();
	virtual void presetBorder();
private:
	static C_Share_Management* m_pMyPointer;
private:
	int m_arAddList		[(int)E_ADD_LIST::E_MAX]{};
	int m_arBorderList	[(int)E_ADD_LIST::E_MAX]{};
	int m_arMinusBorder	[(int)E_COIN::E_MAX]{};
	int m_arStateBorder	[(int)E_COIN::E_MAX]{};
	int m_arProfitList	[(int)E_PROFIT::E_MAX]{};
	int m_arWorstBorder [(int)E_COIN::E_MAX]{};
private:
	S_State_Range* m_arRangeList[(int)E_COIN::E_MAX]{};
private:
	 C_Share_Management() {};
	~C_Share_Management() {};
	 C_Share_Management(C_Share_Management&)		   = delete;
	 C_Share_Management operator=(C_Share_Management&) = delete;
};