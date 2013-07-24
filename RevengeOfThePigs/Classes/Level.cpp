//
//  Level.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-14.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "Level.h"
#include "GameResources.h"
#include "SceneManager.h"

Level::Level(int LevelID,int BigID)
{
//	InitLevel(levelID,BigID);
	this->bigID = BigID;
	this->levelID = LevelID;
}

Level::~Level()
{
    
}

void Level::InitLevel(int LevelID,int BigID,CCTexture2D* BG1_Texture,CCTexture2D* BG2_Texture,CCTexture2D* BG3_Texture,CCTexture2D* BG4_Texture,CCTexture2D* BG5_Texture,CCTexture2D* BG6_Texture,CCTexture2D* BG7_Texture,CCTexture2D* BG8_Texture)
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(s_pPathStart_WaterfallAnim);
	//CCLayer *levelLayer=this;
	BeginInit(LevelID,BigID,this);
    
    LevelInfo* pLevelInfo = SceneManager::SharedSceneManager()->GetLevelInfo(BigID,LevelID);
    if ( pLevelInfo == NULL )
        return;
    
	SetHighestScore(pLevelInfo->GetOneStarScore(),pLevelInfo->GetTwoStarScore(),pLevelInfo->GetThreeStarScore());
    SetPigShotPos(pLevelInfo->GetShotPosX(), pLevelInfo->GetShotPosY());
    //shilin todo temp;
    SetSlingRopePoints(pLevelInfo->GetShotPosX()-10, pLevelInfo->GetShotPosY(),
                   pLevelInfo->GetShotPosX()+10, pLevelInfo->GetShotPosY());
    //
/*  获取左右橡皮条的位置;
    SetSlingRopePoints(pLevelInfo->GetRubberLeftPosX(),pLevelInfo->GetRubberLeftPosY(),
                     pLevelInfo->GetRubberRightPosX(),pLevelInfo->GetRubberRightPosY());   */
	if(BigID==1)
	{
        InitBigFourBackGroundImages(BG1_Texture,BG2_Texture,BG3_Texture,BG4_Texture,BG5_Texture,BG6_Texture,BG7_Texture,BG8_Texture);
	}
	else if(BigID==2)
	{
		InitBigFourBackGroundImages(BG1_Texture,BG2_Texture,BG3_Texture,BG4_Texture,NULL,NULL,NULL,NULL);
	}
	else if(BigID==3)
	{
		InitBigFourBackGroundImages(BG1_Texture,BG2_Texture,BG3_Texture,BG4_Texture,NULL,NULL,NULL,NULL);
	}
	else if(BigID==4)
	{
		InitBigFourBackGroundImages(BG1_Texture,BG2_Texture,BG3_Texture,BG4_Texture,BG5_Texture,BG6_Texture,BG7_Texture,BG8_Texture);
	}
	else if(BigID==5)
	{
		InitBigFourBackGroundImages(BG1_Texture,BG2_Texture,BG3_Texture,BG4_Texture,NULL,NULL,NULL,NULL);
	}
	else if ( BigID == 6 )
	{
		InitBigFourBackGroundImages(BG1_Texture,BG2_Texture,BG3_Texture,BG4_Texture,NULL,NULL,NULL,NULL);
	}
	
	//获得左边弹弓的信息并添加;
    PropsInfo* pPropsInfo = pLevelInfo->GetSlingShotL();
    if ( pPropsInfo != NULL )
        AddProps(pPropsInfo->GetImage().c_str(), pPropsInfo->GetX(), pPropsInfo->GetY(),
		pPropsInfo->GetPolygonPointX(), pPropsInfo->GetPolygonPointY(), -1000, 0, false, -1);
	//获得右边弹弓的信息并添加;
    pPropsInfo = pLevelInfo->GetSlingShotR();
    if ( pPropsInfo != NULL )
        AddProps(pPropsInfo->GetImage().c_str(), pPropsInfo->GetX(), pPropsInfo->GetY(),
		pPropsInfo->GetPolygonPointX(), pPropsInfo->GetPolygonPointY(), -1001, 0, false, -1);
    
	//获取道具信息并添加到场景中;
    std::vector<PropsInfo*> vProps = pLevelInfo->GetProps();
    std::vector<PropsInfo*>::iterator itProps;
    for ( itProps = vProps.begin(); itProps != vProps.end(); ++itProps)
    {
        PropsInfo* pProps = *itProps;
		//如果道具类型为刺梨;
		//if ( pProps->GetPropsType() == 51 )
		//{
		//	char sPearKey[16]={0};
		//	sprintf(sPearKey, "PearCount%d%d", BigID, LevelID);
		//	if ( !CCUserDefault::sharedUserDefault()->getBoolForKey(sPearKey) )
		//		AddProps(pProps->GetImage().c_str(), pProps->GetX(), pProps->GetY(), pProps->GetPolygonPointX(), pProps->GetPolygonPointY(),
		//		pProps->GetPropsType(), pProps->GetRot(),true,0,pProps->GetPropsTag(),pProps->GetPropsTo(),pProps->GetPropsTo2(),pProps->GetState().c_str());
		//}
		//else
			AddProps(pProps->GetImage().c_str(), pProps->GetX(), pProps->GetY(), pProps->GetPolygonPointX(), pProps->GetPolygonPointY(),
			pProps->GetPropsType(), pProps->GetRot(),true,0,pProps->GetPropsTag(),pProps->GetPropsTo(),pProps->GetPropsTo2(),pProps->GetState().c_str());
    }

	//获取小猪的信息并添加到场景中;
	pigsPos.clear();
	std::vector<PigInfo*> vPigs = pLevelInfo->GetPigs();
	std::vector<PigInfo*>::iterator it;
	for ( it = vPigs.begin(); it != vPigs.end(); ++it)
	{
		PigInfo* pPig = *it;
		//AddPig((EPigType)pPig->GetType(), pPig->GetImage().c_str(), pPig->GetX(), pPig->GetY());
		pigsPos.push_back(CCPointMake(pPig->GetX(), pPig->GetY()));
	}
	ShowChoosePigPanel();
	
    EndInit();
}

void Level::ChoosePig(EPigType pigType)
{
	if (pigsPos.size() <= 0)
		return;

	string pigImage;
	switch (pigType)
	{
	case EPigType_Normal:
		{
			pigImage = "NormalPig";
			break;
		}
	case EPigType_Speedup:
		{
			pigImage = "SpeedPig";
			break;
		}
	case EPigType_Separate:
		{
			pigImage = "NinjaPig";
			break;
		}
	case EPigType_Bomb:
		{
			pigImage = "BombPig";
			break;
		}
	case EPigType_Ice:
		{
			pigImage = "FreezePigIce";
			break;
		}
	case EPigType_Ceram:
		{
			pigImage = "CeramPig";
			break;
		}
	default:
		return;
	}

	std::vector<CCPoint>::iterator it = pigsPos.begin();
	CCPoint pos = *it;
	pigsPos.erase(it);

	AddPig(pigType, pigImage.c_str(), pos.x, pos.y);

	if (pigsPos.size() <= 0)
	{
		m_pLevelEx->PositionNextPig();
		m_pLevelEx->ShowOperateGuideAnim(true);
	}
}

void Level::onEnter()
{
	CCLayer::onEnter();
	SceneManager::SharedSceneManager()->inGame = true;
}

void Level::onExit()
{
	CCLayer::onExit();
	SceneManager::SharedSceneManager()->inGame = false;
}



