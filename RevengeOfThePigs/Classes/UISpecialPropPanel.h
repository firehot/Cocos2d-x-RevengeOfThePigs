#ifndef _UIPEARINTROPANEL_H_
#define _UIPEARINTROPANEL_H_

#include "GameIncludeHeader.h"
#include "MyCCMenu.h"
#include "Props.h"

class UISpecialPropPanel : public CCLayer
{
public:
	UISpecialPropPanel();
	virtual ~UISpecialPropPanel();

	void InitEx(CCPoint pearPos);
	virtual bool init();
	static CCScene* scene(CCPoint pearPos, EPropsType propType);
	LAYER_NODE_FUNC(UISpecialPropPanel);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onExit();

private:
	void BtnDownCallback(CCObject* pSender);
	void BtnUpInCallback(CCObject* pSender);
	void BtnUpOutCallback(CCObject* pSender);

	void ActionFunc();
	void ActionRemoveSelf();
	void RemoveSelf();

	virtual void keyBackClicked();

public:
	EPropsType m_propType;

private:
	CCSprite* pearSprite;
};

#endif