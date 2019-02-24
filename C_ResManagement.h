#pragma once
#include "C_FileLoad.h"
#include "C_FNode.h"

class C_ResManagement
{
public:
	static C_ResManagement* create(const std::string& strParentFile);
public:
	static inline C_ResManagement* getInstance() { return m_pMyPointer; };
public:
	virtual void release();
public:
	virtual std::string getRoute(int nMenuType);
	virtual bool getList(const std::string& strType, const int nMenuType, std::vector<C_FNode*>& vecList);
	virtual int  getUseFileCount();
private:
	virtual bool mainBoard();
	virtual bool createParentFile(const std::string& strParentFile);
private:
	virtual bool setFilesName();
private:
	virtual bool isBlank(const char cTarget, const char * arFilterList, const int nFilterSize);
	virtual bool checkSyntax(const std::string arCheck[(int)E_SYNTAX_TYPE::E_MAX]);
	virtual bool setNode(const std::string& strDetectText, const int nFileType);
private:
	virtual int  detectSyntax(const std::string& strSyntax, std::string* arResult);
private:
	virtual void setFilesCount();
	virtual void createUseFiles();
	virtual void createFileBuffer();
	virtual void createCountBuffer();
	virtual void setMenuItemsCount();
	virtual void setSyntaxCount();
	virtual void setAllItemsInfo();
	virtual void init();
	virtual void setTypes();
	virtual void setMarkList();
private:
	virtual std::string getReadText(const std::string& strReadText, int& nPos, const int nMaxLength);
private:
	C_ResManagement() {};
	~C_ResManagement(){};
	C_ResManagement(const C_ResManagement&) = delete;
	C_ResManagement& operator=(const C_ResManagement&) = delete;
private:
	std::string m_arImgType[(int)E_IMG_TYPE::E_MAX]{};
	std::string m_arValueType[(int)E_VALUE_LIST::E_MAX]{};
private:
	std::string* m_arParentInfo;
	std::string* m_arSyntaxType[(int)E_SYNTAX_TYPE::E_MAX]{};
private:
	C_FileLoad*  m_pParentFile;
	C_FileLoad** m_arUseFiles;
private:
	std::vector<C_FNode*> m_arNodeList[(int)E_FILE_TYPE::E_MAX]{};
private:
	static C_ResManagement* m_pMyPointer;
private:
	char m_arFilter[(int)E_MARK_LIST::E_MARK_MAX]{};
private:
	int* m_arMaxNumList;
private:
	int m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_MAX]{};
private:
	int m_nFileCount;
};

