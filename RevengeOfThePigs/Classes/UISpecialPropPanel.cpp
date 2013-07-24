#include "UISpecialPropPanel.h"
#include "GameResources.h"
#include "SceneManager.h"

UISpecialPropPanel::UISpecialPropPanel()
{
    
}

UISpecialPropPanel::~UISpecialPropPanel()
{
    
}

CCScene* UISpecialPropPanel::scene(CCPoint pearPos, EPropsType propType)
{
    CCScene* scene = CCScene::node();
    UISpecialPropPanel* layer = UISpecialPropPanel::node();
	layer->m_propType = propType;
	layer->InitEx(pearPos);
    scene->addChild(layer);
    return scene;
}

void UISpecialPropPanel::InitEx(CCPoint pearPos)
{
	SceneManager::SharedSceneManager()->SetPauseState(true);
	this->setIsKeypadEnabled(true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);

	CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathLight);
	bgSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height/2));
	bgSprite->setScale(CCGetScaleX());
	//bgSprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(25.0f, 360)));
	bgSprite->runAction(CCFadeIn::actionWithDuration(0.5f));
	this->addChild(bgSprite, 0);

	if (m_propType == EPropsType_SP01)
		pearSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp01);
	else if (m_propType == EPropsType_SP02)
		pearSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp02);
	else if (m_propType == EPropsType_SP03)
		pearSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp03);
	else if (m_propType == EPropsType_SP04)
		pearSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp04);
	else if (m_propType == EPropsType_SP05)
		pearSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp05);
	//pearSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height/2));
	pearSprite->setPosition(pearPos);
	pearSprite->setScale(0);
	pearSprite->runAction(CCSequence::actions(CCScaleTo::actionWithDuration(0.5f,CCGetScaleX()),
		CCCallFunc::actionWithTarget(this, callfunc_selector(UISpecialPropPanel::ActionFunc)),
		NULL));
	pearSprite->runAction(CCMoveTo::actionWithDuration(0.5f,ccp(CCGetWinSize().width/2, CCGetWinSize().height/2)));
	this->addChild(pearSprite, 1);
}

bool UISpecialPropPanel::init()
{
	return true;
}

void UISpecialPropPanel::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void UISpecialPropPanel::ActionFunc()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/quit.plist");
	CCSprite* pearIntroSprite;
	if (m_propType == EPropsType_SP01)
		pearIntroSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp01Intro);
	else if (m_propType == EPropsType_SP02)
		pearIntroSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp02Intro);
	else if (m_propType == EPropsType_SP03)
		pearIntroSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp03Intro);
	else if (m_propType == EPropsType_SP04)
		pearIntroSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp04Intro);
	else if (m_propType == EPropsType_SP05)
		pearIntroSprite = CCSprite::spriteWithFile(s_pPathSpecialProps_Sp05Intro);
	pearIntroSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height/2));
	pearIntroSprite->setScale(CCGetScaleX());
	this->addChild(pearIntroSprite, 2);

	CCSprite* quitSprite1 = CCSprite::spriteWithFile(s_pPathButtons_No);
	CCSprite* quitSprite2 = CCSprite::spriteWithFile(s_pPathButtons_No);
	CCMenuItemSprite* quitBtn = CCMenuItemSprite::itemFromNormalSprite(quitSprite1, quitSprite2);
	quitBtn->setPosition(ccp(CCGetWinSize().width-quitSprite1->getContentSize().width*CCGetScaleX()/2,
		quitSprite1->getContentSize().height*CCGetScaleX()/2));
	quitBtn->setScaleX(CCGetScaleX());
	quitBtn->setScaleY(CCGetScaleY());
	quitBtn->setTag(1000);

	MyCCMenu* myMenu = MyCCMenu::menuWithItems(quitBtn, NULL);
	myMenu->setPosition(ccp(0, 0));
	myMenu->setTag(2001);
	myMenu->SetDownUpHandle(this,
		menu_selector(UISpecialPropPanel::BtnDownCallback),
		menu_selector(UISpecialPropPanel::BtnUpInCallback),
		menu_selector(UISpecialPropPanel::BtnUpOutCallback));
	this->addChild(myMenu, 3);

	CCScheduler::sharedScheduler()->setTimeScale(0);

	if ( pearSprite != NULL )
		pearSprite->removeFromParentAndCleanup(true);

	/*
	pearIntroSprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(2.0f),
		CCCallFunc::actionWithTarget(this, callfunc_selector(UISpecialPropPanel::ActionRemoveSelf)),
		NULL));
		*/
}

bool UISpecialPropPanel::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
    if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
        return false;
    return true;
}

void UISpecialPropPanel::ActionRemoveSelf()
{
	this->getParent()->removeFromParentAndCleanup(true);
}

void UISpecialPropPanel::BtnDownCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));

	if ( pBtn->getTag() == 1000 )
	{
		RemoveSelf();
	}
}

void UISpecialPropPanel::BtnUpInCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UISpecialPropPanel::BtnUpOutCallback(CCObject* pSender)
{
	CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
	pBtn->stopAllActions();
	pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UISpecialPropPanel::keyBackClicked()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
	}

	RemoveSelf();
}

void UISpecialPropPanel::RemoveSelf()
{
	SceneManager::SharedSceneManager()->SetPauseState(false);
	CCScheduler::sharedScheduler()->setTimeScale(1);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/quit.plist");
	this->getParent()->removeFromParentAndCleanup(true);
}
