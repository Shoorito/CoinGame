#pragma once
#include <string>
#include "EnumClassList.h"

struct S_KeyStore
{
	static void initKey();

	static int nMenuKey;
	static std::string strBasedScene;
	static std::string strSectionAreaName;
	static std::string strBodyAreaName;
	static std::string arUseType[(int)E_IMG_TYPE::E_MAX];
	static std::string arUseCoinName[(int)E_COIN::E_MAX];
	static std::string arUseSubName[(int)E_COIN::E_MAX];
};