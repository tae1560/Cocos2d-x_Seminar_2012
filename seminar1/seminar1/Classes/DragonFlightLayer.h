// DragonFlightLayer.h

#ifndef __DRAGON_FLIGHT_LAYER_H__
#define __DRAGON_FLIGHT_LAYER_H__

#include "common.h"
#include <list>

class DragonFlightLayer : public CCLayer {
private:
	CCSprite *player;
	float before_x;
	list<CCSprite *> enemies;
    float total_time;

public:
	virtual bool init();

	void createEnemy();
	void afterMoveTo(CCNode* node);

	// CCTouchDelegate
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void myScheduler(float dt);
    
    void fire_bullet();
};
#endif