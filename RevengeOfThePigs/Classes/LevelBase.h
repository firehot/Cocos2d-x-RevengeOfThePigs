//
//  LevelBase.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-3;
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _LEVELBASE_H_
#define _LEVELBASE_H_

#include "GameIncludeHeader.h"
#include "UILevelBase.h"
#include "Box2D/Box2D.h"
//#include "GLES-Render.h"
#include "GameContactListener.h"
#include "Pig.h"

#define PTM_RATIO 32
#define MaxSlingLength (40.0f*CCGetScaleX())
#define MaxSlingRopeWidth (10.0f*CCGetScaleX())
#define MinSlingRopeWidth (4.0f*CCGetScaleX())
#define KCurPigTag 10001

typedef enum
{
	ESlingShotMoveDir_Left,
	ESlingShotMoveDir_Mid,
	ESlingShotMoveDir_Right
} ESlingShotMoveDir;

typedef enum
{
	ESlingShotMoveTo_ToLeft,
	ESlingShotMoveTo_FromLeft,
	ESlingShotMoveTo_ToRight,
	ESlingShotMoveTo_FromRight
} ESlingShotMoveTo;

class LevelBase;
class LevelBaseEx : public CCLayer
{
public:
    LevelBaseEx(CCLayer *layer);
    virtual ~LevelBaseEx();
    
    virtual void draw();
	/** 猪发射的触摸区域 */
	bool containsTouchLocation( CCPoint touchPos );
	/** 改变大炮的角度 */
	bool containsAngleLocation( CCPoint touchPos );
	/** 猪发射的恢复区域 */
	bool containsRecoverLocation( CCPoint touchPos );
    void TouchBegin(CCPoint touchPos);
    void TouchMoved(CCPoint touchPos);
    void TouchEnd(CCPoint touchPos);
    bool IsCurPigTouched();
	bool IsGunCtrlTouched();
    
    void Run();
	/** 设置第二层的地面背景 */
	void SetBackGround(CCTexture2D* Texture);
    void AddPig(EPigType pigType, const char* image, CCPoint pos);
    void AddProps(const char* image, CCPoint pos, std::vector<float> vx, std::vector<float> vy, int propsType, float rot, bool bHasGravity, int z,int tag,int to,int to2,const char* state);
    void SetPigShotPos(CCPoint pos);
    void SetSlingRopePoints(CCPoint posLeft, CCPoint posRight);
    void AddFlyPathPoint(CCSprite* pSprite);
    void ClearFlyPathPoints();
	int GetLockEnemyCount() {return m_LockEnemys->count();}
	void RemoveLockEnemy() {m_LockEnemys->removeLastObject();}
	void LevelIsWin();
	void LevelIsLose();
	bool GetPigZero() {return pigZero;}
    void CalculatePigScore(ccTime delta);  //计算剩余鸟得分数;
    void GameWin(ccTime delta);    //延迟几秒调用结束画面;
	void GameLose(ccTime delta);
	void SetLevelParent(LevelBase* m_Leve){m_LevelBase = m_Leve;};
	LevelBase* GetLevelParent(){return m_LevelBase;};

	/** 将下一只猪放到弹弓上 */
	void PositionNextPig();
	void ShowOperateGuideAnim(bool bHide);

	CCLayer *UILayer;
	int disCount;
protected:
    void InitScene();
    void SetReadyShotState();
    CCRect rectInPixels( CCSprite *pSprite );
    CCPoint GetSlingScreenPos();
    void Update(ccTime delta);
	void UILevelFinish(bool win);
	void CountScore(ccTime delta);
    void HighestScore(ccTime delta);
    void ScoreShow(ccTime delta);
	void ScoreAnim(b2Vec2 force,b2Vec2 pos,int score);  
	void WaitforDiaplayWinFailUI();
	void ActionDisplayFailPanel();
	/** 显示片尾动画 */
	//void ShowEndStory();
	ESlingShotMoveDir GetSlingShotMoveDir();
	//void DoSlingShotAnim( ESlingShotMoveDir toDir );
	//void DoSlingShotAnimEx( ESlingShotMoveTo moveTo );
    
private:
    CCSprite* m_pBg;
	bool isLevelFinish;
    PigWithNoBody* m_pCurPigWithNoBody;
    CCArray* m_vPigs;   //等待上弹弓的猪;
	CCArray* m_vPigs2;  //所有的猪;
	CCArray* m_LockEnemys;
	bool pigZero;
    CCSprite* m_pSling;
    bool m_bPigTouched;
	bool m_bGunCtrlTouched;   //是否触摸改变大炮角度的区域;
	CCPoint curShotPos;       //大炮发射口的位置;
    
    b2World* m_pWorld;
    //GLESDebugDraw* m_pDebugDraw;
    
    CCPoint m_pigShotPos;
    CCArray* m_vFlyPathPoints;
    
    GameContactListener* m_pContactListener;
    
    std::vector<CCPoint> m_vSlingPoints;
    float m_fSlingRopeWidth;

	CCLabelAtlas* m_pCurScoreLabel;
	CCLabelAtlas* m_pHighestScoreLabe;
	int m_iCurScore;     
	int m_iTotalScore;
	int m_iHighestScores;   
	int m_iHighestCurScore;

    bool b_update;
    int PigNumber;  //剩余鸟的数量;
	LevelBase* m_LevelBase;  // 游戏道具的显示;
	bool newrecord;
    int b_scores;
    float b_posX;
    float b_posY;

	//sling shot anim
	ESlingShotMoveDir curSlingShotDir;
	CCSprite* pLeftSlingShot;
	CCSprite* pRightSlingShot;

	bool bCanShotPig;
	CCSprite* m_operateGuideSprite;
};

class LevelBase : public UILevelBase
{
public:
    LevelBase();
    virtual ~LevelBase();
    /** 主要对游戏的运行逻辑初始化，构建物理世界以及碰撞监听等，以及获取最高分数 */
    void BeginInit(int SmallLevelID,int BigLevelID,CCLayer* cc);

    void EndInit();
	/** 初始化背景图片 */
	void InitBigFourBackGroundImages(CCTexture2D* BG1_Texture,CCTexture2D* BG2_Texture,CCTexture2D* BG3_Texture,CCTexture2D* BG4_Texture,CCTexture2D* BG5_Texture,CCTexture2D* BG6_Texture,CCTexture2D* BG7_Texture,CCTexture2D* BG8_Texture);
	/** 添加猪 */
    void AddPig(EPigType pigType, const char* image, float x, float y);
	/** 添加道具 */
    void AddProps(const char* image, float x, float y, std::vector<float> vx, std::vector<float> vy, int propsType = -1, float rot = 0, bool bHasGravity = true, int z = 0,int tag=0,int to=0,int to2=0,const char* state="");
	/** 设置小猪的发射点 */
    void SetPigShotPos(float x, float y);

    void SetSlingRopePoints(float posLeftX, float posLeftY, float posRightX, float posRightY);
	/** 通过函数间的传递，获取本关设置的三个阶段分值 */
	void SetHighestScore(int score1,int score2,int score3);
    
    virtual void registerWithTouchDispatcher();
	//virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	//virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	//virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	//virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    
    void BeginZoom(CCPoint pos1, CCPoint pos2);
    void MoveZoom(CCPoint pos1,CCPoint pos1_pre,CCPoint pos2,CCPoint pos2_pre);

    void InitCloud(CCSprite* pParent, const char* image);
    void CloudUpdate(ccTime delta);

    //touch move;
    void TouchMoveLeft(ccTime delta);
    void TouchMoveRight(ccTime delta);
    void TouchMoveLeftBack(ccTime delta);
    void TouchMoveRightBack(ccTime delta);

public:
	LevelBaseEx* m_pLevelEx;  //用于处理游戏逻辑功能的类;

private:
    float m_fFirstLen;
	float PigShotPoint_x;
	float PigShotPoint_y;
    int CurBigStageID;

    //cloud scroll;
    CCSprite* m_pSpriteCloudParent;
    CCSprite* m_pCloudSprite;
    CCSprite* m_pCloudSpriteRe;
    //

    //touch move;
    CCPoint diff;
};

#endif