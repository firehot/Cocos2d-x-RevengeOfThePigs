//
//  UISelectBigStage.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-23.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UISELECTBIGSTAGE_H_
#define _UISELECTBIGSTAGE_H_

#include "GameIncludeHeader.h"
#include "CCScrollLayer.h"

class UISelectBigStage : public CCLayer, public CCScrollLayerDelegate
{
public:
    UISelectBigStage();
    virtual ~UISelectBigStage();
    
    virtual bool init();
    static CCScene* scene();
    LAYER_NODE_FUNC(UISelectBigStage);
    
	/** 初始化滚动卷轴上的显示 */
    void InitScrollView();
	/** 根据选择的大关跳至小关选择界面 */
	void JumpToSmallSelected();

	virtual void scrollLayerScrollingStarted(CCScrollLayer* sender);
	virtual void scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page);
    
private:
    void BtnDownCallback(CCObject* pSender);
    void BtnUpInCallback(CCObject* pSender);
    void BtnUpOutCallback(CCObject* pSender);
	virtual void keyBackClicked();
	void HideLeftRightBtn();
	CCMenuItemImage* pBtn_Down;
	CCMenuItemSprite* m_pLeftBtn;
	CCMenuItemSprite* m_pRightBtn;
};

#endif
