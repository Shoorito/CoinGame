#pragma once

enum class E_IMG_TYPE
{
	E_NONE	 = 0,
	E_SPRITE = 1,
	E_BUTTON = 2,
	E_ROUTE	 = 3,
	E_COIN	 = 4,
	E_MAX	 = 5
};

enum class E_DATA
{
	E_NONE = 0,
	E_FIRST = 1,
	E_SECOND = 2,
	E_THIRD = 3,
	E_MAX = 4
};

enum class E_PLAYER
{
	E_NONE = 0,
	E_MONEY = 1,
	E_STD = 2,
	E_EAT = 3,
	E_ATM = 4,
	E_VLN = 5,
	E_SDP = 6,
	E_CMT = 7,
	E_TCD = 8,
	E_ECD = 9,
	E_TPT = 10,
	E_DSC = 11,
	E_MAX = 12
};

enum class E_WINDOW_TYPE
{
	E_NONE = 0,
	E_SUBMIT = 1,
	E_SELECT = 2,
	E_MAX = 3
};

enum class E_COIN
{
	E_NONE = 0,
	E_STANDARD = 1,
	E_EATERIUM = 2,
	E_ATOM = 3,
	E_VILLAIN = 4,
	E_STANDARD_PRIME = 5,
	E_COMMENT = 6,
	E_TOUR_CREDIT = 7,
	E_EDIT_CREDIT = 8,
	E_TYPHOON_TOKEN = 9,
	E_DISCREET = 10,
	E_MAX = 11
};

enum class E_RANK_TYPE
{
	E_NONE = 0,
	E_FIRST = 1,
	E_SECOND = 2,
	E_THIRD = 3,
	E_MAX = 4
};

enum class E_RETURN_TYPE
{
	E_NONE = 0,
	E_ERROR	= -1,
	E_SUCCESS = 1
};

enum class E_MARK_LIST
{
	E_NONE = 0,
	E_BLANK = 1,
	E_TAB = 2,
	E_DQM = 3,
	E_MARK_MAX = 4
};

enum class E_FILE_SYNTAX
{
	E_NONE  = 0,
	E_TYPE	= 1,
	E_NAME	= 2,
	E_VALUE_TYPE = 3,
	E_VALUE = 4,
	E_MAX	= 5
};

enum class E_VALUE_LIST
{
	E_NONE = 0,
	E_TAG = 1,
	E_VALUE = 2,
	E_MAX = 3
};

enum class E_SYNTAX_TYPE
{
	E_NONE =  0,
	E_TYPE =  1,
	E_VALUE = 2,
	E_MAX =	  3
};

enum class E_COIN_SYNTAX
{
	E_NONE	 = 0,
	E_NAME	 = 1,
	E_PRICE	 = 2,
	E_TPRICE = 3,
	E_RATE	 = 4,
	E_MAX	 = 5
};

enum class E_BOX_TYPE
{
	E_NONE = 0,
	E_BUY_PRICE = 1,
	E_SELL_PRICE = 2,
	E_BUY_COUNT = 3,
	E_SELL_COUNT = 4,
	E_MAX = 5
};

enum class E_TRADE
{
	E_NONE = 0,
	E_BUY = 1,
	E_SELL = 2,
	E_MAX = 3
};

enum class E_FILE_TYPE
{
	E_NONE = 0,
	E_COIN = 1,
	E_PLAYER = 2,
	E_MAX = 3
};

enum class E_MENU_TYPE
{
	E_NONE = 0,
	E_NEWS = 1,
	E_MARKET = 2,
	E_HISTORY = 3,
	E_WORLD_NEWS = 4,
	E_MYPAGE = 5,
	E_MAX = 6
};

enum class E_PROFIT
{
	E_MINUS = 0,
	E_STATE = 1,
	E_PLUS = 2,
	E_MAX = 3
};

enum class E_ADD_LIST
{
	E_NONE = 0,
	E_UNDER_1000 = 1,
	E_UNDER_10000 = 2,
	E_UNDER_100000 = 3,
	E_UNDER_1000000 = 4,
	E_UNDER_10000000 = 5,
	E_UNDER_100000000 = 6,
	E_MAX = 7
};