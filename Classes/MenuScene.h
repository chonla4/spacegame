#ifndef  __MENU_SCENE__
#define  __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	// there's no 'id' in cpp, so we recommend to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// functions for click even handling
	void onNewGame(CCObject* pSender);
	void onOptions(CCObject* pSender);
	void onQuit(CCObject* pSender);

	// implement the 'static node()' method manually
	CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
