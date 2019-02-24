#include "AppDelegate.h"
#include "MainBoard.h"
#include "ShareKey.h"
#include "Scene_Manager.h"
#include "Layer_Management.h"
#include "Sprite_Management.h"
#include "ClippingNode_Management.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

static cocos2d::Size szDesignRes = cocos2d::Size(540.0f, 960.0f);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	C_MainScene* pGameScene(nullptr);
	Scene*		 pMainScene(nullptr);
	Director*	 pDirector(nullptr);
	GLView*		 pView(nullptr);
	float		 fWinWidth(0.0f);
	float		 fWinHeight(0.0f);

	pDirector	= Director::getInstance();
	pView		= pDirector->getOpenGLView();
    
	fWinWidth  = szDesignRes.width;
	fWinHeight = szDesignRes.height;

	if(!pView)
	{
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
			pView = GLViewImpl::createWithRect("GameEngine", cocos2d::Rect(0, 0, fWinWidth, fWinHeight));
		#else
			pView = GLViewImpl::create("GameEngine");
		#endif
			pDirector->setOpenGLView(pView);
    }

    // turn on display FPS
	pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0f / 60);

    // Set the design resolution
	pView->setDesignResolutionSize(fWinWidth, fWinHeight, ResolutionPolicy::NO_BORDER);
    
	// All Used Keys Initialize
	
	C_Layer_Management::init();
	C_Sprite_Management::init();
	C_ClippingNode_Management::init();
	C_Scene_Manager::create();

	S_KeyStore::initKey();

	pMainScene = C_Scene_Manager::getInstance()->getScene();

	pGameScene = C_MainScene::create();
    
	pDirector->runWithScene(pMainScene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
