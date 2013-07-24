//
//  MyCCMenu.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-22.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "MyCCMenu.h"
#include "SimpleAudioEngine.h"
#include "GameResources.h"
#include "SceneManager.h"

MyCCMenu::MyCCMenu()
: m_pDownHandle(NULL)
, m_pUpInHandle(NULL)
, m_pUpOutHandle(NULL)
{
    
}

MyCCMenu::~MyCCMenu()
{
    
}

bool MyCCMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    if (m_eState != kCCMenuStateWaiting || ! m_bIsVisible)
    {
        return false;
    }
    
    for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
    {
        if (c->getIsVisible() == false)
        {
            return false;
        }
    }
    
    m_pSelectedItem = this->itemForTouch(touch);
    if (m_pSelectedItem)
    {
        m_eState = kCCMenuStateTrackingTouch;
        m_pSelectedItem->selected();
        if ( m_pHandleListener != NULL && m_pDownHandle )
        {
            (m_pHandleListener->*m_pDownHandle)(m_pSelectedItem);   //将选中的菜单项指针传递给触屏按下事件的回调函数;
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathMenu_Confirm, false);
			}			
        }
        return true;
    }
    return false;
}

void MyCCMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
    if (m_pSelectedItem)
    {
        m_pSelectedItem->unselected();
        m_pSelectedItem->activate();
        if ( m_pHandleListener != NULL && m_pUpInHandle )
        {
            (m_pHandleListener->*m_pUpInHandle)(m_pSelectedItem);    //如果有被选中的项那么将该项的指针传递给事件函数;
        }
    }
    m_eState = kCCMenuStateWaiting;
}

void MyCCMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
    CCMenuItem *currentItem = this->itemForTouch(touch);
    if (currentItem != m_pSelectedItem) 
    {
        if (m_pSelectedItem)
        {
            m_pSelectedItem->unselected();
            if ( m_pHandleListener != NULL && m_pUpOutHandle )          //添加在手指移出当前按键的处理事件;
            {
                (m_pHandleListener->*m_pUpOutHandle)(m_pSelectedItem);    
            }
        }
        m_pSelectedItem = currentItem;
        if (m_pSelectedItem)
        {
            m_pSelectedItem->selected();
            if ( m_pHandleListener != NULL && m_pDownHandle )          //添加手指移到新按键上的处理事件;
            {
                (m_pHandleListener->*m_pDownHandle)(m_pSelectedItem);
            }
        }
    }
}

void MyCCMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
    if (m_pSelectedItem)
    {
        m_pSelectedItem->unselected();
        if ( m_pHandleListener != NULL && m_pUpOutHandle )
        {
            (m_pHandleListener->*m_pUpOutHandle)(m_pSelectedItem);
        }
    }
    m_eState = kCCMenuStateWaiting;
}

MyCCMenu * MyCCMenu::menuWithItems(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    MyCCMenu *pRet = new MyCCMenu();
    if (pRet && pRet->initWithItems(item, args))
    {
        pRet->autorelease();
        va_end(args);
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet)
    return NULL;
}

MyCCMenu* MyCCMenu::menuWithItem(CCMenuItem* item)
{
    return menuWithItems(item, NULL);
}

void MyCCMenu::SetDownUpHandle(CCObject* pTarget, SEL_MenuHandler downHandle, SEL_MenuHandler upInHandle, SEL_MenuHandler upOutHandle)
{
    m_pHandleListener = pTarget;
    m_pDownHandle = downHandle;
    m_pUpInHandle = upInHandle;
    m_pUpOutHandle = upOutHandle;
}




