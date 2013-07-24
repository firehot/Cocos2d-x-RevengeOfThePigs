//
//  UISidePausePanel.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-26.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UISidePausePanel.h"
#include "GameResources.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
#include "LevelBase.h"

int BigLevelID;//声明一个用来存放大关卡ID的整形变量;
int SmallLevelID;

UISidePausePanel::UISidePausePanel()
: m_pBgSprite(NULL)
, m_pMenu(NULL)
, m_pBgLayerColor(NULL)
{
    
}

UISidePausePanel::~UISidePausePanel()
{
    
}

CCScene* UISidePausePanel::scene(int ID1,int ID2)
{
	BigLevelID = ID1;//获取当前大关卡ID，供返回小关卡选择界面使用;
	SmallLevelID = ID2;
	CCScene* scene = CCScene::node();
	UISidePausePanel* layer = UISidePausePanel::node();
	scene->addChild(layer);
	return scene;
}

bool UISidePausePanel::init()
{
	this->setIsKeypadEnabled(true);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/pause.plist");
    
    m_pBgLayerColor = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
    this->addChild(m_pBgLayerColor, 0);
    m_pBgLayerColor->runAction(CCFadeTo::actionWithDuration(0.2f, 127));
    
    m_pBgSprite = CCSprite::spriteWithFile(s_pPathPause_ScorePanel);
    m_pBgSprite->setPosition(ccp(winSize.width*0.8f/4, winSize.height/2));
    m_pBgSprite->setScale(CCGetScaleX());
    this->addChild(m_pBgSprite, 1);
    
	//获得当前大关ID和小关ID，并且显示到下面label中;
	char string[8] = {0};
	sprintf(string, "%d.%d", BigLevelID,SmallLevelID);

	CCLabelAtlas* curStageLabel = CCLabelAtlas::labelWithString(string, s_pPathCount1, 30, 50, '.');
	curStageLabel->setPosition(ccp(winSize.width/6, winSize.height*1.6f));
	m_pBgSprite->addChild(curStageLabel);
    
	CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Replay);
	CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Replay);
	CCMenuItemSprite* replayBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    //CCMenuItemImage* replayBtn = CCMenuItemImage::itemFromNormalImage(s_pPathReplay, s_pPathReplay);
    replayBtn->setScale(CCGetScaleX());
    replayBtn->setPosition(ccp(winSize.width*0.8f/6,
                               winSize.height/2+replayBtn->getContentSize().height*1.3f/2*CCGetScaleX()));
    replayBtn->setTag(1000);
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_GateChoose);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_GateChoose);
	CCMenuItemSprite* stageChooseBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    //CCMenuItemImage* stageChooseBtn = CCMenuItemImage::itemFromNormalImage(s_pPathGateChoose, s_pPathGateChoose);
    stageChooseBtn->setScale(CCGetScaleX());
    stageChooseBtn->setPosition(ccp(winSize.width*0.8f/6,
                                    winSize.height/2-stageChooseBtn->getContentSize().height*1.3f/2*CCGetScaleX()));
    stageChooseBtn->setTag(1001);
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_Goon);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Goon);
	CCMenuItemSprite* continueBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
   // CCMenuItemImage* continueBtn = CCMenuItemImage::itemFromNormalImage(s_pPathGoon, s_pPathGoon);
    continueBtn->setScale(CCGetScaleX());
    continueBtn->setPosition(ccp(winSize.width*1.1f/4, winSize.height/2));
    continueBtn->setTag(1002);
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_SoundControl);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_SoundControl);
	musicBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    //musicBtn = CCMenuItemImage::itemFromNormalImage(s_pPathSoundControl2, s_pPathSoundControl2);
    musicBtn->setScale(CCGetScaleX());
    musicBtn->setPosition(ccp(winSize.width*1.0f/12, musicBtn->getContentSize().height*CCGetScaleX()));
    musicBtn->setTag(1003);

	if (!SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())//获取声音状态，从而显示相应图标;
	{
		m_pNoSoundSprite = CCSprite::spriteWithFile(s_pPathStartPanel_NoSound);
		m_pNoSoundSprite->setPosition(CCPointMake(musicBtn->getContentSize().width/2,musicBtn->getContentSize().height/2));
		m_pNoSoundSprite->setScale(CCGetScaleX()*2);
		musicBtn->addChild(m_pNoSoundSprite,4);
	}
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_Question);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Question);
	CCMenuItemSprite* questionBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
   // CCMenuItemImage* questionBtn = CCMenuItemImage::itemFromNormalImage(s_pPathQuestion, s_pPathQuestion);
    questionBtn->setScale(CCGetScaleX());
    questionBtn->setPosition(ccp(winSize.width*1.2f/6, questionBtn->getContentSize().height*CCGetScaleX()));
    questionBtn->setTag(1004);
    
    m_pMenu = MyCCMenu::menuWithItems(replayBtn, stageChooseBtn, continueBtn, musicBtn, questionBtn, NULL);
    m_pMenu->setPosition(ccp(-winSize.width*1.4f/4, 0));
    m_pMenu->setTag(2001);
    m_pMenu->SetDownUpHandle(this,
                            menu_selector(UISidePausePanel::BtnDownCallback),
                            menu_selector(UISidePausePanel::BtnUpInCallback),
                            menu_selector(UISidePausePanel::BtnUpOutCallback));
    this->addChild(m_pMenu, 2);
    
	if ( SceneManager::SharedSceneManager()->bkeyHomeClicked )
	{
		m_pBgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
		m_pMenu->setPosition(ccp(0, 0));
		ActionCallBack();
	}
	else
	{
		m_pBgSprite->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(winSize.width/2, winSize.height/2)));
		m_pMenu->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0.2f, ccp(0, 0)), CCCallFunc::actionWithTarget(this, callfunc_selector(UISidePausePanel::ActionCallBack)),
			NULL));         //动作结束后, 设置游戏速度为0;
	}
    
    return true;
}

void UISidePausePanel::ActionCallBack()
{
	if ( SceneManager::SharedSceneManager()->GetPauseState() )
		CCScheduler::sharedScheduler()->setTimeScale(0);
}

bool UISidePausePanel::containsTouchLocation(CCTouch* pTouch)
{
    CCPoint touchLocation = pTouch->locationInView(pTouch->view());
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    CCRect myRect = CCRectMake(this->getPosition().x, this->getPosition().y,
                               this->getContentSize().width, this->getContentSize().height);
    return CCRect::CCRectContainsPoint(myRect, touchLocation);
}

bool UISidePausePanel::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
    if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
        return false;
    return true;
}

void UISidePausePanel::onExit()
{
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void UISidePausePanel::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
    
	if(pBtn->getTag() != 1003)							//暂停时点击任意非声音的按钮, 设置为可以暂停;
	{
		CCScheduler::sharedScheduler()->setTimeScale(1);
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/pause.plist");
	}

    if ( pBtn->getTag() == 1000 )
    {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
        SceneManager::SharedSceneManager()->JumpToGameLevel(SceneManager::SharedSceneManager()->m_iCurLevel);
    }
    else if ( pBtn->getTag() == 1001 )
    {
        //choose stage
		BackToSmallStage();
    }
    else if ( pBtn->getTag() == 1002 )
    {
        //continue
		SceneManager::SharedSceneManager()->SetPauseState(false);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_pBgSprite->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(winSize.width*0.8f/4, winSize.height/2)));
        m_pMenu->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(-winSize.width*1.4f/4, 0)));
        m_pBgLayerColor->runAction(CCSequence::actions(CCFadeTo::actionWithDuration(0.2f, 0),
                                                       CCCallFunc::actionWithTarget(this, callfunc_selector(UISidePausePanel::RemoveSelfFromParent)),
                                                       NULL));
    }
    else if ( pBtn->getTag() == 1003 )
    {
        //sound control
		SceneManager::SharedSceneManager()->SetPlayBackgroundMusicState();
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();//继续播放背景音乐;
			musicBtn->removeChild(m_pNoSoundSprite,true);//删除图标;
			//CCLOG("resume");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();//暂停播放背景音乐;
			m_pNoSoundSprite = CCSprite::spriteWithFile(s_pPathStartPanel_NoSound);//在声音按钮上添加一把叉的图标;
			m_pNoSoundSprite->setPosition(CCPointMake(musicBtn->getContentSize().width/2,musicBtn->getContentSize().height/2));
			m_pNoSoundSprite->setScale(CCGetScaleX()*2);
			musicBtn->addChild(m_pNoSoundSprite,4);
			//CCLOG("pause");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		}
    }
    else if ( pBtn->getTag() == 1004 )
    {
        //question
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_pBgSprite->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(winSize.width*0.8f/4, winSize.height/2)));//移除背景;
		m_pMenu->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(-winSize.width*1.4f/4, 0)));//移除功能菜单;
		m_pBgLayerColor->runAction(CCSequence::actions(CCFadeTo::actionWithDuration(0.2f, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(UISidePausePanel::RemoveSelfFromParent)),
			NULL));//清除背景颜色层;
		SceneManager::SharedSceneManager()->AddHelpPanel(getParent()->getParent(), 5);
	    
    }
}

void UISidePausePanel::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UISidePausePanel::RemoveSelfFromParent()
{
    this->getParent()->removeFromParentAndCleanup(true);
}

void UISidePausePanel::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UISidePausePanel::BackToSmallStage()
{
	SceneManager::SharedSceneManager()->SetPauseState(false);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/UILevelbase.plist");  //delete pause, replay button;
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/bigsmal_stage.plist");  //回到小关时, 加载资源;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SceneManager::SharedSceneManager()->JumpToSelectSmallStage(BigLevelID);
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		//开始播放背景音乐;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathBackGround_Music, true);
	}
}

void UISidePausePanel::keyBackClicked()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
	}

	CCScheduler::sharedScheduler()->setTimeScale(1);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/pause.plist");

	BackToSmallStage();
}
