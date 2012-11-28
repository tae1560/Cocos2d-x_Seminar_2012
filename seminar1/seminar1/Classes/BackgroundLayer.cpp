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
    
    background_size = backgroundSprite->getContentSize().height;
    backgroundSprite->setPosition(
            ccp(this->getContentSize().width/2, background_size / 2));
    
    
    CCSprite *backgroundSprite2 = CCSprite::create("background.jpeg");
    this->addChild(backgroundSprite2);
    backgroundSprite2->setPosition(
            ccp(this->getContentSize().width/2, background_size / 2 * 3));
    
    
    
    this->schedule(schedule_selector(BackgroundLayer::myScheduler));
    
    return true;
}

void BackgroundLayer::myScheduler(float dt) {
    // 1. 움직임
    // 2. 그림사이즈 보다 아래 가있으면 올리기
    
    this->setPosition(ccp(this->getPosition().x,this->getPosition().y - 5));
    
    if (this->getPosition().y < -background_size) {
        this->setPosition(ccp(this->getPosition().x,this->getPosition().y + background_size));
    }
}