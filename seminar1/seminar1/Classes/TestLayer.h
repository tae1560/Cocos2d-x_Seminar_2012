#ifndef __TEST_LAYER_H__
#define __TEST_LAYER_H__

#include "common.h"

class BulletSprite;

class TestLayer : public CCLayer {
    CCSprite* moveSprite; // member variable
    float totalTime; // elapsed time
    vector<BulletSprite*> bullets;

	CCSprite* followSprite;
	CCLabelTTF* stateLabel;
    
public:
    virtual bool init();
    
    void myScheduler(float dt);

	// CCTouchDelegate
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	bool isSpriteIncludePoint(CCSprite* sprite, CCPoint point);
};

#endif //__TEST_LAYER_H__