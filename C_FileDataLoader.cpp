#include "C_FileDataLoader.h"

C_DataLoader* C_DataLoader::m_pMyPointer = nullptr;

C_DataLoader * C_DataLoader::create()
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_DataLoader();

	m_pMyPointer->init();
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_DataLoader::init()
{
	m_nFileCount	= 0;
}

void C_DataLoader::release()
{

}

void C_DataLoader::mainBoard()
{
	loadFileData();
}

void C_DataLoader::loadFileData()
{
	FileUtils* pUtil(nullptr);

	pUtil = FileUtils::getInstance();

	m_arFileData[(int)E_FILE_TYPE::E_COIN]	 = pUtil->getStringFromFile("CoinData.txt");
	m_arFileData[(int)E_FILE_TYPE::E_PLAYER] = pUtil->getStringFromFile("PlayerData.txt");
}

void C_DataLoader::extractLine(const std::string& strOrigin, const int nDataNum, std::string* arResult)
{
	bool isSwitch(true);
	int  nMaxLength(0);
	int  nMaxNum(0);
	int  nDataCount(0);
	int  nDataPos(0);

	nMaxLength	= strOrigin.size();
	nMaxNum		= nDataNum;
	nDataCount  = 1;

	while ((nDataPos < nMaxLength) && (nDataCount <= nMaxNum))
	{
		while (isSwitch)
		{
			std::string strResult("");
			char cText('\0');

			cText = strOrigin.at(nDataPos);

			if (cText != '\n')
			{
				strResult += cText;
			}
			else
			{
				arResult[nDataCount] = strResult;
				isSwitch = false;
			}

			nDataPos++;
		}

		nDataCount++;
	}
}

void C_DataLoader::extractData(std::string** arData)
{
	for (int nData ((int)E_FILE_TYPE::E_COIN); nData < (int)E_FILE_TYPE::E_MAX; nData++)
	{
		std::string strOrigin("");

		strOrigin = m_arFileData[nData];

		extractLine(strOrigin, m_arMaxNumList[nData], arData[nData]);
	}
}

void C_DataLoader::presetData()
{
	std::string  arCoinData[(int)E_COIN::E_MAX]{};
	std::string  arPlayerData[(int)E_PLAYER::E_MAX]{};
	std::string* arData[(int)E_FILE_TYPE::E_MAX]{};
	std::string* arResult[(int)E_FILE_TYPE::E_MAX]{};

	arData[(int)E_FILE_TYPE::E_COIN]	= arCoinData;
	arData[(int)E_FILE_TYPE::E_PLAYER]	= arPlayerData;

	extractData(arData);

	for (int nDataType((int)E_FILE_TYPE::E_COIN); nDataType < (int)E_FILE_TYPE::E_MAX; nDataType++)
	{
		for (int nDataNum(1); nDataNum < m_arMaxNumList[nDataType]; nDataNum++)
		{
			detectSyntax(arData[nDataType][nDataNum], )
		}
	}
}

bool C_DataLoader::isBlank(const char cTarget, const char * arFilterList, const int nFilterSize)
{
	for (int nListNum((int)E_MARK_LIST::E_BLANK); nListNum < nFilterSize; nListNum++)
	{
		if (cTarget == arFilterList[nListNum])
		{
			return false;
		}
	}

	return true;
}

bool C_DataLoader::checkSyntax(const std::string arCheck[(int)E_SYNTAX_TYPE::E_MAX])
{
	int nTrigger(0);
	bool isTrigger(false);
	std::string strSyntax("");

	for (int nSyntaxNum((int)E_SYNTAX_TYPE::E_TYPE); nSyntaxNum < (int)E_SYNTAX_TYPE::E_MAX; nSyntaxNum ++)
	{
		strSyntax = arCheck[nSyntaxNum];

		for (int nListNum(1); (nListNum < m_arSyntaxNum[nSyntaxNum]) && !isTrigger; nListNum++)
		{
			if (m_arSyntaxType[nSyntaxNum][nListNum] == strSyntax)
			{
				isTrigger = true;
				nTrigger++;
			}
		}

		isTrigger = false;
	}

	if (nTrigger == ((int)E_SYNTAX_TYPE::E_MAX - 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int C_DataLoader::detectSyntax(const std::string & strSyntax, std::string* arResult, const int nLength)
{
	int	nMaxLength(0);
	int nMaxSize(0);
	int	nPosition(0);
	std::string strResult("");
	std::vector<std::string> vecList{};
	std::string* pResult(nullptr);

	nMaxLength = strSyntax.size() - 1;

	if (strSyntax.at(nMaxLength) != ';')
	{
		return -1;
	}

	while (nPosition < nMaxLength - 1)
	{
		strResult = getReadText(strSyntax, nPosition, nMaxLength);

		if (strResult != "")
		{
			vecList.push_back(strResult);
		}
	}

	nMaxSize = vecList.size();

	for (int nDataNum(0); nDataNum < nMaxSize; nDataNum++)
	{
		arResult[nDataNum + 1] = vecList.at(nDataNum);
	}

	return nMaxSize;
}

void C_DataLoader::presetBufferSize()
{
	m_arMaxNumList[(int)E_FILE_TYPE::E_COIN]	= (int)E_COIN::E_MAX;
	m_arMaxNumList[(int)E_FILE_TYPE::E_PLAYER]	= (int)E_PLAYER::E_MAX;
}

void C_DataLoader::setSyntaxCount()
{
	m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_NONE]  = 0;
	m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_TYPE]  = (int)E_IMG_TYPE::E_MAX;
	m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_VALUE] = (int)E_VALUE_LIST::E_MAX;
}

void C_DataLoader::setAllItemsInfo()
{

}

void C_DataLoader::setMarkList()
{
	m_arFilter[(int)E_MARK_LIST::E_NONE]  = '\0';
	m_arFilter[(int)E_MARK_LIST::E_BLANK] = ' ';
	m_arFilter[(int)E_MARK_LIST::E_TAB]	  = '\t';
	m_arFilter[(int)E_MARK_LIST::E_DQM]   = '\"';
}

std::string C_DataLoader::getReadText(const std::string & strReadText, int & nPos, const int nMaxLength)
{
	char		cWord('\0');
	bool		bSwitch(true);
	std::string strResult("");

	for (; (nPos < nMaxLength) && (bSwitch); nPos++)
	{
		cWord = strReadText.at(nPos);

		if (isBlank(cWord, m_arFilter, (int)E_MARK_LIST::E_MARK_MAX))
		{
			strResult += cWord;
		}
		else
		{
			bSwitch = false;
		}
	}

	return strResult;
}
