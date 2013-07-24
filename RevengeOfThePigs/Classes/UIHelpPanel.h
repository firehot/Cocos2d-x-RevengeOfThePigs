#ifndef _UIHELPPANEL_H_
#define _UIHELPPANEL_H_

#include "GameIncludeHeader.h"
#include "MyCCMenu.h"

class UIHelpPanel : public CCLayer
{
public:
	UIHelpPanel();
	virtual ~UIHelpPanel();

	virtual bool init();
	static CCScene* scene();
	LAYER_NODE_FUNC(UIHelpPanel);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onExit();

private:
	void BtnDownCallback(CCObject* pSender);
	void BtnUpInCallback(CCObject* pSender);
	void BtnUpOutCallback(CCObject* pSender);

	bool containsTouchLocation(CCTouch* pTouch);

	void EndAnimationCallback();

	void RemoveSelfFromParent();
	virtual void keyBackClicked();

private:
	CCSprite* m_pHelpBgSprite;
	MyCCMenu* m_pHelpMenu;
	CCLayerColor* m_pHelpBgLayerColor;
	int n;
	CCMenuItemSprite* continueBtn;
	CCMenuItemSprite* nextPicBtn;
};

#endif