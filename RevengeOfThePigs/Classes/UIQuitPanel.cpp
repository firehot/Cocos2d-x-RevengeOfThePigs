//
//  UIQuitPanel.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-25.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UIQuitPanel.h"
#include "MyCCMenu.h"
#include "GameResources.h"
#include "SceneManager.h"

UIQuitPanel::UIQuitPanel()
: m_pBgLayerColor(NULL)
{
    
}

UIQuitPanel::~UIQuitPanel()
{
    
}

CCScene* UIQuitPanel::scene()
{
    CCScene* scene = CCScene::node();
    UIQuitPanel* layer = UIQuitPanel::node();
    scene->addChild(layer);
    return scene;
}

bool UIQuitPanel::init()
{
	this->setIsKeypadEnabled(true);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_pBgLayerColor = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
    this->addChild(m_pBgLayerColor, 0);
    m_pBgLayerColor->runAction(CCFadeTo::actionWithDuration(0.2f, 127));
    
    CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathQuit_Quit);
    bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    bgSprite->setScale(CCGetScaleX());
    this->addChild(bgSprite, 1);
    
    CCPoint bgPosition = bgSprite->getPosition();
    CCSize bgSize = bgSprite->getContentSize();
    
	CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Yes);
	CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
	CCMenuItemSprite* yesBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
   // CCMenuItemImage* yesBtn = CCMenuItemImage::itemFromNormalImage(s_pPathYes, s_pPathYes);
    CCSize yesSize = yesBtn->getContentSize();
    yesBtn->setScale(CCGetScaleX());
    yesBtn->setPosition(bgPosition.x-bgSize.width/4*CCGetScaleX(), bgPosition.y-yesSize.height*1.5f/2*CCGetScaleX());
    yesBtn->setTag(1001);
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_No);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_No);
	CCMenuItemSprite* noBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
  //  CCMenuItemImage* noBtn = CCMenuItemImage::itemFromNormalImage(s_pPathNo, s_pPathNo);
    CCSize noSize = noBtn->getContentSize();
    noBtn->setScale(CCGetScaleX());
    noBtn->setPosition(bgPosition.x+bgSize.width/4*CCGetScaleX(), bgPosition.y-noSize.height*1.5f/2*CCGetScaleX());
    noBtn->setTag(1002);
    
    MyCCMenu* myMenu = MyCCMenu::menuWithItems(yesBtn, noBtn, NULL);
    myMenu->setPosition(ccp(0, 0));
    myMenu->setTag(2001);
    myMenu->SetDownUpHandle(this,
                            menu_selector(UIQuitPanel::BtnDownCallback),
                            menu_selector(UIQuitPanel::BtnUpInCallback),
                            menu_selector(UIQuitPanel::BtnUpOutCallback));
    this->addChild(myMenu, 2);
    
    return true;
}

bool UIQuitPanel::containsTouchLocation(CCTouch* pTouch)
{
    CCPoint touchLocation = pTouch->locationInView(pTouch->view());
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    CCRect myRect = CCRectMake(this->getPosition().x, this->getPosition().y,
                               this->getContentSize().width, this->getContentSize().height);
    return CCRect::CCRectContainsPoint(myRect, touchLocation);
}

bool UIQuitPanel::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    /*
    if (containsTouchLocation(touch))
    {
        return true;
    }
     */
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
    if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
        return false;
    return true;
}

void UIQuitPanel::onExit()
{
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void UIQuitPanel::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
    
    if ( pBtn->getTag() == 1001 )
    {
        //yes
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
    else if ( pBtn->getTag() == 1002 )
    {
        //no
        m_pBgLayerColor->runAction(CCSequence::actions(CCFadeTo::actionWithDuration(0.2f, 0),
                                                       CCCallFunc::actionWithTarget(this, callfunc_selector(UIQuitPanel::RemoveSelfFromParent)),
                                                       NULL));
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/quit.plist");
    }
}

void UIQuitPanel::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UIQuitPanel::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UIQuitPanel::RemoveSelfFromParent()
{
    this->getParent()->removeFromParentAndCleanup(true);
}

void UIQuitPanel::keyBackClicked()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
	}

	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}





