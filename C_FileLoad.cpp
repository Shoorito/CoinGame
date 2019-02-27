#include "C_FileLoad.h"

C_FileLoad * C_FileLoad::create(const std::string & strFileName)
{
	if (strFileName == "")
	{
		return nullptr;
	}

	C_FileLoad* pFile = new(std::nothrow) C_FileLoad();

	pFile->init();
	pFile->setTargetFile(strFileName);
	pFile->setFileInfo();

	return pFile;
}

void C_FileLoad::init()
{
	m_strFileName = "";
	m_nMaxRowNum  = 0;
	m_fUsedFile   = std::fstream("");
}

bool C_FileLoad::setTargetFile(const std::string & strFileName)
{
	if (strFileName == "")
	{
		return false;
	}

	m_strFileName = strFileName;

	m_fUsedFile.close();
	m_fUsedFile.open(m_strFileName);

	return true;
}

std::string C_FileLoad::getLineInfo(const int nRowNum)
{
	std::string strResult("");

	if (nRowNum < 0)
	{
		return "";
	}

	strResult = m_arDataList.at(nRowNum);

	return strResult;
}

bool C_FileLoad::setFileInfo()
{
	std::string strLineText("");

	if (!isFileOpen())
	{
		return false;
	}

	while (!isEof())
	{
		strLineText = getLineText();

		if (strLineText != "")
		{
			m_arDataList.push_back(strLineText);
		}
	}

	m_nMaxRowNum = m_arDataList.size();

	return true;
}

std::string C_FileLoad::getLineText()
{
	std::string strLineContents("");

	if (!isFileOpen())
	{
		return "";
	}

	std::getline(strLineContents, '\n');

	return strLineContents;
}

void C_FileLoad::release()
{
	m_fUsedFile.close();

	m_fUsedFile = std::fstream("");
	m_strFileName = "";
	m_nMaxRowNum = 0;
}