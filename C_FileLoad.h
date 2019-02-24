#pragma once
#include <string>
#include <fstream>
#include <vector>

class C_FileLoad
{
public:
	static C_FileLoad* create(const std::string& strFileName);
public:
	virtual void init();
	virtual void release();
public:
	virtual bool setTargetFile(const std::string& strFileName);
public:
	virtual std::string getLineInfo(const int nRowNum);
public:
	virtual inline std::string getFileName() { return m_strFileName; }
public:
	virtual inline int getMaxRowNumber() { return m_nMaxRowNum; }
private:
	virtual std::string getLineText();
private:
	virtual inline bool isEof()
	{
		if (m_fUsedFile.eof())
			return true;

		return false;
	}
	virtual inline bool isFileOpen()
	{
		if (m_fUsedFile.is_open())
			return true;

		return false;
	}
private:
	virtual bool setFileInfo();
private:
	int	m_nMaxRowNum;
private:
	std::fstream m_fUsedFile;
private:
	std::string	m_strFileName;
	std::vector<std::string> m_arDataList;
private:
	C_FileLoad() {}
	~C_FileLoad() {}
	C_FileLoad(C_FileLoad&) = delete;
	C_FileLoad& operator=(const C_FileLoad&) = delete;
};

