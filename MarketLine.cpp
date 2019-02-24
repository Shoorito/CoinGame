#include "MarketLine.h"
#include "Sprite_Management.h"
#include "Layer_Management.h"
#include "ShareValue.h"
#include "ShareKey.h"
#include "Korean_UTF8.h"
#include "C_CoinManagement.h"

C_Market_Line * C_Market_Line::create(const int nCoinType)
{
	C_Market_Line* pMLine(nullptr);
	
	pMLine = new(std::nothrow) C_Market_Line();
	
	pMLine->init();
	pMLine->presetCoinOption(nCoinType);
	pMLine->mainBoard();

	return pMLine;
}

void C_Market_Line::init()
{
	m_pCoinImg		= nullptr;
	m_pNameImg		= nullptr;
	m_pFavorite[0]  = nullptr;
	m_pFavorite[1]  = nullptr;
	m_pPrice		= nullptr;
	m_pTPrice		= nullptr;
	m_pRate			= nullptr;
	m_pRatePrice	= nullptr;
	m_pLineLayer	= nullptr;
	m_pUpdateNode	= nullptr;
	m_pLine			= nullptr;
	m_isFavorite	= false;
	m_nCoinType		= (int)E_COIN::E_NONE;
}

void C_Market_Line::mainBoard()
{
	presetImage();
	createLabel();
	createLayer();
	createUpdateNode();
	
	addChildItems(); // 이 역시 정식 엔진에서는 "Item_Management.cpp" 기능을 사용합니다.
	
	presetSpriteOption();
	presetLabelOption();

	updateList();
}

void C_Market_Line::presetImage()
{
	C_Coin* pCoin(nullptr);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	m_pCoinImg		= pCoin->getImage();
	m_pNameImg		= pCoin->getNameImg();
	m_pFavorite[0]  = C_Sprite_Management::createSprite("Buttons/", "Favorite_Unselected_icon", pCoin->getName() + "Favorite_UnSelected");
	m_pFavorite[1]	= C_Sprite_Management::createSprite("Buttons/", "Favorite_Selected_icon", pCoin->getName() + "Favorite_Selected");
	m_pLine			= C_Sprite_Management::createSprite("UI_Items/", "Bar", "CoinBorder_" + pCoin->getName());
}

void C_Market_Line::createUpdateNode()
{
	m_pUpdateNode = Node::create();
}

void C_Market_Line::createLabel()
{
	m_pPrice	 = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");
	m_pTPrice	 = Label::createWithBMFont("BMFonts/OmniGothic_030_30px.fnt", "");
	m_pRate		 = Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "");
	m_pRatePrice = Label::createWithBMFont("BMFonts/OmniGothic_040_30px.fnt", "");
}

void C_Market_Line::createLayer()
{
	C_Coin* pCoin(nullptr);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	m_pLineLayer = C_Layer_Management::createColorLayer(pCoin->getName() + "_LineLayer", Color4B(35, 33, 31, 255));

	m_pLineLayer->setContentSize(Size(540.0f, 75.0f));
}

void C_Market_Line::addChildItems()
{
	m_pLineLayer->addChild(m_pCoinImg);
	m_pLineLayer->addChild(m_pNameImg);
	m_pLineLayer->addChild(m_pFavorite[0]);
	m_pLineLayer->addChild(m_pFavorite[1]);
	m_pLineLayer->addChild(m_pPrice);
	m_pLineLayer->addChild(m_pTPrice);
	m_pLineLayer->addChild(m_pRate);
	m_pLineLayer->addChild(m_pRatePrice);
	m_pLineLayer->addChild(m_pUpdateNode);
	m_pLineLayer->addChild(m_pLine);
}

void C_Market_Line::updateList()
{
	CallFunc*	pPriceSetup(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSequance(nullptr);
	Repeat*		pRepeat(nullptr);

	pPriceSetup = CallFunc::create(CC_CALLBACK_0(C_Market_Line::setupPriceValue, this));
	pDelay		= DelayTime::create(0.5f);
	pSequance	= Sequence::create(pPriceSetup, pDelay, nullptr);
	pRepeat		= Repeat::create(pSequance, -1);

	m_pUpdateNode->runAction(pRepeat);
}

void C_Market_Line::setupPriceValue()
{
	int nPrice(0);
	int nTPrice(0);
	C_Coin* pCoin(nullptr);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	nPrice  = pCoin->getPrice();
	nTPrice = pCoin->getTPrice();

	m_pPrice->setString(UTF8(std::to_string(nPrice) + " 원"));
	m_pTPrice->setString(UTF8(std::to_string(nTPrice) + " 백만"));
}

void C_Market_Line::presetSpriteOption()
{
	m_pCoinImg->setVisible(true);
	m_pNameImg->setVisible(true);
	m_pFavorite[m_isFavorite]->setVisible(true);
	m_pLine->setVisible(true);

	m_pCoinImg->setAnchorPoint(Point(0.0f, 0.5f));
	m_pNameImg->setAnchorPoint(Point(0.0f, 0.5f));
	m_pFavorite[0]->setAnchorPoint(Point(0.0f, 0.5f));
	m_pFavorite[1]->setAnchorPoint(Point(0.0f, 0.5f));
	m_pLine->setAnchorPoint(Point(0.5f, 0.0f));

	m_pCoinImg->setPosition(14.0f, 39.5f);
	m_pNameImg->setPosition(66.5f, 39.5f);
	m_pFavorite[0]->setPosition(498.0f, 39.5f);
	m_pFavorite[1]->setPosition(498.0f, 39.5f);
	m_pLine->setPosition(270.0f, 0.0f);

	m_pCoinImg->setScale(0.5f);
	m_pNameImg->setScale(0.5f);
	m_pFavorite[0]->setScale(0.5f);
	m_pFavorite[1]->setScale(0.5f);
	m_pLine->setScaleX(0.5f);
}

void C_Market_Line::presetLabelOption()
{
	m_pRate->setVisible(true);
	m_pPrice->setVisible(true);
	m_pTPrice->setVisible(true);
	m_pRatePrice->setVisible(true);

	m_pRate->setAnchorPoint(Point(0.5f, 0.5f));
	m_pPrice->setAnchorPoint(Point(1.0f, 0.5f));
	m_pTPrice->setAnchorPoint(Point(1.0f, 0.5f));
	m_pRatePrice->setAnchorPoint(Point(0.5f, 0.5f));

	m_pPrice->setPosition(292.0f, 39.5f);
	m_pTPrice->setPosition(402.0f, 39.5f);
	m_pRate->setPosition(479.5f - 30.0f, 31.5f);
	m_pRatePrice->setPosition(479.5f - 30.0f, 47.5f);

	m_pPrice->setScale(0.7f);
	m_pTPrice->setScale(0.7f);
	m_pRate->setScale(0.5f);
	m_pRatePrice->setScale(0.5f);
}
