#ifndef _UIFRUITINTRODUCEPANEL_H_
#define _UIFRUITINTRODUCEPANEL_H_

#include "GameIncludeHeader.h"
#include "MyCCMenu.h"
#include "SceneManager.h"

class UIIntroducePanel : public CCLayer
{
public:
	UIIntroducePanel();
	virtual ~UIIntroducePanel();

	virtual bool init();
	static CCScene* scene(EFruitType type);
	LAYER_NODE_FUNC(UIIntroducePanel);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onExit();
	void InitEx(EFruitType type);

private:
	void BtnDownCallback(CCObject* pSender);
	void BtnUpInCallback(CCObject* pSender);
	void BtnUpOutCallback(CCObject* pSender);

	virtual void keyBackClicked();

private:
	int numberIndex;
	CCSprite* pContentSprite;
	CCMenuItemSprite* pLeftBtn;
	CCMenuItemSprite* pRightBtn;
	EFruitType m_fruitType;
};

#endif