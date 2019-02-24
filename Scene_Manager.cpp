#include "Scene_Manager.h"
#include "Korean_UTF8.h"

C_Scene_Manager* C_Scene_Manager::m_pMyPointer = nullptr;

C_Scene_Manager * C_Scene_Manager::create()
{
	if (m_pMyPointer)
	{
		CCAssert(m_pMyPointer != nullptr, UTF8("씬이 이미 만들어져 있습니다.").c_str());

		return nullptr;
	}

	m_pMyPointer = new(std::nothrow) C_Scene_Manager();

	m_pMyPointer->createScene();

	return m_pMyPointer;
}