#pragma once

#include "cocos2d.h"

USING_NS_CC;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

static const std::string UTF8(const std::string& strInvertText);

static const std::string UTF8(const std::string& strInvertText)
{
	std::string strResult("");
	int			nPreInvert(0);
	int			nPostInvert(0);
	wchar_t*	pWideText(nullptr);
	char*		pCharText(nullptr);

	nPreInvert = MultiByteToWideChar(CP_ACP, 0, strInvertText.c_str(), -1, nullptr, 0);

	pWideText = new(std::nothrow) wchar_t[nPreInvert + 1]{};

	MultiByteToWideChar(CP_ACP, 0, strInvertText.c_str(), -1, pWideText, nPreInvert);

	nPostInvert = WideCharToMultiByte(CP_UTF8, 0, pWideText, -1, nullptr, 0, nullptr, nullptr);

	pCharText = new(std::nothrow) char[nPostInvert + 1]{};

	WideCharToMultiByte(CP_UTF8, 0, pWideText, -1, pCharText, nPostInvert, nullptr, nullptr);

	strResult = pCharText;

	delete[] pWideText;
	delete[] pCharText;

	return strResult;
}

#define UTF8PCHAR(string)    UTF8(string).c_str()

#else

#define UTF8(string)    string
#define UTF8PCHAR(string)    string

#endif

