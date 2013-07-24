//
//  UIBgLightLayer.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-27.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UIBgLightLayer.h"
#include "GameResources.h"

UIBgLightLayer::UIBgLightLayer()
{
    
}

UIBgLightLayer::~UIBgLightLayer()
{
    
}

CCScene* UIBgLightLayer::scene()
{
    CCScene* scene = CCScene::node();
    UIBgLightLayer* layer = UIBgLightLayer::node();
    scene->addChild(layer);
    return scene;
}

bool UIBgLightLayer::init()
{
	CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathLight);
	bgSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height*0.6f/2));
	bgSprite->setScale(CCGetScaleX());
	bgSprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(25.0f, 360)));
	this->addChild(bgSprite, 0);

	//
	/*
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCNode* pNode = CCNode::node();
	for ( int i = 1; i <= 4; ++i )
	{
		char frameName[50] = {0};
		sprintf(frameName, "Start_Panel/Start_BackDrop%d.png", i);
		CCSprite* bgSprite1 = CCSprite::spriteWithFile(frameName);
		bgSprite1->setAnchorPoint(ccp(0, 0.5f));
		bgSprite1->setPosition(ccp(winSize.width/4*(i-3), 0));
		bgSprite1->setScaleX(CCGetScaleX());
		bgSprite1->setScaleY(CCGetScaleY());
		pNode->addChild(bgSprite1, 0);
	}
	pNode->setPosition(ccp(winSize.width/2, winSize.height/2));
	pNode->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(25.0f, 360)));
	this->addChild(pNode, 0);
	*/
	//
    
    return true;
}

void UIBgLightLayer::visit()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    glEnable(GL_SCISSOR_TEST);  //启用裁剪测试;
    CCDirector::sharedDirector()->getOpenGLView()->setScissorInPoints(0, winSize.height*1.5f/4, winSize.width, winSize.height*2.5f/4);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST); //禁用裁剪测试;

	//const GLubyte* name = glGetString(GL_VERSION);
}

