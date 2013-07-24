//
//  UIStartPanel.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-22.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UISTARTPANEL_H_
#define _UISTARTPANEL_H_

#include "GameIncludeHeader.h"

class UIStartPanel: public CCLayer
{
public:
    UIStartPanel();
    virtual ~UIStartPanel();
    
    static CCScene* scene();
    virtual bool init();
    LAYER_NODE_FUNC(UIStartPanel);
    
private:
	/** 触屏按下事件的回调函数 */
    void BtnDownCallback(CCObject* pSender);
	/** 在按键上松开手指的回调函数 */
    void BtnUpInCallback(CCObject* pSender);
	/** 在按键外松开手指的回调函数 */
    void BtnUpOutCallback(CCObject* pSender);
	/** 重新实现了CCKeypadDelegate类中的物理返回键的功能 */
    virtual void keyBackClicked();
	/** 对弹出菜单初始化 */
    void InitPopupMenu();
	/** 设置弹出菜单的弹出缩回属性 */
    void DropdownMenuClick(CCSprite* topSprite, CCSprite* dropBgSprite, CCMenuItemSprite* upBtn, CCMenuItemSprite* downBtn);
	void IntroPopupFinished();
	void JniCheckUpdate();

	/** logo上散雪花效果回调 */
	void FlowerEffectCallBack();
	/** 副图标的弹性效果回调 */
	void ElasticEffectCallBack();
	/** 爆炸雪花效果回调 */
	void FireworkEffectCallBack();

	void InitCloud(CCSprite* pParent, const char* image);
	void CloudUpdate(ccTime delta);
    
private:
	CCSprite* logoSprite;         //"复仇de小猪"logo图标;
	CCSprite* sublogoSprite;      //"冰雪节版"logo图标;
	CCSprite* m_pIntroSprite;     //黄果树信息上的感叹号图标;
    CCSprite* m_pOptionSprite;    //选项按钮的齿轮图标;
    CCSprite* m_pLinkSprite;      //微博分享的三角形图标;
	CCMenuItemImage* m_pCurPopupBtn;
    
	CCSprite* m_pDropIntroSprite;    //介绍弹出菜单;
    CCSprite* m_pDropOptiontSprite;  //选项弹出菜单;
    CCSprite* m_pDropLinkSprite;     //微博弹出菜单;
    CCMenuItemSprite* m_pMusicSprite;  //声音开关（打开状态）;
    CCMenuItemSprite* m_pAboutSprite;  //制作组按钮;
    CCMenuItemSprite* m_pSinaSprite;   //分享新浪微博;
    CCMenuItemSprite* m_pTencenSprite; //分享腾讯微博;
	CCSprite* m_pNoSoundSprite;        //声音开关（关闭状态）;
	CCMenuItemSprite* m_pIntro1Sprite; //特产;
	CCMenuItemSprite* m_pIntro2Sprite; //名胜;

	CCSprite* m_pIntro1Tip;
	CCSprite* m_pIntro2Tip;

	CCSprite* m_pCloudSprite;
	CCSprite* m_pCloudSpriteRe;
};

#endif