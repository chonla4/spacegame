#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"

USING_NS_CC;

typedef enum {
  KENDREASONWIN,
  KENDREASONLOSE
} EndReason;

class HelloWorld : public cocos2d::CCLayer
{
private:
	CCSpriteBatchNode * _batchNode;
	CCSprite * _ship;
	CCParallaxNodeExtras *_backgroundNode;
	CCSprite *_spacedust1;
	CCSprite *_spacedust2;
	CCSprite *_planetsunrise;
	CCSprite *_galaxy;
	CCSprite *_spacialanomaly;
	CCSprite *_spacialanomaly2;

	int _lives;

	double _gameOverTime;
	bool _gameOver;

	int _score;

	float _shipPointsPerSecY; // used for accelerometer

	/**
	 * Asteroids
	 */
	CCArray* _asteroids;
	int _nextAsteroid;
	float _nextAsteroidSpawn;

	/**
	 * Lasers
	 */
	CCArray* _shipLasers;
	int _nextShipLaser;

	/** Win/Lose Detection
	 *
	 */
	void endScene(EndReason endReason);
	void restartTapped();

	// scheduled Update
	void update(float dt);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // used for accelerometer
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

    /**
     * Asteroids
     */
    float randomValueBetween(float low, float high);
    void setInvisible(CCNode * node);
    float getTimeTick();
    // =============================================

    /**
     * Touch events
     */
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);


    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
