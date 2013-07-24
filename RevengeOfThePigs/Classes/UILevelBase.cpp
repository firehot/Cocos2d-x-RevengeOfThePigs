//
//  MyBaseLevel.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-26.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UILevelBase.h"
#include "MyCCMenu.h"
#include "GameResources.h"
#include "SceneManager.h"
#include "Level.h"

UILevelBase::UILevelBase()
	: m_animSprite(NULL)
	, m_bChoosing(false)
{
    PreInit();
}

UILevelBase::~UILevelBase()
{
    
}

CCScene* UILevelBase::scene()
{
    CCScene* scene = CCScene::node();
    UILevelBase* layer = UILevelBase::node();
    scene->addChild(layer);
    return scene;
}

void UILevelBase::PreInit()
{
    init();
}

bool UILevelBase::init()
{
	this->setIsKeypadEnabled(true);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/UILevelbase.plist");
	CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Pause);
	CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Pause);
	CCMenuItemSprite* pauseBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
//    CCMenuItemImage* pauseBtn = CCMenuItemImage::itemFromNormalImage(s_pPathPause, s_pPathPause);
    pauseBtn->setScale(CCGetScaleX());
    pauseBtn->setPosition(ccp(pauseBtn->getContentSize().width*CCGetScaleX() - 12,
        CCGetWinSize().height-pauseBtn->getContentSize().height*CCGetScaleX() + 22));
    pauseBtn->setTag(1001);
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_Replay);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Replay);
	CCMenuItemSprite* replayBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    //CCMenuItemImage* replayBtn = CCMenuItemImage::itemFromNormalImage(s_pPathReplay1, s_pPathReplay1);
    replayBtn->setScale(CCGetScaleX());
    replayBtn->setPosition(ccp(replayBtn->getContentSize().width*2*CCGetScaleX() - 10,
                              CCGetWinSize().height-replayBtn->getContentSize().height*CCGetScaleX() + 22));
    replayBtn->setTag(1002);

	yesb= CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	yesb2 = CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	m_pChoosePigBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	//CCMenuItemImage* replayBtn = CCMenuItemImage::itemFromNormalImage(s_pPathReplay1, s_pPathReplay1);
	m_pChoosePigBtn->setScale(CCGetScaleX());
	m_pChoosePigBtn->setPosition(ccp(m_pChoosePigBtn->getContentSize().width*CCGetScaleX() - 12,
		m_pChoosePigBtn->getContentSize().height*CCGetScaleX() - 22));
	m_pChoosePigBtn->setTag(1003);
    
    MyCCMenu* myMenu = MyCCMenu::menuWithItems(pauseBtn, replayBtn, m_pChoosePigBtn, NULL);
    myMenu->setPosition(ccp(0, 0));
    myMenu->SetDownUpHandle(this,
                            menu_selector(UILevelBase::BtnDownCallback),
                            menu_selector(UILevelBase::BtnUpInCallback),
                            menu_selector(UILevelBase::BtnUpOutCallback));
    this->addChild(myMenu, 2);

	InitChoosePigPanel();
    
    return true;
}

void UILevelBase::InitChoosePigPanel()
{
	//choose pig panel
	m_pDropSprite = CCSprite::spriteWithFile(s_pPathChoosePigPanel_Drop);
	m_pDropSprite->setPosition(m_pChoosePigBtn->getPosition());
	m_pDropSprite->setScaleX(0);
	m_pDropSprite->setScaleY(CCGetScaleY());
	m_pDropSprite->setAnchorPoint(CCPointMake(0, 0.5f));
	this->addChild(m_pDropSprite, 0);

	CCSprite* yesb= CCSprite::spriteWithFile(s_pPathChoosePigPanel_NormalPig);
	CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathChoosePigPanel_NormalPig);
	m_pNormalPig = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pNormalPig->setScale(CCGetScaleX());
	m_pNormalPig->setPosition(m_pChoosePigBtn->getPosition());
	m_pNormalPig->setTag(1004);

	yesb= CCSprite::spriteWithFile(s_pPathChoosePigPanel_SpeedupPig);
	yesb2 = CCSprite::spriteWithFile(s_pPathChoosePigPanel_SpeedupPig);
	m_pSpeedupPig = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pSpeedupPig->setScale(CCGetScaleX());
	m_pSpeedupPig->setPosition(m_pChoosePigBtn->getPosition());
	m_pSpeedupPig->setTag(1005);

	yesb= CCSprite::spriteWithFile(s_pPathChoosePigPanel_SeparatePig);
	yesb2 = CCSprite::spriteWithFile(s_pPathChoosePigPanel_SeparatePig);
	m_pSeparatePig = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pSeparatePig->setScale(CCGetScaleX());
	m_pSeparatePig->setPosition(m_pChoosePigBtn->getPosition());
	m_pSeparatePig->setTag(1006);

	yesb= CCSprite::spriteWithFile(s_pPathChoosePigPanel_BombPig);
	yesb2 = CCSprite::spriteWithFile(s_pPathChoosePigPanel_BombPig);
	m_pBombPig = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pBombPig->setScale(CCGetScaleX());
	m_pBombPig->setPosition(m_pChoosePigBtn->getPosition());
	m_pBombPig->setTag(1007);

	yesb= CCSprite::spriteWithFile(s_pPathChoosePigPanel_IcePig);
	yesb2 = CCSprite::spriteWithFile(s_pPathChoosePigPanel_IcePig);
	m_pIcePig = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pIcePig->setScale(CCGetScaleX());
	m_pIcePig->setPosition(m_pChoosePigBtn->getPosition());
	m_pIcePig->setTag(1008);

	yesb= CCSprite::spriteWithFile(s_pPathChoosePigPanel_ChinaPig);
	yesb2 = CCSprite::spriteWithFile(s_pPathChoosePigPanel_ChinaPig);
	m_pCeramPig = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pCeramPig->setScale(CCGetScaleX());
	m_pCeramPig->setPosition(m_pChoosePigBtn->getPosition());
	m_pCeramPig->setTag(1009);

	MyCCMenu* myMenu = MyCCMenu::menuWithItems(m_pNormalPig, m_pSpeedupPig, m_pSeparatePig, m_pBombPig, m_pIcePig, m_pCeramPig, NULL);
	myMenu->setPosition(ccp(0, 0));
	myMenu->SetDownUpHandle(this,
		menu_selector(UILevelBase::BtnDownCallback),
		menu_selector(UILevelBase::BtnUpInCallback),
		menu_selector(UILevelBase::BtnUpOutCallback));
	this->addChild(myMenu, 1);
	//
}

void UILevelBase::ShowChoosePigPanel(bool bShow)
{
	if (m_bChoosing == bShow)
		return;

	if (bShow)
	{
		m_pChoosePigBtn->runAction(CCRotateBy::actionWithDuration(1.0f, 180));

		float x = m_pChoosePigBtn->getPosition().x+m_pNormalPig->getContentSize().width*CCGetScaleX()*6;
		float y = m_pChoosePigBtn->getPosition().y;

		m_pCeramPig->runAction(CCMoveTo::actionWithDuration(0.84f, CCPointMake(x, y)));
		x -= m_pNormalPig->getContentSize().width*CCGetScaleX();
		m_pIcePig->runAction(CCMoveTo::actionWithDuration(0.7f, CCPointMake(x, y)));
		x -= m_pNormalPig->getContentSize().width*CCGetScaleX();
		m_pBombPig->runAction(CCMoveTo::actionWithDuration(0.56f, CCPointMake(x, y)));
		x -= m_pNormalPig->getContentSize().width*CCGetScaleX();
		m_pSeparatePig->runAction(CCMoveTo::actionWithDuration(0.42f, CCPointMake(x, y)));
		x -= m_pNormalPig->getContentSize().width*CCGetScaleX();
		m_pSpeedupPig->runAction(CCMoveTo::actionWithDuration(0.28f, CCPointMake(x, y)));
		x -= m_pNormalPig->getContentSize().width*CCGetScaleX();
		m_pNormalPig->runAction(CCMoveTo::actionWithDuration(0.14f, CCPointMake(x, y)));

		m_pDropSprite->runAction(CCSequence::actionOneTwo(CCScaleTo::actionWithDuration(0.84f, CCGetScaleX()*1.2, CCGetScaleY()),
			CCCallFunc::actionWithTarget(this, callfunc_selector(UILevelBase::ShowGuideAnim))));
	}
	else
	{
		m_pChoosePigBtn->runAction(CCRotateBy::actionWithDuration(0.7f, -180));

		float x = m_pChoosePigBtn->getPosition().x;
		float y = m_pChoosePigBtn->getPosition().y;
		
		m_pCeramPig->runAction(CCMoveTo::actionWithDuration(0.84f, CCPointMake(x,y)));
		m_pIcePig->runAction(CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(0.14f),
			CCMoveTo::actionWithDuration(0.7f, CCPointMake(x, y))));
		m_pBombPig->runAction(CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(0.28f),
			CCMoveTo::actionWithDuration(0.56f, CCPointMake(x, y))));
		m_pSeparatePig->runAction(CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(0.42f),
			CCMoveTo::actionWithDuration(0.42f, CCPointMake(x, y))));
		m_pSpeedupPig->runAction(CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(0.56f),
			CCMoveTo::actionWithDuration(0.28f, CCPointMake(x, y))));
		m_pNormalPig->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.7f),
			CCMoveTo::actionWithDuration(0.14f, CCPointMake(x, y)),
			CCCallFunc::actionWithTarget(this, callfunc_selector(UILevelBase::HideChoosePanel)),
			NULL));

		m_pDropSprite->runAction(CCScaleTo::actionWithDuration(0.84f, 0, CCGetScaleY()));

		HideGuideAnim();
	}

	m_bChoosing = bShow;
}

void UILevelBase::ShowGuideAnim()
{
	if (SceneManager::SharedSceneManager()->CurBigLevelID != 1 ||
		SceneManager::SharedSceneManager()->m_iCurLevel != 1)
		return;

	m_animSprite = CCSprite::spriteWithFile(s_pPahtOperateGuide_ChooseGuide);
	m_animSprite->setPosition(CCPointMake(m_pBombPig->getPosition().x,
		m_pBombPig->getPosition().y+m_animSprite->getContentSize().height*CCGetScaleX()/2+m_pBombPig->getContentSize().height*CCGetScaleX()/2));
	m_animSprite->setScale(CCGetScaleX());

	//CCAnimation* animation = CCAnimation::animation();
	//char frameName[50] = {0};
	//for (int i = 1; i <= 2; i++)
	//{
	//	sprintf(frameName, "%s%d.png",s_pPathOperateGuide_ArrowPigAnim,i);
	//	animation->addFrameWithFileName(frameName);
	//}
	//CCAnimate *animate = CCAnimate::actionWithDuration(0.6f, animation, true);
	//m_animSprite->runAction(CCRepeatForever::actionWithAction(animate));  

	this->addChild(m_animSprite,3);
}

void UILevelBase::HideGuideAnim()
{
	if (m_animSprite != NULL)
	{
		m_animSprite->removeFromParentAndCleanup(true);
		m_animSprite = NULL;
	}
}

void UILevelBase::HideChoosePanel()
{
	m_pChoosePigBtn->setOpacity((GLubyte)0);
	m_pNormalPig->setOpacity((GLubyte)0);
	m_pSpeedupPig->setOpacity((GLubyte)0);
	m_pSeparatePig->setOpacity((GLubyte)0);
	m_pBombPig->setOpacity((GLubyte)0);
	m_pIcePig->setOpacity((GLubyte)0);
	m_pCeramPig->setOpacity((GLubyte)0);

}

bool UILevelBase::CheckFinishChoosePig()
{
	return SceneManager::SharedSceneManager()->GetCurLevel()->GetRemainChoosePigCount() <= 0;
}

void UILevelBase::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX() * 1.1f));
    
    if ( pBtn->getTag() == 1001 )
    {
        //pause
        SceneManager::SharedSceneManager()->AddPausePanel(this, 5);
    }
    else if ( pBtn->getTag() == 1002 )
    {
        //replay
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
        SceneManager::SharedSceneManager()->JumpToGameLevel(SceneManager::SharedSceneManager()->m_iCurLevel);
    }
	else if ( pBtn->getTag() == 1003 )
	{
		//choose pig
	}
	else if ( pBtn->getTag() == 1004 )
	{
		SceneManager::SharedSceneManager()->GetCurLevel()->ChoosePig(EPigType_Normal);
		if (CheckFinishChoosePig())
			ShowChoosePigPanel(false);
	}
	else if ( pBtn->getTag() == 1005 )
	{
		SceneManager::SharedSceneManager()->GetCurLevel()->ChoosePig(EPigType_Speedup);
		if (CheckFinishChoosePig())
			ShowChoosePigPanel(false);
	}
	else if ( pBtn->getTag() == 1006 )
	{
		SceneManager::SharedSceneManager()->GetCurLevel()->ChoosePig(EPigType_Separate);
		if (CheckFinishChoosePig())
			ShowChoosePigPanel(false);
	}
	else if ( pBtn->getTag() == 1007 )
	{
		SceneManager::SharedSceneManager()->GetCurLevel()->ChoosePig(EPigType_Bomb);
		if (CheckFinishChoosePig())
			ShowChoosePigPanel(false);
	}
	else if ( pBtn->getTag() == 1008 )
	{
		SceneManager::SharedSceneManager()->GetCurLevel()->ChoosePig(EPigType_Ice);
		if (CheckFinishChoosePig())
			ShowChoosePigPanel(false);
	}
	else if( pBtn->getTag() == 1009 )
	{
		SceneManager::SharedSceneManager()->GetCurLevel()->ChoosePig(EPigType_Ceram);
		if(CheckFinishChoosePig())
			ShowChoosePigPanel(false);
	}
}

void UILevelBase::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    //pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UILevelBase::BtnUpOutCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	//pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UILevelBase::keyBackClicked()
{
	if ( !SceneManager::SharedSceneManager()->IsContainWinFailPanel(this) &&
		!SceneManager::SharedSceneManager()->IsContainPausePanel(this) &&
		!SceneManager::SharedSceneManager()->IsContainPearIntroPanel(this) )
	{
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
		}

		SceneManager::SharedSceneManager()->AddPausePanel(this, 5);
	}
}
