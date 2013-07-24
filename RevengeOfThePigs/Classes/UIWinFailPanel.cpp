//
//  UIWinFailPanel.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-26.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UIWinFailPanel.h"
#include "MyCCMenu.h"
#include "GameResources.h"
#include "SceneManager.h"

int CurBigLevelID0;
bool newrecord;

UIWinFailPanel::UIWinFailPanel()
: m_pBgLayerColor(NULL)
, m_pScoreLabel(NULL)
, m_lStarBgSprite(NULL)
, m_mStarBgSprite(NULL)
, m_rStarBgSprite(NULL)
, m_iTotalScore(0)
, m_iStarsCount(1)
{
    
}

UIWinFailPanel::~UIWinFailPanel()
{
    
}

CCScene* UIWinFailPanel::scene( bool bWin, int stars, int score, int CurBigLevelID,bool n_record,bool bHasNextStage)
{
	CurBigLevelID0 = CurBigLevelID;
	newrecord = n_record;
    CCScene* scene = CCScene::node();
    UIWinFailPanel* layer = UIWinFailPanel::node();
    if ( bWin )
        layer->InitWinLayout(stars, score, score, bHasNextStage);
    else
        layer->InitFailLayout(s_pPathWinFail_FailedMonkey, false);
    scene->addChild(layer);
    return scene;
}

UIWinFailPanel* UIWinFailPanel::layer()
{
    UIWinFailPanel* layer = UIWinFailPanel::node();
    return layer;
}

bool UIWinFailPanel::init()
{
	this->setIsKeypadEnabled(true);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/Win_Fail.plist");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_pBgLayerColor = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
    this->addChild(m_pBgLayerColor, 0);
    m_pBgLayerColor->runAction(CCFadeTo::actionWithDuration(0.2f, 127));
    
    CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathWinFail_ScorePanal);
    bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    bgSprite->setScale(CCGetScaleX());
    this->addChild(bgSprite, 1);
    
    return true;
}

void UIWinFailPanel::InitWinLayout( int stars, int score, int bestScore, bool bHasNextStage )
{
    CCSprite* titleSprite = CCSprite::spriteWithFile(s_pPathWinFail_Complted);
    titleSprite->setScale(CCGetScaleX());
    titleSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height-titleSprite->getContentSize().height*2*CCGetScaleX()));
    this->addChild(titleSprite, 2);
    
    m_lStarBgSprite = CCSprite::spriteWithFile(s_pPathWinFail_Star_L_Shadow);
    m_lStarBgSprite->setScale(CCGetScaleX());
    m_lStarBgSprite->setPosition(ccp(CCGetWinSize().width/2-m_lStarBgSprite->getContentSize().width*1.4f*CCGetScaleX(),
                                   CCGetWinSize().height/2+m_lStarBgSprite->getContentSize().height*CCGetScaleX()));
    this->addChild(m_lStarBgSprite, 2);
    
    m_mStarBgSprite = CCSprite::spriteWithFile(s_pPathWinFail_Star_M_Shadow);
    m_mStarBgSprite->setScale(CCGetScaleX());
    m_mStarBgSprite->setPosition(ccp(CCGetWinSize().width/2,
                                   CCGetWinSize().height/2+m_mStarBgSprite->getContentSize().height*CCGetScaleX()));
    this->addChild(m_mStarBgSprite, 2);
    
    m_rStarBgSprite = CCSprite::spriteWithFile(s_pPathWinFail_Star_R_Shadow);
    m_rStarBgSprite->setScale(CCGetScaleX());
    m_rStarBgSprite->setPosition(ccp(CCGetWinSize().width/2+m_rStarBgSprite->getContentSize().width*1.4f*CCGetScaleX(),
                                   CCGetWinSize().height/2+m_rStarBgSprite->getContentSize().height*CCGetScaleX()));
    this->addChild(m_rStarBgSprite, 2);
    
    m_pScoreLabel = CCLabelAtlas::labelWithString("0", s_pPathCount2, 30, 50, '0');
    m_pScoreLabel->setScale(CCGetScaleX());
    m_pScoreLabel->setAnchorPoint(CCPointMake(0.5, 0));
    m_pScoreLabel->setPosition(ccp(m_mStarBgSprite->getPosition().x, CCGetWinSize().height/2-50));
    this->addChild(m_pScoreLabel, 2);
    
    CCScaleTo* action1 = NULL;
    CCScaleTo* action2 = NULL;
    CCScaleTo* action3 = NULL;
	CCScaleTo* action4 = NULL;
	CCScaleTo* action5 = NULL;      //开启新关卡提示;
    CCSprite* lStarSprite = NULL;
    CCSprite* mStarSprite = NULL;
    CCSprite* rStarSprite = NULL;
	CCSprite* NewrecordSprite = NULL;
	CCSprite* OpenNewGate = NULL;

	char GateNumber[30] = {0};
	sprintf(GateNumber,"IsOpen%d1",CurBigLevelID0+1);
	bool IsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey(GateNumber);

    if ( stars >= 1 )
    {
        lStarSprite = CCSprite::spriteWithFile(s_pPathWinFail_Star_L);
        lStarSprite->setScale(0);
        lStarSprite->setPosition(m_lStarBgSprite->getPosition());
        this->addChild(lStarSprite, 3);
        
        action1 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
    }
    
    if ( stars >= 2 )
    {
        mStarSprite = CCSprite::spriteWithFile(s_pPathWinFail_Star_M);
        mStarSprite->setScale(0);
        mStarSprite->setPosition(m_mStarBgSprite->getPosition());
        this->addChild(mStarSprite, 3);
        
        action2 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
    }
    
    if ( stars >= 3 )
    {
        rStarSprite = CCSprite::spriteWithFile(s_pPathWinFail_Star_R);
        rStarSprite->setScale(0);
        rStarSprite->setPosition(m_rStarBgSprite->getPosition());
        this->addChild(rStarSprite, 3);
        
        action3 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
        //rStarSprite->runAction(action3);
    }	
	
	if (newrecord)
	{
		//CCLOG("newrecord!");
		NewrecordSprite = CCSprite::spriteWithFile(s_pPathWinFail_NewHighScore);
		NewrecordSprite->setScale(0);
		NewrecordSprite->setPosition(ccp(m_rStarBgSprite->getPosition().x,m_rStarBgSprite->getPosition().y-70));
		this->addChild(NewrecordSprite, 3);

		action4 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
	}
	
	//显示开启新关卡提示;
	if(!IsOpen && !bHasNextStage)
	{
		OpenNewGate = CCSprite::spriteWithFile(s_pPathWinFail_GateOpen);
		OpenNewGate->setScale(0);
		OpenNewGate->setPosition(ccp(CCGetWinSize().width/2,CCGetWinSize().height/2));
		this->addChild(OpenNewGate,4);

		action5 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
	}
	
    
    float fDelayTime = 0.8f;
    lStarSprite->runAction(CCSequence::actions(action1, NULL));
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWinStar_1,false);
	}
    
    CreateWinStarEffect(s_pPathWinFail_Star_ss1, m_lStarBgSprite->getPosition(), 0);
    CreateWinStarEffect(s_pPathWinFail_Star_ss4, m_lStarBgSprite->getPosition(), 0);
    CreateWinStarEffect(s_pPathWinFail_Star_ss5, m_lStarBgSprite->getPosition(), 0);
    CreateWinStarEffect(s_pPathWinFail_Star_ss7, m_lStarBgSprite->getPosition(), 0);
    
    m_iTotalScore = score;
    m_iStarsCount = stars;
    m_iCurScore = 0;
    this->schedule(schedule_selector(UIWinFailPanel::CountScore));

    if ( action2 != NULL )
    {
        mStarSprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(fDelayTime),
                                                   CCCallFunc::actionWithTarget(this, callfunc_selector(UIWinFailPanel::PopStarMFinishedCallback)),
                                                   action2,
                                                   NULL));
        fDelayTime += 0.8f;
    }
    if ( action3 != NULL )
    {
        rStarSprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(fDelayTime),
                                                   CCCallFunc::actionWithTarget(this, callfunc_selector(UIWinFailPanel::PopStarRFinishedCallback)),
                                                   action3,
                                                   NULL));
		fDelayTime += 0.8f;
    }
	if ( action4 != NULL )
	{
		NewrecordSprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(fDelayTime),
									CCCallFunc::actionWithTarget(this, callfunc_selector(UIWinFailPanel::NewRecordCallback)),
									action4,
									NULL));
		fDelayTime += 0.8f;
	}
	if(action5 != NULL)
	{
		OpenNewGate->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(fDelayTime),
										action5,
										NULL));
	}
    
    InitButtons(bHasNextStage,true);
}

void UIWinFailPanel::CountScore(ccTime delta)
{
    m_iCurScore += m_iTotalScore*delta*1/0.8f/m_iStarsCount;
    if ( m_iCurScore >= m_iTotalScore )
    {
        m_iCurScore = m_iTotalScore;
        this->unschedule(schedule_selector(UIWinFailPanel::CountScore));
    }
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		//分数滚动音效;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScoreRolling,false);
	}
	
    
    char string[8] = {0};
    sprintf(string, "%d", m_iCurScore);
    m_pScoreLabel->setString(string);
}

CCParticleSystem* UIWinFailPanel::CreateWinStarEffect( const char* image, CCPoint point, int location )
{
    CCParticleSystem* effect = CCParticleFireworks::node();
    effect->setPosition(point);
    effect->setTexture(CCTextureCache::sharedTextureCache()->addImage(image));
    effect->setTotalParticles(5);
    effect->setLife(5.0f);
    effect->setLifeVar(0);
    effect->setGravity(CCPointMake(0, -90));
    effect->setDuration(0.5f);
    ccColor4F color = {1,1,1,1};
    ccColor4F colorVar = {0,0,0,0};
    effect->setStartColor(color);
    effect->setStartColorVar(colorVar);
    effect->setEndColor(color);
    effect->setIsAutoRemoveOnFinish(true);
    effect->setEndColorVar(colorVar);
    effect->setStartSpin(-720);
    effect->setStartSize(14);
    effect->setEndSize(1);
    if ( location == 0 ) //left
    {
        effect->setAngle(135);
        effect->setAngleVar(90);
    }
    else if ( location == 1 ) //middle
    {
        effect->setAngle(90);
        effect->setAngleVar(90);
    }
    else if ( location == 2 ) //right
    {
        effect->setAngle(45);
        effect->setAngleVar(90);
    }
    
    this->addChild(effect, 4);
    
    return effect;
}

void UIWinFailPanel::PopStarLFinishedCallback()
{
    
}

void UIWinFailPanel::PopStarMFinishedCallback()
{
    CreateWinStarEffect(s_pPathWinFail_Star_ss1, m_mStarBgSprite->getPosition(), 1);
    CreateWinStarEffect(s_pPathWinFail_Star_ss4, m_mStarBgSprite->getPosition(), 1);
    CreateWinStarEffect(s_pPathWinFail_Star_ss5, m_mStarBgSprite->getPosition(), 1);
    CreateWinStarEffect(s_pPathWinFail_Star_ss7, m_mStarBgSprite->getPosition(), 1);
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWinStar_2,false);
	}
}

void UIWinFailPanel::PopStarRFinishedCallback()
{
    CreateWinStarEffect(s_pPathWinFail_Star_ss1, m_rStarBgSprite->getPosition(), 2);
    CreateWinStarEffect(s_pPathWinFail_Star_ss4, m_rStarBgSprite->getPosition(), 2);
    CreateWinStarEffect(s_pPathWinFail_Star_ss5, m_rStarBgSprite->getPosition(), 2);
    CreateWinStarEffect(s_pPathWinFail_Star_ss7, m_rStarBgSprite->getPosition(), 2);
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWinStar_3,false);
	}
}

void UIWinFailPanel::NewRecordCallback()
{
	PlayNewRecordSound();
}

void UIWinFailPanel::PlayNewRecordSound()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNewRecord,false);
	}
}

void UIWinFailPanel::InitFailLayout( const char* stageImage, bool bHasNextStage )
{
    CCSprite* titleSprite = CCSprite::spriteWithFile(s_pPathWinFail_Failed);
    titleSprite->setScale(CCGetScaleX());
    titleSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height-titleSprite->getContentSize().height*6*CCGetScaleX()));
    this->addChild(titleSprite, 2);

	char frameName[50] = {0};
	sprintf(frameName, "%s%d.png", stageImage, 1);
    CCSprite* stageSprite = CCSprite::spriteWithFile(frameName);
    stageSprite->setScale(CCGetScaleX());
    stageSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height/2));
    this->addChild(stageSprite, 2);

	CCAnimation* animation = CCAnimation::animation();
	for (int i = 1; i <= 6; i++)
	{
		sprintf(frameName, "%s%d.png", stageImage, i);
		animation->addFrameWithFileName(frameName);
	}

	CCAnimate *animate = CCAnimate::actionWithDuration(0.8f, animation, false);
	stageSprite->runAction(CCRepeatForever::actionWithAction(animate));  

    InitButtons(bHasNextStage, false);
}

void UIWinFailPanel::InitButtons( bool bHasNextStage, bool IsWin)
{
    CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_GateChoose);
    CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_GateChoose);
    CCMenuItemSprite*stageChooseBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    // CCMenuItemImage* stageChooseBtn = CCMenuItemImage::itemFromNormalImage(s_pPathGateChoose, s_pPathGateChoose);
    stageChooseBtn->setScale(CCGetScaleX());
    stageChooseBtn->setTag(1001);

    yesb= CCSprite::spriteWithFile(s_pPathButtons_Replay);
    yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Replay);
    CCMenuItemSprite*replayBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
   // CCMenuItemImage* replayBtn = CCMenuItemImage::itemFromNormalImage(s_pPathReplay, s_pPathReplay);
    replayBtn->setScale(CCGetScaleX());
    replayBtn->setTag(1002);

	stageChooseBtn->setPosition(ccp(CCGetWinSize().width/2-stageChooseBtn->getContentSize().width*CCGetScaleX(),
		stageChooseBtn->getContentSize().height*CCGetScaleX()));
	replayBtn->setPosition(ccp(CCGetWinSize().width/2,
		replayBtn->getContentSize().height*CCGetScaleX()));

    CCMenuItemSprite* nextStageBtn = NULL;     //下一关按钮;


    CCPoint beginPos;
    if ( bHasNextStage )
    {
		yesb= CCSprite::spriteWithFile(s_pPathButtons_NextGate);
		yesb2 = CCSprite::spriteWithFile(s_pPathButtons_NextGate);
		nextStageBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
        //nextStageBtn = CCMenuItemImage::itemFromNormalImage(s_pPathNextGate, s_pPathNextGate);
        nextStageBtn->setScale(CCGetScaleX());
        nextStageBtn->setPosition(ccp(CCGetWinSize().width/2+nextStageBtn->getContentSize().width*CCGetScaleX(),
                                      stageChooseBtn->getContentSize().height*CCGetScaleX()));
        nextStageBtn->setTag(1003);
    } 
    else if(IsWin)   //跳到下一大关;
    {
		//添加跳到下一大关的按钮;
		yesb= CCSprite::spriteWithFile(s_pPathButtons_NextGate);
		yesb2 = CCSprite::spriteWithFile(s_pPathButtons_NextGate);
		nextStageBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
		nextStageBtn->setScale(CCGetScaleX());
		nextStageBtn->setPosition(ccp(CCGetWinSize().width/2+nextStageBtn->getContentSize().width*CCGetScaleX(),
			stageChooseBtn->getContentSize().height*CCGetScaleX()));
		nextStageBtn->setTag(1004);
    }
    
    MyCCMenu* pMenu = NULL;
    if ( nextStageBtn != NULL )
        pMenu = MyCCMenu::menuWithItems(stageChooseBtn, replayBtn, nextStageBtn, NULL);
    else
        pMenu = MyCCMenu::menuWithItems(stageChooseBtn, replayBtn, NULL);
    pMenu->setPosition(ccp(0, 0));
    pMenu->setTag(2001);
    pMenu->SetDownUpHandle(this,
                           menu_selector(UIWinFailPanel::BtnDownCallback),
                           menu_selector(UIWinFailPanel::BtnUpInCallback),
                           menu_selector(UIWinFailPanel::BtnUpOutCallback));
    this->addChild(pMenu, 3);
}

bool UIWinFailPanel::containsTouchLocation(CCTouch* pTouch)
{
    CCPoint touchLocation = pTouch->locationInView(pTouch->view());
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    CCRect myRect = CCRectMake(this->getPosition().x, this->getPosition().y,
                               this->getContentSize().width, this->getContentSize().height);
    return CCRect::CCRectContainsPoint(myRect, touchLocation);
}

bool UIWinFailPanel::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
    if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
        return false;
    return true;
}

void UIWinFailPanel::onExit()
{
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void UIWinFailPanel::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
    
    if ( pBtn->getTag() == 1001 )
    {
        //level choose
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/bigsmal_stage.plist");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
        SceneManager::SharedSceneManager()->JumpToSelectSmallStage(CurBigLevelID0);
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathBackGround_Music, true);
		}
    }
    else if ( pBtn->getTag() == 1002 )
    {
        //replay
        /*
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_pBgLayerColor->runAction(CCSequence::actions(CCFadeTo::actionWithDuration(0.2f, 0),
                                                       CCCallFunc::actionWithTarget(this, callfunc_selector(UIWinFailPanel::RemoveSelfFromParent)),
                                                       NULL));
         */
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
        SceneManager::SharedSceneManager()->JumpToGameLevel(SceneManager::SharedSceneManager()->m_iCurLevel);
        
    }
    else if ( pBtn->getTag() == 1003 )
    {
        //next
        /*
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_pBgLayerColor->runAction(CCSequence::actions(CCFadeTo::actionWithDuration(0.2f, 0),
                                                       CCCallFunc::actionWithTarget(this, callfunc_selector(UIWinFailPanel::RemoveSelfFromParent)),
                                                       NULL));
         */
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//{
		//	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		//}
        SceneManager::SharedSceneManager()->JumpToGameLevel(SceneManager::SharedSceneManager()->m_iCurLevel+1);
    }
	else if(pBtn->getTag() == 1004)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//{
			SceneManager::SharedSceneManager()->JumpToStory(CurBigLevelID0 + 1);
		//}
		/*else
		{
			SceneManager::SharedSceneManager()->JumpToNextStage(CurBigLevelID0 +1);
		}*/
	}
}

void UIWinFailPanel::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UIWinFailPanel::RemoveSelfFromParent()
{
    this->getParent()->removeFromParentAndCleanup(true);
}

void UIWinFailPanel::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/Win_Fail.plist");
}

void UIWinFailPanel::keyBackClicked()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/bigsmal_stage.plist");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SceneManager::SharedSceneManager()->JumpToSelectSmallStage(CurBigLevelID0);
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathBackGround_Music, true);
	}
}

