//
//  UIWinFailPanel.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-26.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UIWINFAILPANEL_H_
#define _UIWINFAILPANEL_H_

#include "GameIncludeHeader.h"

class UIWinFailPanel : public CCLayer
{
public:
    UIWinFailPanel();
    virtual ~UIWinFailPanel();
    
    void InitWinLayout( int stars, int score, int bestScore, bool bHasNextStage );
    void InitFailLayout( const char* stageImage, bool bHasNextStage );
    virtual bool init();
    static CCScene* scene( bool bWin, int stars, int score,int CurBigLevelID,bool newrecord,bool bHasNextStage);
    static UIWinFailPanel* layer();
    LAYER_NODE_FUNC(UIWinFailPanel);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void onExit();
    
private:
    void BtnDownCallback(CCObject* pSender);
    void BtnUpInCallback(CCObject* pSender);
    void BtnUpOutCallback(CCObject* pSender);
    
    bool containsTouchLocation(CCTouch* pTouch);
	/** 初始化输赢界面按键 */
    void InitButtons( bool bHasNextStage, bool IsWin);
    void RemoveSelfFromParent();
    void PopStarLFinishedCallback();
    void PopStarMFinishedCallback();
    void PopStarRFinishedCallback();
	void NewRecordCallback();
	void PlayNewRecordSound();
    
    CCParticleSystem* CreateWinStarEffect( const char* image, CCPoint point, int location  );
    
    void CountScore(ccTime delta);

	virtual void keyBackClicked();
    
private:
    CCLayerColor* m_pBgLayerColor;
    CCLabelAtlas* m_pScoreLabel;
    CCSprite* m_lStarBgSprite;
    CCSprite* m_mStarBgSprite;
    CCSprite* m_rStarBgSprite;
    int m_iCurScore;
    int m_iTotalScore;
    int m_iStarsCount;

};

#endif

