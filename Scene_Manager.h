#pragma once

#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;

class C_Scene_Manager
{
public:
	static C_Scene_Manager* create();
	static C_Scene_Manager* getInstance() { return m_pMyPointer; }
public:
	virtual inline Scene* getScene()  { return m_pScene; }
	virtual inline void createScene() { m_pScene = Scene::create(); }
private:
	Scene* m_pScene;
private:
	static C_Scene_Manager* m_pMyPointer;
private:
	C_Scene_Manager() {}
	virtual ~C_Scene_Manager() {}
	C_Scene_Manager(C_Scene_Manager&) = delete;
	C_Scene_Manager operator=(C_Scene_Manager&) = delete;
};