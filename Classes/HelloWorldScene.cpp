#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

#define KNUMASTEROIDS 15
#define KNUMLASERS 5
#define TOTALGAMEDURATION 100000 // if user passes this duration, he/she wins the game

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
								origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/**
	 * Begin to put new code
	 */

    _batchNode = CCSpriteBatchNode::create("Sprites.pvr.ccz");
    this->addChild(_batchNode);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");

    _ship = CCSprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _ship->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    _batchNode->addChild(_ship, 1);

    // 1) Create the CCParallaxNode
    _backgroundNode = CCParallaxNodeExtras::node();
	this->addChild(_backgroundNode,-1);

	// 2) Create the sprites will be added to the CCParallaxNode
	_spacedust1 = CCSprite::create("bg_front_spacedust.png");
	_spacedust2 = CCSprite::create("bg_front_spacedust.png");
	_planetsunrise = CCSprite::create("bg_planetsunrise.png");
	_galaxy = CCSprite::create("bg_galaxy.png");
	_spacialanomaly = CCSprite::create("bg_spacialanomaly.png");
	_spacialanomaly2 = CCSprite::create("bg_spacialanomaly2.png");

	// Adding stars
	this->addChild(CCParticleSystemQuad::create("Stars1.plist"));
	this->addChild(CCParticleSystemQuad::create("Stars2.plist"));
	this->addChild(CCParticleSystemQuad::create("Stars3.plist"));

	// 3) Determine relative movement speeds for space dust and background
	CCPoint dustSpeed = ccp(0.1, 0.1);
	CCPoint bgSpeed = ccp(0.05, 0.05);

	// 4) Add children to CCParallaxNode
	_backgroundNode->addChild(_spacedust1, 0, dustSpeed, ccp(0,winSize.height/2) ); // 2
	_backgroundNode->addChild(_spacedust2, 0, dustSpeed, ccp( _spacedust1->getContentSize().width,winSize.height/2));
	_backgroundNode->addChild(_galaxy, -1, bgSpeed, ccp(0, winSize.height * 0.7));
	_backgroundNode->addChild(_planetsunrise, -1 , bgSpeed, ccp(600, winSize.height * 0));
	_backgroundNode->addChild(_spacialanomaly, -1, bgSpeed, ccp(900, winSize.height * 0.3));
	_backgroundNode->addChild(_spacialanomaly2, -1, bgSpeed, ccp(1500, winSize.height * 0.9));

	/**
	 * Adding asteroids
	 */
	_asteroids = new CCArray();
	for(int i = 0; i < KNUMASTEROIDS; ++i) {
		CCSprite *asteroid = CCSprite::createWithSpriteFrameName("asteroid.png");
		asteroid->setVisible(false);
		_batchNode->addChild(asteroid);
		_asteroids->addObject(asteroid);
	}

	/** Lasers
	 *
	 */
	_shipLasers = new CCArray();
	for(int i = 0; i < KNUMLASERS; ++i) {
		CCSprite *shipLaser = CCSprite::createWithSpriteFrameName("laserbeam_blue.png");
		shipLaser->setVisible(false);
		_batchNode->addChild(shipLaser);
		_shipLasers->addObject(shipLaser);
	}

	// Enable touch
	this->setTouchEnabled(true);


	// Accelerometer
	this->setAccelerometerEnabled(true);


	// Adding sounds
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SpaceGame.wav",true);
	SimpleAudioEngine::sharedEngine()->preloadEffect("explosion_large.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("laser_ship.wav");

	// Win/Lose Detection
	_lives = 3;
	_score = 0;
	double curTime = getTimeTick();
	_gameOverTime = curTime + TOTALGAMEDURATION;

	// Updates
	this->scheduleUpdate();
	
    return true;

    /** **************************************
     * ORIGINAL CODE FROM SAMPLE
     *
     *
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
    */

}


void HelloWorld::update(float dt) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCPoint backgroundScrollVert = ccp(-1000, 0);
	_backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));

	CCArray *spaceDusts = CCArray::createWithCapacity(2);
	spaceDusts->addObject(_spacedust1);
	spaceDusts->addObject(_spacedust2);
	for ( int ii = 0; ii <spaceDusts->count(); ii++ ) {
	    CCSprite * spaceDust = (CCSprite *)(spaceDusts->objectAtIndex(ii));
	    float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x;
	    float size = spaceDust->getContentSize().width;
	    if ( xPosition < -size/2 ) {
	        _backgroundNode->incrementOffset(ccp(spaceDust->getContentSize().width*2,0),spaceDust);
	    }
	}

	CCArray *backGrounds = CCArray::createWithCapacity(4);
	backGrounds->addObject(_galaxy);
	backGrounds->addObject(_planetsunrise);
	backGrounds->addObject(_spacialanomaly);
	backGrounds->addObject(_spacialanomaly2);
	for ( int ii = 0; ii <backGrounds->count(); ii++ ) {
	    CCSprite * background = (CCSprite *)(backGrounds->objectAtIndex(ii));
	    float xPosition = _backgroundNode->convertToWorldSpace(background->getPosition()).x;
	    float size = background->getContentSize().width;
	    if ( xPosition < -size ) {
	        _backgroundNode->incrementOffset(ccp(2000,0),background);
	    }
	}

	/**
	 * Accelerometer
	 */
	float maxY = winSize.height - _ship->getContentSize().height/2;
	float minY = _ship->getContentSize().height/2;

	float diff = (_shipPointsPerSecY * dt);
	float newY = _ship->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);
	_ship->setPosition(ccp(_ship->getPosition().x, newY));



	/**
	 * Asteroids
	 */
	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextAsteroidSpawn) {

	    float randMillisecs = randomValueBetween(0.20, 1.0) * 1000;
	    _nextAsteroidSpawn = randMillisecs + curTimeMillis;

	    float randY = randomValueBetween(0.0, winSize.height);
	    float randDuration = randomValueBetween(2.0, 10.0);

	    CCSprite *asteroid = (CCSprite *)_asteroids->objectAtIndex(_nextAsteroid);
	    _nextAsteroid++;

	    if (_nextAsteroid >= _asteroids->count())
	        _nextAsteroid = 0;

	    asteroid->stopAllActions();
	    asteroid->setPosition( ccp(winSize.width+asteroid->getContentSize().width/2, randY));
	    asteroid->setVisible(true);
	    asteroid->runAction(CCSequence::create(CCMoveBy::create(randDuration,
	    		ccp(-winSize.width-asteroid->getContentSize().width, 0)),
	    		CCCallFuncN::create(this,
	    				callfuncN_selector(HelloWorld::setInvisible)),
	    				NULL // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
	     ));
	}

	/**
	 * Collision Detection
	 */

	// Asteroids
	CCObject* asteroid;
	CCObject* shipLaser;

	CCARRAY_FOREACH(_asteroids, asteroid) {
		if ( !((CCSprite *) asteroid)->isVisible() )
	        continue;

	    CCARRAY_FOREACH(_shipLasers, shipLaser) {
	        if ( !((CCSprite *) shipLaser)->isVisible() )
	            continue;

	        // Laser hits asteroid
	        if (((CCSprite *) shipLaser)->boundingBox().intersectsRect(((CCSprite *)asteroid)->boundingBox()) ) {
	            ((CCSprite *)shipLaser)->setVisible(false);
	            ((CCSprite *)asteroid)->setVisible(false);

	            _score++;

	            continue;
	        }
	    }

	    // Asteroid collides with ship
	    if (_ship->boundingBox().intersectsRect(((CCSprite *)asteroid)->boundingBox()) ) {

	    	SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
	    	((CCSprite *)asteroid)->setVisible(false);
	        _ship->runAction( CCBlink::create(1.0, 9));
	        _lives--;
	    }
	}

	/**
	 * Win/Lose Detection
	 */
	if (_lives <= 0) {
	    _ship->stopAllActions();
	    _ship->setVisible(false);
	    this->setTouchEnabled(false);
	    this->endScene(KENDREASONLOSE);
	}
	else if (curTimeMillis >= _gameOverTime) {
	    this->endScene(KENDREASONWIN);
	}

}


void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue) {
	#define KFILTERINGFACTOR 0.1
	#define KRESTACCELX -0.6
	#define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)
	#define KMAXDIFFX 0.2

	double rollingX;

	// Cocos2DX inverts X and Y accelerometer depending on device orientation
	// in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
	pAccelerationValue->x = pAccelerationValue->y;
	rollingX = (pAccelerationValue->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
	float accelX = pAccelerationValue->x - rollingX;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float accelDiff = accelX - KRESTACCELX;
	float accelFraction = accelDiff / KMAXDIFFX;
	_shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;
}


float HelloWorld::randomValueBetween(float low, float high) {
	return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}


float HelloWorld::getTimeTick() {
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
	return (float) millisecs;
}


void HelloWorld::setInvisible(CCNode * node) {
    node->setVisible(false);
}


void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite *shipLaser = (CCSprite *)_shipLasers->objectAtIndex(_nextShipLaser++);
    if ( _nextShipLaser >= _shipLasers->count() )
        _nextShipLaser = 0;
    shipLaser->setPosition( ccpAdd( _ship->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));

    SimpleAudioEngine::sharedEngine()->playEffect("laser_ship.wav");

    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width, 0)), CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL  // DO NOT FORGET TO TERMINATE WITH NULL
    ));
}


void HelloWorld::restartTapped() {
	CCDirector::sharedDirector()->replaceScene
    (CCTransitionZoomFlipX::create(0.5, this->scene()));
    // reschedule
    this->scheduleUpdate();
}

void HelloWorld::endScene( EndReason endReason ) {
	if (_gameOver)
		return;

    _gameOver = true;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    /*
    char message[10] = "You Win";
    if ( endReason == KENDREASONLOSE)
        strcpy(message,"You Lose");
    */

    char message[12] = { 0 };
    sprintf(message, "Score: %d", _score);

    CCLabelBMFont * label ;
    label = CCLabelBMFont::create(message, "fonts/Arial.fnt");
    label->setScale(0.1);
    label->setPosition(ccp(winSize.width/2 , winSize.height*0.6));
    this->addChild(label);

    CCLabelBMFont * restartLabel;
    strcpy(message,"Restart");
    restartLabel = CCLabelBMFont::create(message, "fonts/Arial.fnt");
    CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(HelloWorld::restartTapped) );
    restartItem->setScale(0.1);
    restartItem->setPosition( ccp(winSize.width/2, winSize.height*0.4));

    CCMenu *menu = CCMenu::create(restartItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);

    // clear label and menu
    restartItem->runAction(CCScaleTo::create(0.5, 1.0));
    label ->runAction(CCScaleTo::create(0.5, 1.0));
    // Terminate update callback
    this->unscheduleUpdate();
}



void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
