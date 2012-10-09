#include "TestLayer.h"
#include "BulletSprite.h"

bool TestLayer::init() {
	if (!CCLayer::init()){
		return false;
	}
//
//	// init
//	CCSprite* sprite = CCSprite::spriteWithFile("HelloWorld.png");
//	this->addChild(sprite);
//	
//	sprite->setPosition( 
//		ccp(sprite->getContentSize().width / 2
//		, sprite->getContentSize().height / 2) );
//	sprite->setIsVisible(false);
//
//	for(int i=0; i<10; i++) {
//		for(int j=0; j<5; j++) {
//			CCSprite* sprite2 = CCSprite::spriteWithFile
//				("CloseNormal.png");
//			this->addChild(sprite2);
//
//			sprite2->setPosition(
//				ccp(i * 50, j * 100));
//			sprite2->setIsVisible(false);
//
//			int value = i * 10 + j;
//			char str[10];
//			sprintf(str, "%d", value);
//			CCLabelTTF* label = CCLabelTTF::
//				labelWithString(str, "Arial", 30);
//			this->addChild(label);
//			label->setPosition(ccp(i * 50, j * 100));
//        label->setIsVisible(false);
//		}	
//	}
//
//	CCLabelTTF* label = CCLabelTTF::
//		labelWithString("Hello Hello Hanza?", "Arial", 30);
//	this->addChild(label);
//	label->setPosition(ccp(100,100));
//    label->setIsVisible(false);
//    
//    totalTime = 0;
//    
////    this->schedule(schedule_selector(TestLayer::myScheduler));
//    
//    moveSprite = CCSprite::spriteWithFile("CloseNormal.png");
//    this->addChild(moveSprite);
//    moveSprite->setIsVisible(false);
//    
//    CCMoveTo* moveTo = CCMoveTo::actionWithDuration(10, ccp(500, 150));
//    moveSprite->runAction(moveTo);
//    
    srand(time(NULL));

    for (int i=0; i<50; i++) {
        // bullet 생성
        BulletSprite* bullet = new BulletSprite();
        bullet->initWithFile("CloseNormal.png");
        this->addChild(bullet);
        bullet->setPosition(ccp(rand() % 500, rand() % 500));
        bullet->release();
        
        bullets.push_back(bullet);
        
        bullet->setVelocity(ccp(rand() % 40, rand() % 40));
    }
    
    this->schedule(schedule_selector(TestLayer::myScheduler));
    

	return true;
}

void TestLayer::myScheduler(float dt) {
    totalTime += dt;
    
    for (int i=0; i<bullets.size(); i++) {
        BulletSprite* bullet = bullets[i];
        
        int x = bullet->getPosition().x;
        int y = bullet->getPosition().y;
        int vx = bullet->getVelocity().x;
        int vy = bullet->getVelocity().y;
        
        float width = CCDirector::sharedDirector()->getWinSize().width;
        float height = CCDirector::sharedDirector()->getWinSize().height;
        
        bullet->setPosition(ccp(
                                (x + vx) % (int)width, 
                                (y + vy) % (int)height));
        
    }
}