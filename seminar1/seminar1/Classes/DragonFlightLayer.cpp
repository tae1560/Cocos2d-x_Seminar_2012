// DragonFlightLayer.cpp
#include "DragonFlightLayer.h"

bool DragonFlightLayer::init() 
{
	if ( !CCLayer::init())
		return false;
	

	// 5�ʸ��� �ѹ��� ����
	// ������ �͵��� �̵�
	// �̵��� ������ ����
	 
	// �ð����� ��ٸ��� �׼�
	CCDelayTime *delay = CCDelayTime::create(5.0); // �ð� : 5.0��  

	// �Լ��� ȣ���ϴ� �׼�
	CCCallFunc *callCreateFunction = CCCallFunc::create(this,
		callfunc_selector(DragonFlightLayer::createEnemy));

	// �׼ǵ��� ���� �� ��  ���� : CCSpawn
	CCFiniteTimeAction *seq = CCSequence::create(delay,
		callCreateFunction,
		NULL);

	// ���ѹݺ� �׼�
	CCRepeatForever *repeatAction = CCRepeatForever::create(
		(CCActionInterval*) seq);

	// �׼� ����
	this->runAction(repeatAction);


	// ����� ĳ���� �����
	player = CCSprite::create("plane.png");
	this->addChild(player);

	float screen_width = CCDirector::sharedDirector()->getWinSize().width;
	float player_height = player->getContentSize().height;
	player->setPosition(ccp(screen_width / 2 , player_height / 2));

	this->setTouchEnabled(true);
	this->schedule(schedule_selector(DragonFlightLayer::myScheduler));

	return true;
}

// createEnemy ����
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

	// ������ ������ ��!
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
	// üũ�� ��� : player vs enemy
	// player�� ����
	// enemies�� ����
	list<CCSprite *>::iterator iter;
	list<CCSprite *>::iterator iter2;
	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		CCSprite *enemy = *iter;
		
		if (enemy->boundingBox().intersectsRect(player->boundingBox())) {
			// �浹 ����
			enemies.remove(enemy);
			this->afterMoveTo(enemy);
			break;
		}
	}
}