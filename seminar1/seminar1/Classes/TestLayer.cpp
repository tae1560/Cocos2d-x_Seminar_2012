#include "TestLayer.h"

bool TestLayer::init() {
	if (!CCLayer::init()){
		return false;
	}

	// init
	CCSprite* sprite = CCSprite::spriteWithFile("HelloWorld.png");
	this->addChild(sprite);
	
	sprite->setPosition( 
		ccp(sprite->getContentSize().width / 2
		, sprite->getContentSize().height / 2) );
	sprite->setVisible(false);

	for(int i=0; i<10; i++) {
		for(int j=0; j<5; j++) {
			CCSprite* sprite2 = CCSprite::spriteWithFile
				("CloseNormal.png");
			this->addChild(sprite2);

			sprite2->setPosition(
				ccp(i * 50, j * 100));
			sprite2->setVisible(false);

			int value = i * 10 + j;
			char str[10];
			sprintf(str, "%d", value);
			CCLabelTTF* label = CCLabelTTF::
				labelWithString(str, "Arial", 30);
			this->addChild(label);
			label->setPosition(ccp(i * 50, j * 100));

		}	
	}

	CCLabelTTF* label = CCLabelTTF::
		labelWithString("Hello Hello Hanza?", "Arial", 30);
	this->addChild(label);
	label->setPosition(ccp(100,100));

	return true;
}