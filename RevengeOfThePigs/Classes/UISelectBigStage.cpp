//
//  UISelectBigStage.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-23.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "UISelectBigStage.h"
#include "MyCCMenu.h"
#include "GameResources.h"
#include "SceneManager.h"

UISelectBigStage::UISelectBigStage()
	: m_pLeftBtn(NULL)
	, m_pRightBtn(NULL)
{
    
}

UISelectBigStage::~UISelectBigStage()
{
    
}

CCScene* UISelectBigStage::scene()
{
    CCScene* scene = CCScene::node();
    UISelectBigStage* layer = UISelectBigStage::node();
    scene->addChild(layer);
    return scene;
}

bool UISelectBigStage::init()
{
	this->setIsKeypadEnabled(true);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(s_pPathstart_panel);  //进入大关时, 删除开始界面和退出界面;

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUI/bigsmal_stage.plist"); 
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bgSprite = CCSprite::spriteWithFile(s_pPathScene_StartBackDrop);
    bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    //bgSprite->setScale(CCGetScaleX());
	bgSprite->setScaleX(CCGetScaleX());
	bgSprite->setScaleY(CCGetScaleY());
    this->addChild(bgSprite, -3);
    
	CCSprite* yesb= CCSprite::spriteWithFile(s_pPathButtons_Back);
	CCSprite* yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Back);
	CCMenuItemSprite* backBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
    //CCMenuItemImage* backBtn = CCMenuItemImage::itemFromNormalImage(s_pPathBack, s_pPathBack);
    CCSize backBtnSize = backBtn->getContentSize();
    backBtn->setScale(CCGetScaleX());
    backBtn->setPosition(ccp(backBtnSize.width*CCGetScaleX()/2-CCGetWinSize().width/96, backBtnSize.height*CCGetScaleX()/2-CCGetWinSize().width/68));
    backBtn->setTag(1001);

	/*
	yesb= CCSprite::spriteWithFile(s_pPathButtons_Prior);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Prior);
	m_pLeftBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pLeftBtn->setScale(CCGetScaleX());
	//m_pLeftBtn->setAnchorPoint(ccp(1,0));
	//m_pLeftBtn->setPosition(ccp(0, CCGetWinSize().height/2));
	m_pLeftBtn->setPosition(ccp(CCGetWinSize().width/3, -m_pLeftBtn->getContentSize().height*CCGetScaleX()/2));
	m_pLeftBtn->setTag(1012);

	yesb= CCSprite::spriteWithFile(s_pPathButtons_Goon);
	yesb2 = CCSprite::spriteWithFile(s_pPathButtons_Goon);
	m_pRightBtn = CCMenuItemSprite::itemFromNormalSprite(yesb,yesb2);
	m_pRightBtn->setScale(CCGetScaleX());
	//m_pRightBtn->setAnchorPoint(ccp(0,0));
	//m_pRightBtn->setPosition(ccp(CCGetWinSize().width-m_pRightBtn->getContentSize().width*CCGetScaleX(), CCGetWinSize().height/2));
	m_pRightBtn->setPosition(ccp(CCGetWinSize().width*2/3, m_pRightBtn->getContentSize().height*CCGetScaleX()/2 - CCGetWinSize().width/68));
	m_pRightBtn->setTag(1013);
	*/
    
    MyCCMenu* myMenu = MyCCMenu::menuWithItems(backBtn, m_pLeftBtn, m_pRightBtn, NULL);
    myMenu->setPosition(ccp(0, 0));
    myMenu->SetDownUpHandle(this,
                            menu_selector(UISelectBigStage::BtnDownCallback),
                            menu_selector(UISelectBigStage::BtnUpInCallback),
                            menu_selector(UISelectBigStage::BtnUpOutCallback));
    this->addChild(myMenu, 1);
    
    InitScrollView();
	//SceneManager::SharedSceneManager()->InitWaterfallAnim(this, 0);
    
    return true;
}

void UISelectBigStage::InitScrollView()
{
	/** 第一关 */
    CCMenuItemImage* item1 = CCMenuItemImage::itemFromNormalImage(s_pPathBigStage_Scene1BackDrop, s_pPathBigStage_Scene1BackDrop);
	float itemContentWidth = item1->getContentSize().width*CCGetScaleX();
	float offSetX = itemContentWidth * 0.8;
	float itemY = CCGetWinSize().height*1.1f/2;
	item1->setScaleX(CCGetScaleX());
	item1->setScaleY(CCGetScaleY());
    item1->setPosition(ccp(itemContentWidth*0+offSetX, itemY));
    item1->setTag(1002);
	//总分数的显示栏;
    CCSprite* bg1 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
    bg1->setPosition(ccp(item1->getContentSize().width/2, item1->getContentSize().height*0.8f/2));
    item1->addChild(bg1);
	//总星星数的显示栏;
    CCSprite* bg2 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
    bg2->setPosition(ccp(item1->getContentSize().width/2, item1->getContentSize().height*0.5f/2));
    item1->addChild(bg2);
	//获得的刺梨数显示栏;
    //CCSprite* bg3 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
    //bg3->setPosition(ccp(item1->getContentSize().width/2, item1->getContentSize().height*0.2f/2));
    //item1->addChild(bg3);

	CCSprite* label1 = CCSprite::spriteWithFile(s_pPathBigStage_TotalScore);
    label1->setPosition(ccp(bg1->getContentSize().width/2, bg1->getContentSize().height*1.5/2));
    bg1->addChild(label1);
	//从userdefault.xml文件中读取第一大关的所有分数的总和;
	int TotalScore = 0, TotalStars = 0, totalPears = 0;
	//循环遍历10关;
	for (int i=1; i <= 10; i++)
	{
		char string[16]={0};
		sprintf(string, "highestScore%d%d", 1,i);
		TotalScore+=CCUserDefault::sharedUserDefault()->getIntegerForKey(string); //如果该键值不存在，默认值为0;
		//从userdefault.xml文件中读取第一大关卡的所有星星数;
		char sStars[16]={0};
		sprintf(sStars, "stars%d%d", 1,i);
		TotalStars+=CCUserDefault::sharedUserDefault()->getIntegerForKey(sStars);
		//从userdefault.xml文件中读取第一大关卡的刺梨数;
		char sPearKey[16]={0};
		sprintf(sPearKey, "PearCount%d%d", 1, i);
		if ( CCUserDefault::sharedUserDefault()->getBoolForKey(sPearKey) )
			totalPears++;
	}

	char string1[16]={0};
	//显示总分;
	sprintf(string1,"%d",TotalScore);
	CCLabelAtlas* label2 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
	label2->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	label2->setPosition(ccp(bg1->getContentSize().width/2, bg1->getContentSize().height*0.7/2));
	bg1->addChild(label2);

	//显示星星数;
	sprintf(string1,"%d/30",TotalStars);
	CCLabelAtlas* label3 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
	label3->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	label3->setPosition(ccp(bg2->getContentSize().width/2, bg2->getContentSize().height*0.7/2));
	bg2->addChild(label3);
	CCSprite* star = CCSprite::spriteWithFile(s_pPathBigStage_Star);
	star->setPosition(ccp(bg2->getContentSize().width/2, bg2->getContentSize().height*1.5/2));
	bg2->addChild(star);

	//显示获得的刺梨数;
	//sprintf(string1, "%d/5", totalPears);
	//CCLabelAtlas* label4 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
	//label4->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	//label4->setPosition(ccp(bg3->getContentSize().width/2, bg3->getContentSize().height*0.7/2));
	//bg3->addChild(label4);
	//CCSprite* fruit = CCSprite::spriteWithFile(s_pPear);
	//fruit->setPosition(ccp(bg3->getContentSize().width/2, bg3->getContentSize().height*1.5/2));
	//bg3->addChild(fruit);

	/** 第二关 */
	CCMenuItemImage* item2 = CCMenuItemImage::itemFromNormalImage(s_pPathBigStage_Scene2BackDrop, s_pPathBigStage_Scene2BackDrop);
	item2->setScaleX(CCGetScaleX());
	item2->setScaleY(CCGetScaleY());
	item2->setPosition(ccp(itemContentWidth*1+offSetX * 1.1, itemY));
	//从userdefault.xml中获取第二大关的第一小关是否开通，如果开通的话则第二大关也开通，未开通则上锁;
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsOpen21") || SceneManager::SharedSceneManager()->IsTestGameMode())
	//if ( true )
	{
		item2->setTag(1003);
		CCSprite* bg21 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg21->setPosition(ccp(item2->getContentSize().width/2, item2->getContentSize().height*0.8f/2));
		item2->addChild(bg21);
		CCSprite* bg22 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg22->setPosition(ccp(item2->getContentSize().width/2, item2->getContentSize().height*0.5f/2));
		item2->addChild(bg22);
		//CCSprite* bg23 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		//bg23->setPosition(ccp(item2->getContentSize().width/2, item2->getContentSize().height*0.2f/2));
		//item2->addChild(bg23);
		CCSprite* label21 = CCSprite::spriteWithFile(s_pPathBigStage_TotalScore);
		label21->setPosition(ccp(bg21->getContentSize().width/2, bg21->getContentSize().height*1.5/2));
		bg21->addChild(label21);
		//从userdefault.xml文件中读取第二大关的所有分数的总和;
		TotalScore=0, TotalStars = 0, totalPears = 0;
		for (int i=1; i<= 10; i++)
		{
			//从userdefault.xml文件中读取第二大关卡的总分;
			char string[16]={0};
			sprintf(string, "highestScore%d%d", 2,i);
			TotalScore+=CCUserDefault::sharedUserDefault()->getIntegerForKey(string);
			//从userdefault.xml文件中读取第二大关卡的所有星星数;
			char sStars[16]={0};
			sprintf(sStars, "stars%d%d", 2,i);
			TotalStars+=CCUserDefault::sharedUserDefault()->getIntegerForKey(sStars);
			//从userdefault.xml文件中读取第二大关卡的所有刺梨数;
			char sPearKey[16]={0};
			sprintf(sPearKey, "PearCount%d%d", 2, i);
			if ( CCUserDefault::sharedUserDefault()->getBoolForKey(sPearKey) )
				totalPears++;
		}
		//总分;
		sprintf(string1,"%d",TotalScore);
		CCLabelAtlas* label22 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label22->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label22->setPosition(ccp(bg21->getContentSize().width/2, bg21->getContentSize().height*0.7/2));
		bg21->addChild(label22);
		//星星数;
		sprintf(string1,"%d/30",TotalStars);
		CCLabelAtlas* label23 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label23->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label23->setPosition(ccp(bg22->getContentSize().width/2, bg22->getContentSize().height*0.7/2));
		bg22->addChild(label23);
		CCSprite* star2 = CCSprite::spriteWithFile(s_pPathBigStage_Star);
		star2->setPosition(ccp(bg22->getContentSize().width/2, bg22->getContentSize().height*1.5/2));
		bg22->addChild(star2);
	}
	else
	{
		CCSprite* suo2 = CCSprite::spriteWithFile(s_pPathBigStage_LevelLocked);
		suo2->setPosition(ccp(item2->getContentSize().width/2, item2->getContentSize().height*0.8f/2));
		item2->addChild(suo2);
	}

	/** 第三关 */
	CCMenuItemImage* item3 = CCMenuItemImage::itemFromNormalImage(s_pPathBigStage_Scene3BackDrop, s_pPathBigStage_Scene3BackDrop);
	item3->setScaleX(CCGetScaleX());
	item3->setScaleY(CCGetScaleY());
	item3->setPosition(ccp(itemContentWidth*2+offSetX * 1.2, itemY));
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsOpen31") || SceneManager::SharedSceneManager()->IsTestGameMode())
	//if ( true )
	{
		item3->setTag(1004);
		CCSprite* bg31 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg31->setPosition(ccp(item3->getContentSize().width/2, item3->getContentSize().height*0.8f/2));
		item3->addChild(bg31);
		CCSprite* bg32 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg32->setPosition(ccp(item3->getContentSize().width/2, item3->getContentSize().height*0.5f/2));
		item3->addChild(bg32);
		//CCSprite* bg33 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		//bg33->setPosition(ccp(item3->getContentSize().width/2, item3->getContentSize().height*0.2f/2));
		//item3->addChild(bg33);
		CCSprite* label31 = CCSprite::spriteWithFile(s_pPathBigStage_TotalScore);
		label31->setPosition(ccp(bg31->getContentSize().width/2, bg31->getContentSize().height*1.5/2));
		bg31->addChild(label31);
		//从userdefault.xml文件中读取第三大关的所有分数的总和;
		TotalScore=0, TotalStars = 0, totalPears = 0;
		for (int i=1; i <= 10; i++)
		{
			char string[16]={0};
			sprintf(string, "highestScore%d%d", 3,i);
			TotalScore+=CCUserDefault::sharedUserDefault()->getIntegerForKey(string);
			//从userdefault.xml文件中读取第三大关卡的所有星星数;
			char sStars[16]={0};
			sprintf(sStars, "stars%d%d", 3,i);
			TotalStars+=CCUserDefault::sharedUserDefault()->getIntegerForKey(sStars);
			//
			char sPearKey[16]={0};
			sprintf(sPearKey, "PearCount%d%d", 3, i);
			if ( CCUserDefault::sharedUserDefault()->getBoolForKey(sPearKey) )
				totalPears++;
		}
		sprintf(string1,"%d",TotalScore);
		//读取结束;	

		CCLabelAtlas* label32 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label32->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label32->setPosition(ccp(bg31->getContentSize().width/2, bg31->getContentSize().height*0.7/2));
		bg31->addChild(label32);

		//char string1[16]={0};
		sprintf(string1,"%d/30",TotalStars);
		CCLabelAtlas* label33 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label33->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label33->setPosition(ccp(bg32->getContentSize().width/2, bg32->getContentSize().height*0.7/2));
		bg32->addChild(label33);
		CCSprite* star3 = CCSprite::spriteWithFile(s_pPathBigStage_Star);
		star3->setPosition(ccp(bg32->getContentSize().width/2, bg32->getContentSize().height*1.5/2));
		bg32->addChild(star3);
		//
		//sprintf(string1, "%d/5", totalPears);
		//CCLabelAtlas* label34 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		//label34->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		//label34->setPosition(ccp(bg33->getContentSize().width/2, bg33->getContentSize().height*0.7/2));
		//bg33->addChild(label34);
		//CCSprite* fruit3 = CCSprite::spriteWithFile(s_pPear);
		//fruit3->setPosition(ccp(bg33->getContentSize().width/2, bg33->getContentSize().height*1.5/2));
		//bg33->addChild(fruit3);
	}
	else
	{
		CCSprite* suo3 = CCSprite::spriteWithFile(s_pPathBigStage_LevelLocked);
		suo3->setPosition(ccp(item3->getContentSize().width/2, item3->getContentSize().height*0.8f/2));
		item3->addChild(suo3);
	}

	/** 第四关 */
	CCMenuItemImage* item4 = CCMenuItemImage::itemFromNormalImage(s_pPathBigStage_Scene4BackDrop, s_pPathBigStage_Scene4BackDrop);
	item4->setScaleX(CCGetScaleX());
	item4->setScaleY(CCGetScaleY());
	item4->setPosition(ccp(itemContentWidth*3+offSetX * 1.3, itemY));
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsOpen41") || SceneManager::SharedSceneManager()->IsTestGameMode())
    //if(true)
	{
		item4->setTag(1005);
		CCSprite* bg41 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg41->setPosition(ccp(item4->getContentSize().width/2, item4->getContentSize().height*0.8f/2));
		item4->addChild(bg41);
		CCSprite* bg42 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg42->setPosition(ccp(item4->getContentSize().width/2, item4->getContentSize().height*0.5f/2));
		item4->addChild(bg42);
		//CCSprite* bg43 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		//bg43->setPosition(ccp(item4->getContentSize().width/2, item4->getContentSize().height*0.2f/2));
		//item4->addChild(bg43);
		CCSprite* label41 = CCSprite::spriteWithFile(s_pPathBigStage_TotalScore);
		label41->setPosition(ccp(bg41->getContentSize().width/2, bg41->getContentSize().height*1.5/2));
		bg41->addChild(label41);
		//从userdefault.xml文件中读取第四大关的所有分数的总和;
		TotalScore=0, TotalStars = 0, totalPears = 0;
		for (int i=1; i <= 10;i++)
		{
			char string[16]={0};
			sprintf(string, "highestScore%d%d", 4,i);
			TotalScore+=CCUserDefault::sharedUserDefault()->getIntegerForKey(string);
			//从userdefault.xml文件中读取第四大关卡的所有星星数;
			char sStars[16]={0};
			sprintf(sStars, "stars%d%d", 4,i);
			TotalStars+=CCUserDefault::sharedUserDefault()->getIntegerForKey(sStars);
			//
			char sPearKey[16]={0};
			sprintf(sPearKey, "PearCount%d%d", 4, i);
			if ( CCUserDefault::sharedUserDefault()->getBoolForKey(sPearKey) )
				totalPears++;
		}
		sprintf(string1,"%d",TotalScore);
		//读取结束;	

		CCLabelAtlas* label42 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label42->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label42->setPosition(ccp(bg41->getContentSize().width/2, bg41->getContentSize().height*0.7/2));
		bg41->addChild(label42);

		//char string1[16]={0};
		sprintf(string1,"%d/30",TotalStars);
		CCLabelAtlas* label43 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label43->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label43->setPosition(ccp(bg42->getContentSize().width/2, bg42->getContentSize().height*0.7/2));
		bg42->addChild(label43);
		CCSprite* star4 = CCSprite::spriteWithFile(s_pPathBigStage_Star);
		star4->setPosition(ccp(bg42->getContentSize().width/2, bg42->getContentSize().height*1.5/2));
		bg42->addChild(star4);
		//
		//sprintf(string1, "%d/5", totalPears);
		//CCLabelAtlas* label44 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		//label44->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		//label44->setPosition(ccp(bg43->getContentSize().width/2, bg43->getContentSize().height*0.7/2));
		//bg43->addChild(label44);
		//CCSprite* fruit4 = CCSprite::spriteWithFile(s_pPear);
		//fruit4->setPosition(ccp(bg43->getContentSize().width/2, bg43->getContentSize().height*1.5/2));
		//bg43->addChild(fruit4);
	}
	else
	{
		CCSprite* suo4 = CCSprite::spriteWithFile(s_pPathBigStage_LevelLocked);
		suo4->setPosition(ccp(item4->getContentSize().width/2, item4->getContentSize().height*0.8f/2));
		item4->addChild(suo4);
	}

	/** 第五关 */
	CCMenuItemImage* item5 = CCMenuItemImage::itemFromNormalImage(s_pPathBigStage_Scene5BackDrop, s_pPathBigStage_Scene5BackDrop);
	//item5->setScale(CCGetScaleX());
	item5->setScaleX(CCGetScaleX());
	item5->setScaleY(CCGetScaleY());
	item5->setPosition(ccp(itemContentWidth*4+offSetX * 1.4, itemY));
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsOpen51") || SceneManager::SharedSceneManager()->IsTestGameMode())
    //if(true)
	{
		item5->setTag(1006);
		CCSprite* bg51 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg51->setPosition(ccp(item5->getContentSize().width/2, item5->getContentSize().height*0.8f/2));
		item5->addChild(bg51);
		CCSprite* bg52 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		bg52->setPosition(ccp(item5->getContentSize().width/2, item5->getContentSize().height*0.5f/2));
		item5->addChild(bg52);
		//CCSprite* bg53 = CCSprite::spriteWithFile(s_pPathBigStage_BackDrop);
		//bg53->setPosition(ccp(item5->getContentSize().width/2, item5->getContentSize().height*0.2f/2));
		//item5->addChild(bg53);
		CCSprite* label51 = CCSprite::spriteWithFile(s_pPathBigStage_TotalScore);
		label51->setPosition(ccp(bg51->getContentSize().width/2, bg51->getContentSize().height*1.5/2));
		bg51->addChild(label51);
		//从userdefault.xml文件中读取第五大关的所有分数的总和;
		TotalScore=0, TotalStars = 0, totalPears = 0;
		for (int i=1; i <= 10; i++)
		{
			char string[16]={0};
			sprintf(string, "highestScore%d%d", 5,i);
			TotalScore+=CCUserDefault::sharedUserDefault()->getIntegerForKey(string);
			//从userdefault.xml文件中读取第五大关卡的所有星星数;
			char sStars[16]={0};
			sprintf(sStars, "stars%d%d", 5,i);
			TotalStars+=CCUserDefault::sharedUserDefault()->getIntegerForKey(sStars);
			//
			char sPearKey[16]={0};
			sprintf(sPearKey, "PearCount%d%d", 5, i);
			if ( CCUserDefault::sharedUserDefault()->getBoolForKey(sPearKey) )
				totalPears++;
		}
		sprintf(string1,"%d",TotalScore);
		//读取结束;	

		CCLabelAtlas* label52 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label52->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label52->setPosition(ccp(bg51->getContentSize().width/2, bg51->getContentSize().height*0.7/2));
		bg51->addChild(label52);

		//char string1[16]={0};
		sprintf(string1,"%d/30",TotalStars);
		CCLabelAtlas* label53 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		label53->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		label53->setPosition(ccp(bg52->getContentSize().width/2, bg52->getContentSize().height*0.7/2));
		bg52->addChild(label53);
		CCSprite* star5 = CCSprite::spriteWithFile(s_pPathBigStage_Star);
		star5->setPosition(ccp(bg52->getContentSize().width/2, bg52->getContentSize().height*1.5/2));
		bg52->addChild(star5);
		//
		//sprintf(string1, "%d/5", totalPears);
		//CCLabelAtlas* label54 = CCLabelAtlas::labelWithString(string1, s_pPathCount3, 15, 25, '/');
		//label54->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		//label54->setPosition(ccp(bg53->getContentSize().width/2, bg53->getContentSize().height*0.7/2));
		//bg53->addChild(label54);
		//CCSprite* fruit5 = CCSprite::spriteWithFile(s_pPear);
		//fruit5->setPosition(ccp(bg53->getContentSize().width/2, bg53->getContentSize().height*1.5/2));
		//bg53->addChild(fruit5);
	}
	else
	{
		CCSprite* suo5 = CCSprite::spriteWithFile(s_pPathBigStage_LevelLocked);
		suo5->setPosition(ccp(item5->getContentSize().width/2, item5->getContentSize().height*0.8f/2));
		item5->addChild(suo5);
	}
    
    MyCCMenu* myMenu = MyCCMenu::menuWithItems(item1, item2, item3, item4, item5, NULL);
    myMenu->SetDownUpHandle(this,
                            menu_selector(UISelectBigStage::BtnDownCallback),
                            menu_selector(UISelectBigStage::BtnUpInCallback),
                            menu_selector(UISelectBigStage::BtnUpOutCallback));

    CCArray* itemsArray = CCArray::array();
    itemsArray->addObject(myMenu);
	//itemsArray->addObject(myMenu2);
    
    CCScrollLayer* scroller = CCScrollLayer::nodeWithLayers(itemsArray, 0);
    scroller->setPosition(ccp(0, 0));
	//scroller->setDelegate(this);
	this->addChild(scroller, 2,2001);
}

void UISelectBigStage::BtnDownCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    if ( pBtn->getTag() == 1001 )
        pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.1f));
    else
        pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()*1.04f, CCGetScaleY()*1.04f));
    
    if ( pBtn->getTag() == 1001 )
    {
        //back
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathstart_panel);
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathStart_WaterfallAnim);
        SceneManager::SharedSceneManager()->JumpToStartPanel();
    }
	else if ( pBtn->getTag() == 1012 )
	{
		HideLeftRightBtn();//左;
		CCScrollLayer* scroller = (CCScrollLayer*)this->getChildByTag(2001);
		scroller->moveToPage(scroller->getCurrentScreen()-1);
	}
	else if ( pBtn->getTag() == 1013 )
	{
		HideLeftRightBtn();//右;
		CCScrollLayer* scroller = (CCScrollLayer*)this->getChildByTag(2001);
		scroller->moveToPage(scroller->getCurrentScreen()+1);
	}
}

void UISelectBigStage::scrollLayerScrollingStarted(CCScrollLayer* sender)
{
	HideLeftRightBtn();
}

void UISelectBigStage::scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page)
{
	if ( page > 0 )
	{
		//m_pLeftBtn->setPosition(ccp(m_pRightBtn->getContentSize().width*CCGetScaleX(),CCGetWinSize().height/2));
		m_pLeftBtn->setPosition(ccp(CCGetWinSize().width/3, m_pLeftBtn->getContentSize().height*CCGetScaleX()/2 -CCGetWinSize().width/68));
	}
	if ( page < sender->getPages()->count()-1 )
	{
		//m_pRightBtn->setPosition(ccp(CCGetWinSize().width-m_pRightBtn->getContentSize().width*CCGetScaleX(), CCGetWinSize().height/2));
		m_pRightBtn->setPosition(ccp(CCGetWinSize().width*2/3, m_pRightBtn->getContentSize().height*CCGetScaleX()/2 -CCGetWinSize().width/68));
	}
}

void UISelectBigStage::HideLeftRightBtn()
{
	m_pLeftBtn->setPosition(ccp(CCGetWinSize().width/3, -m_pLeftBtn->getContentSize().height*CCGetScaleX()/2));
	m_pRightBtn->setPosition(ccp(CCGetWinSize().width*2/3, -m_pRightBtn->getContentSize().height*CCGetScaleX()/2));
}

void UISelectBigStage::BtnUpInCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
    pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX(), CCGetScaleY()));
	
	if( pBtn->getTag()!=1012 && pBtn->getTag()!=1013 )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite* loading_Sprite = CCSprite::spriteWithFile(s_pPathLoading);
		loading_Sprite->setPosition(ccp(winSize.width/2,winSize.height*14/40));
		loading_Sprite->setScale(CCGetScaleX()*1.0f);
		this->addChild(loading_Sprite,3);

		loading_Sprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.1f),
			CCCallFunc::actionWithTarget(this, callfunc_selector(UISelectBigStage::JumpToSmallSelected)),
			CCScaleTo::actionWithDuration(1.0f, 0),
			NULL));
		pBtn_Down = pBtn;
	}
}

void UISelectBigStage::JumpToSmallSelected()
{
	if ( pBtn_Down->getTag() == 1002 )
	{
		SceneManager::SharedSceneManager()->JumpToSelectSmallStage(1);//传递大关卡ID=1;
	}
	if (pBtn_Down->getTag() == 1003)
	{
		SceneManager::SharedSceneManager()->JumpToSelectSmallStage(2);//传递大关卡ID=2;
	}
	if (pBtn_Down->getTag() == 1004)
	{
		SceneManager::SharedSceneManager()->JumpToSelectSmallStage(3);//传递大关卡ID=3;
	}
	if (pBtn_Down->getTag() == 1005)
	{
		SceneManager::SharedSceneManager()->JumpToSelectSmallStage(4);//传递大关卡ID=4;
	}
	if (pBtn_Down->getTag() == 1006)
	{
		SceneManager::SharedSceneManager()->JumpToSelectSmallStage(5);//传递大关卡ID=5;
	}
	if ( pBtn_Down->getTag() == 1007 )
	{
		SceneManager::SharedSceneManager()->JumpToSelectSmallStage(6);//传递大关卡ID=6;
	}
}

void UISelectBigStage::BtnUpOutCallback(CCObject* pSender)
{
    CCMenuItemImage* pBtn = (CCMenuItemImage*)pSender;
    pBtn->stopAllActions();
	if ( pBtn->getTag() == 1001 )
		pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX()));
	else
		pBtn->runAction(CCScaleTo::actionWithDuration(0.1f, CCGetScaleX(), CCGetScaleY()));
}

void UISelectBigStage::keyBackClicked()
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathstart_panel);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathStart_WaterfallAnim);
	SceneManager::SharedSceneManager()->JumpToStartPanel();
}





