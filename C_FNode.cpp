#include "C_FNode.h"

C_FNode * C_FNode::createNode()
{
	C_FNode* pItem(nullptr);

	pItem = new(std::nothrow) C_FNode();

	pItem->init();
	pItem->setSetterList();

	return pItem;
}

void C_FNode::init()
{
	m_strType = "";
	m_strName = "";
	m_strValueType = "";
	m_strValue = "";
}

void C_FNode::setSetterList()
{
	m_arSetterFunc[(int)E_FILE_SYNTAX::E_NONE]		 = nullptr;
	m_arSetterFunc[(int)E_FILE_SYNTAX::E_TYPE]		 = &C_FNode::setType;
	m_arSetterFunc[(int)E_FILE_SYNTAX::E_NAME]		 = &C_FNode::setName;
	m_arSetterFunc[(int)E_FILE_SYNTAX::E_VALUE_TYPE] = &C_FNode::setValueType;
	m_arSetterFunc[(int)E_FILE_SYNTAX::E_VALUE]		 = &C_FNode::setValue;
}

void C_FNode::setNodeInfo(const std::string arTypeList[(int)E_FILE_SYNTAX::E_MAX])
{
	for (int nFuncList((int)E_FILE_SYNTAX::E_TYPE); nFuncList < (int)E_FILE_SYNTAX::E_MAX; nFuncList++)
	{
		(this->*m_arSetterFunc[nFuncList])(arTypeList[nFuncList]);
	}
}
