//
//  Level.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-13.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "LevelBase.h"

class Level : public LevelBase
{
public:
	/** Level类继承自LevelBase，LevelBase继承自UILevelBase，
		所以在构造Level类的时候会将游戏界面的暂停和重来按钮生成出来 */
    Level(int levelID,int BigID);
    virtual ~Level();
	/** 关卡初始化 */
	void InitLevel(int levelID,int BigID,CCTexture2D* BG1_Texture,CCTexture2D* BG2_Texture,CCTexture2D* BG3_Texture,CCTexture2D* BG4_Texture,CCTexture2D* BG5_Texture=NULL,CCTexture2D* BG6_Texture=NULL,CCTexture2D* BG7_Texture=NULL,CCTexture2D* BG8_Texture=NULL);
	int GetBigLevelID(){ return bigID; }
	int GetLevelID(){return levelID;}

	void ChoosePig(EPigType pigType);
	int GetRemainChoosePigCount() { return pigsPos.size(); }

	virtual void onEnter();
	virtual void onExit();
private:
   // void InitLevel(int levelID,int BigID);
	int bigID;
	int levelID;

	std::vector<CCPoint> pigsPos;
};

#endif
