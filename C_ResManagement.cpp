#include "C_ResManagement.h"

C_ResManagement* C_ResManagement::m_pMyPointer = nullptr;

C_ResManagement * C_ResManagement::create(const std::string& strParentFile)
{
	if (m_pMyPointer)
	{
		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_ResManagement();

	m_pMyPointer->init();
	m_pMyPointer->createParentFile(strParentFile);
	m_pMyPointer->mainBoard();

	return m_pMyPointer;
}

void C_ResManagement::init()
{
	m_arUseFiles	= nullptr;
	m_arMaxNumList  = nullptr;
	m_arParentInfo	= nullptr;
	m_pParentFile	= nullptr;
	m_nFileCount	= 0;
}

void C_ResManagement::release()
{

}

bool C_ResManagement::mainBoard()
{
	if (m_pMyPointer == nullptr)
	{
		return false;
	}

	setSyntaxCount();
	setTypes();
	setMarkList();
	setFilesCount();
	setFilesName();

	createUseFiles();
	createFileBuffer();
	createCountBuffer();
	setMenuItemsCount();
	setAllItemsInfo();

	return true;
}

std::string C_ResManagement::getRoute(int nMenuType)
{
	std::vector<C_FNode*>* pNodeList(nullptr);
	C_FNode* pResult(nullptr);
	int nMaxSize(0);

	pNodeList = &(m_arNodeList[nMenuType]);

	nMaxSize = pNodeList->size();

	for (int nListNum(0); nListNum < nMaxSize; nListNum++)
	{
		pResult = pNodeList->at(nListNum);

		if ("Route" == pResult->getType())
		{
			return pResult->getName();
		}
	}

	return "";
}

bool C_ResManagement::getList(const std::string & strType, const int nMenuType, std::vector<C_FNode*>& vecList)
{
	C_FNode* pCheckResult(nullptr);
	int nMaxLength(0);

	if ((nMenuType < 0))
	{
		return false;
	}

	nMaxLength = (int)(m_arNodeList[nMenuType].size());

	for (int nListNum(0); (nListNum < nMaxLength); nListNum++)
	{
		pCheckResult = m_arNodeList[nMenuType].at(nListNum);

		if (pCheckResult->getType() == strType)
		{
			vecList.push_back(pCheckResult);
		}
	}

	return true;
}

int C_ResManagement::getUseFileCount()
{
	return m_nFileCount;
}

bool C_ResManagement::isBlank(const char cTarget, const char * arFilterList, const int nFilterSize)
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

bool C_ResManagement::checkSyntax(const std::string arCheck[(int)E_SYNTAX_TYPE::E_MAX])
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

int C_ResManagement::detectSyntax(const std::string & strSyntax, std::string* arResult)
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
		return NULL;
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

bool C_ResManagement::setNode(const std::string & strDetectText, const int nFileType)
{
	std::string arInfoList[(int)E_FILE_SYNTAX::E_MAX]{};
	std::string arConfirm[(int)E_SYNTAX_TYPE::E_MAX]{};
	C_FNode* pNode(nullptr);

	detectSyntax(strDetectText, arInfoList);

	arConfirm[(int)E_SYNTAX_TYPE::E_TYPE]  = arInfoList[(int)E_FILE_SYNTAX::E_TYPE];
	arConfirm[(int)E_SYNTAX_TYPE::E_VALUE] = arInfoList[(int)E_FILE_SYNTAX::E_VALUE_TYPE];

	if (!checkSyntax(arConfirm))
	{
		return false;
	}

	pNode = C_FNode::createNode();

	pNode->setNodeInfo(arInfoList);

	m_arNodeList[nFileType].push_back(pNode);

	return true;
}

bool C_ResManagement::createParentFile(const std::string & strParentFile)
{
	if (strParentFile == "")
	{
		return false;
	}

	m_pParentFile = C_FileLoad::create(strParentFile);

	return true;
}

void C_ResManagement::setFilesCount()
{
	m_nFileCount = m_pParentFile->getMaxRowNumber();
}

bool C_ResManagement::setFilesName()
{
	m_arParentInfo = new(std::nothrow) std::string[(int)E_FILE_TYPE::E_MAX]{};

	m_arParentInfo[0] = "";

	for (int nListNum((int)E_FILE_TYPE::E_BOTTOM_MENU); nListNum < (int)E_FILE_TYPE::E_MAX; nListNum++)
	{
		m_arParentInfo[nListNum] = m_pParentFile->getLineInfo(nListNum - 1);

		setNode(m_arParentInfo[nListNum], (int)E_FILE_TYPE::E_PARENT);
	}

	return true;
}

void C_ResManagement::createUseFiles()
{
	m_arUseFiles = new(std::nothrow) C_FileLoad*[m_nFileCount + 1]{};
}

void  C_ResManagement::createFileBuffer()
{
	std::string strFilesName("");

	for (int nListNum(0); nListNum < m_nFileCount; nListNum++)
	{
		strFilesName = m_arNodeList[(int)E_FILE_TYPE::E_PARENT].at(nListNum)->getName();

		m_arUseFiles[nListNum + 1] = C_FileLoad::create(strFilesName);
	}
}

void C_ResManagement::createCountBuffer()
{
	m_arMaxNumList = new(std::nothrow) int[m_nFileCount + 1]{};
}

void C_ResManagement::setMenuItemsCount()
{
	for (int nMenu(0); nMenu < m_nFileCount; nMenu++)
	{
		m_arMaxNumList[nMenu] = m_arUseFiles[nMenu + 1]->getMaxRowNumber();
	}
}

void C_ResManagement::setSyntaxCount()
{
	m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_NONE]  = 0;
	m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_TYPE]  = (int)E_IMG_TYPE::E_MAX;
	m_arSyntaxNum[(int)E_SYNTAX_TYPE::E_VALUE] = (int)E_VALUE_LIST::E_MAX;
}

void C_ResManagement::setAllItemsInfo()
{
	C_FileLoad* pTarget(nullptr);

	for (int nFileNum((int)E_FILE_TYPE::E_BOTTOM_MENU); nFileNum < (int)E_FILE_TYPE::E_MAX; nFileNum++)
	{
		int nMaxLength(0);

		pTarget	   = m_arUseFiles[nFileNum];
		nMaxLength = m_arMaxNumList[nFileNum - 1];

		for (int nData(0); nData < nMaxLength; nData++)
		{
			std::string strText("");

			strText = pTarget->getLineInfo(nData);

			setNode(strText, nFileNum);
		}
	}
}

void C_ResManagement::setTypes()
{
	m_arImgType[(int)E_IMG_TYPE::E_NONE]	= "None";
	m_arImgType[(int)E_IMG_TYPE::E_SPRITE]	= "Sprite";
	m_arImgType[(int)E_IMG_TYPE::E_BUTTON]	= "Button";
	m_arImgType[(int)E_IMG_TYPE::E_ROUTE]	= "Route";
	m_arImgType[(int)E_IMG_TYPE::E_COIN]	= "Coin";

	m_arValueType[(int)E_VALUE_LIST::E_NONE]  = "None";
	m_arValueType[(int)E_VALUE_LIST::E_TAG]   = "Tag";
	m_arValueType[(int)E_VALUE_LIST::E_VALUE] = "Value";

	m_arSyntaxType[(int)E_SYNTAX_TYPE::E_NONE]  = nullptr;
	m_arSyntaxType[(int)E_SYNTAX_TYPE::E_TYPE]  = m_arImgType;
	m_arSyntaxType[(int)E_SYNTAX_TYPE::E_VALUE] = m_arValueType;
}

void C_ResManagement::setMarkList()
{
	m_arFilter[(int)E_MARK_LIST::E_NONE]  = '\0';
	m_arFilter[(int)E_MARK_LIST::E_BLANK] = ' ';
	m_arFilter[(int)E_MARK_LIST::E_TAB]	  = '\t';
	m_arFilter[(int)E_MARK_LIST::E_DQM]   = '\"';
}

std::string C_ResManagement::getReadText(const std::string & strReadText, int & nPos, const int nMaxLength)
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
