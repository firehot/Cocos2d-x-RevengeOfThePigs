//
//  Props.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-28.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _PROPS_H_
#define _PROPS_H_

#include "GameIncludeHeader.h"
#include "NodeBase.h"
#include "LevelBase.h"

#define kPropsBreakage1 0.9f
#define kPropsBreakage2 0.2f


class Props : public NodeBase
{
public:
    Props():m_fCurLife(0),m_fMaxLife(0),bUpdated(false),m_propsType(EPropsType_Wood),bBreak1State(false),bBreak2State(false){};
    virtual ~Props(){};
    
	static Props* CreateProps(b2World* world, const char* image, LevelBaseEx* imageParent,
		const char* smashImage, const char* brokenImage, CCPoint pos, float rot,std::vector<float> vx, std::vector<float> vy, int prosType,const char* state,int tag,int to,int to2);
    
    virtual EPropsType GetPropsType(){ return m_propsType; }
    void SetPropsType(EPropsType type){ m_propsType = type; }
    void SetMaxLife(float life){ m_fMaxLife = life; m_fCurLife = life; }
    void DecreaseLife(float deltaLife);
    int UpdateLogic();
	float GetCurLife();
	void FrozenPropsBroken(CCNode*);
	void FrozenStone();
    
private:
	Props* InitProps(b2World* world, const char* image, LevelBaseEx* imageParent,
		const char* smashImage, const char* brokenImage, CCPoint pos, float rot,std::vector<float> vx, std::vector<float> vy, int prosType,const char* state,int tag,int to,int to2);
    CCParticleSystem* CreateDestroyEffect( const char* image, CCPoint point, int location  );
    float m_fMaxLife;
    float m_fCurLife;
    std::string m_sBrokenImage;
    bool bUpdated;
    EPropsType m_propsType;
	bool bBreak1State;
	bool bBreak2State;
	CCNode* node;
};

#endif

