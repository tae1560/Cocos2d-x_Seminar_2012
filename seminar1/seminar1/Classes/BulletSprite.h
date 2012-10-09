#ifndef __BULLET_SPRITE_H__
#define __BULLET_SPRITE_H__

#include "common.h"

class BulletSprite : public CCSprite {
    CCPoint velocity;
    
public:
    //getter and setter
    CCPoint getVelocity();
    void setVelocity(CCPoint point);
};

#endif // __BULLET_SPRITE_H__