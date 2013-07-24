//
//  UISelectSmallStage.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-23.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UISelectSmallStage.h"
#include "MyCCMenu.h"
#include "GameResources.h"
#include "SceneManager.h"

int UISelectSmallStage::CurBigLevelID = 0;

UISelectSmallStage::UISelectSmallStage()
: m_pLeftBtn(NULL)
, m_pRightBtn(NULL)
, m_curLevelIndex(0)
{
    
}

UISelectSmallStage::~UISelectSmallStage()
{
    
}

CCScene* UISelectSmallStage::scene(int BigLevelID)
{
	CurBigLevelID = BigLevelID;//获取当前大关卡ID，供小关卡选择界面中从userdefault.xml中获取并显示星星数使用;
	CCScene* scene = CCScene::node();
	UISelectSmallStage* layer = UISelectSmallStage::node();
	scene->addChild(layer);
	return scene;
}

bool UISelectSmallStage::init()
{
	this->setIsKeypadEnabled(true);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathStart_WaterfallAnim);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	page = SceneManager::SharedSceneManager()->GetLevelsCount() / kMaxLevelAPage;
	if((SceneManager::SharedSceneManager()->GetLevelsCount() % kMaxLevelAPage) > 0)
	{
		page++;
	}

    CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathScene_StartBackDrop);
    bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    //bgSprite->setScale(CCGetScaleX());
	bgSprite->setScaleX(CCGetScaleX());
	bgSprite->setScaleY(CCGetScaleY());
    this->addChild(bgSprite, 0);
    
	CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Back);
	CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Back);
	CCMenuItemSprite* backBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    //CCMenuItem* backBtn = CCMenuItemImage::itemFromNormalImage(s_pPathBack, s_pPathBack);
    CCSize backBtnSize = backBtn->getContentSize();
    backBtn->setScale(CCGetScaleX());
    backBtn->setPosition(ccp(backBtnSize.width*CCGetScaleX()/2-CCGetWinSize().width/96, backBtnSize.height*CCGetScaleX()/2-CCGetWinSize().width/68));
    backBtn->setTag(1001);
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_Prior);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Prior);
	m_pLeftBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
   // m_pLeftBtn = CCMenuItemImage::itemFromNormalImage(s_pPathPrior, s_pPathPrior);
    m_pLeftBtn->setScale(CCGetScaleX());
    m_pLeftBtn->setAnchorPoint(ccp(1,0));
    m_pLeftBtn->setPosition(ccp(0, CCGetWinSize().height/2));
    m_pLeftBtn->setTag(1002);
    
	yesb= CCSprite::spriteWithFile(s_pPathButtons_Goon);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Goon);
	m_pRightBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    //m_pRightBtn = CCMenuItemImage::itemFromNormalImage(s_pPathNext, s_pPathNext);
    m_pRightBtn->setScale(CCGetScaleX());
    m_pRightBtn->setAnchorPoint(ccp(0,0));
	if(page > 1)
	{
		m_pRightBtn->setPosition(ccp(CCGetWinSize().width-m_pRightBtn->getContentSize().width*CCGetScaleX(),
                                 CCGetWinSize().height/2));
	}
	else if(page == 1)
	{
		m_pRightBtn->setPosition(ccp(CCGetWinSize().width, CCGetWinSize().height/2));
	}
    m_pRightBtn->setTag(1003);
    
    MyCCMenu* myMenu = MyCCMenu::menuWithItems(backBtn, m_pLeftBtn, m_pRightBtn, NULL);
    myMenu->setPosition(ccp(0, 0));
    myMenu->SetDownUpHandle(this,
                            menu_selector(UISelectSmallStage::BtnDownCallback),
                            menu_selector(UISelectSmallStage::BtnUpInCallback),
                            menu_selector(UISelectSmallStage::BtnUpOutCallback));
    this->addChild(myMenu, 2);
    
    InitScrollView();
	//SceneManager::SharedSceneManager()->InitWaterfallAnim(this, 2);
    
    return true;
}

void UISelectSmallStage::InitScrollView()
{
	CCArray* itemsArray = CCArray::array();
	for(int i = 1; i <= page; i++)
	{
		MyCCMenu* menu = InitScrollViewPage(CurBigLevelID,i);
		itemsArray->addObject(menu);
	}
    
    CCScrollLayer* scroller = CCScrollLayer::nodeWithLayers(itemsArray, 0);
    scroller->setPosition(ccp(0, 0));
    scroller->setDelegate(this);
    this->addChild(scroller, 3, 2001);

}

MyCCMenu* UISelectSmallStage::InitScrollViewPage( int BigStageId,int page )
{
    CCArray* itemsArray = CCArray::array();
    int i = 0;

	for ( ; i < SceneManager::SharedSceneManager()->GetLevelsCount() && i < kMaxLevelAPage; ++i,m_curLevelIndex++ )
	{
		LevelInfo* pLevelInfo = SceneManager::SharedSceneManager()->GetLevelInfo(BigStageId,i+1);
		if ( pLevelInfo == NULL )
			break;
		//int startCounts=pLevelInfo->GetStarsCount();

		if ( m_curLevelIndex >= SceneManager::SharedSceneManager()->GetLevelsCount() )
			break;		      
		int row = i/5, con = i%5;
		CCMenuItemSprite* item;
		if (CurBigLevelID == 1 && i == 0 && page == 1)//第一大关的第一小关一开始是开通的;
		{
			CCSprite* yesb= CCSprite::spriteWithFile(s_pPathSmallStage_EnterGateGate);
			CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathSmallStage_EnterGateGate);
			item = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
			//item = CCMenuItemImage::itemFromNormalImage(s_pPathEnterGateGate01, s_pPathEnterGateGate01);
			int iTag = SceneManager::SharedSceneManager()->GetLevelIDByIndex(m_curLevelIndex);
			if ( iTag <= 0 )
				continue;
			item->setTag(iTag);
			char buffer[16];
			sprintf(buffer, "%d", m_curLevelIndex+1);
			//CCLabelTTF* label1 = CCLabelTTF::labelWithString(buffer, "Marker Felt", 60);
			CCLabelAtlas* label1 = CCLabelAtlas::labelWithString(buffer, s_pPathCount1, 30, 50, '.');
			label1->setAnchorPoint(CCPointMake(0.5f, 0.5f));
			label1->setPosition(ccp(item->getContentSize().width/2, item->getContentSize().height*1.3/2));
			item->addChild(label1);

			CCSprite* star1 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
			star1->setPosition(ccp(item->getContentSize().width*0.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star1);
			CCSprite* star2 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
			star2->setPosition(ccp(item->getContentSize().width/2, item->getContentSize().height*0.5f/2));
			item->addChild(star2);
			CCSprite* star3 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
			star3->setPosition(ccp(item->getContentSize().width*1.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star3);
		}
		else //后面的关数的开通情况，要根据玩家时候通过前一关来开通,即使得该关可以点击进入;
		{		
			//从userdefault.xml文件中获得对应小关卡的开通标示符IsOpenxx,如果为true，则该关卡开通，可点击;
			char string[16]={0};
			if ( page == 1 )
				sprintf(string,"IsOpen%d%d",CurBigLevelID,i+1);
			else if ( page == 2 )
				sprintf(string,"IsOpen%d%d",CurBigLevelID,i+16);
			bool CurLevelIsOpen = false;
			CurLevelIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey(string);
			if (CurLevelIsOpen || SceneManager::SharedSceneManager()->IsTestGameMode())
			//if(true)//测试阶段，将所有小关全部打开;
			{
				CCSprite* yesb= CCSprite::spriteWithFile(s_pPathSmallStage_EnterGateGate);
				CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathSmallStage_EnterGateGate);
				item = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
				//item = CCMenuItemImage::itemFromNormalImage(s_pPathEnterGateGate01, s_pPathEnterGateGate01);
				int iTag = SceneManager::SharedSceneManager()->GetLevelIDByIndex(m_curLevelIndex);
				if ( iTag <= 0 )
					continue;
				item->setTag(iTag);
				char buffer[16];
				sprintf(buffer, "%d", m_curLevelIndex+1);
				//CCLabelTTF* label1 = CCLabelTTF::labelWithString(buffer, "Marker Felt", 60);
				CCLabelAtlas* label1 = CCLabelAtlas::labelWithString(buffer, s_pPathCount1, 30, 50, '.');
				label1->setAnchorPoint(CCPointMake(0.5f, 0.5f));
				label1->setPosition(ccp(item->getContentSize().width/2, item->getContentSize().height*1.3/2));
				item->addChild(label1);

				CCSprite* star1 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
				star1->setPosition(ccp(item->getContentSize().width*0.5f/2, item->getContentSize().height*0.5f/2));
				item->addChild(star1);
				CCSprite* star2 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
				star2->setPosition(ccp(item->getContentSize().width/2, item->getContentSize().height*0.5f/2));
				item->addChild(star2);
				CCSprite* star3 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
				star3->setPosition(ccp(item->getContentSize().width*1.5f/2, item->getContentSize().height*0.5f/2));
				item->addChild(star3);
			}
			else//否则图标为一把锁的图标，且点击无反应;
			{
				CCSprite* yesb= CCSprite::spriteWithFile(s_pPathSmallStage_LockGate);
				CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathSmallStage_LockGate);
				item = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
				//item = CCMenuItemImage::itemFromNormalImage(s_pPathLockGate01, s_pPathLockGate01);
			}

		}

		//从userdefault.xml中对应当前大关卡及小关卡ID获取相应的星星数;
		char string[20] = {0};
		if (page == 1)
		{
			sprintf(string, "stars%d%d",CurBigLevelID ,i+1);
		}
		else if (page == 2)
		{
			sprintf(string, "stars%d%d",CurBigLevelID ,i+16);
		}
		int stars;
		stars = CCUserDefault::sharedUserDefault()->getIntegerForKey(string);
		//获取结束;
		if (stars==1)
		{
			CCSprite* star1 = CCSprite::spriteWithFile(s_pPathSmallStage_StarS);
			star1->setPosition(ccp(item->getContentSize().width*0.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star1);
			CCSprite* star2 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
			star2->setPosition(ccp(item->getContentSize().width/2, item->getContentSize().height*0.5f/2));
			item->addChild(star2);
			CCSprite* star3 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
			star3->setPosition(ccp(item->getContentSize().width*1.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star3);
		}

		else if (stars==2)
		{
			CCSprite* star1 = CCSprite::spriteWithFile(s_pPathSmallStage_StarS);
			star1->setPosition(ccp(item->getContentSize().width*0.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star1);
			CCSprite* star2 = CCSprite::spriteWithFile(s_pPathSmallStage_StarS);
			star2->setPosition(ccp(item->getContentSize().width/2, item->getContentSize().height*0.5f/2));
			item->addChild(star2);
			CCSprite* star3 = CCSprite::spriteWithFile(s_pPathSmallStage_StarSShadow);
			star3->setPosition(ccp(item->getContentSize().width*1.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star3);
		}

		else if (stars==3)
		{
			CCSprite* star1 = CCSprite::spriteWithFile(s_pPathSmallStage_StarS);
			star1->setPosition(ccp(item->getContentSize().width*0.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star1);
			CCSprite* star2 = CCSprite::spriteWithFile(s_pPathSmallStage_StarS);
			star2->setPosition(ccp(item->getContentSize().width/2, item->getContentSize().height*0.5f/2));
			item->addChild(star2);
			CCSprite* star3 = CCSprite::spriteWithFile(s_pPathSmallStage_StarS);
			star3->setPosition(ccp(item->getContentSize().width*1.5f/2, item->getContentSize().height*0.5f/2));
			item->addChild(star3);
		}
		//结束;


		item->setScale(CCGetScaleX());
		item->setPosition(ccp(CCGetWinSize().width/2+(con-2)*item->getContentSize().width*5/4*CCGetScaleX(),
			CCGetWinSize().height/2+(1-row)*item->getContentSize().height*5/4*CCGetScaleX()));
		itemsArray->addObject(item);
	}

    
    MyCCMenu* myMenu;
	if ( page == 1 )
	{
		myMenu = MyCCMenu::menuWithItems((CCMenuItem*)itemsArray->objectAtIndex(0),(CCMenuItem*)itemsArray->objectAtIndex(1),
			(CCMenuItem*)itemsArray->objectAtIndex(2),(CCMenuItem*)itemsArray->objectAtIndex(3),
			(CCMenuItem*)itemsArray->objectAtIndex(4),(CCMenuItem*)itemsArray->objectAtIndex(5),
			(CCMenuItem*)itemsArray->objectAtIndex(6),(CCMenuItem*)itemsArray->objectAtIndex(7),
			(CCMenuItem*)itemsArray->objectAtIndex(8),(CCMenuItem*)itemsArray->objectAtIndex(9),
			/*(CCMenuItem*)itemsArray->objectAtIndex(10),(CCMenuItem*)itemsArray->objectAtIndex(11),
			(CCMenuItem*)itemsArray->objectAtIndex(12),(CCMenuItem*)itemsArray->objectAtIndex(13),
			(CCMenuItem*)itemsArray->objectAtIndex(14),*/NULL);
	}
	else if ( page == 2 )
	{
		myMenu = MyCCMenu::menuWithItems((CCMenuItem*)itemsArray->objectAtIndex(0),(CCMenuItem*)itemsArray->objectAtIndex(1),
			(CCMenuItem*)itemsArray->objectAtIndex(2),(CCMenuItem*)itemsArray->objectAtIndex(3),
			(CCMenuItem*)itemsArray->objectAtIndex(4),(CCMenuItem*)itemsArray->objectAtIndex(5),
			(CCMenuItem*)itemsArray->objectAtIndex(6),NULL);
	}
	
    myMenu->SetDownUpHandle(this,
                            menu_selector(UISelectSmallStage::BtnDownCallback),
                            menu_selector(UISelectSmallStage::BtnUpInCallback),
                            menu_selector(UISelectSmallStage::BtnUpOutCallback));
    
    return myMenu;
}

void UISelectSmallStage::BtnDownCallback(CCObject* pSender)
{
    CCMenuItem* pBtn = (CCMenuItem*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
    
    if ( pBtn->getTag() == 1001 )
    {
        //back
        SceneManager::SharedSceneManager()->JumpToSelectBigStage();
    }
    else if ( pBtn->getTag() == 1002 )
    {
        HideLeftRightBtn();//左;
        CCScrollLayer* scroller = (CCScrollLayer*)this->getChildByTag(2001);
        scroller->moveToPage(scroller->getCurrentScreen()-1);
    }
    else if ( pBtn->getTag() == 1003 )
    {
        HideLeftRightBtn();//右;
        CCScrollLayer* scroller = (CCScrollLayer*)this->getChildByTag(2001);
        scroller->moveToPage(scroller->getCurrentScreen()+1);
    }
}

void UISelectSmallStage::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItem* pBtn = (CCMenuItem*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
    
	if ( pBtn->getTag() == 1 && CurBigLevelID ==1)
	{
		//如果点击的是第一小关，那么一开始便会出现开场新手向导;
		SceneManager::SharedSceneManager()->JumpToNewGuide();
		//停止播放背景音乐;
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);

	}
	else if(pBtn->getTag() == 1 && CurBigLevelID == 2)
	{
		//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//{
			SceneManager::SharedSceneManager()->JumpToStory(2);
		//}
	}
	else if(pBtn->getTag() == 1 && CurBigLevelID == 3)
	{
		//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//{
			SceneManager::SharedSceneManager()->JumpToStory(3);
		//}
	}
	else if(pBtn->getTag() == 1 && CurBigLevelID == 4)
	{
		//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//{
			SceneManager::SharedSceneManager()->JumpToStory(4);
		//}
	}
	else if(pBtn->getTag() == 1 && CurBigLevelID == 5)
	{
		//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//{
			SceneManager::SharedSceneManager()->JumpToStory(5);
		//}
	}
	else if ( pBtn->getTag()!=1002 && pBtn->getTag()!=1003 )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		loading_Sprite = CCSprite::spriteWithFile(s_pPathLoading);
		loading_Sprite->setPosition(ccp(winSize.width/2,winSize.height*14/40));
		loading_Sprite->setScale(CCGetScaleX()*1.0f);
		//anim
		CCAnimation* animation = CCAnimation::animation();
		char frameName[50] = {0};
		for (int i = 1; i <= 4; i++)
		{
			sprintf(frameName, "%s%d.png",s_pPathLoadingAnim, i);
			animation->addFrameWithFileName(frameName);
		}
		CCAnimate *animate = CCAnimate::actionWithDuration(0.4f, animation, false);
		loading_Sprite->runAction(CCRepeatForever::actionWithAction(animate));  
		//anim
		this->addChild(loading_Sprite,3);

		loading_Sprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.5f),
			CCCallFunc::actionWithTarget(this, callfunc_selector(UISelectSmallStage::JumpToGameLevel)),
			NULL));
		pBtnDown = pBtn;
		//SceneManager::SharedSceneManager()->JumpToGameLevel(pBtn->getTag());
		//停止播放背景音乐;
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/bigsmal_stage.plist");
	}
}

void UISelectSmallStage::JumpToGameLevel()
{
	//CCLOG("small_LevelID=%d",pBtnDown->getTag());
	this->removeChild(loading_Sprite,true);
	SceneManager::SharedSceneManager()->JumpToGameLevel(pBtnDown->getTag());
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/bigsmal_stage.plist");
}

void UISelectSmallStage::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItem* pBtn = (CCMenuItem*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UISelectSmallStage::scrollLayerScrollingStarted(CCScrollLayer* sender)
{
    HideLeftRightBtn();
}

void UISelectSmallStage::scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page)
{
    if ( page > 0 )
    {
        m_pLeftBtn->setPosition(ccp(m_pRightBtn->getContentSize().width*CCGetScaleX(),
                                     CCGetWinSize().height/2));
    }
    if ( page < sender->getPages()->count()-1 )
    {
        m_pRightBtn->setPosition(ccp(CCGetWinSize().width-m_pRightBtn->getContentSize().width*CCGetScaleX(),
                                     CCGetWinSize().height/2));
    }
}

void UISelectSmallStage::HideLeftRightBtn()
{
    m_pLeftBtn->setPosition(ccp(0, CCGetWinSize().height/2));
    m_pRightBtn->setPosition(ccp(CCGetWinSize().width, CCGetWinSize().height/2));
}

void UISelectSmallStage::keyBackClicked()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
	}

	SceneManager::SharedSceneManager()->JumpToSelectBigStage();
}




