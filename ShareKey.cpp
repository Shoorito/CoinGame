#include "ShareKey.h"

int S_KeyStore::nMenuKey					= 0;
std::string S_KeyStore::strBasedScene		= "";
std::string S_KeyStore::strBodyAreaName		= "";
std::string S_KeyStore::strSectionAreaName	= "";
std::string	S_KeyStore::arUseType[(int)E_IMG_TYPE::E_MAX]{};
std::string S_KeyStore::arUseCoinName[(int)E_COIN::E_MAX]{};
std::string S_KeyStore::arUseSubName[(int)E_COIN::E_MAX]{};

void S_KeyStore::initKey()
{
	nMenuKey = (int)E_MENU_TYPE::E_NEWS;
	strBasedScene		= "BasedScene";
	strBodyAreaName		= "BodyAreaLayer";
	strSectionAreaName  = "SectionAreaLayer";

	arUseType[(int)E_IMG_TYPE::E_NONE]		= "None";
	arUseType[(int)E_IMG_TYPE::E_SPRITE]	= "Sprite";
	arUseType[(int)E_IMG_TYPE::E_BUTTON]	= "Button";
	arUseType[(int)E_IMG_TYPE::E_ROUTE]		= "Route";

	arUseCoinName[(int)E_COIN::E_NONE]				= "None";
	arUseCoinName[(int)E_COIN::E_STANDARD]			= "���Ĵٵ�����(SDC)";
	arUseCoinName[(int)E_COIN::E_EATERIUM]			= "���͸���(ETR)";
	arUseCoinName[(int)E_COIN::E_ATOM]				= "����(ATM)";
	arUseCoinName[(int)E_COIN::E_VILLAIN]			= "����(VLN)";
	arUseCoinName[(int)E_COIN::E_STANDARD_PRIME]	= "���Ĵٵ�������(SDP)";
	arUseCoinName[(int)E_COIN::E_COMMENT]			= "�ڸ�Ʈ(CMT)";
	arUseCoinName[(int)E_COIN::E_TOUR_CREDIT]		= "����ũ����(TCD)";
	arUseCoinName[(int)E_COIN::E_EDIT_CREDIT]		= "����ũ����(ECD)";
	arUseCoinName[(int)E_COIN::E_TYPHOON_TOKEN]		= "Ÿ��Ǭ��ū(TPT)";
	arUseCoinName[(int)E_COIN::E_DISCREET]			= "���ũ��(DSC)";

	arUseSubName[(int)E_COIN::E_NONE] = "None";
	arUseSubName[(int)E_COIN::E_STANDARD] = "STD";
	arUseSubName[(int)E_COIN::E_EATERIUM] = "EAT";
	arUseSubName[(int)E_COIN::E_ATOM] = "ATM";
	arUseSubName[(int)E_COIN::E_VILLAIN] = "VLN";
	arUseSubName[(int)E_COIN::E_STANDARD_PRIME] = "SDP";
	arUseSubName[(int)E_COIN::E_COMMENT] = "CMT";
	arUseSubName[(int)E_COIN::E_TOUR_CREDIT] = "TCD";
	arUseSubName[(int)E_COIN::E_EDIT_CREDIT] = "ECD";
	arUseSubName[(int)E_COIN::E_TYPHOON_TOKEN] = "TPT";
	arUseSubName[(int)E_COIN::E_DISCREET] = "DSC";
}
