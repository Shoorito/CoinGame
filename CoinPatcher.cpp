#include "CoinPatcher.h"
#include "StateRange.h"
#include "ShareValue.h"
#include "Scene_Manager.h"
#include "C_Market_Menu.h"
#include "C_CoinManagement.h"
#include "Layer_Management.h"
#include "Korean_UTF8.h"
#include "ShareKey.h"

C_Coin_Patcher * C_Coin_Patcher::create(const int nCoinType)
{
	C_Coin_Patcher* pPatcher(nullptr);

	pPatcher = new(std::nothrow) C_Coin_Patcher();
	
	pPatcher->init();
	pPatcher->presetCoinType(nCoinType);
	pPatcher->mainBoard();

	return pPatcher;
}

void C_Coin_Patcher::init()
{
	m_nCoinType			= 0;
	m_nPriceBorder		= 0;
	m_isMinusEvent		= false;
	m_pPriceUpdateNode	= nullptr;
	m_pTPriceUpdateNode = nullptr;
	m_pGradeUpdateNode	= nullptr;
	m_pProfitNode		= nullptr;
	m_pProfitUpdateNode = nullptr;
	m_pSetupLayer		= nullptr;
}

void C_Coin_Patcher::mainBoard()
{
	createSetupLayer();
	createNode();
	presetProfit();
	addNodeChild();

	callGradeSetup();
	callPriceSetup();
	callProfitSetup();
}

void C_Coin_Patcher::createSetupLayer()
{
	m_pSetupLayer = C_Layer_Management::createLayer("SetupLayer_" + std::to_string(m_nCoinType));
}

void C_Coin_Patcher::presetProfit()
{
	C_Share_Management* pManager(nullptr);

	pManager = C_Share_Management::getInstance();

	m_arProfitBorder[(int)E_PROFIT::E_MINUS] = pManager->getMinusBorder(m_nCoinType);
	m_arProfitBorder[(int)E_PROFIT::E_STATE] = pManager->getStateBorder(m_nCoinType);
	m_arProfitBorder[(int)E_PROFIT::E_PLUS]  = pManager->getRange(m_nCoinType)->getMax() + 1;
}

void C_Coin_Patcher::callPriceSetup()
{
	CallFunc*	pFunc(nullptr);
	CallFunc*	pPriceCheck(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSequence(nullptr);
	Repeat*		pRepeat(nullptr);

	pFunc = CallFunc::create(CC_CALLBACK_0(C_Coin_Patcher::setupPrice, this));
	pPriceCheck = CallFunc::create(CC_CALLBACK_0(C_Coin_Patcher::setupPriceCheck, this));
	pDelay = DelayTime::create(0.1f);
	pSequence = Sequence::create(pFunc, pPriceCheck, pDelay, nullptr);
	pRepeat = Repeat::create(pSequence, -1);

	m_pPriceUpdateNode->runAction(pRepeat);
}

void C_Coin_Patcher::callTPriceSetup()
{
	CallFunc*	pFunc(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSequence(nullptr);
	Repeat*		pRepeat(nullptr);

	pFunc		= CallFunc::create(CC_CALLBACK_0(C_Coin_Patcher::setupTPrice, this));
	pDelay		= DelayTime::create(10.0f);
	pSequence	= Sequence::create(pFunc, pDelay, nullptr);
	pRepeat		= Repeat::create(pSequence, -1);

	m_pTPriceUpdateNode->runAction(pRepeat);
}

void C_Coin_Patcher::callGradeSetup()
{
	C_Share_Management* pShare(nullptr);
	CallFunc*	pFunc(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSequence(nullptr);
	Repeat*		pRepeat(nullptr);

	pShare = C_Share_Management::getInstance();

	pFunc = CallFunc::create(CC_CALLBACK_0(C_Coin_Patcher::checkPriceGrade, this));
	pDelay = DelayTime::create(0.02f);
	pSequence = Sequence::create(pFunc, pDelay, nullptr);
	pRepeat = Repeat::create(pSequence, -1);

	m_pGradeUpdateNode->runAction(pRepeat);
}

void C_Coin_Patcher::callProfitSetup()
{
	CallFunc*	pFunc(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSequence(nullptr);
	Repeat*		pRepeat(nullptr);

	pFunc		= CallFunc::create(CC_CALLBACK_0(C_Coin_Patcher::setupProfit, this));
	pDelay		= DelayTime::create(0.5f);
	pSequence	= Sequence::create(pFunc, pDelay, nullptr);
	pRepeat		= Repeat::create(pSequence, -1);

	m_pProfitNode->runAction(pRepeat);
}

void C_Coin_Patcher::setupPrice()
{
	int nCheckValue(0);
	int nAddNum(0);
	C_Share_Management* pShare(nullptr);
	C_Coin* pCoin(nullptr);
	S_State_Range* pRange(nullptr);

	pShare = C_Share_Management::getInstance();
	pCoin  = C_CoinManagement::getInstance()->getCoin(m_nCoinType);
	pRange = pShare->getRange(m_nCoinType);

	nCheckValue = random(pRange->getMin(), pRange->getMax());

	nAddNum = (pShare->getAddNum(m_nPriceBorder)) * (checkProfit(nCheckValue));
	pCoin->setPrice(pCoin->getPrice() + nAddNum);

	//CCLOG(std::to_string(nCheckValue).c_str());
}

void C_Coin_Patcher::setupTPrice()
{

}

void C_Coin_Patcher::setupProfit()
{
	int nProfit(0);
	int nPrePrice(0);
	float fProfitPer(0.0f);
	C_Coin* pCoin(nullptr);
	std::string strPersent("");
	C_Market_Line* pLine(nullptr);

	pCoin = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	nPrePrice	= pCoin->getPrePrice();
	nProfit		= pCoin->getPrice() - nPrePrice;
	pLine		= C_Market_Management::getInstance()->getCoinLine(m_nCoinType);
	fProfitPer	= (float)nProfit / (float)nPrePrice * 100.0f;
	strPersent	= checkPercent(std::to_string(abs(fProfitPer)));

	pCoin->setRate(fProfitPer); // 이후 수정 요망
	pCoin->setRatePrice(nProfit); // 이후 수정 요망

	if (nProfit > 0)
	{
		pLine->getMyRate()->setColor(Color3B::GREEN);
		pLine->getMyRatePrice()->setColor(Color3B::GREEN);
		pLine->getMyRate()->setString(UTF8("▲" + strPersent + "%"));
	}
	else if (nProfit < 0)
	{
		pLine->getMyRate()->setColor(Color3B::RED);
		pLine->getMyRatePrice()->setColor(Color3B::RED);
		pLine->getMyRate()->setString(UTF8("▼" + strPersent + "%"));
	}

	pLine->getMyRatePrice()->setString(std::to_string(nProfit));
}

void C_Coin_Patcher::setupPriceCheck()
{
	C_Share_Management* pManager(nullptr);
	C_Coin* pCoin(nullptr);
	int nPrice(0);
	int nWorstBorder(0);

	pManager = C_Share_Management::getInstance();
	pCoin	 = C_CoinManagement::getInstance()->getCoin(m_nCoinType);

	nPrice		 = pCoin->getPrice();
	nWorstBorder = pManager->getWorstBorder(m_nCoinType);

	if((nPrice <= nWorstBorder) && !m_isMinusEvent)
	{
		CallFunc* pFunc(nullptr);
		DelayTime* pDelay(nullptr);
		Sequence* pSeq(nullptr);

		pManager->setProfit(m_nCoinType, 0, 9);
		
		m_isMinusEvent = true;

		pFunc	= CallFunc::create(CC_CALLBACK_0(C_Coin_Patcher::setPriceState, this));
		pDelay	= DelayTime::create(30.0f);
		pSeq	= Sequence::create(pDelay, pFunc, nullptr);

		m_pProfitUpdateNode->runAction(pSeq);
	
		CCLOG("WorstBorder!");
	}
}

void C_Coin_Patcher::setPriceState()
{
	C_Share_Management::getInstance()->setProfit(m_nCoinType, 45, 55);
	m_isMinusEvent = false;
}

bool C_Coin_Patcher::checkPriceGrade()
{
	C_Coin* pCoin(nullptr);
	C_Share_Management* pShare(nullptr);

	pCoin  = C_CoinManagement::getInstance()->getCoin(m_nCoinType);
	pShare = C_Share_Management::getInstance();

	for (int nPriceNum((int)E_ADD_LIST::E_UNDER_1000); nPriceNum < (int)E_ADD_LIST::E_MAX; nPriceNum++)
	{
		if (pCoin->getPrice() < pShare->getBorderNum(nPriceNum))
		{
			m_nPriceBorder = nPriceNum;

			return true;
		}
	}

	return false;
}

std::string C_Coin_Patcher::checkPercent(const std::string& strCheck)
{
	int nMax(0);
	int nResultLength(0);
	bool isSwitch(false);
	std::string strResult("");

	nMax = strCheck.size();

	for (int nPos(0); nPos < (nMax - 4); nPos++)
	{
		strResult += strCheck.at(nPos);
	}

	return strResult;
}

int C_Coin_Patcher::checkProfit(const int nCheckNum)
{
	C_Share_Management* pManager(nullptr);

	pManager = C_Share_Management::getInstance();

	m_arProfitBorder[(int)E_PROFIT::E_MINUS] = pManager->getMinusBorder(m_nCoinType);
	m_arProfitBorder[(int)E_PROFIT::E_STATE] = pManager->getStateBorder(m_nCoinType);

	for (int nListNum((int)E_PROFIT::E_MINUS); nListNum < (int)E_PROFIT::E_MAX; nListNum++)
	{
		if (nCheckNum < m_arProfitBorder[nListNum])
		{
			return C_Share_Management::getInstance()->getProfitNum(nListNum);
		}
	}

	CCLOG("OUT_OF_RANGE_CHECK_CODE");

	return 0;
}

void C_Coin_Patcher::createNode()
{
	m_pPriceUpdateNode	= Node::create();
	m_pTPriceUpdateNode = Node::create();
	m_pGradeUpdateNode	= Node::create();
	m_pProfitNode		= Node::create();
	m_pProfitUpdateNode = Node::create();
}

void C_Coin_Patcher::addNodeChild()
{
	C_Scene_Manager::getInstance()->getScene()->addChild(m_pSetupLayer);

	m_pSetupLayer->addChild(m_pPriceUpdateNode);
	m_pSetupLayer->addChild(m_pTPriceUpdateNode);
	m_pSetupLayer->addChild(m_pGradeUpdateNode);
	m_pSetupLayer->addChild(m_pProfitNode);
	m_pSetupLayer->addChild(m_pProfitUpdateNode);
}
