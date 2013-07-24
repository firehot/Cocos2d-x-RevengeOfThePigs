#include "UINewGuideNext.h"
#include "GameResources.h"
#include "SceneManager.h"
#include "MyCCMenu.h"

UINewGuideNext::UINewGuideNext()
	: m_pGuideMenu(NULL)
	, m_pGuideBgLayerColor(NULL)
{

}

UINewGuideNext::~UINewGuideNext()
{

}

CCScene* UINewGuideNext::scene()
{
	CCScene* scene = CCScene::node();
	UINewGuideNext* layer = UINewGuideNext::node();
	scene->addChild(layer);
	return scene;
}

bool UINewGuideNext::init()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/YN.plist");
	i=0;
	TotalDelayTime=0.0f;
	DelayTime=0.8f;
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathScene_StartBackDrop);
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	bgSprite->setScale(CCGetScaleX());
	this->addChild(bgSprite, -3);

	m_pGuideBgLayerColor = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
	this->addChild(m_pGuideBgLayerColor, 0);
	m_pGuideBgLayerColor->runAction(CCFadeTo::actionWithDuration(0, 127));

	for (int m=0;m<7;m++)
	{
		AddNewGuidePic();	
	}

	m_pGuideMenu = MyCCMenu::menuWithItems( continueBtn,NULL);
	//m_pGuideMenu->setPosition(ccp(-winSize.width*1.4f/4, 0));
	m_pGuideMenu->setPosition(ccp(winSize.width/16, winSize.height/32));
	m_pGuideMenu->setTag(2001);
	m_pGuideMenu->SetDownUpHandle(this,
		menu_selector(UINewGuideNext::BtnDownCallback),
		menu_selector(UINewGuideNext::BtnUpInCallback),
		menu_selector(UINewGuideNext::BtnUpOutCallback));
	this->addChild(m_pGuideMenu, 2);

	return true;
}

bool UINewGuideNext::containsTouchLocation(CCTouch* pTouch)
{
	CCPoint touchLocation = pTouch->locationInView(pTouch->view());
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	CCRect myRect = CCRectMake(this->getPosition().x, this->getPosition().y,
		this->getContentSize().width, this->getContentSize().height);
	return CCRect::CCRectContainsPoint(myRect, touchLocation);
}

bool UINewGuideNext::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	m_pGuideBgSprite->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pGuideBgSprite2->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pGuideBgSprite3->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pGuideBgSprite4->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pGuideBgSprite5->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	m_pGuideBgSprite6->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	continueBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));

	CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
	if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
		return false;
	return true;
}

void UINewGuideNext::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void UINewGuideNext::BtnDownCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));



	if ( pBtn->getTag() == 1002 )
	{
		//continue
		SceneManager::SharedSceneManager()->JumpToGameLevel(1);
		SceneManager::SharedSceneManager()->AddHelpPanel((CCNode*)SceneManager::SharedSceneManager()->GetCurLevel(), 5);
	}

}

void UINewGuideNext::BtnUpInCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UINewGuideNext::RemoveSelfFromParent()
{
	this->getParent()->removeFromParentAndCleanup(true);
}

void UINewGuideNext::BtnUpOutCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UINewGuideNext::AddNewGuidePic()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScaleTo* action1 = NULL;
	if(i == 0)
	{
		m_pGuideBgSprite = CCSprite::spriteWithFile(s_pPathOpeningStory7);
		m_pGuideBgSprite->setPosition(ccp(winSize.width*0.323, winSize.height*0.758));
		m_pGuideBgSprite->setScale(CCGetScaleX());
		this->addChild(m_pGuideBgSprite, 1);
		m_pGuideBgSprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.0f),
			CCCallFunc::actionWithTarget(this, NULL),
			NULL));

	}
	else if (i == 1)
	{
		m_pGuideBgSprite2 = CCSprite::spriteWithFile(s_pPathOpeningStory8);
		m_pGuideBgSprite2->setPosition(ccp(winSize.width*0.686, winSize.height*0.758));
		m_pGuideBgSprite2->setScale(0);
		this->addChild(m_pGuideBgSprite2, 2);

		action1 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pGuideBgSprite2->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			//CCCallFunc::actionWithTarget(this, callfunc_selector(UINewGuide::DoNothing)),
			action1,
			NULL));
	}
	else if (i == 2)
	{
		m_pGuideBgSprite3 = CCSprite::spriteWithFile(s_pPathOpeningStory9);
		m_pGuideBgSprite3->setPosition(ccp(winSize.width*0.505, winSize.height*0.443));
		m_pGuideBgSprite3->setScale(0);
		this->addChild(m_pGuideBgSprite3, 1);

		action1 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pGuideBgSprite3->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			//CCCallFunc::actionWithTarget(this, callfunc_selector(UINewGuide::DoNothing)),
			action1,
			NULL));
	}
	else if (i == 3)
	{
		m_pGuideBgSprite4 = CCSprite::spriteWithFile(s_pPathOpeningStory10);
		m_pGuideBgSprite4->setPosition(ccp(winSize.width*0.317, winSize.height*0.175));
		m_pGuideBgSprite4->setScale(0);
		this->addChild(m_pGuideBgSprite4, 1);

		action1 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pGuideBgSprite4->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			//CCCallFunc::actionWithTarget(this, callfunc_selector(UINewGuide::DoNothing)),
			action1,
			NULL));
	}
	else if (i == 4)
	{
		m_pGuideBgSprite5 = CCSprite::spriteWithFile(s_pPathOpeningStory11);
		m_pGuideBgSprite5->setPosition(ccp(winSize.width*0.680, winSize.height*0.175));
		m_pGuideBgSprite5->setScale(0);
		this->addChild(m_pGuideBgSprite5, 1);

		action1 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pGuideBgSprite5->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			//CCCallFunc::actionWithTarget(this, callfunc_selector(UINewGuide::DoNothing)),
			action1,
			NULL));
	}
	else if (i == 5)
	{
		m_pGuideBgSprite6 = CCSprite::spriteWithFile(s_pPathOpeningStory12);
		m_pGuideBgSprite6->setPosition(ccp(winSize.width*0.680, winSize.height*0.17));
		m_pGuideBgSprite6->setScale(0);
		this->addChild(m_pGuideBgSprite6, 1);

		action1 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		m_pGuideBgSprite6->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			//CCCallFunc::actionWithTarget(this, callfunc_selector(UINewGuide::DoNothing)),
			action1,
			NULL));
	}
	else if (i == 6)
	{
		CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Yes);
		CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
		continueBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
		// = CCMenuItemImage::itemFromNormalImage(s_pPathYes, s_pPathYes);
		continueBtn->setScale(0);
		//	continueBtn->setRotation(-90);
		continueBtn->setPosition(ccp(winSize.width*7/8, winSize.height*1/16));
		continueBtn->setTag(1002);
		action1 = CCScaleTo::actionWithDuration(0.1f, CCGetScaleX());
		continueBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(TotalDelayTime),
			//CCCallFunc::actionWithTarget(this, callfunc_selector(UINewGuide::DoNothing)),
			action1,
			NULL));
	}
	TotalDelayTime+=DelayTime;
	i++;
}
