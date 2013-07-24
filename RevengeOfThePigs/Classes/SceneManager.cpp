//
//  SceneManager.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-9.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "SceneManager.h"
#include "UISelectBigStage.h"
#include "UIQuitPanel.h"
#include "UIStartPanel.h"
#include "UISelectSmallStage.h"
#include "UIWinFailPanel.h"
#include "UISidePausePanel.h"
#include "UIHelpPanel.h"
#include "UINewGuide.h"
#include "UINewGuideNext.h"
#include "UIStory.h"
#include "Level.h"
#include "MyXMLParser.h"
//#include "process.h" /* _beginthread, _endthread */ 
#include "UIIntroducePanel.h"
#include "UISpecialPropPanel.h"

SceneManager* SceneManager::m_pSceneManager = NULL;

SceneManager::SceneManager()
: m_iCurLevel(-1)
, isZero(false)
//, bLoadFixedProps(false)
, m_pCurLevel(NULL)
, bCheckedUpdate(false)
, bkeyHomeClicked(false)
//, m_curVersion(EGameVersion_BXJ)
, m_bIsTestMode(false)
, BG1_Texture(NULL)
, BG2_Texture(NULL)
, BG3_Texture(NULL)
, BG4_Texture(NULL)
, BG5_Texture(NULL)
, BG6_Texture(NULL)
, BG7_Texture(NULL)
, BG8_Texture(NULL)
, inGame(false)
{
    
}

SceneManager* SceneManager::SharedSceneManager()
{
    if ( m_pSceneManager == NULL )
    {
        m_pSceneManager = new SceneManager();
		//m_pSceneManager->LoadVersionConfig();
		m_pSceneManager->LoadModeControlConfig();
    }
    return m_pSceneManager;
}

void SceneManager::Init()
{
	//_beginthread( PreLoadSound, 0, NULL ); 
	//HANDLE hThread;
	//hThread = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
	//pthread_t threadID;
	//pthread_create(threadID,0,PreLoadSound,NULL);
    //LoadXMLConfig();
	//CCLOG("go before!");
}

void SceneManager::JumpToSelectBigStage()
{
	CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCScene* selectBigStage = UISelectBigStage::scene();
	//以交叉腿色的方式过渡到下一个场景;
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(kSceneTransitionTime, selectBigStage));
}

void SceneManager::JumpToStartPanel()
{
    CCScene* Startscene = UIStartPanel::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(kSceneTransitionTime, Startscene)); // 让场景切换产生渐变的效果;
}

void SceneManager::JumpToSelectSmallStage(int BigLevelID)
{
	LoadXMLConfig(BigLevelID);

	InitBackGround(BigLevelID);

	CCScene* scene = UISelectSmallStage::scene(CurBigLevelID);
	

	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(kSceneTransitionTime, scene));
	//CCLOG("CurBigLevelID=%d",CurBigLevelID);
}

bool SceneManager::InitBackGround(int BigLevelID)
{
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	CurBigLevelID = BigLevelID;
	if (CurBigLevelID == 1)
	{
		BG1_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level1bg1);
		BG2_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level1bg2);
		BG3_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level1bg3);
		BG4_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level1bg4);
		return true;
	}
	else if (CurBigLevelID == 2)
	{
		BG1_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPahtScene_Level2bg1);
		BG2_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level2bg2);
		BG3_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level2bg3);
		BG4_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level2bg4);
		return true;
	}
	else if (CurBigLevelID == 3)
	{
		BG1_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level3bg1);
		BG2_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level3bg2);
		BG3_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level3bg3);
		BG4_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level3bg4);
		return true;
	}
	else if (CurBigLevelID == 4)
	{
		BG1_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level4bg1);
		BG2_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level4bg2);
		BG3_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level4bg3);
		BG4_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level4bg4);
		return true;
	}
	else if (CurBigLevelID == 5)
	{
		BG1_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level5bg1);
		BG2_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level5bg2);
		BG3_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level5bg3);
		BG4_Texture=CCTextureCache::sharedTextureCache()->addImage(s_pPathScene_Level5bg4);
		return true;
	}
}

void SceneManager::JumpToGameLevel(int levelID)
{

	//每次调用该函数时，首先将当前得分设为0;
	SetPauseState(false);
	CurTotalScore = 0;
	std::map<int,LevelInfo*>::iterator it;
	for (it = m_vLevelInfos[CurBigLevelID-1].begin(); it != m_vLevelInfos[CurBigLevelID-1].end(); ++it)
	{
		if ( it->first == levelID )
			break;
	}
	if ( it == m_vLevelInfos[CurBigLevelID-1].end() )
		return;
    
    m_iCurLevel = levelID;
    
    CCScene* levelScene = CCScene::node();
    m_pCurLevel = new Level(levelID,CurBigLevelID);
	m_pCurLevel->InitLevel(levelID, CurBigLevelID,BG1_Texture,BG2_Texture,BG3_Texture,BG4_Texture,BG5_Texture,BG6_Texture,BG7_Texture,BG8_Texture);
	levelScene->addChild(m_pCurLevel);
    m_pCurLevel->autorelease();
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(kSceneTransitionTime, levelScene));
}

void SceneManager::JumpToNextStage(int BigLevelID)
{
	CurBigLevelID = BigLevelID;
	LoadXMLConfig(CurBigLevelID);
	InitBackGround(CurBigLevelID);
	JumpToGameLevel(1);
}

void SceneManager::AddBattleResultPanel(CCNode* pParent, bool bWin, int z,int stars,int score,bool newrecord)
{
	if ( pParent == NULL  )
		return;

	bool bHasNextStage = true;
	int total = m_vLevelInfos[m_pCurLevel->GetBigLevelID()-1].size(); 
    if ( m_pCurLevel->GetLevelID() >= total )
		bHasNextStage = false;

	CCScene* scene = UIWinFailPanel::scene(bWin, stars, score, CurBigLevelID, newrecord, bHasNextStage);
	pParent->addChild(scene, z, kWinFailPanel);
}

void SceneManager::AddPausePanel(CCNode* pParent, int z)
{
	pParent->removeChildByTag(kPausePanel, true);

	SetPauseState(true);
	CCScene* scene = UISidePausePanel::scene(CurBigLevelID,m_iCurLevel);
	pParent->addChild(scene, z, kPausePanel);
	playscene=pParent;
}

bool SceneManager::IsContainPausePanel(CCNode* pParent)
{
	if ( pParent == NULL )
		return false;

	CCNode* pNode = pParent->getChildByTag(kPausePanel);
	return pNode == NULL ? false : true;
}

bool SceneManager::IsContainWinFailPanel(CCNode* pParent)
{
	if ( pParent == NULL )
		return false;

	CCNode* pNode = pParent->getChildByTag(kWinFailPanel);
	return pNode == NULL ? false : true;
}

bool SceneManager::IsContainQuitPanel(CCNode* pParent)
{
	if ( pParent == NULL )
		return false;

	CCNode* pNode = pParent->getChildByTag(kQuitPanel);
	return pNode == NULL ? false : true;
}

bool SceneManager::IsContainIntroPanel(CCNode* pParent)
{
	if ( pParent == NULL )
		return false;

	CCNode* pNode = pParent->getChildByTag(kIntroPanel);
	return pNode == NULL ? false : true;
}

bool SceneManager::IsContainPearIntroPanel(CCNode* pParent)
{
	if ( pParent == NULL )
		return false;

	CCNode* pNode = pParent->getChildByTag(kPearIntroPanel);
	return pNode == NULL ? false : true;
}

void SceneManager::SetPauseState(bool PState)
{
	PauseState = PState;
}

void SceneManager::AddHelpPanel(CCNode* pParent, int z)
{
	if ( pParent == NULL )
		return;

	CCScene* scene = UIHelpPanel::scene();
	pParent->addChild(scene,z);//将帮助信息场景加载到游戏层次节点;

}

void SceneManager::JumpToNewGuide()
{
	CCScene* scene = UINewGuide::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(kSceneTransitionTime, scene));
}

void SceneManager::JumpToNewGuideNext()
{
	CCScene* scene = UINewGuideNext::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(kSceneTransitionTime, scene));
}

void SceneManager::JumpToStory(int level)
{
	CCScene* scene = UIStory::scene(level);
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(kSceneTransitionTime, scene));
}

void SceneManager::AddPearIntroPanel(CCNode* pParent, CCPoint pearPos, EPropsType propType, int z)
{
	if ( pParent == NULL )
		return;

	if ( IsContainPearIntroPanel(pParent) )
		return;

	CCScene* scene = UISpecialPropPanel::scene(pearPos, propType);
	pParent->addChild(scene, z, kPearIntroPanel);
}

void SceneManager::AddIntroducePanel(CCNode* pParent, EFruitType type, int z)
{
	if ( pParent == NULL )
		return;

	CCScene* scene = UIIntroducePanel::scene(type);
	pParent->addChild(scene, 7, kIntroPanel);
}

void SceneManager::AddQuitPanel(CCNode* pParent, int z)
{
	if ( pParent == NULL )
		return;

    CCScene* scene = UIQuitPanel::scene();
    pParent->addChild(scene, z, kQuitPanel);
}

void SceneManager::LoadXMLConfig(int bigStageID)
{
	int count = m_vLevelInfos[bigStageID-1].size(); 
	if ( count > 0 )
		return;

	char imageFullName[50] = {0};
	sprintf(imageFullName, "%s%d.xml", s_pPathConfig_Level,bigStageID);
    MyXMLParser::ParserWithFile(imageFullName, EXMLConfigType_Levels);
}

//void SceneManager::LoadVersionConfig()
//{
//	MyXMLParser::ParserWithFile(s_pPathConfig_Version, EXMLConfigType_Version);
//}

void SceneManager::LoadModeControlConfig()
{
	MyXMLParser::ParserWithFile(s_pPathConfig_Mode, EXMLConfigType_ModeControl);
}

void SceneManager::SetIsTestGameMode( bool isTest )
{
	m_bIsTestMode = isTest;

	if ( isTest )
	{
		CCDirector *pDirector = CCDirector::sharedDirector();
		pDirector->setDisplayFPS(true);
	}
}

void SceneManager::AddNewLevelConfig(LevelInfo* pLevelInfo)
{
    if ( pLevelInfo == NULL )
        return;
    std::map<int,LevelInfo*>::iterator it= m_vLevelInfos[pLevelInfo->GetBigId()-1].find(pLevelInfo->getID()); 
    if ( it != m_vLevelInfos[pLevelInfo->GetBigId()-1].end() )
        return;
    
     m_vLevelInfos[pLevelInfo->GetBigId()-1].insert(std::map<int, LevelInfo*>::value_type(pLevelInfo->getID(), pLevelInfo));
}

std::vector<int> SceneManager::GetAllLevelKeys()
{
    std::vector<int> v;
    for(std::map<int, LevelInfo*>::iterator it = m_vLevelInfos[CurBigLevelID-1].begin(); it != m_vLevelInfos[CurBigLevelID-1].end(); ++it)
    {
        v.push_back(it->first);
    }
    return v;
}

int SceneManager::GetLevelIDByIndex(int index)
{
    if ( index >= m_vLevelInfos[CurBigLevelID-1].size() )
        return -1;
    return GetAllLevelKeys()[index];
}

int SceneManager::GetLevelsCount()
{
    return m_vLevelInfos[CurBigLevelID-1].size();
}

int SceneManager::GetLevelsCountByBigID(int BigID)
{
	return m_vLevelInfos[BigID-1].size();
}

LevelInfo* SceneManager::GetLevelInfo(int levelBigID,int levelSmallID)
{
    std::map<int,LevelInfo*>::iterator it= m_vLevelInfos[levelBigID-1].find(levelSmallID); 
    if ( it == m_vLevelInfos[levelBigID-1].end() )
        return NULL;
    
    return m_vLevelInfos[levelBigID-1][levelSmallID];
}

void SceneManager::GetCurTotalScore(int score)
{
	CurTotalScore += score;//累加并保存当前得分;
}

int SceneManager::SetCurTotalScore()
{
	return CurTotalScore;
}

void SceneManager::SetPlayBackgroundMusicState()
{
	PlayBackgroundMusic = !CCUserDefault::sharedUserDefault()->getBoolForKey("PlayBackgroundMusic");
	CCUserDefault::sharedUserDefault()->setBoolForKey("PlayBackgroundMusic", PlayBackgroundMusic);
	CCUserDefault::sharedUserDefault()->flush();//这里一定要提交写入，否则不会记录到xml中，下次启动游戏你就获取不到value了;
}

bool SceneManager::GetPlayBackgroundMusicState()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("PlayBackgroundMusic", true);
}
//void SceneManager::InitWaterfallAnim(CCLayer* bg, int n)
//{
//	CCAnimation* animation = CCAnimation::animation();
//	char frameName[100] = {0};
//	for (int i = 1; i <= 10; i+=1)
//	{
//		sprintf(frameName, "Start_Waterfall%d.png", i);
//		//animation->addFrameWithFileName(frameName);
//		animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
//	}
//	for (int i = 10; i >= 1; i-=1)
//	{
//		sprintf(frameName, "Start_Waterfall%d.png", i);
//		//animation->addFrameWithFileName(frameName);
//		animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
//	}
//
//	CCAnimate *animate = CCAnimate::actionWithDuration(4.0f, animation, false);
//	CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName("Start_Waterfall1.png");
//	pSprite->setScale(CCGetScaleX());
//	pSprite->setPosition(ccp(CCGetWinSize().width*1.338f/4, CCGetWinSize().height*0.59f/4));
//	pSprite->runAction(CCRepeatForever::actionWithAction(animate));
//	bg->addChild(pSprite, n); 
//}

void SceneManager::ShowSnowEffect(CCNode* node, int z, CCPoint pos, CCPoint posVar)
{
	CCParticleSystem* m_emitter = CCParticleSnow::node();
	m_emitter->retain();
	m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage(s_pPathSnow));
	m_emitter->setPositionType(kCCPositionTypeGrouped);
	node->addChild(m_emitter,z);
	m_emitter->setLife(9);
	m_emitter->setLifeVar(1);
	m_emitter->setGravity(CCPointMake(0,-10));
	m_emitter->setSpeed(50);
	m_emitter->setSpeedVar(5);
	
	float sizeRatio = 1.0f;
	//if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
	//{
	//	m_emitter->setTotalParticles(200);
	//	sizeRatio = 2.0f/3.0f;
	//	m_emitter->setAngle(-90);
	//	m_emitter->setAngleVar(20);
	//	m_emitter->setPosition(pos);
	//	m_emitter->setPosVar(posVar);
	//}
	//else if (SceneManager::SharedSceneManager()->GetGameVersion() == EGmaeVersion_JX)
	//{
		m_emitter->setTotalParticles(50);
		sizeRatio = 1;
		m_emitter->setAngle(-120);
		m_emitter->setAngleVar(10);
		pos.x = pos.x * 4.0f / 3.0f;
		m_emitter->setPosition(pos);
		m_emitter->setPosVar(posVar);
		m_emitter->setStartSpin(360);
		m_emitter->setStartSpinVar(-720);
	//}
	//m_emitter->setAngle(0);
	ccColor4F startColor = m_emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	m_emitter->setStartColor(startColor);
	ccColor4F startColorVar = m_emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	m_emitter->setStartColorVar(startColorVar);

	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());

	float startSize = m_emitter->getStartSize();
	m_emitter->setStartSize(startSize*sizeRatio);
	float startSizeVar = m_emitter->getStartSizeVar();
	m_emitter->setStartSizeVar(startSizeVar*sizeRatio);
	float endSize = m_emitter->getEndSize();
	m_emitter->setEndSize(endSize*sizeRatio);
	float endSizeVar = m_emitter->getEndSizeVar();
	m_emitter->setEndSizeVar(endSizeVar*sizeRatio);
}

void SceneManager::ShowFlowerEffect(CCNode* node, int z, CCPoint pos, CCPoint posVar,ccTime time,CCPoint des)
{
	CCParticleSystem* m_emitter = CCParticleFlower::node();
	m_emitter->retain();
	node->addChild(m_emitter, z);
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_pPathSnow) );
	m_emitter->setIsAutoRemoveOnFinish(true);

	m_emitter->setPosition(pos);
	m_emitter->setPosVar(posVar);

	//初始和结束的颜色;
	ccColor4F startColor = m_emitter->getStartColor();
	startColor.r = 1.0f;
	startColor.g = 1.0f;
	startColor.b = 1.0f;
	m_emitter->setStartColor(startColor);
	ccColor4F startColorVar = m_emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	m_emitter->setStartColorVar(startColorVar);

	//初始和结束的大小;
	float startSize = m_emitter->getStartSize();
	m_emitter->setStartSize(startSize*2/3);
	float startSizeVar = m_emitter->getStartSizeVar();
	m_emitter->setStartSizeVar(startSizeVar*2/3);
	float endSize = m_emitter->getEndSize();
	m_emitter->setEndSize(endSize*2/3);
	float endSizeVar = m_emitter->getEndSizeVar();
	m_emitter->setEndSizeVar(endSizeVar*2/3);

	m_emitter->setLife(3.0f);

	m_emitter->setDuration(time);  //持续时间;

	CCActionInterval*  actionTo = CCMoveTo::actionWithDuration(time, des);
	m_emitter->runAction(actionTo);
}

void SceneManager::ShowFireworkEffect(CCNode* node, int z, CCPoint pos, CCPoint posVar,ccTime time)
{
	CCParticleSystem* m_emitter = CCParticleFireworks::node();
	m_emitter->retain();
	node->addChild(m_emitter, z);

	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_pPathSnow) );

	//初始和结束的颜色;
	ccColor4F startColor = m_emitter->getStartColor();
	startColor.r = 1.0f;
	startColor.g = 1.0f;
	startColor.b = 1.0f;
	startColor.a = 1.0f;
	m_emitter->setStartColor(startColor);
	ccColor4F startColorVar = m_emitter->getStartColorVar();
	startColorVar.r = 0.0f;
	startColorVar.g = 0.0f;
	startColorVar.b = 0.0f;
	startColorVar.a = 0.0f;
	m_emitter->setStartColorVar(startColorVar);
	ccColor4F endColor = m_emitter->getEndColor();
	endColor.r = 1.0f;
	endColor.g = 1.0f;
	endColor.b = 1.0f;
	endColor.a = 0.0f;
	m_emitter->setEndColor(endColor);
	ccColor4F endColorVar = m_emitter->getEndColorVar();
	endColorVar.r = 0.0f;
	endColorVar.g = 0.0f;
	endColorVar.b = 0.0f;
	endColorVar.a = 0.0f;
	m_emitter->setEndColorVar(endColorVar);

	m_emitter->setSpeed(80);
	m_emitter->setSpeedVar(20);

	m_emitter->setGravity(ccp(0,-120));

	m_emitter->setPosition(pos);
	m_emitter->setPosVar(posVar);

	m_emitter->setStartSize(10.0f);

	m_emitter->setLife(1.5f);

	m_emitter->setDuration(time);

	m_emitter->setIsAutoRemoveOnFinish(true);
	m_emitter->setIsBlendAdditive(true);
}

void SceneManager::ResumeGame( bool bPause )
{
	bkeyHomeClicked = bPause;

	if ( !bPause )
		return;

	if ( SceneManager::SharedSceneManager()->GetPauseState() )
		return;

	if ( !SceneManager::SharedSceneManager()->IsContainWinFailPanel(m_pCurLevel) &&
		!SceneManager::SharedSceneManager()->IsContainPausePanel(m_pCurLevel) &&
		!SceneManager::SharedSceneManager()->IsContainPearIntroPanel(m_pCurLevel) )
	{
		if (inGame)
			SceneManager::SharedSceneManager()->AddPausePanel(m_pCurLevel, 5);
	}
}
