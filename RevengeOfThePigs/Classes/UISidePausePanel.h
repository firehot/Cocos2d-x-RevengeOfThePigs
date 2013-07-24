//
//  UISidePausePanel.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-26.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UISIDEPAUSEPANEL_H_
#define _UISIDEPAUSEPANEL_H_

#include "GameIncludeHeader.h"
#include "MyCCMenu.h"

class UISidePausePanel : public CCLayer
{
public:
    UISidePausePanel();
    virtual ~UISidePausePanel();
    
    virtual bool init();
    static CCScene* scene(int BigLevelID,int SmallLevelID);
    LAYER_NODE_FUNC(UISidePausePanel);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void onExit();
    
private:
    void BtnDownCallback(CCObject* pSender);
    void BtnUpInCallback(CCObject* pSender);
    void BtnUpOutCallback(CCObject* pSender);
    void ActionCallBack();  //当点击暂停界面时, 设置游戏运行速度为0;    
    bool containsTouchLocation(CCTouch* pTouch);
	void BackToSmallStage();
    
    void RemoveSelfFromParent();
	virtual void keyBackClicked();
    
private:
    CCSprite* m_pBgSprite;
    MyCCMenu* m_pMenu;
    CCLayerColor* m_pBgLayerColor;
	CCMenuItemSprite* musicBtn;
	CCSprite* m_pNoSoundSprite;
};

#endif

