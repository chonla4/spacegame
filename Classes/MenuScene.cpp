#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

CCScene* MenuScene::scene()
{
	CCScene* scene = NULL;
	do {
		// scene is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// layer is an autorelease object
		MenuScene *layer = MenuScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);

	} while (0);

	// return the Main menu scene
	return scene;
}

// on init you need to initialize your instance
bool MenuScene::init()
{
	bool bRet = false;
	do {
		CC_BREAK_IF(! CCLayer::init());

		// Enable touch/click actions
		this->setTouchEnabled(true);

		// Play background music
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SpaceGame.wav",true);


		// Main menu with 2 items
		CCMenuItemFont* item1 = CCMenuItemFont::create( "New Game", this, menu_selector(MenuScene::onNewGame) );
		//CCMenuItemFont* item2 = CCMenuItemFont::create( "Options", this, menu_selector(MenuScene::onOptions) );
		CCMenuItemFont* item3 = CCMenuItemFont::create( "Quit", this, menu_selector(MenuScene::onQuit) );

		// combine to form a menu and align Vertically
		CCMenu* menu = CCMenu::create( item1, item3, NULL );

		menu->alignItemsVertically();

		// add this to the layer
		this->addChild( menu, 1 );

		bRet = true;

	} while (0);

	return bRet;

}


void MenuScene::onNewGame(CCObject* pSender)
{
	CCScene *pScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}


void MenuScene::onOptions(CCObject* pSender)
{

}


void MenuScene::onQuit(CCObject* pSender)
{
	// Exit game
	CCDirector::sharedDirector()->end();
}
