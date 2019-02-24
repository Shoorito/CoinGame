#pragma once
#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;

class C_Layer_Management
{
public:
	static	void	init			();
	static	Layer*	createLayer		(const std::string strName);
	static  Layer*	createColorLayer(const std::string& strName, Color4B colorType);
	static	Layer*	getLayer		(const std::string strName);
	static	void	release			();
private:
	static	std::map<std::string, Layer*>* m_arLayerList;
private:
	C_Layer_Management()								= delete;
	C_Layer_Management(C_Layer_Management&)				= delete;
	C_Layer_Management operator=(C_Layer_Management&)	= delete;
};