#ifndef __TEST_LAYER_H__
#define __TEST_LAYER_H__

#include "common.h"

class BulletSprite;

class TestLayer : public CCLayer {
    CCSprite* moveSprite; // member variable
    float totalTime; // elapsed time
    vector<BulletSprite*> bullets;
    
public:
    virtual bool init();
    
    void myScheduler(float dt);
};

#endif //__TEST_LAYER_H__