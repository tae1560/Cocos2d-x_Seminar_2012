// DragonFlightLayer.cpp
#include "DragonFlightLayer.h"
#include "YoumSprite.h"

bool DragonFlightLayer::init() 
{
	if ( !CCLayer::init())
		return false;
	

	// 5√ ∏∂¥Ÿ «—π¯æø ª˝º∫
	// ª˝º∫µ» ∞ÕµÈ¿∫ ¿Ãµø
	// ¿Ãµø¿Ã ≥°≥™∏È ªË¡¶
	 
	// Ω√∞£µøæ» ±‚¥Ÿ∏Æ¥¬ æ◊º«
	CCDelayTime *delay = CCDelayTime::create(5.0); // Ω√∞£ : 5.0√   

	// «‘ºˆ∏¶ »£√‚«œ¥¬ æ◊º«
	CCCallFunc *callCreateFunction = CCCallFunc::create(this,
		callfunc_selector(DragonFlightLayer::createEnemy));

	// æ◊º«µÈ¿ª π≠æÓ ¡Ÿ ∞Õ  ¬¸¡∂ : CCSpawn
	CCFiniteTimeAction *seq = CCSequence::create(delay,
		callCreateFunction,
		NULL);

	// π´«—π›∫π æ◊º«
	CCRepeatForever *repeatAction = CCRepeatForever::create(
		(CCActionInterval*) seq);

	// æ◊º« Ω««‡
	this->runAction(repeatAction);
    
    CCDelayTime *delay_0_1s = CCDelayTime::create(0.5);
    CCCallFunc *call_fire_bullet_function = CCCallFunc::create(this, callfunc_selector( DragonFlightLayer::fire_bullet ));
    
    CCSequence *calling_every_time =
        (CCSequence*)CCSequence::create(delay_0_1s, call_fire_bullet_function, NULL);
    
    this->runAction(CCRepeatForever::create( calling_every_time ));


	// ªÁøÎ¿⁄ ƒ≥∏Ø≈Õ ∏∏µÈ±‚
	player = CCSprite::create("plane.png");
	this->addChild(player);

	float screen_width = CCDirector::sharedDirector()->getWinSize().width;
	float player_height = player->getContentSize().height;
	player->setPosition(ccp(screen_width / 2 , player_height / 2));

	this->setTouchEnabled(true);
	this->schedule(schedule_selector(DragonFlightLayer::myScheduler));
    
    total_time = 0;

	return true;
}

// createEnemy ±∏«ˆ
void DragonFlightLayer::createEnemy() {
	CCLOG("createEnemy");

	for (int i=0; i<5; i++) {
		// enemy
		YoumSprite* sprite = YoumSprite::create("CloseNormal.png");
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
			callfuncN_selector(DragonFlightLayer::delete_enemy));
		// sequence
		CCActionInterval *seq = (CCActionInterval*) 
			CCSequence::create(moveTo, callFunc, NULL);

		sprite->runAction(seq);
	}
}

void DragonFlightLayer::delete_enemy(CCNode* node) {
	node->removeFromParentAndCleanup(true);
	
	// remove to list
	enemies.remove((YoumSprite*)node);
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

	// π€¿∏∑Œ ≥™∞°¡ˆ ∏∂!
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
	// √º≈©«“ ¥ÎªÛ : player vs enemy
    total_time += dt;
    
	// player¥¬ ¿÷¿Ω
	// enemiesµµ ¿÷¿Ω
	list<YoumSprite *>::iterator iter;
    bool is_bullet_deleted = false;
	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
        // iterate enemy
		YoumSprite *enemy = *iter;
		
		if (enemy->boundingBox().intersectsRect(player->boundingBox())) {
			// √Êµπ ≥≠∞Õ
			
            CCScene* scene = CCScene::create();
            
            CCLayer* layer = CCLayer::create();
            scene->addChild(layer);
            
            CCLabelTTF* gameoverLabel = CCLabelTTF::create("Jinji GameOver", "arial", 50);
            layer->addChild(gameoverLabel);
            gameoverLabel->setPosition(ccp(layer->getContentSize().width / 2, layer->getContentSize().height / 2));
            
            CCDirector::sharedDirector()->replaceScene(scene);
            
			break;
		}
        
        list<CCSprite *>::iterator bullet_iter;
        for (bullet_iter = bullets.begin(); bullet_iter != bullets.end(); bullet_iter++) {
            CCSprite *bullet = *bullet_iter;
            
            if (enemy->boundingBox().intersectsRect(bullet->boundingBox())) {
                // enemy hited by bullet
                this->delete_bullet(bullet);
                
                enemy->decrease_hp(50);
                if (! enemy->is_alive()) {
                    // remove enemy
                    this->delete_enemy(enemy);
                    is_bullet_deleted = true;
                }
                
                break;
            }
        }
        
        if (is_bullet_deleted) {
            break;
        }
	}
    
}

void DragonFlightLayer::fire_bullet() {
    // firebullet
    CCSprite* bullet = CCSprite::create("plane.png");
    this->addChild(bullet);
    
    bullets.push_back(bullet);
    
    bullet->setPosition(player->getPosition());
    
    CCMoveBy *moveby = CCMoveBy::create(5.0,
        ccp(0, CCDirector::sharedDirector()->getWinSize().height));
    
    CCCallFuncN *delete_bullet = CCCallFuncN::create(
                                                this,
                                                callfuncN_selector(DragonFlightLayer::delete_bullet));
    
    bullet->runAction(CCSequence::create(moveby,
                                         delete_bullet,
                                         NULL));
}

void DragonFlightLayer::delete_bullet(CCNode* node) {
    node->removeFromParentAndCleanup(true);
    
    bullets.remove((CCSprite*)node);
}