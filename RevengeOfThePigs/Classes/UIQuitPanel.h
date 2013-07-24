//
//  UIQuitPanel.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-25.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UIQUITPANEL_H_
#define _UIQUITPANEL_H_

#include "GameIncludeHeader.h"

class UIQuitPanel : public CCLayer
{
public:
    UIQuitPanel();
    virtual ~UIQuitPanel();
    
    virtual bool init();
    static CCScene* scene();
    LAYER_NODE_FUNC(UIQuitPanel);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void onExit();
    
private:
    void BtnDownCallback(CCObject* pSender);
    void BtnUpInCallback(CCObject* pSender);
    void BtnUpOutCallback(CCObject* pSender);
    
    bool containsTouchLocation(CCTouch* pTouch);
    void RemoveSelfFromParent();
	virtual void keyBackClicked();
    
private:
    CCLayerColor* m_pBgLayerColor;
};

#endif
