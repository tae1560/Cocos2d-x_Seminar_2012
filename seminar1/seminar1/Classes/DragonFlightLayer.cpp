// DragonFlightLayer.cpp
#include "DragonFlightLayer.h"

bool DragonFlightLayer::init() 
{
	if ( !CCLayer::init())
		return false;
	

	// 5초마다 한번씩 생성
	// 생성된 것들은 이동
	// 이동이 끝나면 삭제
	 
	// 시간동안 기다리는 액션
	CCDelayTime *delay = CCDelayTime::create(5.0); // 시간 : 5.0초  

	// 함수를 호출하는 액션
	CCCallFunc *callCreateFunction = CCCallFunc::create(this,
		callfunc_selector(DragonFlightLayer::createEnemy));

	// 액션들을 묶어 줄 것  참조 : CCSpawn
	CCFiniteTimeAction *seq = CCSequence::create(delay,
		callCreateFunction,
		NULL);

	// 무한반복 액션
	CCRepeatForever *repeatAction = CCRepeatForever::create(
		(CCActionInterval*) seq);

	// 액션 실행
	this->runAction(repeatAction);


	// 사용자 캐릭터 만들기
	player = CCSprite::create("plane.png");
	this->addChild(player);

	float screen_width = CCDirector::sharedDirector()->getWinSize().width;
	float player_height = player->getContentSize().height;
	player->setPosition(ccp(screen_width / 2 , player_height / 2));

	this->setTouchEnabled(true);
	this->schedule(schedule_selector(DragonFlightLayer::myScheduler));

	return true;
}

// createEnemy 구현
void DragonFlightLayer::createEnemy() {
	CCLOG("createEnemy");

	for (int i=0; i<5; i++) {
		// enemy
		CCSprite* sprite = CCSprite::create("CloseNormal.png");
		this->addChild(sprite);

		// add to list
		enemies.push_back(sprite);

		float width = CCDirector::sharedDirector()->getWinSize().width;
		float x = width / 6 * (i+1);
		float image_height = sprite->getContentSize().height;
		float y = CCDirector::sharedDirector()->getWinSize().height + image_height;

		sprite->setPosition(ccp(x,y));

		// move
		CCMoveTo *moveTo = CCMoveTo::create(3.0, ccp(x, -image_height));
		// call function
		CCCallFuncN *callFunc = CCCallFuncN::create(
			this,
			callfuncN_selector(DragonFlightLayer::afterMoveTo));
		// sequence
		CCActionInterval *seq = (CCActionInterval*) 
			CCSequence::create(moveTo, callFunc, NULL);

		sprite->runAction(seq);
	}
}

void DragonFlightLayer::afterMoveTo(CCNode* node) {
	node->removeFromParentAndCleanup(true);
	
	// remove to list
	enemies.remove((CCSprite*)node);
}


void DragonFlightLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint point = touch->getLocation();

	before_x = point.x;
}
void DragonFlightLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint point = touch->getLocation();

	float after_x = point.x;
	float diff = after_x - before_x;

	// move player 
	CCPoint before_position = player->getPosition();
	CCPoint after_position = ccp(before_position.x + diff, before_position.y);

	// 밖으로 나가지 마!
	float screen_width = CCDirector::sharedDirector()->getWinSize().width;
	if (after_position.x < 0) after_position.x = 0;
	else if (after_position.x > screen_width) after_position.x = screen_width;

	player->setPosition(after_position);

	before_x = point.x;
}
void DragonFlightLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint point = touch->getLocation();
}

void DragonFlightLayer::myScheduler(float dt) {
	// 체크할 대상 : player vs enemy
	// player는 있음
	// enemies도 있음
	list<CCSprite *>::iterator iter;
	list<CCSprite *>::iterator iter2;
	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		CCSprite *enemy = *iter;
		
		if (enemy->boundingBox().intersectsRect(player->boundingBox())) {
			// 충돌 난것
			enemies.remove(enemy);
			this->afterMoveTo(enemy);
			break;
		}
	}
}