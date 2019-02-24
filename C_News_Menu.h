#pragma once

#include "cocos2d.h"

USING_NS_CC;

class C_News_Management
{
public:
	static C_News_Management* create();
	static inline C_News_Management* getInstance() { return m_pMyPointer; }
public:
	virtual void release();
	virtual void setEventEnabled(const bool isEnabled);
	virtual inline Layer* getNewsLayer() { return m_pMenuLayer; }
private:
	virtual void init();
	virtual void mainBoard();
	virtual void createNewsLayer();
	virtual void loadNewsMenu();
	virtual void presetNewsLayer();
	virtual void presetNewsPosition();
	virtual void addChildLayer();
private:
	static C_News_Management* m_pMyPointer;
	Layer* m_pMenuLayer;
	Layer* m_pSectionLayer;
	Layer* m_pVolumeChart;
	Layer* m_pRateChart;
private:
	C_News_Management()  {};
	~C_News_Management() {};
	C_News_Management(C_News_Management&)			= delete;
	C_News_Management operator=(C_News_Management&) = delete;
};