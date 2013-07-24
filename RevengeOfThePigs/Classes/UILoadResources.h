#ifndef _UILOADRESOURCES_H_
#define _UILOADRESOURCES_H_

#include "GameIncludeHeader.h"

class UILoadResources: public CCLayer
{
public:
	UILoadResources();
	virtual ~UILoadResources();

	static CCScene* scene();
	virtual bool init();
	LAYER_NODE_FUNC(UILoadResources);

	/** 预加载一些声音资源以及开始界面的背景图片loading图片 */
	void LoadBegin();
	/** 预加载声音资源以及跳转到开始界面 */
	void LoadFinished();
private:
	

private:
	CCSprite* CloudGameLogoSprite;  //开发组logo图片精灵;
	CCSprite* loading_Sprite;   //loading图片的精灵;
	CCSprite* bgSprite;        //背景图片的精灵;
	CCSprite* logoSprite;      //复仇D小猪logo精灵;
	//bool b;

};

#endif