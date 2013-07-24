//
//  PropsBase.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-27.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _NODEBASE_H_
#define _NODEBASE_H_

#include "GameIncludeHeader.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "GameResources.h"
//#include "LevelBase.h"

class LevelBaseEx;
typedef enum
{
    EPropsType_Base,
    EPropsType_Pig,
    EPropsType_Wood,
    EPropsType_Grass,
	EPropsType_Ball,
	EPropsType_Balloon,
	EPropsType_Boat,
	EPropsType_Cage,
	EPropsType_EnemyA,
	EPropsType_EnemyB,
	EPropsType_EnemyC,
	EPropsType_EnemyD,
	EPropsType_EnemyE,
	EPropsType_EnemyF,
    EPropsType_Flower,
    EPropsType_Floor,
	EPropsType_LanuchPad,
	EPropsType_Glass,
    EPropsType_Lamp,//吊灯类型;
    EPropsType_Stone,
	EPropsType_PaperBox,//纸箱;
	EPropsType_WoodBox,//木箱;
	EPropsType_Fruit,
	EPropsType_SP01,    //五种特殊道具;
	EPropsType_SP02,
	EPropsType_SP03,
	EPropsType_SP04,
	EPropsType_SP05,
	EPropsType_FrozenWood,
	EPropsType_FrozenGlass,
	EPropsType_FrozenStone,
} EPropsType;

#define kMaxSmashImageCount 4
#define kMaxFrozenImageCount 4

class LevelBaseEx;
class NodeBase : public CCNode
{
public:
    NodeBase();
    virtual ~NodeBase();
    
	void CreateNodeBody(b2World* world, b2BodyDef* bodyDef, b2FixtureDef* fixtureDef,
		const char* image, LevelBaseEx* imageParent, const char* smashImage, int propsType,CCSprite *pTempSprite,const char* state,int tag,int to,int to2);
    
    CCSprite* GetSprite(){ return m_pSprite; }
    b2Body* GetBody(){ return m_pBody; }
    void ChangeSprite(const char* imageFullName);
    virtual EPropsType GetPropsType(){ return EPropsType_Base; }
    void DestroyNodeImmediately();
    
    virtual int UpdateLogic(){return 0;};
    virtual void SingleTouchBeginCallback(){};
    virtual void SingleTouchEndCallback(){};
    void ActionCallBackN(CCNode * spender);
protected:
    void PlaySmashAnim();
    void BrokenCallback();
	void FrozenBroken();
    
    b2World* m_pWorld;
    b2Body* m_pBody;
	b2Body* m_pPreBody;
    CCSprite* m_pSprite;
    LevelBaseEx* m_pSpriteParent;
    std::string m_sImage;
    std::string m_sSmashImage;   //破碎的效果资源图片;
	void RemoveSprite();
    
private:
  
    void RemoveBody();
};

#endif

