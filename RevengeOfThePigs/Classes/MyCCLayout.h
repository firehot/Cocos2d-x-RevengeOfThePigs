//
//  MyCCLayout.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-23.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _MYCCLAYOUT_H_
#define _MYCCLAYOUT_H_

#include "cocos2d.h"
using namespace cocos2d;

#define CC_DESIGN_W (960.0f)
#define CC_DESIGN_H (640.0f)


inline float CCGetScaleX()
{
    CCSize winSize = 
    CCDirector::sharedDirector()->getWinSize();
    return winSize.width  / CC_DESIGN_W;
}


inline float CCGetScaleY()
{
    CCSize winSize = 
    CCDirector::sharedDirector()->getWinSize();
    return winSize.height / CC_DESIGN_H;
}


inline float CCGetCenterX()
{
    CCSize winSize = 
    CCDirector::sharedDirector()->getWinSize();
    return winSize.width / 2.0f;
}


inline float CCGetCenterY()
{
    CCSize winSize = 
    CCDirector::sharedDirector()->getWinSize();
    return winSize.height / 2.0f;
}


inline CCPoint CCGetCenterXY()
{
    CCSize winSize = 
    CCDirector::sharedDirector()->getWinSize();
    return ccp(winSize.width / 2.0f, winSize.height / 2.0f);
}

/** 获取屏幕尺寸 */
inline CCSize CCGetWinSize()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    return winSize;
}

#endif