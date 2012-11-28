//
//  BackgroundLayer.cpp
//  Seminar1
//
//  Created by Tae-ho Lee on 12. 11. 28..
//
//

#include "BackgroundLayer.h"

bool BackgroundLayer::init() {
    if (! CCLayer::init()) {
        return false;
    }
    
    // 배경
    CCSprite *backgroundSprite = CCSprite::create("background.jpeg");
    this->addChild(backgroundSprite);
    
    return true;
}