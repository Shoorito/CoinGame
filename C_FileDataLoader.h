#pragma once

#include "cocos2d.h"
#include "EnumClassList.h"

USING_NS_CC;

class C_DataLoader
{
public:
	static C_DataLoader* create();
public:
	static inline C_DataLoader* getInstance() { return m_pMyPointer; };
public:
	virtual void release();
private:
	virtual void init();
	virtual void mainBoard();
private:
	virtual void loadFileData();
	virtual void extractLine(const std::string& strOrigin, const int nDataNum, std::string* arResult);
	virtual void extractData(std::string** arData);
	virtual void presetData();
private:
	virtual bool isBlank(const char cTarget, const char * arFilterList, const int nFilterSize);
	virtual int  detectSyntax(const std::string& strSyntax, const int nType);
private:
	virtual void presetBufferSize();
	virtual void setSyntaxCount();
	virtual void setMarkList();
private:
	virtual std::string getReadText(const std::string& strReadText, int& nPos, const int nMaxLength);
private:
	C_DataLoader() {};
	~C_DataLoader() {};
	C_DataLoader(const C_DataLoader&) = delete;
	C_DataLoader& operator=(const C_DataLoader&) = delete;
private:
	std::string m_arFileData[(int)E_FILE_TYPE::E_MAX]{};
private:
	std::vector<std::string*> m_vecCoinInfo{};
	std::vector<std::string*> m_vecPlayerInfo{};
private:
	static C_DataLoader* m_pMyPointer;
private:
	char m_arFilter[(int)E_MARK_LIST::E_MARK_MAX]{};
private:
	int m_arMaxNumList[(int)E_FILE_TYPE::E_MAX]{};
private:
	int m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_MAX]{};
private:
	int m_nFileCount;
};