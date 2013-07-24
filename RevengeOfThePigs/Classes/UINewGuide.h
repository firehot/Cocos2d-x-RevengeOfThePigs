#ifndef _UINEWGUIDE_H_
#define _UINEWGUIDE_H_

#include "GameIncludeHeader.h"
#include "MyCCMenu.h"

class UINewGuide : public CCLayer
{
public:
	UINewGuide();
	virtual ~UINewGuide();

	virtual bool init();
	static CCScene* scene();
	LAYER_NODE_FUNC(UINewGuide);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onExit();

private:
	void BtnDownCallback(CCObject* pSender);
	void BtnUpInCallback(CCObject* pSender);
	void BtnUpOutCallback(CCObject* pSender);

	bool containsTouchLocation(CCTouch* pTouch);

	void RemoveSelfFromParent();
	void AddNewGuidePic();
	//void DoNothing();
	//void DoNothing2();

private:
	//CCSprite* m_pGuideBgSprite;
	MyCCMenu* m_pGuideMenu;
	CCLayerColor* m_pGuideBgLayerColor;
	CCMenuItemSprite* continueBtn;
	int i;
	float TotalDelayTime;
	float DelayTime;
	CCSprite* m_pGuideBgSprite;
	CCSprite* m_pGuideBgSprite2;
	CCSprite* m_pGuideBgSprite3;
	CCSprite* m_pGuideBgSprite4;
	CCSprite* m_pGuideBgSprite5;
	CCSprite* m_pGuideBgSprite6;
};

#endif