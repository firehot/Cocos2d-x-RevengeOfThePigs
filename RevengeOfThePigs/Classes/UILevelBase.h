//
//  MyBaseLevel.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-26.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UILEVELBASE_H_
#define _UILEVELBASE_H_

#include "GameIncludeHeader.h"

class UILevelBase : public CCLayer
{
public:
    UILevelBase();
    virtual ~UILevelBase();
    
    virtual bool init();
    static CCScene* scene();
    LAYER_NODE_FUNC(UILevelBase);

	void ShowChoosePigPanel(bool bShow = true);
    
private:
    void BtnDownCallback(CCObject* pSender);
    void BtnUpInCallback(CCObject* pSender);
    void BtnUpOutCallback(CCObject* pSender);
    void PreInit();
	virtual void keyBackClicked();

	void InitChoosePigPanel();
	bool CheckFinishChoosePig();
	void HideChoosePanel();
	void ShowGuideAnim();
	void HideGuideAnim();
    
protected:
    CCLabelAtlas* m_pHighestScore;
    CCLabelAtlas* m_pScore;

private:
	CCMenuItemSprite* m_pChoosePigBtn;
	CCSprite* m_pDropSprite;
	CCMenuItemSprite* m_pNormalPig;
	CCMenuItemSprite* m_pSpeedupPig;
	CCMenuItemSprite* m_pSeparatePig;
	CCMenuItemSprite* m_pBombPig;
	CCMenuItemSprite* m_pIcePig;
	CCMenuItemSprite* m_pCeramPig;
	CCSprite* m_animSprite;
	bool m_bChoosing;
};

#endif

