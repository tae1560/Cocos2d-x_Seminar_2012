//
//  YoumSprite.cpp
//  Seminar1
//
//  Created by Tae-ho Lee on 12. 11. 28..
//
//

#include "YoumSprite.h"

YoumSprite* YoumSprite::create(const char *pszFileName)
{
    YoumSprite *pobSprite = new YoumSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    
    // init
    pobSprite->hp = 100;
    
    return NULL;
}

void YoumSprite::decrease_hp(int damage) {
    hp -= damage;
}
bool YoumSprite::is_alive() {
    return hp > 0;
}