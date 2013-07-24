#include "UINewGuide.h"
#include "GameResources.h"
#include "SceneManager.h"
#include "MyCCMenu.h"

UINewGuide::UINewGuide()
	: m_pGuideMenu(NULL)
	, m_pGuideBgLayerColor(NULL)
{

}

UINewGuide::~UINewGuide()
{

}

CCScene* UINewGuide::scene()
{
	CCScene* scene = CCScene::node();
	UINewGuide* layer = UINewGuide::node();
	scene->addChild(layer);
	return scene;
}

bool UINewGuide::init()
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
		menu_selector(UINewGuide::BtnDownCallback),
		menu_selector(UINewGuide::BtnUpInCallback),
		menu_selector(UINewGuide::BtnUpOutCallback));
	this->addChild(m_pGuideMenu, 2);

	return true;
}

bool UINewGuide::containsTouchLocation(CCTouch* pTouch)
{
	CCPoint touchLocation = pTouch->locationInView(pTouch->view());
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	CCRect myRect = CCRectMake(this->getPosition().x, this->getPosition().y,
		this->getContentSize().width, this->getContentSize().height);
	return CCRect::CCRectContainsPoint(myRect, touchLocation);
}

bool UINewGuide::ccTouchBegan(CCTouch* touch, CCEvent* event)
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

void UINewGuide::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void UINewGuide::BtnDownCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));


	
	if ( pBtn->getTag() == 1002 )
	{
		//if(SceneManager::SharedSceneManager()->GetGameVersion() != EGmaeVersion_JX)
		//{
		//	//continue
		//	SceneManager::SharedSceneManager()->JumpToGameLevel(1);
		//	SceneManager::SharedSceneManager()->AddHelpPanel((CCNode*)SceneManager::SharedSceneManager()->GetCurLevel(), 5);
		//}
		//else
		//{
			SceneManager::SharedSceneManager()->JumpToNewGuideNext();
		//}

	}

}

void UINewGuide::BtnUpInCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UINewGuide::RemoveSelfFromParent()
{
	this->getParent()->removeFromParentAndCleanup(true);
}

void UINewGuide::BtnUpOutCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UINewGuide::AddNewGuidePic()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScaleTo* action1 = NULL;
	if(i == 0)
	{
		m_pGuideBgSprite = CCSprite::spriteWithFile(s_pPathOpeningStory1);
		m_pGuideBgSprite->setPosition(ccp(winSize.width*0.307, winSize.height*0.723));
		m_pGuideBgSprite->setScale(CCGetScaleX());
		this->addChild(m_pGuideBgSprite, 1);
		m_pGuideBgSprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.0f),
														CCCallFunc::actionWithTarget(this, NULL),
														NULL));

	}
	else if (i == 1)
	{
		m_pGuideBgSprite2 = CCSprite::spriteWithFile(s_pPathOpeningStory2);
		m_pGuideBgSprite2->setPosition(ccp(winSize.width*0.520, winSize.height*0.781));
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
		m_pGuideBgSprite3 = CCSprite::spriteWithFile(s_pPathOpeningStory3);
		m_pGuideBgSprite3->setPosition(ccp(winSize.width*0.712, winSize.height*0.723));
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
		m_pGuideBgSprite4 = CCSprite::spriteWithFile(s_pPathOpeningStory4);
		m_pGuideBgSprite4->setPosition(ccp(winSize.width*0.272, winSize.height*0.403));
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
		m_pGuideBgSprite5 = CCSprite::spriteWithFile(s_pPathOpeningStory5);
		m_pGuideBgSprite5->setPosition(ccp(winSize.width*0.273, winSize.height*0.182));
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
		m_pGuideBgSprite6 = CCSprite::spriteWithFile(s_pPathOpeningStory6);
		m_pGuideBgSprite6->setPosition(ccp(winSize.width*0.684, winSize.height*0.264));
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

