#include "UIIntroducePanel.h"
#include "GameResources.h"
#include "SceneManager.h"

UIIntroducePanel::UIIntroducePanel()
	:pContentSprite(NULL)
	,pLeftBtn(NULL)
	,pRightBtn(NULL)
	,numberIndex(1)
{
    
}

UIIntroducePanel::~UIIntroducePanel()
{
    
}

CCScene* UIIntroducePanel::scene(EFruitType type)
{
    CCScene* scene = CCScene::node();
    UIIntroducePanel* layer = UIIntroducePanel::node();
	layer->InitEx(type);
    scene->addChild(layer);
    return scene;
}

void UIIntroducePanel::InitEx(EFruitType type)
{
	this->setIsKeypadEnabled(true);
	//重新注册为单点触控，第二个参数为优先级，数值越低，优先级越高;
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/quit.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/bigsmal_stage.plist"); 

	m_fruitType = type;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* bgSprite;
	if ( m_fruitType == EFruitType_Pear )
		bgSprite = CCSprite::spriteWithFile(s_pPathIntroduce2_TCBG);
	else if ( m_fruitType == EFruitType_HGS )
		bgSprite = CCSprite::spriteWithFile(s_pPathIntroduce1_JDBG);
	else if ( m_fruitType == EFruitType_Design )
		bgSprite = CCSprite::spriteWithFile(s_pPathIntroduce1_JDBG);
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	bgSprite->setScaleX(CCGetScaleX());
	bgSprite->setScaleY(CCGetScaleY());
	this->addChild(bgSprite, 0);

	if ( m_fruitType == EFruitType_Pear )
	{
		pContentSprite = CCSprite::spriteWithFile(s_pPathIntroduce2_TC1);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSpecialty1Intro);
	}
	else if ( m_fruitType == EFruitType_HGS )
	{
		pContentSprite = CCSprite::spriteWithFile(s_pPathIntroduce1_JD1);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScene1Intro);
	}
	else if ( m_fruitType == EFruitType_Design )
		pContentSprite = CCSprite::spriteWithFile(s_pPathTeam_Credits);
	pContentSprite->setPosition(ccp(winSize.width/2, winSize.height*1.5/4));
	pContentSprite->setScaleX(CCGetScaleX());
	pContentSprite->setScaleY(CCGetScaleY());
	this->addChild(pContentSprite, 1);

	CCSprite* quitSprite1 = CCSprite::spriteWithFile(s_pPathButtons_No);
	CCSprite* quitSprite2 = CCSprite::spriteWithFile(s_pPathButtons_No);
	CCMenuItemSprite* quitBtn = CCMenuItemSprite::itemFromNormalSprite(quitSprite1, quitSprite2);
	quitBtn->setPosition(ccp(quitSprite1->getContentSize().width*CCGetScaleX()/2,
		CCGetWinSize().height-quitSprite1->getContentSize().height*CCGetScaleX()/2));
	quitBtn->setScaleX(CCGetScaleX());
	quitBtn->setScaleY(CCGetScaleY());
	quitBtn->setTag(1001);

	CCSprite* leftSprite1 = CCSprite::spriteWithFile(s_pPathButtons_Prior);
	CCSprite* leftSprite2 = CCSprite::spriteWithFile(s_pPathButtons_Prior);
	pLeftBtn = CCMenuItemSprite::itemFromNormalSprite(leftSprite1, leftSprite2);
	pLeftBtn->setPosition(ccp(leftSprite1->getContentSize().width*CCGetScaleX()/2,
		leftSprite1->getContentSize().height*CCGetScaleX()/2-CCGetWinSize().width/68));
	pLeftBtn->setScaleX(CCGetScaleX());
	pLeftBtn->setScaleY(CCGetScaleY());
	pLeftBtn->setTag(1002);
	pLeftBtn->setIsVisible(false);

	CCSprite* rightSprite1 = CCSprite::spriteWithFile(s_pPathButtons_Goon);
	CCSprite* rightSprite2 = CCSprite::spriteWithFile(s_pPathButtons_Goon);
	pRightBtn = CCMenuItemSprite::itemFromNormalSprite(rightSprite1, rightSprite2);
	pRightBtn->setPosition(ccp(CCGetWinSize().width-rightSprite1->getContentSize().width*CCGetScaleX()/2,
		rightSprite1->getContentSize().height*CCGetScaleX()/2-CCGetWinSize().width/68));
	pRightBtn->setScaleX(CCGetScaleX());
	pRightBtn->setScaleY(CCGetScaleY());
	pRightBtn->setTag(1003);
	if ( m_fruitType == EFruitType_Design )
		pRightBtn->setIsVisible(false);

	MyCCMenu* myMenu = MyCCMenu::menuWithItems(quitBtn, pLeftBtn, pRightBtn, NULL);
	myMenu->setPosition(ccp(0, 0));
	myMenu->setTag(2001);
	myMenu->SetDownUpHandle(this,
		menu_selector(UIIntroducePanel::BtnDownCallback),
		menu_selector(UIIntroducePanel::BtnUpInCallback),
		menu_selector(UIIntroducePanel::BtnUpOutCallback));
	this->addChild(myMenu, 2);
}

bool UIIntroducePanel::init()
{
	return true;
}

void UIIntroducePanel::onExit()
{
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool UIIntroducePanel::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
    if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
        return false;
    return true;
}

void UIIntroducePanel::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
    
    if ( pBtn->getTag() == 1001 )
    {
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/quit.plist");
		//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		//}
		this->getParent()->removeFromParentAndCleanup(true);
	}
	else if ( pBtn->getTag() == 1002 )
	{
		if ( numberIndex <= 1 )
			return;
		numberIndex--;
		char imageFullName[70] = {0};
		if ( m_fruitType == EFruitType_Pear )
		{
			sprintf(imageFullName, "%s%d.png", s_pPathIntroduce2_TC,numberIndex);
			//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
			//{
				if(numberIndex == 1)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSpecialty1Intro);
				}
				else if(numberIndex == 2)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSpecialty2Intro);
				}
				else if(numberIndex == 3)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSpecialty3Intro);
				}
			//}
		}
		else if ( m_fruitType == EFruitType_HGS )
		{
			sprintf(imageFullName, "%s%d.png", s_pPathIntroduce1_JD,numberIndex);
			//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
			//{
				if(numberIndex == 1)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScene1Intro);
				}
				else if(numberIndex == 2)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScene2Intro);
				}
				else if(numberIndex == 3)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScene3Intro);
				}
			//}
		}
		pContentSprite->initWithFile(imageFullName);
		
		int maxIndex = 3;
		if ( m_fruitType == EFruitType_Pear )
			maxIndex = 3;
		//else if ( m_fruitType == EFruitType_HGS && SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_SZ )
		//	maxIndex = 6;

		if ( numberIndex <= 1 )
			pLeftBtn->setIsVisible(false);
		if ( numberIndex < maxIndex )
			pRightBtn->setIsVisible(true);
	}
	else if ( pBtn->getTag() == 1003 )
	{
		int maxIndex = 3;
		if ( m_fruitType == EFruitType_Pear )
			maxIndex = 3;
		//else if ( m_fruitType == EFruitType_HGS && SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_SZ )
		//	maxIndex = 6;

		if ( numberIndex >= maxIndex )
			return;
		numberIndex++;
		char imageFullName[70] = {0};
		if ( m_fruitType == EFruitType_Pear )
		{
			sprintf(imageFullName, "%s%d.png",s_pPathIntroduce2_TC, numberIndex);
			//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
			//{
				if(numberIndex == 1)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSpecialty1Intro);
				}
				else if(numberIndex == 2)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSpecialty2Intro);
				}
				else if(numberIndex == 3)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSpecialty3Intro);
				}
			//}
		}
		else if ( m_fruitType == EFruitType_HGS )
		{
			sprintf(imageFullName, "%s%d.png",s_pPathIntroduce1_JD, numberIndex);
			//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
			//{
				if(numberIndex == 1)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScene1Intro);
				}
				else if(numberIndex == 2)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScene2Intro);
				}
				else if(numberIndex == 3)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathScene3Intro);
				}
			//}
		}
		pContentSprite->initWithFile(imageFullName);

		if ( numberIndex >= maxIndex )
			pRightBtn->setIsVisible(false);
		if ( numberIndex > 1 )
			pLeftBtn->setIsVisible(true);
	}
}

void UIIntroducePanel::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UIIntroducePanel::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UIIntroducePanel::keyBackClicked()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/quit.plist");
	this->getParent()->removeFromParentAndCleanup(true);
}
