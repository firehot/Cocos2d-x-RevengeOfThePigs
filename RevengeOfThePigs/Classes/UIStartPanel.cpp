//
//  UIStartPanel.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-22.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UIStartPanel.h"
#include "MyCCMenu.h"
#include "UIBgLightLayer.h"
#include "SimpleAudioEngine.h"
#include "GameResources.h"
#include "SceneManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

UIStartPanel::UIStartPanel()
: m_pOptionSprite(NULL)
, m_pLinkSprite(NULL)
, m_pDropOptiontSprite(NULL)
, m_pDropLinkSprite(NULL)
, m_pAboutSprite(NULL)
, m_pMusicSprite(NULL)
, m_pSinaSprite(NULL)
, m_pTencenSprite(NULL)
, m_pIntroSprite(NULL)
, m_pCurPopupBtn(NULL)
, m_pIntro1Tip(NULL)
, m_pIntro2Tip(NULL)
{
    //CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
}

UIStartPanel::~UIStartPanel()
{
    
}

CCScene* UIStartPanel::scene()
{
	CCScene * scene = NULL;
	do 
	{
		//scene是自动释放的对象;
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		//layer是自动释放的对象;
		UIStartPanel *layer = UIStartPanel::node();  //在初始化的时候调用init函数;
		CC_BREAK_IF(! layer);

		//将层（layer）作为一个子对象添加给场景（scene）;
		scene->addChild(layer);
	} while (0);

    return scene;
}

bool UIStartPanel::init()
{
	this->setIsKeypadEnabled(true);
    if ( !CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathBackGround_Music, true);//第二个参数表示是否循环播放;
    if (!SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
    {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathScene_StartBackDrop);    //背景;
    bgSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height/2));
    //bgSprite->setScale(CCGetScaleX());
	bgSprite->setScaleX(CCGetScaleX());
	bgSprite->setScaleY(CCGetScaleY());
    this->addChild(bgSprite, 0);

    //CCScene* lightScene = UIBgLightLayer::scene(); //显示开始按键旁的白光效果;
    //this->addChild(lightScene, 1);

	//if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ ||
	//	SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
	//{
		CCPoint pos = ccp(CCGetWinSize().width/2, CCGetWinSize().height + 20);  //粒子发射器的位置;
		CCPoint posVar = ccp(CCGetWinSize().width/2, 0);                        //粒子发射器的偏移量;
		SceneManager::SharedSceneManager()->ShowSnowEffect(this, 1, pos, posVar);
	//}

	//if ( SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ )
	//{
	//	//logo;
	//	logoSprite = CCSprite::spriteWithFile(s_pPathStartPanel_GameLogo);
	//	logoSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height - logoSprite->getContentSize().height*CCGetScaleX()/2));
	//	logoSprite->setScale(CCGetScaleX());
	//	this->addChild(logoSprite, 2);

	//	//logoSprite = CCSprite::spriteWithFile(s_pPathStart_Logo2);
	//	//logoSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height - logoSprite->getContentSize().height*CCGetScaleX()/2));
	//	//logoSprite->setScale(CCGetScaleX());
	//	//this->addChild(logoSprite, 3);

	//	//“冰雪节版”logo;
	//	sublogoSprite = CCSprite::spriteWithFile(s_pPathStartPanel_SubLogo);
	//	sublogoSprite->setPosition(ccp(-(sublogoSprite->getContentSize().width*CCGetScaleX()/2), logoSprite->getPosition().y - logoSprite->getContentSize().height*CCGetScaleX()/2 - sublogoSprite->getContentSize().height*CCGetScaleX()/2));
	//	sublogoSprite->setScale(CCGetScaleX());
	//	this->addChild(sublogoSprite,3);

	//	this->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.5f),
	//		CCCallFunc::actionWithTarget(this, callfunc_selector(UIStartPanel::FlowerEffectCallBack)),
	//		CCDelayTime::actionWithDuration(2.5f),
	//		CCCallFunc::actionWithTarget(this, callfunc_selector(UIStartPanel::ElasticEffectCallBack)),
	//		CCCallFunc::actionWithTarget(this, callfunc_selector(UIStartPanel::FireworkEffectCallBack)),
	//		NULL));
	//	logoSprite->runAction(CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(0.5f),CCFadeOut::actionWithDuration(2.0f)));
	//}
	//else if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
	//{
		//logo;
		CCSprite* logoSprite = CCSprite::spriteWithFile(s_pPathStartPanel_GameLogo);
		logoSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height*3/4));
		logoSprite->setScale(CCGetScaleX());
		this->addChild(logoSprite, 2);

		sublogoSprite = CCSprite::spriteWithFile(s_pPathStartPanel_SubLogo);
		sublogoSprite->setPosition(ccp(sublogoSprite->getContentSize().width*CCGetScaleX() + 30, logoSprite->getPosition().y - logoSprite->getContentSize().height*CCGetScaleX()/2 - sublogoSprite->getContentSize().height*CCGetScaleX()/2 + 10));
		sublogoSprite->setScale(CCGetScaleX());
		this->addChild(sublogoSprite,3);
	//}
	//else
	//{
	//	//logo;
	//	CCSprite* logoSprite = CCSprite::spriteWithFile(s_pPathStartPanel_GameLogo);
	//	logoSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height*3/4));
	//	logoSprite->setScale(CCGetScaleX());
	//	this->addChild(logoSprite, 2);
	//}

	//开始游戏按钮;
	CCSprite* menusprite1 = CCSprite::spriteWithFile(s_pPathButtons_StartGame);
	CCSprite* menusprite2 = CCSprite::spriteWithFile(s_pPathButtons_StartGame);
    CCMenuItemSprite* startBtn = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
    startBtn->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height*1.3f/4));
    startBtn->setScale(CCGetScaleX()/50);

	startBtn->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)CCSequence::actions(CCScaleTo::actionWithDuration(0.25f, CCGetScaleX()),
		CCDelayTime::actionWithDuration(0.15f),
		CCScaleTo::actionWithDuration(0.25f, CCGetScaleX()*0.92f),
		NULL)));
    startBtn->setTag(1000);
    
	//退出游戏按钮;
	menusprite1 = CCSprite::spriteWithFile(s_pPathButtons_LeaveGame);
	menusprite2 = CCSprite::spriteWithFile(s_pPathButtons_LeaveGame);
	CCMenuItemSprite* quitBtn = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
    CCSize quitBtnSize = quitBtn->getContentSize();
    quitBtn->setScale(CCGetScaleX());
    quitBtn->setPosition(ccp(quitBtnSize.width*CCGetScaleX()/2-CCGetWinSize().width/96, quitBtnSize.height*CCGetScaleX()/2-CCGetWinSize().width/68));
    quitBtn->setTag(1001);
    
	//微博分享按钮;
	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	CCMenuItemSprite* linkBtn = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
	CCSize linkBtnSize = linkBtn->getContentSize();
	linkBtn->setScale(CCGetScaleX());
	linkBtn->setPosition(ccp(CCGetWinSize().width-linkBtnSize.width*CCGetScaleX()/2, linkBtnSize.height*CCGetScaleX()/2-CCGetWinSize().width/68));
	linkBtn->setTag(1002);
    
	//选项按钮，显示声音开关和制作组;
	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	CCMenuItemSprite* optionBtn = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
    CCSize optionBtnSize = optionBtn->getContentSize();
    optionBtn->setScale(CCGetScaleX());
    optionBtn->setPosition(ccp(linkBtn->getPosition().x-optionBtnSize.width*CCGetScaleX(), optionBtnSize.height*CCGetScaleX()/2-CCGetWinSize().width/68));
    optionBtn->setTag(1003);
    
	//黄果树信息按钮;
	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_Other);
	CCMenuItemSprite* otherBtn = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
    CCSize otherBtnSize = otherBtn->getContentSize();
    otherBtn->setScale(CCGetScaleX());
    otherBtn->setPosition(ccp(optionBtn->getPosition().x-otherBtnSize.width*CCGetScaleX(), otherBtnSize.height*CCGetScaleX()/2-CCGetWinSize().width/68));
    otherBtn->setTag(1004);
    
	//将按钮添加到菜单项;
    MyCCMenu* myMenu = MyCCMenu::menuWithItems(startBtn, optionBtn, quitBtn, linkBtn, otherBtn, NULL);
    myMenu->setPosition(ccp(0, 0));
    myMenu->SetDownUpHandle(this,
                            menu_selector(UIStartPanel::BtnDownCallback),
                            menu_selector(UIStartPanel::BtnUpInCallback),
                            menu_selector(UIStartPanel::BtnUpOutCallback));
    this->addChild(myMenu, 5);
    
	//微博分享按钮上的三角形箭头;
    m_pLinkSprite = CCSprite::spriteWithFile(s_pPathStartPanel_ReleaseTo);
    CCPoint linkSpritePos = linkBtn->getPosition();
    linkSpritePos.x = linkSpritePos.x+m_pLinkSprite->getContentSize().width*CCGetScaleX()/50.0f;
    linkSpritePos.y = linkSpritePos.y+m_pLinkSprite->getContentSize().width*CCGetScaleX()/20.0f;
    m_pLinkSprite->setPosition(linkSpritePos);
    m_pLinkSprite->setScale(CCGetScaleX());
    this->addChild(m_pLinkSprite, 6);
    
	//选项按钮的齿轮图标;
    m_pOptionSprite = CCSprite::spriteWithFile(s_pPathStartPanel_Setup);
    CCPoint optionSpritePos = optionBtn->getPosition();
    optionSpritePos.x = optionSpritePos.x+m_pLinkSprite->getContentSize().width*CCGetScaleX()/150.0f;
    optionSpritePos.y = optionSpritePos.y+m_pLinkSprite->getContentSize().width*CCGetScaleX()/15.0f;
    m_pOptionSprite->setPosition(optionSpritePos);
    m_pOptionSprite->setScale(CCGetScaleX());
    this->addChild(m_pOptionSprite, 6);

	//感叹号的图标;
	m_pIntroSprite = CCSprite::spriteWithFile(s_pPathStartPanel_GanTan);
	CCPoint introSpritePos = otherBtn->getPosition();
	introSpritePos.x = introSpritePos.x+m_pIntroSprite->getContentSize().width*CCGetScaleX()/250.0f;
	introSpritePos.y = introSpritePos.y+m_pIntroSprite->getContentSize().width*CCGetScaleX()/15.0f;
	m_pIntroSprite->setPosition(introSpritePos);
	m_pIntroSprite->setScale(CCGetScaleX());
	this->addChild(m_pIntroSprite, 6);

	//特产;
	m_pIntro1Tip = CCSprite::spriteWithFile(s_pPathStartPanel_teChanTip);
	m_pIntro1Tip->setScale(CCGetScaleX());
	m_pIntro1Tip->setAnchorPoint(CCPointMake(0, 0.5f));
	m_pIntro1Tip->setPosition(CCPointMake(otherBtn->getPosition().x+otherBtn->getContentSize().width*0.6f/2*CCGetScaleX(),
		CCGetWinSize().height/2.4f));
	m_pIntro1Tip->setOpacity((GLubyte)0);
	this->addChild(m_pIntro1Tip, 6);

	//名胜;
	m_pIntro2Tip = CCSprite::spriteWithFile(s_pPathStartPanel_mingShengTip);
	m_pIntro2Tip->setScale(CCGetScaleX());
	m_pIntro2Tip->setAnchorPoint(CCPointMake(0, 0.5f));
	m_pIntro2Tip->setPosition(CCPointMake(otherBtn->getPosition().x+otherBtn->getContentSize().width*0.6f/2*CCGetScaleX(),
		CCGetWinSize().height/4.0f));
	m_pIntro2Tip->setOpacity((GLubyte)0);
	this->addChild(m_pIntro2Tip, 6);
    
    InitPopupMenu();
	//SceneManager::SharedSceneManager()->InitWaterfallAnim(this, 2);
	
	//检查更新;
	//if ( !SceneManager::SharedSceneManager()->bCheckedUpdate )
	//{
	//	SceneManager::SharedSceneManager()->bCheckedUpdate = true;
	//	JniCheckUpdate();
	//}

	//if (SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		InitCloud(NULL, s_pPathStartPanel_Cloud);
    
    return true;
}

void UIStartPanel::InitCloud(CCSprite* pParent, const char* image)
{
	char imageFullName[50] = {0};
	sprintf(imageFullName, "%s.png", image);
	m_pCloudSprite = CCSprite::spriteWithFile(imageFullName);
	//m_pCloudSprite->setAnchorPoint(ccp(0,0));
	m_pCloudSprite->setScale(CCGetScaleX());
	//    m_pCloudSprite->setScaleY(CCGetScaleY());
	m_pCloudSprite->setPosition(ccp(CCGetWinSize().width/2, CCGetWinSize().height/2));
	this->addChild(m_pCloudSprite, 1);

	m_pCloudSpriteRe = CCSprite::spriteWithFile(imageFullName);
	//m_pCloudSpriteRe->setAnchorPoint(ccp(0,0));
	m_pCloudSpriteRe->setScale(CCGetScaleX());
	//    m_pCloudSpriteRe->setScaleY(CCGetScaleY());
	m_pCloudSpriteRe->setPosition(ccp(CCGetWinSize().width*3/2,CCGetWinSize().height/2));
	this->addChild(m_pCloudSpriteRe, 1);

	this->schedule(schedule_selector(UIStartPanel::CloudUpdate));
}

void UIStartPanel::CloudUpdate(ccTime delta)
{
	float totalWidth = CCGetWinSize().width;

	//   m_pCloudSprite->setPositionY(0);
	m_pCloudSprite->setPositionX(m_pCloudSprite->getPositionX()-20*CCGetScaleX()*delta);
	if ( m_pCloudSprite->getPositionX()<-totalWidth/2 )
		m_pCloudSprite->setPositionX(m_pCloudSprite->getPositionX()+2*totalWidth);

	//    m_pCloudSpriteRe->setPositionY(0);
	m_pCloudSpriteRe->setPositionX(m_pCloudSpriteRe->getPositionX()-20*CCGetScaleX()*delta);
	if ( m_pCloudSpriteRe->getPositionX()<-totalWidth/2 )
		m_pCloudSpriteRe->setPositionX(m_pCloudSpriteRe->getPositionX()+2*totalWidth);
}

void UIStartPanel::InitPopupMenu()
{
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//微博弹出菜单的黑框;
    m_pDropLinkSprite = CCSprite::spriteWithFile(s_pPathStartPanel_BackDrop);
    m_pDropLinkSprite->setPosition(m_pLinkSprite->getPosition());
    m_pDropLinkSprite->setScaleX(CCGetScaleX());
    m_pDropLinkSprite->setScaleY(0);
    m_pDropLinkSprite->setAnchorPoint(CCPointMake(0.5f, 0));
    this->addChild(m_pDropLinkSprite, 3);
    
	CCSprite *menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_SinaWeibo);
	CCSprite *menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_SinaWeibo);
	m_pSinaSprite = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
 //   m_pSinaSprite = CCMenuItemImage::itemFromNormalImage(s_pPathSinaWeibo, s_pPathSinaWeibo);
    m_pSinaSprite->setPosition(m_pLinkSprite->getPosition());
    m_pSinaSprite->setScale(CCGetScaleX());
    m_pSinaSprite->setTag(2001);
    

	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_TencentWeibo);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_TencentWeibo);
	m_pTencenSprite = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
    //m_pTencenSprite = CCMenuItemImage::itemFromNormalImage(s_pPathTencentWeibo, s_pPathTencentWeibo);
    m_pTencenSprite->setPosition(m_pLinkSprite->getPosition());
    m_pTencenSprite->setScale(CCGetScaleX());
    m_pTencenSprite->setTag(2002);
    
	//选项弹出菜单;
    m_pDropOptiontSprite = CCSprite::spriteWithFile(s_pPathStartPanel_BackDrop);
    m_pDropOptiontSprite->setPosition(m_pOptionSprite->getPosition());
    m_pDropOptiontSprite->setScaleX(CCGetScaleX());
    m_pDropOptiontSprite->setScaleY(0);
    m_pDropOptiontSprite->setAnchorPoint(CCPointMake(0.5f, 0));
    this->addChild(m_pDropOptiontSprite, 3);
    
	//制作人员按钮;
	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_List);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_List);
	m_pAboutSprite = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
    m_pAboutSprite->setPosition(m_pOptionSprite->getPosition());
    m_pAboutSprite->setScale(CCGetScaleX());
    m_pAboutSprite->setTag(2003);
    
	//声音开关;
	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_SoundControl2);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_SoundControl2);
	m_pMusicSprite = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
    m_pMusicSprite->setPosition(m_pOptionSprite->getPosition());
    m_pMusicSprite->setScale(CCGetScaleX());
    m_pMusicSprite->setTag(2004);

	//介绍的弹出框;
	m_pDropIntroSprite = CCSprite::spriteWithFile(s_pPathStartPanel_BackDrop);
	m_pDropIntroSprite->setPosition(m_pIntroSprite->getPosition());
	m_pDropIntroSprite->setScaleX(CCGetScaleX());
	m_pDropIntroSprite->setScaleY(0);
	m_pDropIntroSprite->setAnchorPoint(CCPointMake(0.5f, 0));
	this->addChild(m_pDropIntroSprite, 3);

	//特产按钮;
	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_teChan);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_teChan);
	m_pIntro1Sprite = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
	m_pIntro1Sprite->setPosition(m_pIntroSprite->getPosition());
	m_pIntro1Sprite->setScale(CCGetScaleX());
	m_pIntro1Sprite->setTag(2005);

	//名胜按钮;
	menusprite1 = CCSprite::spriteWithFile(s_pPathStartPanel_mingSheng);
	menusprite2 = CCSprite::spriteWithFile(s_pPathStartPanel_mingSheng);
	m_pIntro2Sprite = CCMenuItemSprite::itemFromNormalSprite(menusprite1,menusprite2);
	m_pIntro2Sprite->setPosition(m_pIntroSprite->getPosition());
	m_pIntro2Sprite->setScale(CCGetScaleX());
	m_pIntro2Sprite->setTag(2006);

	if (!SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())//获取声音状态，从而显示相应图标;
	{
		m_pNoSoundSprite = CCSprite::spriteWithFile(s_pPathStartPanel_NoSound);
		m_pNoSoundSprite->setPosition(CCPointMake(m_pMusicSprite->getContentSize().width/2,m_pMusicSprite->getContentSize().height/2));
		m_pNoSoundSprite->setScale(CCGetScaleX()*2);
		m_pMusicSprite->addChild(m_pNoSoundSprite,4);
	}
	
    
    MyCCMenu* myMenu = MyCCMenu::menuWithItems(m_pSinaSprite, m_pTencenSprite, m_pAboutSprite, m_pMusicSprite,
		m_pIntro1Sprite, m_pIntro2Sprite, NULL);
    myMenu->setPosition(ccp(0, 0));
    myMenu->SetDownUpHandle(this,
                            menu_selector(UIStartPanel::BtnDownCallback),
                            menu_selector(UIStartPanel::BtnUpInCallback),
                            menu_selector(UIStartPanel::BtnUpOutCallback));
    this->addChild(myMenu, 4);
}

void UIStartPanel::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
}

void UIStartPanel::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));

	if (  m_pDropLinkSprite->getScaleY() == 0 && m_pDropOptiontSprite->getScaleY() == 0 && m_pDropIntroSprite->getScaleY() == 0 )
		m_pCurPopupBtn = NULL;

    switch ( pBtn->getTag() )
    {
        case 1000:
        {
            //start
            SceneManager::SharedSceneManager()->JumpToSelectBigStage();
            break;
        }
        case 1001:
        {
            //quit
			//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/quit.plist"); 
            SceneManager::SharedSceneManager()->AddQuitPanel(this, 7);
            break;
        }
        case 1002:
        {
            //link
            if ( m_pLinkSprite->numberOfRunningActions() <= 0 )
            {
                m_pLinkSprite->stopAllActions();
                if ( m_pDropLinkSprite->getScaleY() == 0 )
				{
					if ( m_pCurPopupBtn != NULL && m_pCurPopupBtn != pBtn )
						BtnUpInCallback(m_pCurPopupBtn);
					m_pCurPopupBtn = pBtn;
                    m_pLinkSprite->runAction(CCRotateBy::actionWithDuration(0.3f, 180));
				}
                else
                    m_pLinkSprite->runAction(CCRotateBy::actionWithDuration(0.3f, -180));
                
                DropdownMenuClick(m_pLinkSprite, m_pDropLinkSprite, m_pSinaSprite, m_pTencenSprite);
            }

            break;
        }
        case 1003:
        {
            //option
            if ( m_pOptionSprite->numberOfRunningActions() <= 0 )
            {
                m_pOptionSprite->stopAllActions();
                if ( m_pDropOptiontSprite->getScaleY() == 0 )
				{
					if ( m_pCurPopupBtn != NULL && m_pCurPopupBtn != pBtn )
						BtnUpInCallback(m_pCurPopupBtn);
					m_pCurPopupBtn = pBtn;
                    m_pOptionSprite->runAction(CCRotateBy::actionWithDuration(0.3f, 180));
				}
                else
                    m_pOptionSprite->runAction(CCRotateBy::actionWithDuration(0.3f, -180));
                
                DropdownMenuClick(m_pOptionSprite, m_pDropOptiontSprite, m_pAboutSprite, m_pMusicSprite);
            }
            break;
        }
        case 1004:
        {
            //other
			if ( m_pIntroSprite->numberOfRunningActions() <= 0 )
			{
				m_pIntroSprite->stopAllActions();
				if ( m_pDropIntroSprite->getScaleY() == 0 )
				{
					if ( m_pCurPopupBtn != NULL && m_pCurPopupBtn != pBtn )
						BtnUpInCallback(m_pCurPopupBtn);
					m_pCurPopupBtn = pBtn;
					m_pIntroSprite->runAction(CCSequence::actions(CCRotateBy::actionWithDuration(0.3f, 180),
						CCCallFunc::actionWithTarget(this, callfunc_selector(UIStartPanel::IntroPopupFinished)),
						NULL));
				}
				else
				{
					m_pIntro1Tip->stopAllActions();
					m_pIntro2Tip->stopAllActions();
					m_pIntro1Tip->setOpacity((GLubyte)0);
					m_pIntro2Tip->setOpacity((GLubyte)0);
					m_pIntroSprite->runAction(CCRotateBy::actionWithDuration(0.3f, -180));
				}

				DropdownMenuClick(m_pIntroSprite, m_pDropIntroSprite, m_pIntro1Sprite, m_pIntro2Sprite);
			}
			break;
        }
        case 2001:
        {
            //sina;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			JniMethodInfo minfo;
			bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/RevengeOfThePigsJX/RevengeOfThePigs","SinaWeiboFun", "()V"); 

			if (!isHave)
			{
			}
			else
			{
				minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
			}
			/*
			JniMethodInfo minfo;
			bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/RevengeOfThePigsJX/RevengeOfThePigs",
				"RtnActivity", "()Ljava/lang/Object;"); 

			jobject jobj;
			if ( isHave )
				jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

			isHave = JniHelper::getMethodInfo(minfo,"org/RevengeOfThePigsJX/RevengeOfThePigs",
				"SinaWeiboFun", "()V");
			if ( isHave )
				minfo.env->CallVoidMethod(jobj, minfo.methodID);
				*/
#endif
            break;
        }
        case 2002:
        {
            //tencent;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			JniMethodInfo minfo;
			bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/RevengeOfThePigsJX/RevengeOfThePigs","TencentWeiboFun", "()V"); 

			if (!isHave)
			{
			}
			else
			{
				minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
			}
			/*
			JniMethodInfo minfo;
			bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/RevengeOfThePigsJX/RevengeOfThePigs",
				"RtnActivity", "()Ljava/lang/Object;"); 

			jobject jobj;
			if ( isHave )
				jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

			isHave = JniHelper::getMethodInfo(minfo,"org/RevengeOfThePigsJX/RevengeOfThePigs",
				"TencentWeiboFun", "()V");
			if ( isHave )
				minfo.env->CallVoidMethod(jobj, minfo.methodID);
				*/
#endif
            break;
        }
        case 2003:
        {
            //about;
			SceneManager::SharedSceneManager()->AddIntroducePanel(this, EFruitType_Design, 7);
            break;
        }
        case 2004:
        {
            //sound control;
			SceneManager::SharedSceneManager()->SetPlayBackgroundMusicState();
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();//继续播放背景音乐;
				m_pMusicSprite->removeChild(m_pNoSoundSprite,true);//删除图标;
				//CCLOG("resume");
			}
			else
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();//暂停播放背景音乐;
				m_pNoSoundSprite = CCSprite::spriteWithFile(s_pPathStartPanel_NoSound);//在声音按钮上添加一把叉的图标;
				m_pNoSoundSprite->setPosition(CCPointMake(m_pMusicSprite->getContentSize().width/2,m_pMusicSprite->getContentSize().height/2));
				m_pNoSoundSprite->setScale(CCGetScaleX()*2);
				m_pMusicSprite->addChild(m_pNoSoundSprite,4);
				//CCLOG("pause");
			}
            break;
        }
		case 2005:
		{
			//intro 1
			//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
			//{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			//}
			SceneManager::SharedSceneManager()->AddIntroducePanel(this, EFruitType_Pear, 7);
			break;
		}
		case 2006:
		{
			//intro2
			//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
			//{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			//}
			SceneManager::SharedSceneManager()->AddIntroducePanel(this, EFruitType_HGS, 7);
			break;
		}
    }
}

void UIStartPanel::JniCheckUpdate()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/RevengeOfThePigsJX/RevengeOfThePigs","CheckUpdate", "()V"); 

	if (!isHave)
	{
	}
	else
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
}

void UIStartPanel::IntroPopupFinished()
{
	m_pIntro1Tip->runAction(CCFadeIn::actionWithDuration(0.5f));
	m_pIntro2Tip->runAction(CCFadeIn::actionWithDuration(0.5f));
}

void UIStartPanel::DropdownMenuClick(CCSprite* topSprite, CCSprite* dropBgSprite, CCMenuItemSprite* upBtn, CCMenuItemSprite* downBtn)
{
	//如果弹出菜单未弹出，则设置其弹出属性;
    if ( dropBgSprite != NULL && dropBgSprite->getScaleY() == 0 )
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCPoint upPos = topSprite->getPosition();
        upPos.y = upPos.y+dropBgSprite->getContentSize().height/2*CCGetScaleX()+upBtn->getContentSize().height*CCGetScaleX();
        CCPoint downPos = topSprite->getPosition();
        downPos.y = downPos.y+dropBgSprite->getContentSize().height/2*CCGetScaleX()-downBtn->getContentSize().height/2*CCGetScaleX();
        upBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.07f),
                                                      CCMoveTo::actionWithDuration(0.13f, upPos),
                                                      NULL));
        downBtn->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.13f),
                                                      CCMoveTo::actionWithDuration(0.07f, downPos),
                                                      NULL));
        dropBgSprite->runAction(CCScaleTo::actionWithDuration(0.2f, CCGetScaleX(), CCGetScaleY()));
    }
	//如果弹出菜单已弹出，则设置缩回的属性;
    else if ( dropBgSprite != NULL && dropBgSprite->getScaleY() == CCGetScaleY() )
    {
        upBtn->runAction(CCMoveTo::actionWithDuration(0.13f, topSprite->getPosition()));
        downBtn->runAction(CCMoveTo::actionWithDuration(0.07f, topSprite->getPosition()));
        dropBgSprite->runAction(CCScaleTo::actionWithDuration(0.2f, CCGetScaleX(), 0));
    }
}

void UIStartPanel::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));

	if ( pBtn->getTag() == 1000 )
	{
		pBtn->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)CCSequence::actions(CCScaleTo::actionWithDuration(0.25f, CCGetScaleX()),
			CCDelayTime::actionWithDuration(0.15f),
			CCScaleTo::actionWithDuration(0.25f, CCGetScaleX()*0.92f),
			NULL)));
	}
}
void UIStartPanel::keyBackClicked()
{
	if ( !SceneManager::SharedSceneManager()->IsContainIntroPanel(this) &&
		!SceneManager::SharedSceneManager()->IsContainQuitPanel(this) )
	{
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
		}

		//在主菜单按返回键将添加添加退出确定的场景;
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/quit.plist");
		SceneManager::SharedSceneManager()->AddQuitPanel(this, 7);                 
	}
}

void UIStartPanel::FlowerEffectCallBack()
{
	CCPoint pos = ccp(CCGetWinSize().width/2 - logoSprite->getContentSize().width*CCGetScaleX()/2, logoSprite->getPosition().y);
	CCPoint posVar = ccp(0, logoSprite->getContentSize().height*CCGetScaleX()/2 - 10);
	CCPoint des = ccp(CCGetWinSize().width/2 + logoSprite->getContentSize().width*CCGetScaleX()/2, logoSprite->getPosition().y);
	ccTime time = 1.5f;   //该时间用于控制发射器从左到右的移动时间;
	SceneManager::SharedSceneManager()->ShowFlowerEffect(this, 10, pos, posVar,time,des);
}


void UIStartPanel::ElasticEffectCallBack()
{
	int offset = CCGetWinSize().width/2 + sublogoSprite->getContentSize().width*CCGetScaleX()/2;
	CCFiniteTimeAction *ElasticAction = CCEaseElasticOut::actionWithAction(CCMoveBy::actionWithDuration(1, ccp(offset ,0)), 0.5f);
	sublogoSprite->runAction(ElasticAction);
}

void UIStartPanel::FireworkEffectCallBack()
{
	CCPoint pos = ccp(CCGetWinSize().width/2, sublogoSprite->getPosition().y);
	CCPoint posVar = ccp(sublogoSprite->getContentSize().width*CCGetScaleX()/2, 0);
	ccTime time = 0.1f;   //发射为瞬间;
	SceneManager::SharedSceneManager()->ShowFireworkEffect(this,10,pos,posVar,time);
}