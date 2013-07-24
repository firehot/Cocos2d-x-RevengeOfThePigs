//
//  MyCCMenu.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-22.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _MYCCMENU_H_
#define _MYCCMENU_H_

#include "GameIncludeHeader.h"
#include "CCObject.h"

class MyCCMenu : public CCMenu
{
public:
    MyCCMenu();
    virtual ~MyCCMenu();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);  //该事件在正常触摸手指离开时触发;
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event); //该事件在非正常触摸完触发，比如在触摸过程中被电话中断;
    
    static MyCCMenu* menuWithItems(CCMenuItem* item, ...);
    static MyCCMenu* menuWithItem(CCMenuItem* item);
    
	/** 设置触摸按下和松开时间函数的指针 */
    void SetDownUpHandle(CCObject* pTarget, SEL_MenuHandler downHandle, SEL_MenuHandler upInHandle, SEL_MenuHandler upOutHandle);
    
private:
    CCObject* m_pHandleListener;     //触摸监控，保存接受触摸层的指针;
    SEL_MenuHandler m_pDownHandle;   //触屏按下事件的函数指针;
    SEL_MenuHandler m_pUpInHandle;   //触屏在按键上松开事件的函数指针;
    SEL_MenuHandler m_pUpOutHandle;  //触屏在按键外松开事件的函数指针;
};

#endif

