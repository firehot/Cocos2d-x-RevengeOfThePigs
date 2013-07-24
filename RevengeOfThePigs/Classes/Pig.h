//
//  Pig.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-20.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _PIG_H_
#define _PIG_H_

#include "GameIncludeHeader.h"
#include "GameResources.h"
#include "NodeBase.h"

typedef enum
{
    EPigType_Normal = 1,
    EPigType_Separate = 2,
    EPigType_Speedup = 3,
    EPigType_Bomb = 4,
	EPigType_Ice = 5,
	EPigType_Ceram = 6,
} EPigType;

typedef enum
{
    EPigState_Idle,
    EPigState_Jumping,
    EPigState_BeginFly,
    EPigState_Fly,
    EPigState_EndFly,
    EPigState_GameWinRemain,
} EPigState;

typedef void (CCObject::*DrawPointHandler)(CCSprite*);
#define drawPoint_selector(_SELECTOR) (DrawPointHandler)(&_SELECTOR)

#define kDistancePathPoints 13*CCGetScaleX()

class Pig : public NodeBase
{
public:
    Pig();
    virtual ~Pig();
    
    static Pig* CreatePig(EPigType type, b2World* world, const char* image,
                                LevelBaseEx* imageParent, const char* smashImage, CCPoint pos,
                                CCObject* pListener, DrawPointHandler handle);
    virtual EPropsType GetPropsType(){ return EPropsType_Pig; }
    
    void DrawPoint(ccTime delta);
	void EdgesJuges(ccTime delta);//判断是否超出边界;
    void SetState(EPigState state);
    EPigState GetState(){return m_state;}
    EPigType GetPigType(){ return m_type; }
    void SetDrawPathPoint(bool bDraw);
    int UpdateLogic();
    void SingleTouchBeginCallback();
    void BombTouchBeginCallback();
    void SingleTouchEndCallback();
    
    void SetPigScore(int s);
    int GetPigScore();

	void DoNothing();
	void DoNothing2();

	void PlayHitEffect();

	bool bFirstHitProps;
	bool bFirstHitGround;

protected:
    EPigState m_state;
    CCObject* m_pHandleListener;
    DrawPointHandler m_drawPointHandle;
    CCPoint m_lastPoint;
    EPigType m_type;
    bool m_bDrawPathPoint;
    bool m_bFirstPathPoint;
    
    bool bSmallPathPoint;
    int pig_score;

private:
    Pig* InitPig(EPigType type, b2World* world, const char* image,
                     LevelBaseEx* imageParent, const char* smashImage, CCPoint pos,
                     CCObject* pListener, DrawPointHandler handle);
	CCParticleSystem* CreatePigDestroyEffect( const char* image, CCPoint point, int location  );
    void DoSeparatePigSkill();
    void DoSpeedupPigSkill();
    void DoBombPigSkill();
	/** 陶瓷猪技能函数 */
	void DoCeramPigSkill();
    
    void WaitForDestroy(ccTime delta);
    void WaitForBomb(ccTime delta);
    bool bUpdated;
	bool CurPigExist;
	CCNode* node;
};

class PigWithNoBody : public CCSprite
{
public:
    PigWithNoBody();
    virtual ~PigWithNoBody();
    
    static PigWithNoBody* spriteWithFile(const char *pszFileName, EPigType type);
    
    void RandomJumpAnim(ccTime delta);
    void SetState(EPigState state);
    EPigState GetState(){ return m_pigState; }
    void SetPigType(EPigType type){ m_pigType = type; }
    EPigType GetPigType(){ return m_pigType; }
    void SetImage(std::string image){ m_sImage = image; }
    std::string GetImage(){ return m_sImage; }
private:
    EPigState m_pigState;
    EPigType m_pigType;
    std::string m_sImage;
};

#endif

