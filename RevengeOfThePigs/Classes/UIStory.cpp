#include "UIStory.h"
#include "GameResources.h"
#include "SceneManager.h"
#include "MyCCMenu.h"

int UIStory::NextGameLevel = 0;

UIStory::UIStory()
	:m_pStoryMenu(NULL)
	,m_pStoryBgLayerColor(NULL)
	,m_pStoryBgSprite1(NULL)
	,m_pStoryBgSprite2(NULL)
	,m_pStoryBgSprite3(NULL)
	,m_pStoryBgSprite4(NULL)
	,m_pStoryBgSprite5(NULL)
	,m_pStoryBgSprite6(NULL)
{

}

UIStory::~UIStory()
{

}


CCScene* UIStory::scene(int level)
{
	NextGameLevel = level;

	CCScene* scene = CCScene::node();
	UIStory* layer = UIStory::node();
	scene->addChild(layer);
	return scene;
}

bool UIStory::init()
{
	iStory = 0;
	TotalDelayTime = 0.0f;
	DelayTime = 0.8f;
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathScene_StartBackDrop);
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	bgSprite->setScale(CCGetScaleX());
	this->addChild(bgSprite, -3);

	m_pStoryBgLayerColor = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
	this->addChild(m_pStoryBgLayerColor, 0);
	m_pStoryBgLayerColor->runAction(CCFadeTo::actionWithDuration(0, 127));

	//if(NextGameLevel == 1)
	//{
	//	for (int m=0;m<7;m++)
	//	{
	//		AddStoryPic_Level1();	
	//	}
	//}
	if(NextGameLevel ==2)
	{
		for (int m=0;m<7;m++)
		{
			AddStoryPic_Level2();	
		}
	}
	else if(NextGameLevel == 3)
	{
		for (int m=0;m<7;m++)
		{
			AddStoryPic_Level3();	
		}
	}
	else if(NextGameLevel == 4)
	{
		for (int m=0;m<6;m++)
		{
			AddStoryPic_Level4();	
		}
	}
	else if(NextGameLevel == 5)
	{
		for (int m=0;m<6;m++)
		{
			AddStoryPic_Level5();	
		}
	}
	else if(NextGameLevel == 6)
	{
		for(int m=0;m<6;m++)
		{
			AddStoryPic_LevelEnd();
		}
	}


	m_pStoryMenu = MyCCMenu::menuWithItems( continueBtn,NULL);
	//m_pGuideMenu->setPosition(ccp(-winSize.width*1.4f/4, 0));
	m_pStoryMenu->setPosition(ccp(winSize.width/16, winSize.height/32));
	m_pStoryMenu->setTag(2001);
	m_pStoryMenu->SetDownUpHandle(this,
		menu_selector(UIStory::BtnDownCallback),
		menu_selector(UIStory::BtnUpInCallback),
		menu_selector(UIStory::BtnUpOutCallback));
	this->addChild(m_pStoryMenu, 2);

	return true;
}

bool UIStory::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	m_pStoryBgSprite1->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pStoryBgSprite2->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pStoryBgSprite3->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pStoryBgSprite4->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pStoryBgSprite5->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	if(m_pStoryBgSprite6 != NULL)
	{
		m_pStoryBgSprite6->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	}
	
	continueBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));

	CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
	if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
		return false;
	return true;
}

void UIStory::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void UIStory::BtnUpInCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));

	if ( pBtn->getTag() == 1002 )
	{
		//continue
		//SceneManager::SharedSceneManager()->JumpToGameLevel(1);
		if(NextGameLevel != 6)
		{
			
			SceneManager::SharedSceneManager()->JumpToNextStage(NextGameLevel);
		}
		else
		{
			SceneManager::SharedSceneManager()->JumpToStartPanel();
		}
	}

}

void UIStory::BtnDownCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
}

void UIStory::RemoveSelfFromParent()
{
	this->getParent()->removeFromParentAndCleanup(true);
}

void UIStory::BtnUpOutCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UIStory::AddStoryPic_Level2()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScaleTo* action = NULL;
	if(iStory == 0)
	{
		m_pStoryBgSprite1 = CCSprite::spriteWithFile(s_pPathStage2Story1);
		m_pStoryBgSprite1->setPosition(ccp(winSize.width*0.333f, winSize.height*0.716f));
		m_pStoryBgSprite1->setScale(CCGetScaleX());
		this->addChild(m_pStoryBgSprite1, 1);
		m_pStoryBgSprite1->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.0f),
			CCCallFunc::actionWithTarget(this, NULL),
			NULL));
	}
	else if (iStory == 1)
	{
		m_pStoryBgSprite2 = CCSprite::spriteWithFile(s_pPathStage2Story2);
		m_pStoryBgSprite2->setPosition(ccp(winSize.width*0.745, winSize.height*0.716));
		m_pStoryBgSprite2->setScale(0);
		this->addChild(m_pStoryBgSprite2, 2);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite2->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 2)
	{
		m_pStoryBgSprite3 = CCSprite::spriteWithFile(s_pPathStage2Story3);
		m_pStoryBgSprite3->setPosition(ccp(winSize.width*0.296, winSize.height*0.452));
		m_pStoryBgSprite3->setScale(0);
		this->addChild(m_pStoryBgSprite3, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite3->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 3)
	{
		m_pStoryBgSprite4 = CCSprite::spriteWithFile(s_pPathStage2Story4);
		m_pStoryBgSprite4->setPosition(ccp(winSize.width*0.296, winSize.height*0.241));
		m_pStoryBgSprite4->setScale(0);
		this->addChild(m_pStoryBgSprite4, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite4->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 4)
	{
		m_pStoryBgSprite5 = CCSprite::spriteWithFile(s_pPathStage2Story5);
		m_pStoryBgSprite5->setPosition(ccp(winSize.width*0.706, winSize.height*0.336));
		m_pStoryBgSprite5->setScale(0);
		this->addChild(m_pStoryBgSprite5, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite5->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 5)
	{
		m_pStoryBgSprite6 = CCSprite::spriteWithFile(s_pPathStage2Story6);
		m_pStoryBgSprite6->setPosition(ccp(winSize.width*0.801, winSize.height*0.259));
		m_pStoryBgSprite6->setScale(0);
		this->addChild(m_pStoryBgSprite6, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite6->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 6)
	{
		CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Yes);
		CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
		continueBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
		continueBtn->setScale(0);
		continueBtn->setPosition(ccp(winSize.width*7/8, winSize.height*1/16));
		continueBtn->setTag(1002);
		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		continueBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	TotalDelayTime+=DelayTime;
	iStory++;
}

void UIStory::AddStoryPic_Level3()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScaleTo* action = NULL;
	if(iStory == 0)
	{
		m_pStoryBgSprite1 = CCSprite::spriteWithFile(s_pPathStage3Story1);
		m_pStoryBgSprite1->setPosition(ccp(winSize.width*0.290, winSize.height*0.691));
		m_pStoryBgSprite1->setScale(CCGetScaleX());
		this->addChild(m_pStoryBgSprite1, 1);
		m_pStoryBgSprite1->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.0f),
			CCCallFunc::actionWithTarget(this, NULL),
			NULL));
	}
	else if (iStory == 1)
	{
		m_pStoryBgSprite2 = CCSprite::spriteWithFile(s_pPathStage3Story2);
		m_pStoryBgSprite2->setPosition(ccp(winSize.width*0.708, winSize.height*0.691));
		m_pStoryBgSprite2->setScale(0);
		this->addChild(m_pStoryBgSprite2, 2);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite2->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 2)
	{
		m_pStoryBgSprite3 = CCSprite::spriteWithFile(s_pPathStage3Story3);
		m_pStoryBgSprite3->setPosition(ccp(winSize.width*0.309, winSize.height*0.310));
		m_pStoryBgSprite3->setScale(0);
		this->addChild(m_pStoryBgSprite3, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite3->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 3)
	{
		m_pStoryBgSprite4 = CCSprite::spriteWithFile(s_pPathStage3Story4);
		m_pStoryBgSprite4->setPosition(ccp(winSize.width*0.290, winSize.height*0.242));
		m_pStoryBgSprite4->setScale(0);
		this->addChild(m_pStoryBgSprite4, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite4->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 4)
	{
		m_pStoryBgSprite5 = CCSprite::spriteWithFile(s_pPathStage3Story5);
		m_pStoryBgSprite5->setPosition(ccp(winSize.width*0.65, winSize.height*0.310));
		m_pStoryBgSprite5->setScale(0);
		this->addChild(m_pStoryBgSprite5, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite5->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 5)
	{
		m_pStoryBgSprite6 = CCSprite::spriteWithFile(s_pPathStage3Story6);
		m_pStoryBgSprite6->setPosition(ccp(winSize.width*0.842, winSize.height*0.310));
		m_pStoryBgSprite6->setScale(0);
		this->addChild(m_pStoryBgSprite6, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite6->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 6)
	{
		CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Yes);
		CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
		continueBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
		continueBtn->setScale(0);
		continueBtn->setPosition(ccp(winSize.width*7/8, winSize.height*1/16));
		continueBtn->setTag(1002);
		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		continueBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	TotalDelayTime+=DelayTime;
	iStory++;
}

void UIStory::AddStoryPic_Level4()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScaleTo* action = NULL;
	if(iStory == 0)
	{
		m_pStoryBgSprite1 = CCSprite::spriteWithFile(s_pPathStage4Story1);
		m_pStoryBgSprite1->setPosition(ccp(winSize.width*0.280, winSize.height*0.698));
		m_pStoryBgSprite1->setScale(CCGetScaleX());
		this->addChild(m_pStoryBgSprite1, 1);
		m_pStoryBgSprite1->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.0f),
			CCCallFunc::actionWithTarget(this, NULL),
			NULL));
	}
	else if (iStory == 1)
	{
		m_pStoryBgSprite2 = CCSprite::spriteWithFile(s_pPathStage4Story2);
		m_pStoryBgSprite2->setPosition(ccp(winSize.width*0.686, winSize.height*0.698));
		m_pStoryBgSprite2->setScale(0);
		this->addChild(m_pStoryBgSprite2, 2);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite2->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 2)
	{
		m_pStoryBgSprite3 = CCSprite::spriteWithFile(s_pPathStage4Story3);
		m_pStoryBgSprite3->setPosition(ccp(winSize.width*0.302, winSize.height*0.355));
		m_pStoryBgSprite3->setScale(0);
		this->addChild(m_pStoryBgSprite3, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite3->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 3)
	{
		m_pStoryBgSprite4 = CCSprite::spriteWithFile(s_pPathStage4Story4);
		m_pStoryBgSprite4->setPosition(ccp(winSize.width*0.708, winSize.height*0.355));
		m_pStoryBgSprite4->setScale(0);
		this->addChild(m_pStoryBgSprite4, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite4->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 4)
	{
		m_pStoryBgSprite5 = CCSprite::spriteWithFile(s_pPathStage4Story5);
		m_pStoryBgSprite5->setPosition(ccp(winSize.width*0.785, winSize.height*0.353));
		m_pStoryBgSprite5->setScale(0);
		this->addChild(m_pStoryBgSprite5, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite5->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 5)
	{
		CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Yes);
		CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
		continueBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
		continueBtn->setScale(0);
		continueBtn->setPosition(ccp(winSize.width*7/8, winSize.height*1/16));
		continueBtn->setTag(1002);
		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		continueBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	TotalDelayTime+=DelayTime;
	iStory++;
}

void UIStory::AddStoryPic_Level5()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScaleTo* action = NULL;
	if(iStory == 0)
	{
		m_pStoryBgSprite1 = CCSprite::spriteWithFile(s_pPathStage5Story1);
		m_pStoryBgSprite1->setPosition(ccp(winSize.width*0.226, winSize.height*0.714));
		m_pStoryBgSprite1->setScale(CCGetScaleX());
		this->addChild(m_pStoryBgSprite1, 1);
		m_pStoryBgSprite1->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.0f),
			CCCallFunc::actionWithTarget(this, NULL),
			NULL));
	}
	else if (iStory == 1)
	{
		m_pStoryBgSprite2 = CCSprite::spriteWithFile(s_pPathStage5Story2);
		m_pStoryBgSprite2->setPosition(ccp(winSize.width*0.472, winSize.height*0.714));
		m_pStoryBgSprite2->setScale(0);
		this->addChild(m_pStoryBgSprite2, 2);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite2->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 2)
	{
		m_pStoryBgSprite3 = CCSprite::spriteWithFile(s_pPathStage5Story3);
		m_pStoryBgSprite3->setPosition(ccp(winSize.width*0.740, winSize.height*0.714));
		m_pStoryBgSprite3->setScale(0);
		this->addChild(m_pStoryBgSprite3, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite3->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 3)
	{
		m_pStoryBgSprite4 = CCSprite::spriteWithFile(s_pPathStage5Story4);
		m_pStoryBgSprite4->setPosition(ccp(winSize.width*0.304, winSize.height*0.304));
		m_pStoryBgSprite4->setScale(0);
		this->addChild(m_pStoryBgSprite4, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite4->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 4)
	{
		m_pStoryBgSprite5 = CCSprite::spriteWithFile(s_pPathStage5Story5);
		m_pStoryBgSprite5->setPosition(ccp(winSize.width*0.715, winSize.height*0.304));
		m_pStoryBgSprite5->setScale(0);
		this->addChild(m_pStoryBgSprite5, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite5->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 5)
	{
		CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Yes);
		CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
		continueBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
		continueBtn->setScale(0);
		continueBtn->setPosition(ccp(winSize.width*7/8, winSize.height*1/16));
		continueBtn->setTag(1002);
		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		continueBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	TotalDelayTime+=DelayTime;
	iStory++;
}

void UIStory::AddStoryPic_LevelEnd()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScaleTo* action = NULL;
	if(iStory == 0)
	{
		m_pStoryBgSprite1 = CCSprite::spriteWithFile(s_pPathEndingStory1);
		m_pStoryBgSprite1->setPosition(ccp(winSize.width*0.334, winSize.height*0.685));
		m_pStoryBgSprite1->setScale(CCGetScaleX());
		this->addChild(m_pStoryBgSprite1, 1);
		m_pStoryBgSprite1->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.0f),
			CCCallFunc::actionWithTarget(this, NULL),
			NULL));
	}
	else if (iStory == 1)
	{
		m_pStoryBgSprite2 = CCSprite::spriteWithFile(s_pPathEndingStory2);
		m_pStoryBgSprite2->setPosition(ccp(winSize.width*0.737, winSize.height*0.685));
		m_pStoryBgSprite2->setScale(0);
		this->addChild(m_pStoryBgSprite2, 2);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite2->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 2)
	{
		m_pStoryBgSprite3 = CCSprite::spriteWithFile(s_pPathEndingStory3);
		m_pStoryBgSprite3->setPosition(ccp(winSize.width*0.188 , winSize.height*0.292));
		m_pStoryBgSprite3->setScale(0);
		this->addChild(m_pStoryBgSprite3, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite3->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 3)
	{
		m_pStoryBgSprite4 = CCSprite::spriteWithFile(s_pPathEndingStory4);
		m_pStoryBgSprite4->setPosition(ccp(winSize.width*0.372 , winSize.height*0.292));
		m_pStoryBgSprite4->setScale(0);
		this->addChild(m_pStoryBgSprite4, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite4->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 4)
	{
		m_pStoryBgSprite5 = CCSprite::spriteWithFile(s_pPathEndingStory5);
		m_pStoryBgSprite5->setPosition(ccp(winSize.width*0.683, winSize.height*0.292));
		m_pStoryBgSprite5->setScale(0);
		this->addChild(m_pStoryBgSprite5, 1);

		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pStoryBgSprite5->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	else if (iStory == 5)
	{
		CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Yes);
		CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
		continueBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
		continueBtn->setScale(0);
		continueBtn->setPosition(ccp(winSize.width*7/8, winSize.height*1/16));
		continueBtn->setTag(1002);
		action = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		continueBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			action,
			NULL));
	}
	TotalDelayTime+=DelayTime;
	iStory++;
}