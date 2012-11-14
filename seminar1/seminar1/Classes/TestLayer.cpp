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
	totalTime = 0;

    for (int i=0; i<10; i++) {
        // bullet 생성
        BulletSprite* bullet = new BulletSprite();
        bullet->initWithFile("CloseNormal.png");
        this->addChild(bullet);
		//위치설정
        bullet->setPosition(ccp(rand() % 500, 0));
        bullet->release();
        
        bullets.push_back(bullet);
        //속도설정
        bullet->setVelocity(ccp(rand() % 100 - 50, rand() % 80 - 40));
    }
    
    this->schedule(schedule_selector(TestLayer::myScheduler));
    
	this->setTouchEnabled(true);

	followSprite = CCSprite::spriteWithFile("plane.png");
	this->addChild(followSprite);
	//followSprite->setScale(0.3f);

	followSprite->setPosition( ccp(200, 150) );

	stateLabel = CCLabelTTF::create("Test","Arial",30);
	this->addChild(stateLabel);
	stateLabel->setPosition(ccp(200, 400));

	char temp[10];
	int t = -5 % 3;
	sprintf(temp, "%d", t);
	stateLabel->setString(temp);

	return true;
}

void TestLayer::myScheduler(float dt) {
    totalTime += dt;

	char buf[100];
	sprintf(buf, "%f", totalTime);
	stateLabel->setString(buf);
    
    for (int i=0; i<bullets.size(); i++) {
        BulletSprite* bullet = bullets[i];
        
        float x = bullet->getPosition().x;
        float y = bullet->getPosition().y;

		// -20~19
        float vx = bullet->getVelocity().x * dt;
        float vy = bullet->getVelocity().y * dt;
        
        float width = CCDirector::sharedDirector()->getWinSize().width;
        float height = CCDirector::sharedDirector()->getWinSize().height;
        
        bullet->setPosition(ccp(
                                (int)(x + vx + width) % (int)width, 
                                (int)(y + vy + height) % (int)height));
        

		if ( followSprite->boundingBox().
			intersectsRect(
			bullet->boundingBox())) {
			// event 처리 부딪혔을때
				stateLabel->setString("부딪힘 ㅠㅠ");
				CCDirector::sharedDirector()
					->stopAnimation();
		}
    }
}

void TestLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint point = touch->getLocation();
	CCLog("Began %f %f", point.x, point.y);

	followSprite->setPosition(point);

	/*
	if (isSpriteIncludePoint(followSprite, point)) 
		stateLabel->setString("Sprite touched");
	else
		stateLabel->setString("Not touched");
		*/

	
}
void TestLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint point = touch->getLocation();
	CCLog("Moved %f %f", point.x, point.y);

	followSprite->setPosition(point);

	// make followSprite to follow touch location
	//followSprite->setPosition(point);
}
void TestLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint point = touch->getLocation();
	CCLog("Ended %f %f", point.x, point.y);
}
void TestLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {
	CCLog("Cancelled");
	CCLog("Cancelled %d", 5);
}

bool TestLayer::isSpriteIncludePoint(CCSprite* sprite, CCPoint point) {
	CCPoint spritePosition = sprite->getPosition();
	CCSize spriteSize = sprite->getContentSize();
	float spriteScale = sprite->getScale();

	if ( spritePosition.x - spriteSize.width * spriteScale / 2<= point.x
		&& spritePosition.x + spriteSize.width * spriteScale / 2 >= point.x
		&& spritePosition.y - spriteSize.height * spriteScale / 2<= point.y
		&& spritePosition.y + spriteSize.height * spriteScale / 2 >= point.y) {
			// if sprite touched
		return true;
	} else {
		return false;
	}
}