#include "StateRange.h"

S_State_Range * S_State_Range::create(const int nMinNum, const int nMaxNum)
{
	S_State_Range* pRange(nullptr);

	pRange = new(std::nothrow) S_State_Range();

	pRange->init();
	pRange->setRange(nMinNum, nMaxNum);

	return pRange;
}

void S_State_Range::release()
{
}
