#pragma once
#include <string>
#include "EnumClassList.h"

class C_FNode
{
public:
	static C_FNode* createNode();
public:
	virtual void setNodeInfo(const std::string arTypeList[(int)E_FILE_SYNTAX::E_MAX]);
private:
	virtual void init();
	virtual void setSetterList();
private:
	virtual inline void setType(const std::string& strType)			  { m_strType = strType; }
	virtual inline void setName(const std::string& strName)			  { m_strName = strName; }
	virtual inline void setValueType(const std::string& strValueType) { m_strValueType = strValueType; }
	virtual inline void setValue(const std::string& strValue)		  { m_strValue = strValue; }
public:
	virtual inline std::string getType()	{ return m_strType; }
	virtual inline std::string getName()	{ return m_strName; }
	virtual inline std::string getTagType() { return m_strValueType; }
	virtual inline std::string getTagName() { return m_strValue; }
private:
	std::string m_strType;
	std::string m_strName;
	std::string m_strValueType;
	std::string m_strValue;
private:
	void(C_FNode::*m_arSetterFunc[(int)E_FILE_SYNTAX::E_MAX])(const std::string& strType);
private:
	C_FNode() {};
	~C_FNode() {};
};

