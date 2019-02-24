#pragma once
#include <iostream>

struct S_State_Range
{
public:
	static S_State_Range* create(const int nMinNum, const int nMaxNum);
private:
	virtual inline void init()
	{
		m_nMin = 0;
		m_nMax = 0;
	}
public:
	virtual inline void setRange(const int nMin, const int nMax)
	{
		m_nMin = nMin;
		m_nMax = nMax;
	}
	virtual inline int getMin() { return m_nMin; }
	virtual inline int getMax() { return m_nMax; }
public:
	virtual void release();
private:
	int m_nMin;
	int m_nMax;
private:
	S_State_Range() {};
	S_State_Range(S_State_Range&) = delete;
	S_State_Range operator=(S_State_Range&) = delete;
	virtual ~S_State_Range() {};
};
