#include "UIHelpPanel.h"
#include "GameResources.h"
#include "SceneManager.h"

UIHelpPanel::UIHelpPanel()
: m_pHelpBgSprite(NULL)
, m_pHelpMenu(NULL)
, m_pHelpBgLayerColor(NULL)
{
    
}

UIHelpPanel::~UIHelpPanel()
{
    
}

CCScene* UIHelpPanel::scene()
{
    CCScene* scene = CCScene::node();
    UIHelpPanel* layer = UIHelpPanel::node();
    scene->addChild(layer);
    return scene;
}

bool UIHelpPanel::init()
{
	n=0;
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/YN.plist");  //╪сть;
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_pHelpBgLayerColor = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
    this->addChild(m_pHelpBgLayerColor, 0);
    m_pHelpBgLayerColor->runAction(CCFadeTo::actionWithDuration(0.2f, 127));
    
    m_pHelpBgSprite = CCSprite::spriteWithFile(s_pPathNewGuide_Help0);
	//m_pHelpBgSprite->setScale(0.125f);
    m_pHelpBgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    m_pHelpBgSprite->setScale(CCGetScaleX());
	//
	char frameName[50] = {0};
	CCAnimation* animation = CCAnimation::animation();
	for (int i = 1; i <= 3; i++)
	{
		sprintf(frameName, "%s%d.png",s_pPathNewGuide_Help0Anim, i);
		animation->addFrameWithFileName(frameName);
	}
	CCAnimate *animate = CCAnimate::actionWithDuration(1.5f, animation, false);
	m_pHelpBgSprite->runAction(CCSequence::actions(animate,
		CCCallFunc::actionWithTarget(this,callfunc_selector(UIHelpPanel::EndAnimationCallback)),
		NULL));  
	//
    this->addChild(m_pHelpBgSprite, 1);
    
	CCSprite *menusprite3 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
	CCSprite *menusprite4 = CCSprite::spriteWithFile(s_pPathButtons_Yes);
	continueBtn = CCMenuItemSprite::itemFromNormalSprite(menusprite3,menusprite4);
   // continueBtn = CCMenuItemImage::itemFromNormalImage(s_pPathYes, s_pPathYes);
    continueBtn->setScale(CCGetScaleX());
	//continueBtn->setRotation(-90);
    continueBtn->setPosition(ccp(winSize.width*1.1f/1.5, winSize.height/6));
    continueBtn->setTag(1002);
	//continueBtn->getIsEnabled(false);
	continueBtn->setIsVisible(false);

	menusprite3 = CCSprite::spriteWithFile(s_pPathButtons_Goon);
	menusprite4 = CCSprite::spriteWithFile(s_pPathButtons_Goon);
	nextPicBtn = CCMenuItemSprite::itemFromNormalSprite(menusprite3,menusprite4);
	//nextPicBtn = CCMenuItemImage::itemFromNormalImage(s_pPathNext,s_pPathNext);
	nextPicBtn->setScale(CCGetScaleX());
	nextPicBtn->setPosition(ccp(winSize.width*1.1f/1.5, winSize.height/6));
	nextPicBtn->setTag(1001);
	nextPicBtn->setIsVisible(false);
   
    m_pHelpMenu = MyCCMenu::menuWithItems( continueBtn,nextPicBtn,NULL);
    m_pHelpMenu->setPosition(ccp(0, 0));
    m_pHelpMenu->setTag(2001);
    m_pHelpMenu->SetDownUpHandle(this,
                            menu_selector(UIHelpPanel::BtnDownCallback),
                            menu_selector(UIHelpPanel::BtnUpInCallback),
                            menu_selector(UIHelpPanel::BtnUpOutCallback));
    this->addChild(m_pHelpMenu, 2);
    
    //m_pHelpBgSprite->runAction(CCMoveTo::actionWithDuration(0, ccp(winSize.width/2, winSize.height/2)));
    //m_pHelpMenu->runAction(CCMoveTo::actionWithDuration(0, ccp(0, 0)));
    
    return true;
}

void UIHelpPanel::EndAnimationCallback()
{
	nextPicBtn->setIsVisible(true);
}

bool UIHelpPanel::containsTouchLocation(CCTouch* pTouch)
{
    CCPoint touchLocation = pTouch->locationInView(pTouch->view());
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    CCRect myRect = CCRectMake(this->getPosition().x, this->getPosition().y,
                               this->getContentSize().width, this->getContentSize().height);
    return CCRect::CCRectContainsPoint(myRect, touchLocation);
}

bool UIHelpPanel::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(2001);
    if ( pMenu != NULL && pMenu->itemForTouch(touch) != NULL )
        return false;
    return true;
}

void UIHelpPanel::onExit()
{
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void UIHelpPanel::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
}

void UIHelpPanel::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));

	if (pBtn->getTag() == 1001)
	{
		//nextPic
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		if(n == 0)
		{
			this->removeChild(m_pHelpBgSprite,1);
			m_pHelpBgSprite = CCSprite::spriteWithFile(s_pPathNewGuide_Help1);
			m_pHelpBgSprite->setPosition(ccp(winSize.width*0.8f/1.6f, winSize.height/2));
			m_pHelpBgSprite->setScale(CCGetScaleX());
			//
			char frameName[50] = {0};
			CCAnimation* animation = CCAnimation::animation();
			for (int i = 1; i <= 3; i++)
			{
				sprintf(frameName, "%s%d.png",s_pPathNewGuide_Help1Anim, i);
				animation->addFrameWithFileName(frameName);
			}
			CCAnimate *animate = CCAnimate::actionWithDuration(1.0f, animation, false);
			m_pHelpBgSprite->runAction(CCSequence::actions(animate,
				CCCallFunc::actionWithTarget(this,callfunc_selector(UIHelpPanel::EndAnimationCallback)),
				NULL));  
			//
			this->addChild(m_pHelpBgSprite, 1);
		}
		if (n == 1)
		{
			this->removeChild(m_pHelpBgSprite,1);
			m_pHelpBgSprite = CCSprite::spriteWithFile(s_pPathNewGuide_Help2);
			m_pHelpBgSprite->setPosition(ccp(winSize.width*0.8f/1.6f, winSize.height/2));
			m_pHelpBgSprite->setScale(CCGetScaleX());
			//
			char frameName[50] = {0};
			CCAnimation* animation = CCAnimation::animation();
			for (int i = 1; i <= 3; i++)
			{
				sprintf(frameName, "%s%d.png",s_pPathNewGuide_Help2Anim, i);
				animation->addFrameWithFileName(frameName);
			}
			CCAnimate *animate = CCAnimate::actionWithDuration(1.0f, animation, false);
			m_pHelpBgSprite->runAction(CCSequence::actions(animate,
				CCCallFunc::actionWithTarget(this,callfunc_selector(UIHelpPanel::EndAnimationCallback)),
				NULL));  
			//
			this->addChild(m_pHelpBgSprite, 1);
		}	
		if (n == 2)
		{
			this->removeChild(m_pHelpBgSprite,1);
			m_pHelpBgSprite = CCSprite::spriteWithFile(s_pPathNewGuide_Help3);
			m_pHelpBgSprite->setPosition(ccp(winSize.width*0.8f/1.6f, winSize.height/2));
			m_pHelpBgSprite->setScale(CCGetScaleX());
			//
			char frameName[50] = {0};
			CCAnimation* animation = CCAnimation::animation();
			for (int i = 1; i <= 3; i++)
			{
				sprintf(frameName, "%s%d.png",s_pPathNewGuide_Help3Anim, i);
				animation->addFrameWithFileName(frameName);
			}
			CCAnimate *animate = CCAnimate::actionWithDuration(1.0f, animation, false);
			m_pHelpBgSprite->runAction(CCSequence::actions(animate,
				CCCallFunc::actionWithTarget(this,callfunc_selector(UIHelpPanel::EndAnimationCallback)),
				NULL));  
			//
			this->addChild(m_pHelpBgSprite, 1);
		}
		if (n == 3)
		{
			this->removeChild(m_pHelpBgSprite,1);
			m_pHelpBgSprite = CCSprite::spriteWithFile(s_pPathNewGuide_Help4);
			m_pHelpBgSprite->setPosition(ccp(winSize.width*0.8f/1.6f, winSize.height/2));
			m_pHelpBgSprite->setScale(CCGetScaleX());
			//
			char frameName[50] = {0};
			CCAnimation* animation = CCAnimation::animation();
			for (int i = 1; i <= 3; i++)
			{
				sprintf(frameName, "%s%d.png", s_pPathNewGuide_Help4Anim, i);
				animation->addFrameWithFileName(frameName);
			}
			CCAnimate *animate = CCAnimate::actionWithDuration(1.0f, animation, false);
			m_pHelpBgSprite->runAction(CCSequence::actions(animate,
				NULL));  
			//
			this->addChild(m_pHelpBgSprite, 1);
			continueBtn->setIsVisible(true);
		}
		n++;
		nextPicBtn->setIsVisible(false);
	}

	if ( n == 4 && pBtn->getTag() == 1002 )
	{
		//continue
		SceneManager::SharedSceneManager()->SetPauseState(false);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_pHelpBgSprite->runAction(CCMoveTo::actionWithDuration(0, ccp(winSize.width*0.8f/4, winSize.height/2)));
		m_pHelpMenu->runAction(CCMoveTo::actionWithDuration(0, ccp(-winSize.width*1.4f/4, 0)));
		m_pHelpBgLayerColor->runAction(CCSequence::actions(CCFadeTo::actionWithDuration(0, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(UIHelpPanel::RemoveSelfFromParent)),
			NULL));
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUI/YN.plist");
	}
}

void UIHelpPanel::RemoveSelfFromParent()
{
    this->getParent()->removeFromParentAndCleanup(true);
}

void UIHelpPanel::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
}

void UIHelpPanel::keyBackClicked()
{
	RemoveSelfFromParent();
}
