//
//  LevelBase.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-3;
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "LevelBase.h"
#include "SimpleAudioEngine.h"
#include "GameResources.h"
#include "Pig.h"
#include "SceneManager.h"
#include "UIWinFailPanel.h"
#include "Props.h"
#include "Level.h"


int CurSmallLevelID;
int CurBigID;
//第一三个阶段分值;
int OneStarScore;
int TwoStarScore;
int ThreeStarScore;

LevelBaseEx::LevelBaseEx(CCLayer *layer)
: m_pBg(NULL)
, m_pCurPigWithNoBody(NULL)
, m_pWorld(NULL)
, m_pSling(NULL)
//, m_pDebugDraw(NULL)
, m_vPigs(NULL)
, m_vPigs2(NULL)
, m_LockEnemys(NULL)
, m_bPigTouched(false)
, m_vFlyPathPoints(NULL)
, m_pContactListener(NULL)
, disCount(0)
, pigZero(false)
, isLevelFinish(false)
, m_fSlingRopeWidth(MaxSlingRopeWidth)
, b_update(true)
, PigNumber(0)
, newrecord(false)
, curSlingShotDir(ESlingShotMoveDir_Mid)
, bCanShotPig(true)
, m_operateGuideSprite(NULL)
{
	UILayer=layer;
    InitScene();
}

LevelBaseEx::~LevelBaseEx()
{
    CC_SAFE_RELEASE(m_vPigs);
	 CC_SAFE_RELEASE(m_vPigs2);
    CC_SAFE_RELEASE(m_vFlyPathPoints);
	CC_SAFE_RELEASE(m_LockEnemys);
    delete m_pContactListener;
    m_pContactListener = NULL;
}

void LevelBaseEx::Run()
{
    PositionNextPig();
    this->schedule(schedule_selector(LevelBaseEx::Update));
}

void LevelBaseEx::SetBackGround(CCTexture2D* m_pBgTexture)
{
	m_pBg = CCSprite::spriteWithTexture(m_pBgTexture);
	m_pBg->setAnchorPoint(CCPointZero);
	m_pBg->setScale(CCGetScaleX());
	m_pBg->setPosition(CCPointZero);
	this->addChild(m_pBg, -1);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);
	groundBody->SetUserData(NULL);
	b2PolygonShape groundBox;
	b2FixtureDef fixtureDef;
	fixtureDef.friction = 1.0f;
	// bottom
	groundBox.SetAsBox(m_pBg->getContentSize().width*CCGetScaleX()/2/PTM_RATIO, 0,
		b2Vec2(m_pBg->getContentSize().width*CCGetScaleX()/2/PTM_RATIO,135*CCGetScaleX()/PTM_RATIO), 0);
	fixtureDef.shape = &groundBox;
	groundBody->CreateFixture(&fixtureDef);
	// top
	/*
	groundBox.SetAsBox(CCGetWinSize().width/2/PTM_RATIO, 0,
		b2Vec2(CCGetWinSize().width/2/PTM_RATIO, CCGetWinSize().height/PTM_RATIO), 0);
	groundBody->CreateFixture(&groundBox, 0);
	*/
	SceneManager::SharedSceneManager()->SetGroundBody(groundBody);

}

void LevelBaseEx::AddPig(EPigType pigType, const char* image, CCPoint pos)
{
    PigNumber++;
    PigWithNoBody* pPig = PigWithNoBody::spriteWithFile(image, pigType);
    pPig->setScale(CCGetScaleX());
    pPig->setPosition(pos);
    this->addChild(pPig);
    
    m_vPigs->addObject(pPig);
	m_vPigs2->addObject(pPig);
}


void LevelBaseEx::AddProps(const char* image, CCPoint pos, std::vector<float> vx, std::vector<float> vy, int propsType, float rot, bool bHasGravity, int z,int tag,int to,int to2,const char* state)
{
    if ( !bHasGravity )
    {
        char imageFullName[50] = {0};
        sprintf(imageFullName, "%s.png", image);
		CCSprite *pSprite = NULL;
		if ( SceneManager::SharedSceneManager()->GetCurLevel()->GetBigLevelID() <= 6/* &&  SceneManager::SharedSceneManager()->GetCurLevel()->GetLevelID() < 4 */)
			pSprite = CCSprite::spriteWithSpriteFrameName(imageFullName);
		else
			pSprite = CCSprite::spriteWithFile(imageFullName);
        pSprite->setScale(CCGetScaleX());
        pSprite->setPosition(pos);
        this->addChild(pSprite, z);

		//if(SceneManager::SharedSceneManager()->GetGameVersion() != EGmaeVersion_JX)
		//{
		//	if ( propsType == -1000 ) // left sling shot
		//	{
		//		pSprite->initWithFile("SlingShot/SlingShot_L1.png");
		//		pLeftSlingShot = pSprite;
		//	}
		//	else if ( propsType == -1001 ) //right sling shot
		//	{
		//		pSprite->initWithFile("SlingShot/SlingShot_R1.png");
		//		pRightSlingShot = pSprite;
		//	}
		//}
		//else
		//{
			if ( propsType == -1000 ) // 大炮;
			{
				pSprite->spriteWithSpriteFrameName("SlingShot_L.png");
				pLeftSlingShot = pSprite;
			}
			else if ( propsType == -1001 ) //大炮底座;
			{
				pSprite->spriteWithSpriteFrameName("SlingShot_R.png");
				pRightSlingShot = pSprite;
			}
		//}

    }
    else
    {
        Props* pProps = Props::CreateProps(m_pWorld, image, this, s_pPathDispearFog, image, pos, rot,vx,vy,propsType,state,tag,to,to2);
        if ( propsType == 1 )//猪;
            pProps->SetMaxLife(200000.0f);
        else if ( propsType == 2)//草;
        {
            pProps->SetMaxLife(1.5f);
            pProps->SetPropsType(EPropsType_Grass);
			//pProps->GetBody()->GetFixtureList()->SetSensor(true);
			//pProps->GetBody()->SetType(b2_kinematicBody);
        }
        else if ( propsType == 3 || propsType == 77 || propsType == 603)//普通木块;
        {
            pProps->SetMaxLife(1.5f);
            pProps->SetPropsType(EPropsType_Wood);
        }
        else if(propsType==6)//花;
        {
            pProps->SetMaxLife(1.5f);
            pProps->SetPropsType(EPropsType_Flower);
			//pProps->GetBody()->GetFixtureList()->SetSensor(true);
			//pProps->GetBody()->SetType(b2_kinematicBody); //物体运动但不受力;
        }
		else if(propsType==7)//大的发射台;
        {
            pProps->SetPropsType(EPropsType_Floor);
            pProps->SetMaxLife(200000.0f);
			pProps->GetBody()->SetType(b2_staticBody); //物体模拟时不会运动;
        }
		else if(propsType == 100 || propsType == 101 || propsType == 102)  //球;
		{
			pProps->SetPropsType(EPropsType_Ball);
			pProps->SetMaxLife(200000.0f);
		}
		else if(propsType == 103)  //气球;
		{
			pProps->SetMaxLife(1.0f);
			pProps->SetPropsType(EPropsType_Balloon);
			//pProps->GetBody()->SetType(b2_kinematicBody);
		}
		else if(propsType == 106) //笼子;
		{
			pProps->SetMaxLife(1.5f);
			pProps->SetPropsType(EPropsType_Cage);
		}
		else if(propsType == 104 || propsType == 105)  //龙舟;
		{
			pProps->SetMaxLife(200000.0f);
			pProps->SetPropsType(EPropsType_Boat);
			pProps->GetBody()->SetType(b2_kinematicBody);
		}
		else if (propsType == 11)//纸箱;
		{
			pProps->SetMaxLife(1.0f);
			pProps->SetPropsType(EPropsType_PaperBox);
		}
		else if (propsType == 13)//木箱;
		{
			pProps->SetMaxLife(3.5f);
			pProps->SetPropsType(EPropsType_WoodBox);
		}
		else if(propsType == 15 || propsType == 615)//玻璃类型;
		{
			pProps->SetMaxLife(2.0f);
			pProps->SetPropsType(EPropsType_Glass);
		}
		else if (propsType == 33 || propsType == 633)//石头;
		{
			pProps->SetMaxLife(4.0f);   //2.0f;
			pProps->SetPropsType(EPropsType_Stone);
		}
		else if (propsType == 50 || propsType == 602)//水果;
		{
			pProps->SetMaxLife(1.5f);
			pProps->SetPropsType(EPropsType_Fruit);
		}
		else if ( propsType == 51 ) //刺梨;
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_SP01);
		}
		else if ( propsType == 52 )
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_SP02);
		}
		else if ( propsType == 53 )
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_SP03);
		}
		else if ( propsType == 54 )
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_SP04);
		}
		else if ( propsType == 55 )
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_SP05);
		}
		else if (propsType == 21)//敌方角色A;
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_EnemyA);

			m_LockEnemys->addObject(pProps);
			float type1 = CCRANDOM_0_1() * 5;
			while(type1 <= 1)
				type1 = CCRANDOM_0_1() * 5;
			CCAnimation* animation = CCAnimation::animation();
			char str[64] = {0};  
			for(int i = 0; i <= 23; i++)   
			{  
				sprintf(str, "%s_%d.png",s_pPathBirds_BirdAAnim, i);  
				animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
			}  
			CCAnimate *animate = CCAnimate::actionWithDuration(type1, animation, false);
				pProps->GetSprite()->runAction(CCRepeatForever::actionWithAction(animate));
		}
		else if (propsType == 22)//敌方角色B;
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_EnemyB);
			m_LockEnemys->addObject(pProps);
			float type1 = CCRANDOM_0_1() * 10;
			while(type1 <= 1)
				type1 = CCRANDOM_0_1() * 5;
			CCAnimation* animation = CCAnimation::animation();
			char str[64] = {0};  
			for(int i = 0; i <= 26; i++)   
			{  
				sprintf(str, "%s_%d.png",s_pPathBirds_BirdBAnim, i);   
				animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
			}  
			CCAnimate *animate = CCAnimate::actionWithDuration(type1, animation, false);
				pProps->GetSprite()->runAction(CCRepeatForever::actionWithAction(animate));
		}
		else if (propsType == 23)//敌方角色C;
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_EnemyC);

			m_LockEnemys->addObject(pProps);

			float type1 = CCRANDOM_0_1() * 10;
			while(type1 <= 1)
				type1 = CCRANDOM_0_1() * 5;
			CCAnimation* animation = CCAnimation::animation();
			char str[64] = {0};  
			for(int i = 0; i <= 15; i++)   
			{  
				sprintf(str, "%s_%d.png",s_pPathBirds_BirdCAnim, i);  
				animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
			}  
			CCAnimate *animate = CCAnimate::actionWithDuration(type1, animation, false);  
			pProps->GetSprite()->runAction(CCRepeatForever::actionWithAction(animate));
		}
		else if (propsType == 24)//敌方角色D;
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_EnemyD);

			m_LockEnemys->addObject(pProps);

			float type1 = CCRANDOM_0_1() * 10;
			while(type1 <= 1)
				type1 = CCRANDOM_0_1() * 5;
			CCAnimation* animation = CCAnimation::animation();
			char str[64] = {0};  
			for(int i = 0; i <= 7; i++)   
			{  
				sprintf(str, "%s_%d.png",s_pPathBirds_BirdDAnim, i);  
				animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
			}  
			CCAnimate *animate = CCAnimate::actionWithDuration(type1, animation, false);  
			pProps->GetSprite()->runAction(CCRepeatForever::actionWithAction(animate));
		}
		else if (propsType == 25)//敌方角色E;
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_EnemyE);

			m_LockEnemys->addObject(pProps);

			float type1 = CCRANDOM_0_1() * 10;
			while(type1 <= 1)
				type1 = CCRANDOM_0_1() * 5;
			CCAnimation* animation = CCAnimation::animation();
			char str[64] = {0};  
			for(int i = 0; i <= 13; i++)   
			{  
				sprintf(str, "%s_%d.png",s_pPathBirds_BirdEAnim, i);  
				animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
			}  
			CCAnimate *animate = CCAnimate::actionWithDuration(type1, animation, false);  
			pProps->GetSprite()->runAction(CCRepeatForever::actionWithAction(animate));
		}
		else if (propsType == 26)//敌方角色F;
		{
			pProps->SetMaxLife(0.0f);
			pProps->SetPropsType(EPropsType_EnemyF);

			m_LockEnemys->addObject(pProps);

			float type1 = CCRANDOM_0_1() * 10;
			while(type1 <= 1)
				type1 = CCRANDOM_0_1() * 5;
			CCAnimation* animation = CCAnimation::animation();
			char str[64] = {0};  
			for(int i = 0; i <= 15; i++)   
			{  
				sprintf(str, "%s_%d.png",s_pPathBirds_BirdFAnim, i);  
				animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
			}  
			CCAnimate *animate = CCAnimate::actionWithDuration(type1, animation, false);  
			pProps->GetSprite()->runAction(CCRepeatForever::actionWithAction(animate));
		}
		else if (propsType == 200)//链条，花的类型，都是防止产生分裂的效果;
		{
			pProps->SetMaxLife(1.0f);
			pProps->SetPropsType(EPropsType_Flower);
        }
        this->addChild(pProps);
    }
}

void LevelBaseEx::LevelIsWin()
{

	if(!isLevelFinish)
	{
		if(m_LockEnemys->count() <= 0 )
		{
			m_bPigTouched = false;

			if(!pigZero)		//剩余小猪;
            {
				this->schedule(schedule_selector(LevelBaseEx::CalculatePigScore),2.0);  //播放剩余鸟的得分;
			    this->schedule(schedule_selector(LevelBaseEx::GameWin),4.0);      //播放胜利画面;
			}
			else				//最后一只小猪打掉笼子;
			{
				this->schedule(schedule_selector(LevelBaseEx::GameWin),2.0);      //播放胜利画面;
			}
			isLevelFinish = true;
		}

	}
}
void LevelBaseEx::LevelIsLose()
{
	if(!isLevelFinish)
	{
		this->schedule(schedule_selector(LevelBaseEx::GameLose));
		isLevelFinish = true;
	}
}

void LevelBaseEx::GameLose(ccTime delta)
{
	if ( SceneManager::SharedSceneManager()->GetPauseState() )
		return;

	this->unschedule(schedule_selector(LevelBaseEx::GameLose));
	UILevelFinish(false);
}

void LevelBaseEx::UILevelFinish(bool win)
{
	//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
	//{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//}
	if(win)
	{
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			if(CurBigID == 1)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel1_Win);
			}
			else if(CurBigID == 2)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel2_Win);
			}
			else if(CurBigID == 3)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel3_Win);
			}
			else if(CurBigID == 4)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel4_Win);
			}
			else if(CurBigID == 5)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel5_Win);
			}
		}
        int star;
        b_update=false;
        if (m_iTotalScore>=OneStarScore && m_iTotalScore<TwoStarScore)
        {
            star = 1;
        }
        else if (m_iTotalScore>=TwoStarScore && m_iTotalScore<ThreeStarScore)
        {
            star = 2;
        }
        else if (m_iTotalScore>=ThreeStarScore)
        {
            star = 3;
        }
		SceneManager::SharedSceneManager()->AddBattleResultPanel(m_LevelBase, win, 7,star,m_iTotalScore,newrecord);
		//if(CurBigID == 5 && CurSmallLevelID == 10)
		//{
		//	if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
		//	{
		//		this->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(5.0f),
		//			CCCallFunc::actionWithTarget(this,callfunc_selector(LevelBaseEx::ShowEndStory)),
		//			NULL));
		//	}
		//}
     
	}
	else
	{
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			if(CurBigID == 1)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel1_Lose);
			}
			else if(CurBigID == 2)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel2_Lose);
			}
			else if(CurBigID == 3)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel3_Lose);
			}
			else if(CurBigID == 4)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel4_Lose);
			}
			else if(CurBigID == 5)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel5_Lose);
			}
		}
        b_update=false;
		this->runAction( CCSequence::actions(CCDelayTime::actionWithDuration(1.0f),
			CCCallFunc::actionWithTarget(this,callfunc_selector(LevelBaseEx::ActionDisplayFailPanel)),
			NULL)); 
	}
}

//void LevelBaseEx::ShowEndStory()
//{
//	SceneManager::SharedSceneManager()->JumpToStory(6);
//}

void LevelBaseEx::ActionDisplayFailPanel()
{
	SceneManager::SharedSceneManager()->AddBattleResultPanel(m_LevelBase, false, 7);
}

void LevelBaseEx::SetPigShotPos(CCPoint pos)
{ 
    m_pigShotPos = pos;
}

void LevelBaseEx::SetSlingRopePoints(CCPoint posLeft, CCPoint posRight)
{
    m_vSlingPoints.push_back(posLeft);
    m_vSlingPoints.push_back(posRight);
    CCPoint posMiddle = CCPointMake((posLeft.x+posRight.x)/2, (posLeft.y+posRight.y)/2);
    m_vSlingPoints.push_back(posMiddle);
}

void LevelBaseEx::InitScene()
{
    m_vPigs = CCArray::array();
    m_vPigs->retain();
	m_vPigs2 = CCArray::array();
	m_vPigs2->retain();
    m_vFlyPathPoints = CCArray::array();
    m_vFlyPathPoints->retain();
	m_LockEnemys = CCArray::array();
	m_LockEnemys->retain();
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
    bool doSleep = true;
    m_pWorld = new b2World(gravity);
    m_pWorld->SetAllowSleeping(doSleep);
    //m_pDebugDraw = new GLESDebugDraw(PTM_RATIO);
    //m_pWorld->SetDebugDraw(m_pDebugDraw);
    m_pContactListener = new GameContactListener();
    m_pWorld->SetContactListener(m_pContactListener);
    
    //uint32 flags = 0;
    //flags += b2Draw::e_shapeBit;
    //flags += b2Draw::e_centerOfMassBit;
    //m_pDebugDraw->SetFlags(flags);

	m_iHighestScores = 0;
	m_iHighestCurScore = 0;
	m_iCurScore = 0;
	m_iTotalScore = 0;

    int iHeight = CCGetWinSize().height;

	//获取当前关卡的最高得分记录;
	char string[16] = {0};
	sprintf(string, "highestScore%d%d", CurBigID,CurSmallLevelID);
	int recordScore=0;
	recordScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(string);
	sprintf(string,"%6d",recordScore);

	if ( recordScore > 0 )
	{
		//CCLabelTTF* label1 = CCLabelTTF::labelWithString("HIGHEST SCORE", "Marker Felt", 18);
		CCSprite* label1 = CCSprite::spriteWithFile(s_pPathScoreUI_HighScore);
		label1->setScale(CCGetScaleX());
		label1->setAnchorPoint(CCPointMake(1, 1));
		label1->setPosition(ccp(CCGetWinSize().width, iHeight));
		UILayer->addChild(label1, 2);

		iHeight -= label1->getContentSize().height*CCGetScaleX();
		m_iHighestScores = recordScore;
		m_iHighestCurScore= recordScore;

		m_pHighestScoreLabe = CCLabelAtlas::labelWithString(string, s_pPathCount1, 30, 50, '.');
		m_pHighestScoreLabe->setScale(CCGetScaleX());
		m_pHighestScoreLabe->setAnchorPoint(CCPointMake(1, 1));
		m_pHighestScoreLabe->setPosition(ccp(CCGetWinSize().width,iHeight));
		UILayer->addChild(m_pHighestScoreLabe, 2);

		iHeight-=m_pHighestScoreLabe->getContentSize().height*CCGetScaleX();
	}

    //CCLabelTTF* label2 = CCLabelTTF::labelWithString("SCORE", "Marker Felt", 18);
	CCSprite* label2 = CCSprite::spriteWithFile(s_pPathScoreUI_Score);
	label2->setScale(CCGetScaleX());
    label2->setAnchorPoint(CCPointMake(1, 1));
    label2->setPosition(ccp(CCGetWinSize().width,iHeight));
    UILayer->addChild(label2, 2);

    iHeight-=label2->getContentSize().height*CCGetScaleX();

    m_pCurScoreLabel = CCLabelAtlas::labelWithString("0", s_pPathCount1, 30, 50, '.');
    m_pCurScoreLabel->setScale(CCGetScaleX());
    m_pCurScoreLabel->setAnchorPoint(CCPointMake(1, 1));
    m_pCurScoreLabel->setPosition(ccp(CCGetWinSize().width,iHeight));
    UILayer->addChild(m_pCurScoreLabel, 2);

	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		if(CurBigID == 1)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathLevel1_BackGround,true);
			if(CurSmallLevelID == 1)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel1_Begin);
			}	
		}
		else if(CurBigID == 2)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathLevel2_BackGround,true);
		}
		else if(CurBigID == 3)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathLevel3_BackGround,true);
			if(CurSmallLevelID == 1)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathLevel3_Begin);
			}
		}
		else if(CurBigID == 4)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathLevel4_BackGround,true);
		}
		else if(CurBigID == 5)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_pPathLevel5_BackGround,true);
		}
	}
}

void LevelBaseEx::Update(ccTime delta)
{
    if(b_update)
    {

		if (!SceneManager::SharedSceneManager()->GetPauseState())//判断是否处于暂停状态;
		{
			m_pWorld->Step(1/60.0f, 10, 10);
		}
        this->schedule(schedule_selector(LevelBaseEx::CountScore));

         if(m_iTotalScore>m_iHighestScores)
        {
             m_iHighestScores=m_iTotalScore;
        }
        b2Body* curBody = m_pWorld->GetBodyList();
        b2Body* nextBody = NULL;
         while ( curBody != NULL )
        {
             nextBody = curBody->GetNext();

		     b2Vec2 Cur_Vec=curBody->GetPosition();
			 SceneManager::SharedSceneManager()->SetPropsDestroyPosition(Cur_Vec);
        
             NodeBase* pNode = (NodeBase*)curBody->GetUserData();
		    if ( pNode != NULL && pNode->GetSprite() != NULL )
		    {
				if(SceneManager::SharedSceneManager()->GetZero() && m_LockEnemys->count() == 0)   //当地上的小猪为0并且敌人为0时,判断是否为赢;
					LevelIsWin();

			    int score = pNode->UpdateLogic();//每个木块碰撞的得分;
				if ( (pNode->GetPropsType() == EPropsType_SP01 ||
					pNode->GetPropsType() == EPropsType_SP02 ||
					pNode->GetPropsType() == EPropsType_SP03 ||
					pNode->GetPropsType() == EPropsType_SP04 ||
					pNode->GetPropsType() == EPropsType_SP05 ) && score == 5000 )
				{
					bool bNeedShowPearPanel;
					std::string sKey = "";
					if (pNode->GetPropsType() == EPropsType_SP01)
						sKey = "NeedShowPearPanel";
					else if (pNode->GetPropsType() == EPropsType_SP02)
						sKey = "NeedShowMapPanel";
					else if (pNode->GetPropsType() == EPropsType_SP03)
						sKey = "NeedShowPaperPanel";
					else if (pNode->GetPropsType() == EPropsType_SP04)
						sKey = "NeedShowRapePanel";
					else if (pNode->GetPropsType() == EPropsType_SP05)
						sKey = "NeedShowRicePanel";
					bNeedShowPearPanel = CCUserDefault::sharedUserDefault()->getBoolForKey(sKey.c_str(), true);
					if ( bNeedShowPearPanel )
					{
						CCUserDefault::sharedUserDefault()->setBoolForKey(sKey.c_str(), false);
						CCUserDefault::sharedUserDefault()->flush();
						//第一次显示刺梨的介绍;
						SceneManager::SharedSceneManager()->AddPearIntroPanel(m_LevelBase, this->convertToWorldSpace(pNode->GetSprite()->getPosition()), pNode->GetPropsType(), 7);
					}
				}
				
				if ( pNode->GetPropsType() == EPropsType_Pig && !curBody->IsAwake() )
				{
					Pig* pPig = (Pig*)pNode;
					if ( pPig->GetState() == EPigState_Fly )
						pPig->SetState(EPigState_EndFly);
				}

                m_iTotalScore+=score;

			    pNode->GetSprite()->setPosition(ccp(curBody->GetPosition().x * PTM_RATIO, curBody->GetPosition().y * PTM_RATIO));  //根据物理引擎里物体的位置来更新图片资源的位置;
			    pNode->GetSprite()->setRotation(-1 * CC_RADIANS_TO_DEGREES(curBody->GetAngle()));   //根据物理引擎里物体的角度来更新图片资源的角度;

				if (score>0)
				{
					ScoreAnim(curBody->GetLinearVelocity(),Cur_Vec,score);
				}
		    }
        
             curBody = nextBody;
         }
    }
}

void LevelBaseEx::CountScore(ccTime delta)
{
	m_iCurScore +=1000;
	if ( m_iCurScore >= m_iTotalScore )
	{
		m_iCurScore = m_iTotalScore;
		this->unschedule(schedule_selector(LevelBaseEx::CountScore));
	}

	char string[8] = {0};
	sprintf(string, "%6d", m_iCurScore);
	m_pCurScoreLabel->setString(string);
}

void LevelBaseEx::ScoreAnim(b2Vec2 force,b2Vec2 pos,int score)
{
	b_posX = pos.x*PTM_RATIO;
	b_posY = pos.y*PTM_RATIO;
	if (score==3000)
	{
		CCSprite *scorePic;
		CCActionInterval*  actionBy = CCScaleBy::actionWithDuration(0.5 ,  0.0);
		CCActionInterval*  actionByBack = actionBy->reverse();
		scorePic=CCSprite::spriteWithFile(s_pPathCount3000);
		scorePic->setScale(CCGetScaleX());
		scorePic->setPosition(ccp(b_posX,b_posY+20));

		this->addChild(scorePic);

		scorePic->runAction( CCSequence::actions(CCDelayTime::actionWithDuration(0.5f),actionBy,NULL));     
	}
	else if (score==5000)
	{
		CCSprite *scorePic;
		CCActionInterval*  actionBy = CCScaleBy::actionWithDuration(0.5 ,  0.0);
		CCActionInterval*  actionByBack = actionBy->reverse();
		scorePic=CCSprite::spriteWithFile(s_pPathCount5000);
		scorePic->setScale(CCGetScaleX());
		scorePic->setPosition(ccp(b_posX,b_posY+20));

		this->addChild(scorePic);

		scorePic->runAction( CCSequence::actions(CCDelayTime::actionWithDuration(0.5f),actionBy,NULL));     
	}
	else
	{
        b_scores=score;
		this->schedule(schedule_selector(LevelBaseEx::ScoreShow),0.1);
	}
}

void LevelBaseEx::ScoreShow(ccTime delta)
{
    this->unschedule(schedule_selector(LevelBaseEx::ScoreShow));


    char buf[20];
    sprintf(buf,"%d",b_scores);
    CCActionInterval*  actionBy = CCScaleBy::actionWithDuration(0.5 ,  0.0);
    CCLabelAtlas* m_pHighestScore;
    m_pHighestScore = CCLabelAtlas::labelWithString(buf, s_pPathCount1, 30, 50, '.');
    m_pHighestScore->setAnchorPoint(CCPointMake(1, 1));
    m_pHighestScore->setScale(CCGetScaleX());
    m_pHighestScore->setPosition(ccp(b_posX, b_posY));
    this->addChild(m_pHighestScore);
    m_pHighestScore->runAction( CCSequence::actions(actionBy,NULL)); 
}

void LevelBaseEx::draw()
{
    //CCNode *node=GetLevelParent()->getChildByTag(1000);

	//glDisable(GL_TEXTURE_2D);
	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//m_pWorld->DrawDebugData();

	//glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 //   if(SceneManager::SharedSceneManager()->GetGameVersion() != EGmaeVersion_JX )
	//{
	//	if ( m_vSlingPoints.size() >= 3 )
	//	{
	//		glLineWidth(m_fSlingRopeWidth);
	//		glColor4ub(57, 33, 13, 255);
	//		ccDrawLine(m_vSlingPoints[0], m_vSlingPoints[2]);
	//		ccDrawLine(m_vSlingPoints[1], m_vSlingPoints[2]);

	//		glLineWidth(1.0f);
	//	}
	//}

}

CCPoint LevelBaseEx::GetSlingScreenPos()
{
    return m_pSling->getParent()->convertToWorldSpace(m_pSling->getPosition());
}

void LevelBaseEx::ShowOperateGuideAnim(bool bHide)
{
	if (SceneManager::SharedSceneManager()->CurBigLevelID != 1 ||
		SceneManager::SharedSceneManager()->m_iCurLevel != 1)
		return;

	if (bHide)
	{
		m_operateGuideSprite = CCSprite::spriteWithFile(s_pPathOperateGuide_Arrow);
		m_operateGuideSprite->setPosition(CCPointMake(m_pigShotPos.x + 2*m_operateGuideSprite->getContentSize().width*CCGetScaleX(),
			m_pigShotPos.y));
		m_operateGuideSprite->setScale(CCGetScaleX());

		CCAnimation* animation = CCAnimation::animation();
		char frameName[50] = {0};
		for (int i = 1; i <= 4; i++)
		{
			sprintf(frameName, "%s%d.png",s_pPathOperateGuide_ArrowAnim, i);
			animation->addFrameWithFileName(frameName);
		}
		CCAnimate *animate = CCAnimate::actionWithDuration(0.6f, animation, false);
		m_operateGuideSprite->runAction(CCRepeatForever::actionWithAction(animate));  

		this->addChild(m_operateGuideSprite,3);
	}
	else
	{
		if (m_operateGuideSprite != NULL)
		{
			m_operateGuideSprite->removeFromParentAndCleanup(true);
			m_operateGuideSprite  = NULL;
		}
	}
}

void LevelBaseEx::PositionNextPig()
{
	if ( m_vPigs->count() <= 0  )         
	{
		pigZero = true;
		return;
	}
	pigZero = false;

    m_pCurPigWithNoBody = (PigWithNoBody*)m_vPigs->lastObject();
    m_pCurPigWithNoBody->SetState(EPigState_Jumping);
    m_vPigs->removeLastObject();
	//CCPoint pos = pLeftSlingShot->convertToWorldSpace(m_pCurPigWithNoBody->getPosition());

	//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
	//{
		m_pCurPigWithNoBody->removeFromParentAndCleanup(false);
		m_pCurPigWithNoBody->setScale(1);
		pLeftSlingShot->addChild(m_pCurPigWithNoBody,-1);
		CCPoint Shotpos = ccp(pLeftSlingShot->getContentSize().width,pLeftSlingShot->getContentSize().height/2 + 20);
		//CCPoint pos = pLeftSlingShot->convertToNodeSpace(m_pCurPigWithNoBody->getPosition());
		m_pCurPigWithNoBody->setPosition(Shotpos);
		m_pCurPigWithNoBody->stopAllActions();
		m_pCurPigWithNoBody->runAction(CCRotateTo::actionWithDuration(0.1f, 0));
		m_pCurPigWithNoBody->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0.8f, Shotpos),
			CCCallFunc::actionWithTarget(this, callfunc_selector(LevelBaseEx::SetReadyShotState)),
			NULL));
	//}
	//else
	//{
	//	m_pCurPigWithNoBody->stopAllActions();
	//	m_pCurPigWithNoBody->runAction(CCRotateTo::actionWithDuration(0.1f, 0));
	//	m_pCurPigWithNoBody->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0.8f, m_pigShotPos),
	//		CCCallFunc::actionWithTarget(this, callfunc_selector(LevelBaseEx::SetReadyShotState)),
	//		NULL));
	//}
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		//小猪跳到弹弓上的音效;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_jump, false);
	}
	//m_pCurPigWithNoBody->setPosition(ccp(pLeftSlingShot->getContentSize().width*CCGetScaleX()/2,pLeftSlingShot->getContentSize().height*CCGetScaleX()/2));
}

void LevelBaseEx::SetReadyShotState()
{
    if ( m_pCurPigWithNoBody != NULL )
        m_pCurPigWithNoBody->SetState(EPigState_BeginFly);
}

CCRect LevelBaseEx::rectInPixels( CCSprite *pSprite )
{
	CCSize s = pSprite->getContentSize();
    s = CCSizeMake(s.width*CCGetScaleX(), s.height*CCGetScaleX());
	return CCRectMake(pSprite->getPosition().x-s.width*2.0f, pSprite->getPosition().y-s.height*2.0f, s.width*4, s.height*4);
	//return CCRectMake(pSprite->getPosition().x-s.width*0.5f, pSprite->getPosition().y-s.height*0.5f, s.width, s.height);
}

bool LevelBaseEx::containsTouchLocation( CCPoint touchPos )
{
    if ( m_pCurPigWithNoBody != NULL && m_pCurPigWithNoBody->GetState() == EPigState_BeginFly )
    {
        CCRect r = this->rectInPixels(m_pCurPigWithNoBody);
        return CCRect::CCRectContainsPoint(r, touchPos);
    }
    else
    {
        return false;
    }
}

bool LevelBaseEx::containsAngleLocation( CCPoint touchPos )
{
	if ( m_pCurPigWithNoBody != NULL && m_pCurPigWithNoBody->GetState() == EPigState_BeginFly )
	{
		CCRect r = CCRectMake(m_pigShotPos.x + 40.0f, m_pigShotPos.y - 50.0f, 100, 200);
		return CCRect::CCRectContainsPoint(r, touchPos);
	}
	else
	{
		return false;
	}
}

bool LevelBaseEx::containsRecoverLocation( CCPoint touchPos)
{
	if(m_pCurPigWithNoBody != NULL && m_pCurPigWithNoBody->GetState() == EPigState_BeginFly)
	{
		CCRect RecoverRect = CCRectMake(m_pigShotPos.x - 7.5f, m_pigShotPos.y - 7.5f, 15, 15);
		return CCRect::CCRectContainsPoint(RecoverRect,touchPos);
	}
	else
	{
		return false;
	}
}

bool LevelBaseEx::IsCurPigTouched()
{
    return m_bPigTouched;
}

bool LevelBaseEx::IsGunCtrlTouched()
{
	return m_bGunCtrlTouched;
}

void LevelBaseEx::TouchBegin(CCPoint touchPos)
{
	if(m_LockEnemys->count() > 0)
	{
		Pig* pPig = (Pig*)this->getChildByTag(KCurPigTag);
		if ( pPig != NULL )
		{
            if(pPig->GetPigType() != EPigType_Normal && pPig->GetState() == EPigState_Fly && pPig->GetPigType() != EPigType_Bomb)   //点击 大云朵 和动画;
            {
				bCanShotPig = false;
				char imageFullName[50] = {0};
				sprintf(imageFullName, "%s%d.png", s_pPathDispearFog,1);
                 CCSprite *bigFog = CCSprite::spriteWithSpriteFrameName(imageFullName);
                 bigFog->setPosition(pPig->GetSprite()->getPosition());
                 bigFog->setScale(CCGetScaleX()*0.6f);
				 AddFlyPathPoint(bigFog);
            }
			pPig->setTag(0);
			//区分爆炸猪的两种状态，一种是还在天上飞，另外一种是已经落地;
            if((pPig->GetPigType() == EPigType_Bomb || pPig->GetPigType() == EPigType_Ceram) && pPig->GetState()== EPigState_EndFly)
                pPig->BombTouchBeginCallback();
			else
                pPig->SingleTouchBeginCallback();
        }
		else
		{
				m_bGunCtrlTouched = containsAngleLocation(touchPos);
				if (m_bGunCtrlTouched)
					ShowOperateGuideAnim(false);
		}
		if(!SceneManager::SharedSceneManager()->GetPigFlyState())//获取小鸟的飞行状态,如果为假，则单击鼠标时屏幕会自动回到发射点;
		{
	/*		CCNode* node = m_LevelBase->getChildByTag(1000);
			CCActionInterval* actionBy = CCMoveTo::actionWithDuration(1, CCPointMake(-CCGetWinSize().width*(node->getScale()-0.6667)*0.5,node->getPosition().y));//设定一个动作;
			CCActionInterval* actionScale = CCScaleTo::actionWithDuration(1, node->getScale());
			CCActionInterval* spw = CCSpawn::actionOneTwo(actionBy, actionScale);
			node->runAction( CCSequence::actions(spw,NULL));   */
		}
	}
}

void LevelBaseEx::TouchMoved(CCPoint touchPos)
{
	if ( !bCanShotPig )
		return;
	//if(SceneManager::SharedSceneManager()->GetGameVersion() != EGmaeVersion_JX)
	//{
	//	CCPoint vector = ccpSub(touchPos, m_pigShotPos);
	//	CCPoint normalVector = ccpNormalize(vector);
	//	float length = ccpLength(vector);
	//	if (length > MaxSlingLength)
	//		length = MaxSlingLength;

	//	CCPoint newPos = ccpAdd(m_pigShotPos, ccpMult(normalVector, length));
	//	m_pCurPigWithNoBody->setPosition(newPos);

	//	if ( m_vSlingPoints.size() >= 3 )
	//	{
	//		m_vSlingPoints[2] = newPos;

	//		float fTemp = length == 0 ? 1 : (MaxSlingLength-length)/length;
	//		m_fSlingRopeWidth = (MinSlingRopeWidth+MaxSlingRopeWidth*fTemp)/(1+fTemp);
	//	}

	//	DoSlingShotAnim(GetSlingShotMoveDir());
	//}
	//else
	//{
		if(m_bGunCtrlTouched)
		{
			float angle = atan((touchPos.y - m_pigShotPos.y)/( touchPos.x - m_pigShotPos.x ));
			angle = CC_RADIANS_TO_DEGREES(angle);
			CCLog("%f",angle);
			float Anglenum = pLeftSlingShot->getRotation();
			//CCPoint normalVector = ccpForAngle(angle);
			//float radius = pLeftSlingShot->getContentSize().width*CCGetScaleX()/2;
			//CCPoint newPigPos = ccpAdd(m_pigShotPos, ccpMult(normalVector, radius));
			if( /*Anglenum + (-angle) > -61 && Anglenum + (-angle) < 16*/ angle < 61 && angle > -16 )
			{
				//float angle_pig = pLeftSlingShot->getRotation();
				//CCLog("%f",angle_pig);
				//float Hypotenuse = pLeftSlingShot->getContentSize().width*CCGetScaleX()/2;
				//CCLog("%f",Hypotenuse);
				//float deltaWidth =  (pLeftSlingShot->getPosition().x + Hypotenuse*cos(-angle_pig)) - m_pCurPigWithNoBody->getPosition().x;
				//float deltaHeight = (pLeftSlingShot->getPosition().y + Hypotenuse*sin(-angle_pig)) - m_pCurPigWithNoBody->getPosition().y;

				//CCLog("猪的起始位置x:%f y:%f ",m_pCurPigWithNoBody->getPosition().x, m_pCurPigWithNoBody->getPosition().y);
				//CCLog("炮口位置x:%f 炮口位置y:%f",pLeftSlingShot->getPosition().x + Hypotenuse*cos(-angle_pig),(pLeftSlingShot->getPosition().y + Hypotenuse*sin(-angle_pig)));
				//CCLog("Height:%f Width:%f",deltaHeight,deltaWidth);

				//m_pCurPigWithNoBody->runAction(CCMoveTo::actionWithDuration(0.1f,ccp(pLeftSlingShot->getPosition().x + Hypotenuse*cos(-angle_pig),pLeftSlingShot->getPosition().y + Hypotenuse*sin(-angle_pig))));
				//m_pCurPigWithNoBody->setPosition(newPigPos);
				//pLeftSlingShot->runAction(CCRotateBy::actionWithDuration(0.1f, -40*angle));
				pLeftSlingShot->setRotation(-angle);
			}
			else if(/*Anglenum + (-angle) <= -61*/ angle >= 61)
			{
				//pLeftSlingShot->runAction(CCRotateTo::actionWithDuration(0.1f, -70));
				pLeftSlingShot->setRotation(-60);
			}
			else if(/*Anglenum + (-angle) >= 16*/ angle <= -16)
			{
				//pLeftSlingShot->runAction(CCRotateTo::actionWithDuration(0.1f, 15));
				pLeftSlingShot->setRotation(15);
			}
			//if(SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			//{
			//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSound_Rotate);
			//}
		}
	//}
}

void LevelBaseEx::TouchEnd(CCPoint touchPos)
{
	if ( !bCanShotPig )
	{
		bCanShotPig = true;
		return;
	}

	//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
	//{
		if ( m_bGunCtrlTouched )
		{
			float angle_pig = pLeftSlingShot->getRotation();
			angle_pig = CC_DEGREES_TO_RADIANS(angle_pig);
			float Hypotenuse = pLeftSlingShot->getContentSize().width/2;
			float curShotPosX =  (pLeftSlingShot->getPosition().x + Hypotenuse*cos(-angle_pig));
			float curShotPosY = (pLeftSlingShot->getPosition().y + Hypotenuse*sin(-angle_pig));
			curShotPos = ccp(curShotPosX,curShotPosY);

			//CCLog("大炮的角度:%f",angle_pig);
			//CCLog("大炮口改变的坐标:%f %f",Hypotenuse*cos(-angle_pig),Hypotenuse*sin(-angle_pig));

			m_bGunCtrlTouched = false;
			PigNumber--;
			m_vPigs2->removeLastObject();
			Pig* pPrePig = (Pig*)this->getChildByTag(KCurPigTag);
			if ( pPrePig != NULL )
			{
				pPrePig->SetDrawPathPoint(false);
			}
			int pigType=m_pCurPigWithNoBody->GetPigType();
			Pig* pPig = Pig::CreatePig(m_pCurPigWithNoBody->GetPigType(), m_pWorld, m_pCurPigWithNoBody->GetImage().c_str(),
										   this, s_pPathDispearFog, curShotPos,
										   this, drawPoint_selector(LevelBaseEx::AddFlyPathPoint));
			pPig->setTag(KCurPigTag);
			disCount++;//每次发射完后，使得已经发射完的猪的数量加1;
			pPig->SingleTouchEndCallback();
			this->addChild(pPig);
			//设定小鸟的飞行状态为真;
			pPig->SetState(EPigState_Fly);
			SceneManager::SharedSceneManager()->SetPigFlyState(true);
			SceneManager::SharedSceneManager()->SetZero(false);
        
			float param;
			if(pigType == EPigType_Normal)  //normal pig普通猪;
				param = 0.08f;
			else if(pigType == EPigType_Separate){    //separate pig分身猪;
				param = 0.07f;
			}else if(pigType == EPigType_Speedup){   //speed pig加速猪;
				param = 0.11f;
			}else if(pigType == EPigType_Bomb){   //bomb pig爆炸猪;
				param = 0.19f;
			}
			else if ( pigType == EPigType_Ice )
			{
				param = 0.1f;
			}
			else if( pigType == EPigType_Ceram )
			{
				param = 0.13f;
			}

			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				if ( pPig->GetPigType() == EPigType_Normal)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_fly,false);
				}
				if ( pPig->GetPigType() == EPigType_Speedup)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsExplosionPig_fly,false);
				}
				if ( pPig->GetPigType() == EPigType_Separate)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_fly,false);
				}
				if ( pPig->GetPigType() == EPigType_Bomb)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_fly,false);
				}
				if ( pPig->GetPigType() == EPigType_Ice)
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathIcePig_Fly,false);
				}
			}

			//CCPoint curPigPos = this->convertToWorldSpaceAR(m_pCurPigWithNoBody->getPosition());
			//方向为大炮中心到小猪发射位置的向量;
			CCPoint vector = ccpSub(curShotPos,pLeftSlingShot->getPosition()/*, curPigPos*/);
			//CCPoint vector = ccp(3.0f,3.0f);

			//CCLog("vector.x:%f vector.y:%f",vector.x,vector.y);
			//CCLog("curPigPos.x:%f curPigPos.y:%f",curShotPos.x , curShotPos.y);
			//CCLog("炮台的中心位置：%f %f",pLeftSlingShot->getPosition().x,pLeftSlingShot->getPosition().y);
			//CCLog("炮台的锚点：%f %f",pLeftSlingShot->getAnchorPoint().x,pLeftSlingShot->getAnchorPoint().y);

			/*if ( ccpLength(vector) > MaxSlingLength )
				vector = CCPointMake(ccpNormalize(vector).x*MaxSlingLength, ccpNormalize(vector).y*MaxSlingLength);*/
			b2Vec2 force = b2Vec2(b2Vec2(vector.x*param/2, vector.y*param/2));
			//CCLog("power is: %f, %f", force.x, force.y);
			//CCLog("pig's size is: %f, %f",pPig->GetSprite()->getContentSize().width,pPig->GetSprite()->getContentSize().height);
			pPig->GetBody()->ApplyLinearImpulse(force, pPig->GetBody()->GetWorldCenter());

			/************************************************************************/
			/*   猪发射的烟雾效果                                                                   */
			/************************************************************************/
			char szImageFileName[128] = {0};
			sprintf(szImageFileName,"%s.png",s_pPathEffect_GunSmoke);
			CCSprite *launch = CCSprite::spriteWithSpriteFrameName(szImageFileName);
			launch->setPosition(ccp(pLeftSlingShot->getContentSize().width,pLeftSlingShot->getContentSize().height/2));
			launch->setScale(2);
			pLeftSlingShot->addChild(launch);
			//launch->setPosition(curShotPos);
			//this->addChild(launch,10);

			CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
			CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(kMaxSmashImageCount);
			//szImageFileName[128] = '\0';

			//CCAnimation* animation = CCAnimation::animation();
			for(int i = 1; i < 5; i++)
			{
				//sprintf(szImageFileName,"Fog/DispearFog/DispearFog%d.png",i);
				sprintf(szImageFileName,"%s%d.png",s_pPathEffect_GunSmoke,i);
				//animation->addFrameWithFileName(szImageFileName);
				CCSpriteFrame* frame = cache->spriteFrameByName( szImageFileName );  
				animFrames->addObject(frame);
			}
			//animation->setDelay(0.25f / 4.0f);
			//CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
			CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,0.1f);  
			CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
			animFrames->release();
			launch->runAction(CCSequence::actionOneTwo(animate,CCCallFuncN::actionWithTarget(this,callfuncN_selector(NodeBase::ActionCallBackN))));

			if(SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathSound_Fire);
			}

			ClearFlyPathPoints();
        
			m_pCurPigWithNoBody->removeFromParentAndCleanup(true);
			m_pCurPigWithNoBody = NULL;
        
			PositionNextPig();
        
		}
	//}
	//else
	//{
	//	if ( m_bPigTouched )
	//	{
	//		if(this->containsRecoverLocation(touchPos))
	//		{
	//			m_pCurPigWithNoBody->runAction(CCMoveTo::actionWithDuration(0.1,m_pigShotPos));
	//			if ( m_vSlingPoints.size() >= 3 )
	//			{
	//				m_vSlingPoints[2] = CCPointMake((m_vSlingPoints[0].x+m_vSlingPoints[1].x)/2,
	//					(m_vSlingPoints[0].y+m_vSlingPoints[1].y)/2);
	//			}
	//			return;
	//		}
	//		m_bPigTouched = false;
	//		PigNumber--;
	//		m_vPigs2->removeLastObject();
	//		Pig* pPrePig = (Pig*)this->getChildByTag(KCurPigTag);
	//		if ( pPrePig != NULL )
	//		{
	//			pPrePig->SetDrawPathPoint(false);
	//		}
	//		int pigType=m_pCurPigWithNoBody->GetPigType();
	//		Pig* pPig = Pig::CreatePig(m_pCurPigWithNoBody->GetPigType(), m_pWorld, m_pCurPigWithNoBody->GetImage().c_str(),
	//			this, s_pPathDispearFog, m_pCurPigWithNoBody->getPosition(),
	//			this, drawPoint_selector(LevelBaseEx::AddFlyPathPoint));
	//		pPig->setTag(KCurPigTag);
	//		disCount++;//每次发射完后，使得已经发射完的猪的数量加1;
	//		pPig->SingleTouchEndCallback();
	//		this->addChild(pPig);
	//		//设定小鸟的飞行状态为真;
	//		pPig->SetState(EPigState_Fly);
	//		SceneManager::SharedSceneManager()->SetPigFlyState(true);
	//		SceneManager::SharedSceneManager()->SetZero(false);

	//		float param;
	//		if(pigType == 1)  //normal pig普通猪;
	//			param = 0.1f;
	//		else if(pigType == 2){    //separate pig分身猪;
	//			param = 0.07f;
	//		}else if(pigType == 3){   //speed pig加速猪;
	//			param = 0.11f;
	//		}else if(pigType == 4){   //bomb pig爆炸猪;
	//			param = 0.19f;
	//		}
	//		else if ( pigType == 5 )
	//		{
	//			param = 0.1f;
	//		}

	//		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	//		{
	//			if ( pPig->GetPigType() == EPigType_Normal)
	//			{
	//				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_fly,false);
	//			}
	//			if ( pPig->GetPigType() == EPigType_Speedup)
	//			{
	//				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsExplosionPig_fly,false);
	//			}
	//			if ( pPig->GetPigType() == EPigType_Separate)
	//			{
	//				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_fly,false);
	//			}
	//			if ( pPig->GetPigType() == EPigType_Bomb)
	//			{
	//				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_fly,false);
	//			}
	//			if ( pPig->GetPigType() == EPigType_Ice)
	//			{
	//				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathIcePig_Fly,false);
	//			}
	//		}

	//		CCPoint curPigPos = m_pCurPigWithNoBody->getPosition();
	//		CCPoint vector = ccpSub(m_pigShotPos, curPigPos);
	//		if ( ccpLength(vector) > MaxSlingLength )
	//			vector = CCPointMake(ccpNormalize(vector).x*MaxSlingLength, ccpNormalize(vector).y*MaxSlingLength);
	//		b2Vec2 force = b2Vec2(b2Vec2(vector.x*param, vector.y*param));
	//		//CCLog("power is: %f, %f", force.x, force.y);
	//		//CCLog("pig's size is: %f, %f",pPig->GetSprite()->getContentSize().width,pPig->GetSprite()->getContentSize().height);
	//		pPig->GetBody()->ApplyLinearImpulse(force, pPig->GetBody()->GetWorldCenter());
	//		if(vector.x > 0)
	//		{
	//			CCNode* node = m_LevelBase->getChildByTag(1000);
	//			CCActionInterval* actionBy = CCMoveTo::actionWithDuration(1, CCPointMake(-CCGetWinSize().width*(node->getScale()-0.6667)*1.3,node->getPosition().y));//设定一个动作;
	//			CCActionInterval* actionScale = CCScaleTo::actionWithDuration(1, node->getScale());
	//			CCActionInterval* spw = CCSpawn::actionOneTwo(actionBy, actionScale);
	//			node->runAction( CCSequence::actions(spw,NULL));
	//		} 


	//		ClearFlyPathPoints();

	//		m_pCurPigWithNoBody->removeFromParentAndCleanup(true);
	//		m_pCurPigWithNoBody = NULL;

	//		PositionNextPig();

	//		if ( m_vSlingPoints.size() >= 3 )
	//		{
	//			m_vSlingPoints[2] = CCPointMake((m_vSlingPoints[0].x+m_vSlingPoints[1].x)/2,
	//				(m_vSlingPoints[0].y+m_vSlingPoints[1].y)/2);
	//		}

	//		DoSlingShotAnim(ESlingShotMoveDir_Mid);
	//	}
	//}

}

void LevelBaseEx::ClearFlyPathPoints()
{
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(m_vFlyPathPoints, pObject)
    {
        CCSprite* pSprite = (CCSprite*)pObject;
        this->removeChild(pSprite, true);
    }
    
    m_vFlyPathPoints->removeAllObjects();
}

ESlingShotMoveDir LevelBaseEx::GetSlingShotMoveDir()
{
	if ( m_vSlingPoints.size() >= 3 )
	{
		if ( m_vSlingPoints[2].x < m_vSlingPoints[0].x )
			return ESlingShotMoveDir_Left;
		else if ( m_vSlingPoints[2].x > m_vSlingPoints[1].x )
			return ESlingShotMoveDir_Right;
		else
			return ESlingShotMoveDir_Mid;
	}

	return ESlingShotMoveDir_Mid;
}

//void LevelBaseEx::DoSlingShotAnim( ESlingShotMoveDir toDir )
//{
//	if ( toDir == ESlingShotMoveDir_Mid )
//	{
//		if ( curSlingShotDir != ESlingShotMoveDir_Mid )
//		{
//			if ( curSlingShotDir == ESlingShotMoveDir_Left )
//			{
//				DoSlingShotAnimEx(ESlingShotMoveTo_FromLeft);
//			}
//			else if ( curSlingShotDir == ESlingShotMoveDir_Right )
//			{
//				DoSlingShotAnimEx(ESlingShotMoveTo_FromRight);
//			}
//
//			curSlingShotDir = ESlingShotMoveDir_Mid;
//		}
//	}
//	else if ( toDir == ESlingShotMoveDir_Left )
//	{
//		if ( curSlingShotDir != ESlingShotMoveDir_Left )
//		{
//			DoSlingShotAnimEx(ESlingShotMoveTo_ToLeft);
//			curSlingShotDir = ESlingShotMoveDir_Left;
//		}
//	}
//	else if ( toDir == ESlingShotMoveDir_Right )
//	{
//		if ( curSlingShotDir != ESlingShotMoveDir_Right )
//		{
//			DoSlingShotAnimEx(ESlingShotMoveTo_ToRight);
//			curSlingShotDir = ESlingShotMoveDir_Right;
//		}
//	}
//}
//
//void LevelBaseEx::DoSlingShotAnimEx( ESlingShotMoveTo moveTo )
//{
//	pLeftSlingShot->stopAllActions();
//	pRightSlingShot->stopAllActions();
//
//	int index = 1;
//	if ( moveTo == ESlingShotMoveTo_ToLeft || moveTo == ESlingShotMoveTo_FromLeft )
//		index = 1;
//	else
//		index = 4;
//
//	CCAnimation* animationLeft = CCAnimation::animation();
//	char frameNameLeft[50] = {0};
//	animationLeft->addFrameWithFileName("SlingShot/SlingShot_L1.png");
//	for (int i = index; i <= index+2; i++)
//	{
//		sprintf(frameNameLeft, "SlingShot/SlingShot_L1_%d.png", i);
//		animationLeft->addFrameWithFileName(frameNameLeft);
//	}
//	CCActionInterval* pActionLeft = CCAnimate::actionWithDuration(0.1f, animationLeft, false);
//
//	CCAnimation* animationRight = CCAnimation::animation();
//	char frameNameRight[50] = {0};
//	animationRight->addFrameWithFileName("SlingShot/SlingShot_R1.png");
//	for (int i = index; i <= index+2; i++)
//	{
//		sprintf(frameNameRight, "SlingShot/SlingShot_R1_%d.png", i);
//		animationRight->addFrameWithFileName(frameNameRight);
//	}
//	CCActionInterval* pActionRight = CCAnimate::actionWithDuration(0.1f, animationRight, false);
//
//	if ( moveTo == ESlingShotMoveTo_FromLeft || moveTo == ESlingShotMoveTo_FromRight )
//	{
//		pLeftSlingShot->runAction(pActionLeft->reverse());
//		pRightSlingShot->runAction(pActionRight->reverse());
//	}
//	else
//	{
//		pLeftSlingShot->runAction(pActionLeft);
//		pRightSlingShot->runAction(pActionRight);
//	}
//}

void LevelBaseEx::AddFlyPathPoint(CCSprite* pSprite)
{
    this->addChild(pSprite, -1);
    m_vFlyPathPoints->addObject(pSprite);
}

void LevelBaseEx::CalculatePigScore(ccTime delta)
{
    if ( SceneManager::SharedSceneManager()->GetPauseState() )
		return;

    this->unschedule(schedule_selector(LevelBaseEx::CalculatePigScore));
    for(int i=0;i<PigNumber;i++)    
    {
        m_iTotalScore+=10000;
	/*
        CCActionInterval*  actionBy = CCScaleBy::actionWithDuration(1.0 ,  0.0);
        m_pCurPigWithNoBody->SetState(EPigState_GameWinRemain);
        m_pCurPigWithNoBody->initWithFile(s_pPathCount5000);
        m_pCurPigWithNoBody->stopAllActions();
        m_pCurPigWithNoBody->runAction( CCSequence::actions(CCDelayTime::actionWithDuration(0.5f),actionBy,NULL));  
		m_vPigs2->removeLastObject();
        m_pCurPigWithNoBody = (PigWithNoBody*)m_vPigs2->lastObject();
		*/
		CCSprite *scorePic;
		CCActionInterval*  actionBy = CCScaleBy::actionWithDuration(0.5 ,  0.0);
		CCActionInterval*  actionByBack = actionBy->reverse();
		scorePic=CCSprite::spriteWithFile(s_pPathCount10000_1);
		scorePic->setScale(CCGetScaleX());
		//if(SceneManager::SharedSceneManager()->GetGameVersion() != EGmaeVersion_JX)
		//{
		//	scorePic->setPosition(ccp(m_pCurPigWithNoBody->getPosition().x,m_pCurPigWithNoBody->getPosition().y+20));
		//}
		//else
		//{
			if(i == 0)
			{
				scorePic->setPosition(ccp(curShotPos.x,curShotPos.y+20));
			}
			else
			{
				scorePic->setPosition(ccp(m_pCurPigWithNoBody->getPosition().x,m_pCurPigWithNoBody->getPosition().y+20));
			}
		//}

		this->addChild(scorePic,10);
		scorePic->runAction( CCSequence::actions(CCDelayTime::actionWithDuration(0.5f),actionBy,NULL));  
		m_pCurPigWithNoBody->SetState(EPigState_GameWinRemain);
		m_pCurPigWithNoBody->stopAllActions();
		m_vPigs2->removeLastObject();
		m_pCurPigWithNoBody = (PigWithNoBody*)m_vPigs2->lastObject();
    }
}

void LevelBaseEx::GameWin(ccTime delta)
{
	if ( SceneManager::SharedSceneManager()->GetPauseState() )
		return;

    this->unschedule(schedule_selector(LevelBaseEx::GameWin));
    //UILevelFinish(true);
    //获取记录的最高得分;
    char string[16] = {0};
    sprintf(string, "highestScore%d%d", CurBigID,CurSmallLevelID);
    int recordScore=0;
    recordScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(string);
    //如果当前得分大于记录的最高得分，并且通过本关，则更新最高得分;
    if (m_iTotalScore>recordScore)
    {
		newrecord = true;
        CCUserDefault::sharedUserDefault()->setIntegerForKey(string, m_iTotalScore);
        CCUserDefault::sharedUserDefault()->flush();//这里一定要提交写入，否则不会记录到xml中，下次启动游戏你就获取不到value了;

        //玩家刷新了最高记录，对应的星星数也应该刷新存储;
        sprintf(string, "stars%d%d",CurBigID,CurSmallLevelID);

        if (m_iTotalScore>OneStarScore && m_iTotalScore<TwoStarScore)
        {
            CCUserDefault::sharedUserDefault()->setIntegerForKey(string, 1);
            CCUserDefault::sharedUserDefault()->flush();
        }
        else if (m_iTotalScore>=TwoStarScore && m_iTotalScore<ThreeStarScore)
        {
            CCUserDefault::sharedUserDefault()->setIntegerForKey(string, 2);
            CCUserDefault::sharedUserDefault()->flush();
        }
        else if (m_iTotalScore>=ThreeStarScore)
        {
            CCUserDefault::sharedUserDefault()->setIntegerForKey(string, 3);
            CCUserDefault::sharedUserDefault()->flush();
        }

    }
	UILevelFinish(true);

    //如果赢了本关，则向userdefault.xml文件中改变（或者说增加开通下一关的一个bool值变量为真）;
    //char string[16]={0};
    if (CurSmallLevelID == SceneManager::SharedSceneManager()->GetLevelsCountByBigID(CurBigID))    //如果当前小关卡的ID为最后一关即第22关，则开通下一个大关的第一小关;
    {
        sprintf(string,"IsOpen%d%d",CurBigID+1,1);
        CCUserDefault::sharedUserDefault()->setBoolForKey(string,true);
        CCUserDefault::sharedUserDefault()->flush();
    }
    else                         //否则开通本大关下的下一小关;
    {
        sprintf(string,"IsOpen%d%d",CurBigID,CurSmallLevelID+1);
        CCUserDefault::sharedUserDefault()->setBoolForKey(string,true);
        CCUserDefault::sharedUserDefault()->flush();
    }
    isLevelFinish = true;
}

////////////////////////////////////////////////////////////////////////////////////

LevelBase::LevelBase()
: m_pLevelEx(NULL)
{
    setIsTouchEnabled( true );
}

LevelBase::~LevelBase()
{
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CC_SAFE_RELEASE(m_pLevelEx);
}

void LevelBase::BeginInit(int SmallLevelID,int BigLevelID,CCLayer* cc)
{
	CurSmallLevelID = SmallLevelID;
	CurBigID = BigLevelID;
    CurBigStageID=BigLevelID;
	m_pLevelEx = new LevelBaseEx(cc); //初始化逻辑层;
	m_pLevelEx->SetLevelParent(this); //将逻辑附加到显示界面;
}

void LevelBase::EndInit()
{
    if ( m_pLevelEx != NULL )
        m_pLevelEx->Run();
}

void LevelBase::InitCloud(CCSprite* pParent, const char* image)
{
    //char imageFullName[50] = {0};
    //sprintf(imageFullName, "%s.png", image);
    m_pCloudSprite = CCSprite::spriteWithFile(image);
    m_pCloudSprite->setAnchorPoint(ccp(0,0));
    m_pCloudSprite->setScale(pParent->getScale());
//    m_pCloudSprite->setScaleY(CCGetScaleY());
    m_pCloudSprite->setPosition(ccp(0,CCGetWinSize().height/2));
    pParent->addChild(m_pCloudSprite, 5);

    m_pCloudSpriteRe = CCSprite::spriteWithFile(image);
    m_pCloudSpriteRe->setAnchorPoint(ccp(0,0));
    m_pCloudSpriteRe->setScale(pParent->getScale());
//    m_pCloudSpriteRe->setScaleY(CCGetScaleY());
    m_pCloudSpriteRe->setPosition(ccp(-pParent->getContentSize().width,CCGetWinSize().height/2));
    pParent->addChild(m_pCloudSpriteRe, 5);
    m_pSpriteCloudParent = pParent;

    this->schedule(schedule_selector(LevelBase::CloudUpdate));
}

void LevelBase::CloudUpdate(ccTime delta)
{
    float totalWidth = m_pSpriteCloudParent->getContentSize().width;

 //   m_pCloudSprite->setPositionY(0);
    m_pCloudSprite->setPositionX(m_pCloudSprite->getPositionX()+20*CCGetScaleX()*delta);
    if ( m_pCloudSprite->getPositionX()>totalWidth )
        m_pCloudSprite->setPositionX(m_pCloudSprite->getPositionX()-2*totalWidth);

//    m_pCloudSpriteRe->setPositionY(0);
    m_pCloudSpriteRe->setPositionX(m_pCloudSpriteRe->getPositionX()+20*CCGetScaleX()*delta);
    if ( m_pCloudSpriteRe->getPositionX()>totalWidth )
        m_pCloudSpriteRe->setPositionX(m_pCloudSpriteRe->getPositionX()-2*totalWidth);
}

void LevelBase::InitBigFourBackGroundImages(CCTexture2D* bg1Texture,CCTexture2D* bg2Texture,CCTexture2D* bg3Texture,CCTexture2D* bg4Texture,CCTexture2D* bgTexture1,CCTexture2D* bgTexture2,CCTexture2D* bgTexture3,CCTexture2D* bgTexture4)
{
	CCSprite* bg1 = CCSprite::spriteWithTexture(bg1Texture);
	bg1->setAnchorPoint(ccp(0,0));
	bg1->setScale(CCGetScaleX());

	//第二张素材做为地面;
	if ( m_pLevelEx != NULL )
	{
		m_pLevelEx->SetBackGround(bg2Texture);
		m_pLevelEx->setAnchorPoint(ccp(0,0));

		//if ( SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ )
		//{
		//	CCPoint pos = ccp(bg2Texture->getContentSize().width/2, CCGetWinSize().height*1.5f);
		//	CCPoint posVar = ccp(bg2Texture->getContentSize().width/2, 0);
		//	SceneManager::SharedSceneManager()->ShowSnowEffect(m_pLevelEx, -2, pos, posVar);
		//}
	}

	CCSprite* bg3 = CCSprite::spriteWithTexture(bg3Texture);
	bg3->setAnchorPoint(ccp(0,0));
	bg3->setScale(CCGetScaleX());

	CCSprite* bg4 = CCSprite::spriteWithTexture(bg4Texture);
	bg4->setAnchorPoint(ccp(0,0));
	bg4->setScale(CCGetScaleX());

	//if ( SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_HGS )
	//{
	//	if(CurBigStageID == 1)
	//	{
	//		CCAnimation* animation = CCAnimation::animation();
	//		for (int i = 1; i <= 4; i+=1)
	//		{
	//			CCRect rect = CCRectZero;
	//			if (i==1)
	//			{
	//				rect.size = bgTexture1->getContentSize();
	//				animation->addFrameWithTexture(bgTexture1,rect);
	//			}
	//			else if (i==2)
	//			{
	//				rect.size = bgTexture2->getContentSize();
	//				animation->addFrameWithTexture(bgTexture2,rect);
	//			}
	//			else if (i==3)
	//			{
	//				rect.size = bgTexture3->getContentSize();
	//				animation->addFrameWithTexture(bgTexture3,rect);
	//			}
	//			else if (i==4)
	//			{
	//				rect.size = bgTexture4->getContentSize();
	//				animation->addFrameWithTexture(bgTexture4,rect);
	//			}
	//		}

	//		CCAnimate *animate = CCAnimate::actionWithDuration(1.0f, animation, false);
	//		bg4->runAction(CCRepeatForever::actionWithAction(animate));
	//	}
	//	else if(CurBigStageID == 4)
	//	{
	//		CCAnimation* animation = CCAnimation::animation();
	//		for (int i = 1; i <= 4; i+=1)
	//		{
	//			CCRect rect = CCRectZero;
	//			if (i==1)
	//			{
	//				rect.size = bgTexture1->getContentSize();
	//				animation->addFrameWithTexture(bgTexture1,rect);
	//			}
	//			else if (i==2)
	//			{
	//				rect.size = bgTexture2->getContentSize();
	//				animation->addFrameWithTexture(bgTexture2,rect);
	//			}
	//			else if (i==3)
	//			{
	//				rect.size = bgTexture3->getContentSize();
	//				animation->addFrameWithTexture(bgTexture3,rect);
	//			}
	//			else if (i==4)
	//			{
	//				rect.size = bgTexture4->getContentSize();
	//				animation->addFrameWithTexture(bgTexture4,rect);
	//			}
	//		}

	//		CCAnimate *animate = CCAnimate::actionWithDuration(1.0f, animation, false);
	//		bg3->setScale(CCGetScaleX());
	//		bg3->runAction(CCRepeatForever::actionWithAction(animate));
	//	}
	//}
	if(CurBigStageID == 1)
		InitCloud(bg4, s_pPathScene_Level1bg5);
	else if(CurBigStageID == 2)
		InitCloud(bg4, s_pPathScene_Level2bg5);
	else if(CurBigStageID == 3)
		InitCloud(bg4, s_pPathScene_Level3bg5);
	else if(CurBigStageID == 4)
		InitCloud(bg4, s_pPathScene_Level4bg5);
	else if(CurBigStageID == 5)
		InitCloud(bg4,s_pPathScene_Level5bg5);

	//CCActionInterval* actionBy = CCMoveTo::actionWithDuration(1, CCPointMake(PigShotPoint_x/PTM_RATIO-150,PigShotPoint_y/PTM_RATIO));//设定一个动作;
	//CCActionInterval* actionScale = CCScaleTo::actionWithDuration(1, 1);
	//CCActionInterval* spw = CCSpawn::actionOneTwo(actionBy, actionScale);

	//一个可以模拟出视差的节点;
	CCParallaxNode* voidNode = CCParallaxNode::node();
	voidNode->addChild(bg1, 3, ccp(1.0f,0.5f), ccp(0,0)); //near
	voidNode->addChild(m_pLevelEx, 2, ccp(0.8f,0.5f), ccp(0,0) );
	voidNode->addChild(bg3, 0, ccp(0.6f,0.5f), ccp(0,0));  //(bg2->getContentSize().height-20)*CCGetScaleX();
	voidNode->addChild(bg4, -1, ccp(0.2f,0.5f), ccp(0,0)); //far
	voidNode->setPosition(ccp(-CCGetWinSize().width*voidNode->getScale()/5.0f,-CCGetWinSize().height/7.0f)); 
	this->addChild(voidNode, -1, 1000);
}

void LevelBase::AddPig(EPigType pigType, const char* image, float x, float y)
{
    if ( m_pLevelEx != NULL )
        m_pLevelEx->AddPig(pigType, image, CCPointMake(x*CCGetScaleX(), y*CCGetScaleY()));
}

void LevelBase::AddProps(const char* image, float x, float y, std::vector<float> vx, std::vector<float> vy, int propsType, float rot, bool bHasGravity, int z,int tag,int to,int to2,const char* state)
{
	if ( m_pLevelEx != NULL )
		m_pLevelEx->AddProps(image, CCPointMake(x*CCGetScaleX(), y*CCGetScaleY()), vx, vy, propsType, rot, bHasGravity, z,tag,to,to2,state);
}

void LevelBase::SetPigShotPos(float x, float y)
{
    if ( m_pLevelEx != NULL )
        m_pLevelEx->SetPigShotPos(CCPointMake(x*CCGetScaleX(), y*CCGetScaleY()));
	PigShotPoint_x = x;
	PigShotPoint_y = y;
}

void LevelBase::SetSlingRopePoints(float posLeftX, float posLeftY, float posRightX, float posRightY)
{
    if ( m_pLevelEx != NULL )
        m_pLevelEx->SetSlingRopePoints(CCPointMake(posLeftX*CCGetScaleX(), posLeftY*CCGetScaleY()),
                                   CCPointMake(posRightX*CCGetScaleX(), posRightY*CCGetScaleY()));
}

void LevelBase::registerWithTouchDispatcher()
{
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
	CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this, 0);
}

void LevelBase::BeginZoom(CCPoint pos1, CCPoint pos2)
{
    m_fFirstLen = ccpDistance(pos1, pos2);
}

void LevelBase::MoveZoom(CCPoint pos1,CCPoint pos1_pre,CCPoint pos2,CCPoint pos2_pre)
{
    float length = ccpDistance(pos1, pos2);	 //现在两指的距离;
    float length_pre=ccpDistance(pos1_pre,pos2_pre);  //之前两指的距离;
    float diff = (length-length_pre);



    if(diff>0)    //放大;
    {
        CCNode* node = getChildByTag(1000);
        CCPoint curP=node->getPosition();
        float news=diff/400+1;


        if(node->getScale()<1.2)
        {
            node->setScale(node->getScale()*news>1.2?1.2:(node->getScale())*news);  //缩放比大于1.5 则为1.5;
            //放大时node坐标左下角移动,  最右边的时候放大！;
            node->setPosition((curP.x-diff)< -CCGetWinSize().width*(node->getScale()-0.6667)*1.5?-CCGetWinSize().width*(node->getScale()-0.6667)*1.5: (curP.x-diff),(curP.y-diff)<-CCGetWinSize().height/4?-CCGetWinSize().height/4:(curP.y-diff));

        }
      

    }else if(diff<=0)
    {
        CCNode* node2 = getChildByTag(1000);
        CCPoint curP2=node2->getPosition();

        if(node2->getScale()<=0.6667)
        {
            node2->setScale(0.6667);
            //m_curPoint 一开始的时候的坐标;
            node2->setPosition(ccp(0,0));
        }else if(node2->getScale()>0.6667){
            float news2=1+diff/400;
            node2->setScale(node2->getScale()*news2<=0.6667?0.6667:node2->getScale()*news2); //缩放比小于1.0，则为1.0;
            // 缩小的时候node坐标右上角移动，  镜头在最左边的时候 缩小 注意！;
            float newCurPX=curP2.x-diff;
            if(newCurPX<-CCGetWinSize().width*(node2->getScale()-0.6667)*1.5)  //最右边缩小时;
                newCurPX=-CCGetWinSize().width*(node2->getScale()-0.6667)*1.5;
            else if(newCurPX>0)
                newCurPX=0;
            node2->setPosition(newCurPX,(curP2.y-diff)>0?0:(curP2.y-diff));
        }
     
    }
}

void LevelBase::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCLog("ccTouchesBegan----------------------");
    diff.x=0;

	switch (pTouches->count()) 
	{
	case 1:
		{
			CCSetIterator it = pTouches->begin();
			CCTouch* pTouch = (CCTouch*)(*it);
			CCPoint touchLocation = pTouch->locationInView(pTouch->view());
			touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
			m_pLevelEx->TouchBegin(m_pLevelEx->convertToNodeSpace(touchLocation));
		}
		break;
	case 2:
		{
			CCTouch *touch1 = (CCTouch*)(*pTouches->begin());
			pTouches->removeObject(touch1);
			CCTouch *touch2 = (CCTouch*)(*pTouches->begin());

			CCPoint touchLocation1 = touch1->locationInView(touch1->view());
			touchLocation1 = CCDirector::sharedDirector()->convertToGL(touchLocation1);
			CCPoint touchLocation2 = touch2->locationInView(touch2->view());
			touchLocation2 = CCDirector::sharedDirector()->convertToGL(touchLocation2);

			BeginZoom(touchLocation1, touchLocation2);
		}
		break;
	}
}

void LevelBase::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCLog("ccTouchesEnded!!!!!!!!!!!!!!!!!!");
	if(diff.x<0)
	{
		this->unschedule(schedule_selector(LevelBase::TouchMoveRight));
		this->schedule(schedule_selector(LevelBase::TouchMoveLeft));            
	}
	else if(diff.x>0)
	{
		this->unschedule(schedule_selector(LevelBase::TouchMoveLeft));
		this->schedule(schedule_selector(LevelBase::TouchMoveRight));
	}

	CCSetIterator it = pTouches->begin();
	CCTouch* pTouch = (CCTouch*)(*it);
    CCPoint touchLocation = pTouch->locationInView(pTouch->view());
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    m_pLevelEx->TouchEnd(m_pLevelEx->convertToNodeSpace(touchLocation));
}

void LevelBase::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

void LevelBase::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	switch (pTouches->count()) 
	{
	case 1:
		{
			CCSetIterator it = pTouches->begin();
			CCTouch* pTouch = (CCTouch*)(*it);
			CCPoint touchLocation = pTouch->locationInView( pTouch->view() );	
			CCPoint prevLocation = pTouch->previousLocationInView( pTouch->view() );	
			touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
			prevLocation = CCDirector::sharedDirector()->convertToGL( prevLocation );
			//if(SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
			//{
				if ( m_pLevelEx != NULL && (m_pLevelEx->IsCurPigTouched() || m_pLevelEx->IsGunCtrlTouched()) )
				{
					m_pLevelEx->TouchMoved( m_pLevelEx->convertToNodeSpace(touchLocation) );
				}
				else
				{
					diff = ccpSub(touchLocation,prevLocation);//获取移动的位差;
					diff.y = 0;//将移动的位差的y方向位移设为0，使得只能在x方向移动;

					CCNode* node = getChildByTag(1000);//获取作用节点;
					CCPoint currentPos = node->getPosition();//获取节点当前坐标;;
					CCPoint newPos = ccpAdd(currentPos, diff);//根据x方向上的偏移计算出新的节点坐标;
					//判断x方向上的偏移量是否超出边界;
					//       if ( newPos.x < -CCGetWinSize().width*node->getScale()/1.5 || newPos.x > -CCGetWinSize().width*node->getScale()/4.8f )	//判断x方向上的偏移量是否超出边界;
					if ( newPos.x <= -CCGetWinSize().width*(node->getScale()-0.6667)*1.5 || newPos.x >= 0)	//判断x方向上的偏移量是否超出边界;
						return;//如果超出边界则返回，不付给节点新的坐标;

					node->setPosition(newPos);//付给节点新的坐标;

					CCActionManager::sharedManager()->removeAllActionsFromTarget(node);//移除node节点中所有的动作;
				}
			//}
			//else
			//{
			//	if ( m_pLevelEx != NULL && m_pLevelEx->IsCurPigTouched() )
			//	{
			//		m_pLevelEx->TouchMoved( m_pLevelEx->convertToNodeSpace(touchLocation) );
			//	}
			//	else
			//	{
			//		diff = ccpSub(touchLocation,prevLocation);//获取移动的位差;
			//		diff.y = 0;//将移动的位差的y方向位移设为0，使得只能在x方向移动;

			//		CCNode* node = getChildByTag(1000);//获取作用节点;
			//		CCPoint currentPos = node->getPosition();//获取节点当前坐标;;
			//		CCPoint newPos = ccpAdd(currentPos, diff);//根据x方向上的偏移计算出新的节点坐标;
			//		//判断x方向上的偏移量是否超出边界;
			//		//       if ( newPos.x < -CCGetWinSize().width*node->getScale()/1.5 || newPos.x > -CCGetWinSize().width*node->getScale()/4.8f )	//判断x方向上的偏移量是否超出边界;
			//		if ( newPos.x <= -CCGetWinSize().width*(node->getScale()-0.6667)*1.5 || newPos.x >= 0)	//判断x方向上的偏移量是否超出边界;
			//			return;//如果超出边界则返回，不付给节点新的坐标;

			//		node->setPosition(newPos);//付给节点新的坐标;

			//		CCActionManager::sharedManager()->removeAllActionsFromTarget(node);//移除node节点中所有的动作;
			//	}
			//}



		}
		break;
	case 2:
		{
			CCTouch *touch1 = (CCTouch*)(*pTouches->begin());
			pTouches->removeObject(touch1);
			CCTouch *touch2 = (CCTouch*)(*pTouches->begin());

			CCPoint touchLocation1 = touch1->locationInView(touch1->view());
			CCPoint touchLocation1_pre = touch1->previousLocationInView(touch1->view());
			touchLocation1 = CCDirector::sharedDirector()->convertToGL(touchLocation1);
			CCPoint touchLocation2 = touch2->locationInView(touch2->view());
			CCPoint touchLocation2_pre = touch2->previousLocationInView(touch2->view());
			touchLocation2 = CCDirector::sharedDirector()->convertToGL(touchLocation2);
			MoveZoom(touchLocation1,touchLocation1_pre,touchLocation2,touchLocation2_pre);
		}
		break;
	}
}

void LevelBase::SetHighestScore(int score1,int score2,int score3)
{
	OneStarScore = score1;
	TwoStarScore = score2;
	ThreeStarScore = score3;
}

void LevelBase::TouchMoveLeft(ccTime delta)
{
    if(diff.x<0)
    {
        CCNode* node = getChildByTag(1000);//获取作用节点;
        CCPoint nowPos = node->getPosition();//获取节点当前坐标;
        nowPos.x+=diff.x/1.0;
        if(nowPos.x<=-CCGetWinSize().width*(node->getScale()-0.6667)*1.5)
        {
            nowPos.x=-CCGetWinSize().width*(node->getScale()-0.6667)*1.5;
            this->schedule(schedule_selector(LevelBase::TouchMoveLeftBack));
            this->unschedule(schedule_selector(LevelBase::TouchMoveLeft));
        }
        node->setPosition(nowPos);
        CCActionManager::sharedManager()->removeAllActionsFromTarget(node);//移除node节点中所有的动作;
    }
}

void LevelBase::TouchMoveRight(ccTime delta)
{
    if(diff.x>0)
    {
        CCNode* node = getChildByTag(1000);//获取作用节点;
        CCPoint nowPos = node->getPosition();//获取节点当前坐标;
        nowPos.x+=diff.x/1.0;
        if(nowPos.x>=0)
        {
            nowPos.x=0;
            this->schedule(schedule_selector(LevelBase::TouchMoveRightBack));
            this->unschedule(schedule_selector(LevelBase::TouchMoveRight));
        }
        node->setPosition(nowPos);
        CCActionManager::sharedManager()->removeAllActionsFromTarget(node);//移除node节点中所有的动作;
    }
}

void LevelBase::TouchMoveLeftBack(ccTime delta)
{
    CCNode* node = getChildByTag(1000);//获取作用节点;
    CCPoint nowPos = node->getPosition();//获取节点当前坐标;
    nowPos.x+=1.0;
    if(nowPos.x>-CCGetWinSize().width*(node->getScale()-0.6667)*1.45)
    {
        nowPos.x=-CCGetWinSize().width*(node->getScale()-0.6667)*1.45;
        this->unschedule(schedule_selector(LevelBase::TouchMoveLeftBack));
    }
    node->setPosition(nowPos);  
}

void LevelBase::TouchMoveRightBack(ccTime delta)
{
    CCNode* node = getChildByTag(1000);//获取作用节点;
    CCPoint nowPos = node->getPosition();//获取节点当前坐标;
    nowPos.x-=1.0;
    if(nowPos.x<-CCGetWinSize().width*(node->getScale()-0.6667)*0.1)
    {
        nowPos.x=-CCGetWinSize().width*(node->getScale()-0.6667)*0.1;
        this->unschedule(schedule_selector(LevelBase::TouchMoveRightBack));
    }
    node->setPosition(nowPos);  
}


