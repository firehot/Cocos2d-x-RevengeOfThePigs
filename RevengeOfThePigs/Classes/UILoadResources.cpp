#include "UIStartPanel.h"
#include "MyCCMenu.h"
#include "UIBgLightLayer.h"
#include "SimpleAudioEngine.h"
#include "GameResources.h"
#include "SceneManager.h"
#include "UILoadResources.h"

UILoadResources::UILoadResources()
{
	//b = true;
}

UILoadResources::~UILoadResources()
{

}

CCScene* UILoadResources::scene()
{
	CCScene * scene = NULL;
	do 
	{
		//scene是自动释放的对象;
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		//layer是自动释放的对象;
		UILoadResources *layer = UILoadResources::node();  //在初始化的时候调用init函数;
		CC_BREAK_IF(! layer);

		//将层（layer）作为一个子对象添加给场景（scene）;
		scene->addChild(layer);
	} while (0);

	return scene;
}

bool UILoadResources::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CloudGameLogoSprite=CCSprite::spriteWithFile(s_pPathCloudGameLogo);
	CloudGameLogoSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	CloudGameLogoSprite->setScale(CCGetScaleX());
	this->addChild(CloudGameLogoSprite,3);
	
	/** 将logo图片显示出来后延迟0.5秒将logo图片最小化最后调用LoadBegin函数 */
	CloudGameLogoSprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.5f),
		CCScaleTo::actionWithDuration(0, 0),
		CCCallFunc::actionWithTarget(this, callfunc_selector(UILoadResources::LoadBegin)),
		NULL));
		
	return true;
}

void UILoadResources::LoadBegin()
{
	//背景音乐的预加载;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(s_pPathBackGround_Music);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(s_pPathLevel1_BackGround);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(s_pPathLevel2_BackGround);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(s_pPathLevel3_BackGround);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(s_pPathLevel4_BackGround);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(s_pPathLevel5_BackGround);
	//音效的预加载;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathMenu_Confirm);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathSound_Fire);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathSound_Rotate);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathScene1Intro);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathScene2Intro);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathScene3Intro);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathSpecialty1Intro);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathSpecialty2Intro);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathSpecialty3Intro);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel1_Begin);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel3_Begin);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsWinStar_1);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsWinStar_2);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsWinStar_3);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathNewRecord);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel1_Win);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel2_Win);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel3_Win);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel4_Win);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel5_Win);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel1_Lose);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel2_Lose);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel3_Lose);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel4_Lose);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathLevel5_Lose);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsGlass_destroy);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsStone_destroy);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsWood_destroy);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathPearAttached);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsPlant_break);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsBird_destroy);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathScoreRolling);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathNormalPig_destroy);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathNormalPig_jump);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathNormalPig_coll);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathNormalPig_fly);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsSeparatePig_coll);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsSeparatePig_nimpo);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsSpeedUpPig_coll);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsSpeedUpPig_fly);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsExplosionPig_coll);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsExplosionPig_explosion);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathsExplosionPig_fly);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(s_pPathIcePig_Fly);


	this->removeChild(CloudGameLogoSprite,true);  //删除之前的logo资源;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	bgSprite = CCSprite::spriteWithFile(s_pPathScene_StartBackDrop);    //背景;
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	bgSprite->setScaleX(CCGetScaleX());
	bgSprite->setScaleY(CCGetScaleY());
	this->addChild(bgSprite, 0);

	//if ( SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ )
	//	logoSprite = CCSprite::spriteWithFile(s_pPathStartPanel_GameLogo);
	//else
		logoSprite = CCSprite::spriteWithFile(s_pPathStartPanel_GameLogo);
	logoSprite->setPosition(ccp(winSize.width/2, CCGetWinSize().height - logoSprite->getContentSize().height*CCGetScaleX()/2)); 
	logoSprite->setScale(CCGetScaleX());
	this->addChild(logoSprite, 2);

	loading_Sprite = CCSprite::spriteWithFile(s_pPathLoading);
	loading_Sprite->setPosition(ccp(winSize.width/2,winSize.height*14/40));
	loading_Sprite->setScale(CCGetScaleX()*1.0f);
	this->addChild(loading_Sprite,3);
	
	loading_Sprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.1f),
		CCScaleTo::actionWithDuration(1.0f, 0),
		CCCallFunc::actionWithTarget(this, callfunc_selector(UILoadResources::LoadFinished)),
		NULL));
	
}

void UILoadResources::LoadFinished()
{

	//加载图片资源;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathPigs_PigsList);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathBirds_BirdsList);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathProps_PropsList);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathVersion_SpList);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathDispearFogList);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathEffect_BombFogList);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathEffect_SteamFogList);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_pPathEffect_GunSmokeList);


	this->removeChild(bgSprite,true);
	this->removeChild(logoSprite,true);
	this->removeChild(loading_Sprite,true);
	SceneManager::SharedSceneManager()->JumpToStartPanel();
}
