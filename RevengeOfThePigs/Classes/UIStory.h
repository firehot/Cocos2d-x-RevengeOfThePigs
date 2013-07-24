#ifndef _UISTORY_H_
#define _UISTORY_H_

#include "GameIncludeHeader.h"
#include "MyCCMenu.h"

class UIStory : public CCLayer
{
public:
	UIStory();
	virtual ~UIStory();

	virtual bool init();
	static CCScene* scene(int level);
	LAYER_NODE_FUNC(UIStory);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onExit();

	static int NextGameLevel;

private:
	void BtnDownCallback(CCObject* pSender);
	void BtnUpInCallback(CCObject* pSender);
	void BtnUpOutCallback(CCObject* pSender);

	void RemoveSelfFromParent();
	void AddStoryPic_Level1();
	void AddStoryPic_Level2();
	void AddStoryPic_Level3();
	void AddStoryPic_Level4();
	void AddStoryPic_Level5();
	void AddStoryPic_LevelEnd();

	MyCCMenu* m_pStoryMenu;
	CCLayerColor* m_pStoryBgLayerColor;
	CCMenuItemSprite* continueBtn;
	int iStory;                 //动画图片计数;
	float TotalDelayTime;  //总延迟时间;
	float DelayTime;       //延迟时间;
	CCSprite* m_pStoryBgSprite1;
	CCSprite* m_pStoryBgSprite2;
	CCSprite* m_pStoryBgSprite3;
	CCSprite* m_pStoryBgSprite4;
	CCSprite* m_pStoryBgSprite5;
	CCSprite* m_pStoryBgSprite6;
};

#endif