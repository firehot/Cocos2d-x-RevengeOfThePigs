//
//  SceneManager.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-9.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "cocos2d.h"
#include "GameElementStruct.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "GameResources.h"
#include "Props.h"

using namespace cocos2d;

#define kSceneTransitionTime 0.3f
#define kPausePanel 90001
#define kWinFailPanel 90002
#define kQuitPanel 90003
#define kIntroPanel 90004
#define kPearIntroPanel 90005

typedef enum
{
	EFruitType_Pear,
	EFruitType_HGS,
	EFruitType_Design,
} EFruitType;

//typedef enum
//{
//	EGameVersion_BXJ=1, //冰雪节版;
//	EGameVersion_SZ=2, //深圳高校版;
//	EGameVersion_HGS=3, //黄果树版;
//	EGmaeVersion_JX=4,  //江西版;
//} EGameVersion;

//void PreLoadSound(void *);
class Level;
class SceneManager
{
public:
    static SceneManager* SharedSceneManager();
    
    void Init();

	/** 跳转到选择大关界面; */
    void JumpToSelectBigStage();
	/** 跳转到开始界面; */
    void JumpToStartPanel();
	/** 根据大关ID跳转到小关选择界面 */
    void JumpToSelectSmallStage(int BigLevelID);
	/** 根据小关ID跳转到游戏界面; */
    void JumpToGameLevel(int levelID);
	/** 跳转到新手引导界面; */
	void JumpToNewGuide();
	/** 跳转到第二张新手引导界面 */
	void JumpToNewGuideNext();
	/** 跳转到过场动画 */
	void JumpToStory(int level);
	/** 跳转到下一大关的第一小关 */
	void JumpToNextStage(int BigLevelID);
	/** 初始化背景图片 */
	bool InitBackGround(int BigLevelID);
    
	void AddPearIntroPanel(CCNode* pParent, CCPoint pearPos, EPropsType propType, int z = 0);
	void AddIntroducePanel(CCNode* pParent, EFruitType type, int z = 0);
    void AddQuitPanel(CCNode* pParent, int z = 0);
    void AddBattleResultPanel(CCNode* pParent, bool bWin, int z=0,int stars=0,int score=0,bool newrecord=false);
//    void AddBattleResultPanel2(CCNode* pParent, bool bWin, int z , int stars , int score );
    void AddPausePanel(CCNode* pParent, int z = 0);
	void AddHelpPanel(CCNode* pParent, int z = 0);
    void LoadXMLConfig(int bigStageID); 
	/** 创建背景瀑布的动画; */
   /* void InitWaterfallAnim(CCLayer* bg,int n);*/
    void AddNewLevelConfig(LevelInfo* pLevelInfo);
    std::vector<int> GetAllLevelKeys();
    int GetLevelIDByIndex(int index);
	/** 获取当前大关卡的小关卡数 */
	int GetLevelsCount();
	/** 根据传入的大关卡参数获得小关卡数 */
	int GetLevelsCountByBigID(int BigID);
	void GetCurTotalScore(int score);
	int SetCurTotalScore();
    LevelInfo* GetLevelInfo(int levelSmallID,int levelBigId);
	void SetPauseState(bool PauseState);
	bool GetPauseState(){return PauseState;};
	void SetPlayBackgroundMusicState();
	/** 从数据库中读取声音设置状态; */
	bool GetPlayBackgroundMusicState();
	void SetPigFlyState(bool state){PigFlyState = state;}//设定小鸟飞行状态;
	bool GetPigFlyState(){return PigFlyState;}//获取小鸟飞行状态;
//道具连接所需修改;
	void SavePropsBody(b2Body* boy){m_pPreBody = boy;}
	b2Body* GetPropsBody(){return m_pPreBody;}
	void SetGroundBody(b2Body* boy){groundBody = boy;}
	b2Body* GetGroundBody(){return groundBody;}
	
	void SaveTag1Body(b2Body* boy){m_pTag1Body = boy;}
	b2Body* GetTag1Body(){return m_pTag1Body;}
	void SaveTag2Body(b2Body* boy){m_pTag2Body = boy;}
	b2Body* GetTag2Body(){return m_pTag2Body;}
//结束;
	Level* GetCurLevel(){ return m_pCurLevel; }
	void SetPreSoundFinishedState(bool f){LoadSoundFinished = f;}
	bool GetPreSoundFinishedState(){return LoadSoundFinished;}
	//HANDLE Get_hThread(){return hThread;}
//传递道具坐标;
	void SetPropsDestroyPosition(b2Vec2 p){prop_Vec = p;}
	b2Vec2 GetPropsDestroyPosition(){return prop_Vec;}

	bool IsContainPausePanel(CCNode* pParent);
	bool IsContainWinFailPanel(CCNode* pParent);
	bool IsContainQuitPanel(CCNode* pParent);
	bool IsContainIntroPanel(CCNode* pParent);
	bool IsContainPearIntroPanel(CCNode* pParent);

	/** 背景下雪效果; */;
	void ShowSnowEffect(CCNode* node, int z, CCPoint pos, CCPoint posVar);
	/** logo散雪效果; */;
	void ShowFlowerEffect(CCNode* node, int z, CCPoint pos, CCPoint posVar,ccTime time,CCPoint des);
	/** 雪花爆炸效果; */;
	void ShowFireworkEffect(CCNode* node, int z, CCPoint pos,CCPoint posVar,ccTime time);

	void ResumeGame( bool bPause );

	//void LoadVersionConfig();
	//void SetGameVersion( EGameVersion version ) { m_curVersion = version; }
	//EGameVersion GetGameVersion() { return m_curVersion; }

	void LoadModeControlConfig();
	void SetIsTestGameMode( bool isTest );
	bool IsTestGameMode() { return m_bIsTestMode; }
public:
	int m_iCurLevel;
	CCNode* playscene;
	int CurBigLevelID;   //声明大关卡的ID,从JumpToSelectSmallStage()函数中获取;
	int CurTotalScore;
	bool PauseState;
	bool PlayBackgroundMusic;
	bool PigFlyState;
	b2Body* m_pPreBody;
	b2Body* m_pTag1Body;
	b2Body* m_pTag2Body;
	b2Body* groundBody;
	CCSprite *pTempSprite;
	b2Vec2* Vec;
	b2Vec2 prop_Vec;

	bool LoadSoundFinished;
	//HANDLE hThread;
	CCTexture2D* BG1_Texture;    //4层地面背景;
	CCTexture2D* BG2_Texture;
	CCTexture2D* BG3_Texture;
	CCTexture2D* BG4_Texture;

	CCTexture2D* BG5_Texture;    //4张背景动画;
	CCTexture2D* BG6_Texture;
	CCTexture2D* BG7_Texture;
	CCTexture2D* BG8_Texture;
    void SetZero(bool Zero){isZero = Zero;}
	bool GetZero(){return isZero;}
	bool bCheckedUpdate;
	bool bkeyHomeClicked;

	bool inGame;

private:
    SceneManager();

	Level* m_pCurLevel;    //当前关卡的对象;
    static SceneManager* m_pSceneManager;  //唯一的一个对象;
    std::map<int,LevelInfo*> m_vLevelInfos[6]; 
	bool isZero;    //地上的小猪为0;
	//EGameVersion m_curVersion;
	bool m_bIsTestMode;
};

#endif
