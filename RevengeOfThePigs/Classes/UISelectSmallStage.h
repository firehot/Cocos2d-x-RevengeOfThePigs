//
//  UISelectSmallStage.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-23.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UISELECTSMALLSTAGE_H_
#define _UISELECTSMALLSTAGE_H_

#include "GameIncludeHeader.h"
#include "CCScrollLayer.h"

#define kMaxLevelAPage 15

class MyCCMenu;

class UISelectSmallStage : public CCLayer, public CCScrollLayerDelegate
{
public:
    UISelectSmallStage();
    virtual ~UISelectSmallStage();
    
    virtual bool init();
    static CCScene* scene(int BigLevelID);
    LAYER_NODE_FUNC(UISelectSmallStage);
    
    void InitScrollView();
    MyCCMenu* InitScrollViewPage(int BigStageId, int page );
    
    virtual void scrollLayerScrollingStarted(CCScrollLayer* sender);
    virtual void scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page);
	
	void JumpToGameLevel();
    
private:
    void BtnDownCallback(CCObject* pSender);
    void BtnUpInCallback(CCObject* pSender);
    void BtnUpOutCallback(CCObject* pSender);
    
    void HideLeftRightBtn();
	virtual void keyBackClicked();
    
    CCMenuItemSprite* m_pLeftBtn;
    CCMenuItemSprite* m_pRightBtn;
    
    int m_curLevelIndex;

	CCMenuItem* pBtnDown;
	CCSprite* loading_Sprite;

	static int CurBigLevelID;    //声明一个用来存放大关卡ID的整形变量;
	int page;  //关卡页数;
};

#endif
