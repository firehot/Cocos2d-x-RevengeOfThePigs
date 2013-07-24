//
//  Props.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-28.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "Props.h"
#include "SceneManager.h"
#include "Level.h"

Props* Props::CreateProps(b2World* world, const char* image, LevelBaseEx* imageParent,
	const char* smashImage, const char* brokenImage, CCPoint pos, float rot,std::vector<float> vx, std::vector<float> vy,int propsType,const char* state,int tag,int to,int to2)
{
    Props* props = new Props();
    props->autorelease();
    
    return props->InitProps(world, image, imageParent, smashImage, brokenImage, pos, rot,vx,vy,propsType,state,tag,to,to2);
}

Props* Props::InitProps(b2World* world, const char* image, LevelBaseEx* imageParent,
	const char* smashImage, const char* brokenImage, CCPoint pos, float rot,std::vector<float> vx, std::vector<float> vy,int prosType,const char* state,int tag,int to,int to2)
{
    m_sBrokenImage = brokenImage;
    
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;   //该类型的物体能够被完全模拟，会受到力的作用并发生碰撞;
	bodyDef.position.Set(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
    bodyDef.angle = CC_DEGREES_TO_RADIANS(rot);
	
    char imageFullName[50] = {0};
    sprintf(imageFullName, "%s.png", image);
	CCSprite *pTempSprite = NULL;
	if ( SceneManager::SharedSceneManager()->GetCurLevel()->GetBigLevelID() <= 6/* && SceneManager::SharedSceneManager()->GetCurLevel()->GetLevelID() < 4*/)
		pTempSprite = CCSprite::spriteWithSpriteFrameName(imageFullName);
	else
		pTempSprite = CCSprite::spriteWithFile(imageFullName);
	b2PolygonShape dynamicBox;  //多边形形状;
    b2CircleShape dynamicBox2;  //圆形形状;
	if ( vx.size() > 0 && vx.size() == vy.size() )
	{
		if ( vx.size() == 1 && vx[0] == 0 && vy[0] == 0 ) //circle
		{
			dynamicBox2.m_radius = pTempSprite->getContentSize().width*CCGetScaleX()/2/PTM_RATIO;
		}
		else //polygon
		{
			int pointsNum = vx.size();
			b2Vec2 *vertices = new b2Vec2[pointsNum];
			for ( int i = 0; i < pointsNum; ++i )
			{
				vertices[i].Set(vx[i]*CCGetScaleX()/PTM_RATIO, vy[i]*CCGetScaleY()/PTM_RATIO);
			}
			dynamicBox.Set(vertices, pointsNum);
			delete[] vertices;
		}
	}
    else if(prosType == 77)   //等腰三角形;
    {
        b2Vec2 vertices[3];
        vertices[0].Set(pTempSprite->getContentSize().width/2*CCGetScaleX()/PTM_RATIO, (-1)*pTempSprite->getContentSize().height/2*CCGetScaleY()/PTM_RATIO);
        vertices[1].Set(0.0f,pTempSprite->getContentSize().height/2*CCGetScaleX()/PTM_RATIO);
        vertices[2].Set((-1)*pTempSprite->getContentSize().width/2*CCGetScaleX()/PTM_RATIO, (-1)*pTempSprite->getContentSize().height/2*CCGetScaleY()/PTM_RATIO);
        dynamicBox.Set(vertices, 3);

    }
	//else if(prosType == 100 || prosType == 101 || prosType == 102)//圆;
	//{               
 //       dynamicBox2.m_radius = pTempSprite->getContentSize().width*CCGetScaleX()/2/PTM_RATIO;
 //   }
	else if(prosType == 99) //直角三角形，直角在左下角;
	{
        b2Vec2 vertices[3];
        vertices[0].Set(pTempSprite->getContentSize().width/2*CCGetScaleX()/PTM_RATIO, (-1)*pTempSprite->getContentSize().height/2*CCGetScaleY()/PTM_RATIO);
        vertices[1].Set((-1)*pTempSprite->getContentSize().width/2*CCGetScaleX()/PTM_RATIO,pTempSprite->getContentSize().height/2*CCGetScaleX()/PTM_RATIO);
        vertices[2].Set((-1)*pTempSprite->getContentSize().width/2*CCGetScaleX()/PTM_RATIO, (-1)*pTempSprite->getContentSize().height/2*CCGetScaleY()/PTM_RATIO);
        dynamicBox.Set(vertices, 3);
    }
	//如果没有定义多边形顶点，则物理形状默认为图片大小的矩形框;
	else//四方形;
	{
		dynamicBox.SetAsBox(pTempSprite->getContentSize().width/2*CCGetScaleX()/PTM_RATIO,
			pTempSprite->getContentSize().height/2*CCGetScaleX()/PTM_RATIO,
			b2Vec2(0, 0), 0);
	}
    
	b2FixtureDef fixtureDef;
    fixtureDef.restitution = 0.0;  //恢复可以使对象弹起，0表示不会弹起，称为非弹性碰撞，1表示以相同速度反弹，称为完全弹性碰撞;
	fixtureDef.friction = 1.0f;    //摩擦;

    if ( vx.size() == 1 && vx[0] == 0 && vy[0] == 0 ) //circle
	    fixtureDef.shape = &dynamicBox2;
    else //polygon
        fixtureDef.shape = &dynamicBox;

	if (prosType == 2 || prosType == 602)//草;
	{
		fixtureDef.density = 0.4f;  //密度;		
	}
	else if (prosType == 3 || prosType ==603)//木块;
	{
		fixtureDef.density = 0.6f;
	}
	else if(prosType == 100 || prosType == 101 || prosType == 102) //球;
	{
		fixtureDef.density = 0.6f;
		fixtureDef.restitution = 0.5f;
	}
	else if(prosType == 103)    //气球;
	{
		fixtureDef.density = 0.1f;
		bodyDef.gravityScale = 0.0f;   //让气球浮起来;
	}
	else if(prosType == 104 || prosType == 105)  //龙舟;
	{

	}
	else if(prosType == 106) //笼子;
	{
		fixtureDef.density = 2.0f;
	}
	else if (prosType == 6)//花;
	{
		fixtureDef.density = 0.4f;
	}
	else if (prosType == 7)//根道具，质量设大点;
	{
		fixtureDef.density = 20.0f;
	}
	else if (prosType == 11)//纸箱;
	{
		fixtureDef.density = 0.4f;//0.6f;
	}
	else if (prosType == 13)//木箱;
	{
		fixtureDef.density = 1.5f;
	}
	else if (prosType == 15 || prosType == 615)//玻璃;
	{
		fixtureDef.density = 0.7f;
	}
	else if(prosType == 33 || prosType == 633) //石头;
	{   
		fixtureDef.density = 3.0f;
	}	
	else if (prosType == 50)//水果;
	{
		fixtureDef.density = 0.2f;
	}
	else if (prosType == 200)//悬挂道具(链条);
	{
		fixtureDef.density = 22.0f;
		fixtureDef.friction = 0.2f;
	}
	else if(prosType == 21 || prosType == 22 || prosType == 23)   //敌方鸟角色;
    {
        fixtureDef.density = 0.3f;
    }
	else //普通道具;
	{
		fixtureDef.density = 0.6f;
	}
	
    CreateNodeBody(world, &bodyDef, &fixtureDef, image, imageParent, smashImage, prosType,pTempSprite,state,tag,to,to2);
    return this;
}

void Props::DecreaseLife(float deltaLife)
{
    m_fCurLife -= deltaLife;
    bUpdated = true;
}

int Props::UpdateLogic()
{
    if ( !bUpdated )
        return 0;
    bUpdated = false;
    
    float ratio = m_fCurLife/(m_fMaxLife+0.0000001f);
    if ( ratio <= 0 )
    {
		node=m_pSpriteParent->GetLevelParent()->getChildByTag(1000);
		b2Vec2 prop_position = SceneManager::SharedSceneManager()->GetPropsDestroyPosition();
		float a=prop_position.x*36;
		float b=prop_position.y*40;
		if(this->GetPropsType() == EPropsType_EnemyA || this->GetPropsType() == EPropsType_EnemyB ||this->GetPropsType() == EPropsType_EnemyC ||this->GetPropsType() == EPropsType_EnemyD ||this->GetPropsType() == EPropsType_EnemyE ||this->GetPropsType() == EPropsType_EnemyF)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//鸟消失的音效;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsBird_destroy, false);
			}
			m_pSpriteParent->RemoveLockEnemy();
			//if (this->GetPropsType() == EPropsType_EnemyA)
			//{
			//	for (int i=0;i<8;i++)
			//	{
			//		CreateDestroyEffect(s_pPathBirdFragment1, CCPointMake(a,b), i);
			//	}
			//}
			//else if (this->GetPropsType() == EPropsType_EnemyB)
			//{
			//	for (int i=0;i<8;i++)
			//	{
			//		CreateDestroyEffect(s_pPathBirdFragment2, CCPointMake(a,b), i);
			//	}
			//}
			//else if (this->GetPropsType() == EPropsType_EnemyC)
			//{
			//	for (int i=0;i<8;i++)
			//	{
			//		CreateDestroyEffect(s_pPathBirdFragment3, CCPointMake(a,b), i);
			//	}
			//}
			//else if (this->GetPropsType() == EPropsType_EnemyD)
			//{
			//	for (int i=0;i<8;i++)
			//	{
			//		CreateDestroyEffect(s_pPathBirdFragment4, CCPointMake(a,b), i);
			//	}
			//}
			//else if (this->GetPropsType() == EPropsType_EnemyE)
			//{
			//	for (int i=0;i<8;i++)
			//	{
			//		CreateDestroyEffect(s_pPathBirdFragment5, CCPointMake(a,b), i);
			//	}
			//}
			//else if (this->GetPropsType() == EPropsType_EnemyF)
			//{
			//	for (int i=0;i<8;i++)
			//	{
			//		CreateDestroyEffect(s_pPathBirdFragment6, CCPointMake(a,b), i);
			//	}
			//}
			PlaySmashAnim();
// 			if(SceneManager::SharedSceneManager()->GetZero())
// 			  m_pSpriteParent->LevelIsWin();
			return 5000;
		}
		else if(this->GetPropsType() == EPropsType_Flower)
        {
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//花草碰撞及消失的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsPlant_coll, false);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsPlant_break, false);
			}
            PlaySmashAnim();
            return 300;
        }
		else if(this->GetPropsType() == EPropsType_Grass)
        {
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//花草碰撞及消失的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsPlant_coll, false);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsPlant_break, false);
			}
             PlaySmashAnim();
             return 100;
        }
		else if(this->GetPropsType() == EPropsType_Fruit || this->GetPropsType() == EPropsType_SP01 ||
			this->GetPropsType() == EPropsType_SP02 || this->GetPropsType() == EPropsType_SP03 ||
			this->GetPropsType() == EPropsType_SP04 || this->GetPropsType() == EPropsType_SP05)
		{
			PlaySmashAnim();
			
			if (this->GetPropsType() == EPropsType_SP01 ||
				this->GetPropsType() == EPropsType_SP02 || this->GetPropsType() == EPropsType_SP03 ||
				this->GetPropsType() == EPropsType_SP04 || this->GetPropsType() == EPropsType_SP05)
			{
				if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
				{
					//刺梨消失的音效;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathPearAttached, false);
				}
				int bigLevelID = SceneManager::SharedSceneManager()->GetCurLevel()->GetBigLevelID();
				int smallLevelID = SceneManager::SharedSceneManager()->GetCurLevel()->GetLevelID();
				char string[16]={0};
				sprintf(string, "PearCount%d%d", bigLevelID, smallLevelID);
				CCUserDefault::sharedUserDefault()->setBoolForKey(string, true);
				CCUserDefault::sharedUserDefault()->flush();
				return 5000;
			}

			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//水果碰撞及消失的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsPlant_coll, false);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsPlant_break, false);
			}

			return 200;
		}
		else if(this->GetPropsType() == EPropsType_Wood)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//木头消失的音效;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWood_destroy, false);
			}
			//for (int i=0;i<8;i++)
			//{
			//	CreateDestroyEffect(s_pPathWoodFragment1, CCPointMake(a,b), i);
			//}
			PlaySmashAnim();
			return 500;
		}
		else if(this->GetPropsType() == EPropsType_Glass)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//玻璃消失的音效;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_destroy, false);
			}
			//for (int i=0;i<8;i++)
			//{
			//	CreateDestroyEffect(s_pPathGlassFragment1, CCPointMake(a,b), i);
			//}
			PlaySmashAnim();
			return 500;
		}
		else if(this->GetPropsType() == EPropsType_Stone)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//石头消失的音效;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsStone_destroy, false);
			}
			PlaySmashAnim();
			return 450;
		}
		else if (this->GetPropsType() == EPropsType_PaperBox)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//纸箱消失的音效;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWood_destroy, false);
			}
			PlaySmashAnim();
			return 300;
		}
		else if (this->GetPropsType() == EPropsType_WoodBox)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//木箱消失的音效;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWood_destroy, false);
			}
			//for (int i=0;i<8;i++)
			//{
			//	CreateDestroyEffect(s_pPathWoodFragment1, CCPointMake(a,b), i);
			//}
			PlaySmashAnim();
			return 600;
		}
		// 气球被击中销毁;
		else if(this->GetPropsType() == EPropsType_Balloon)
		{
			PlaySmashAnim();
			return 100;
		}
		else if(this->GetPropsType() == EPropsType_Lamp)
		{
			//PlaySmashAnim();
			char imageFullName[50] = {0};
			sprintf(imageFullName, "%s_%d.png", m_sBrokenImage.c_str(), 1);
			m_pSprite->initWithSpriteFrameName(imageFullName);
			return 0;
		}
		else if(this->GetPropsType() == EPropsType_FrozenWood)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//冰冻木头破碎的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsStone_destroy, false);
			}
			PlaySmashAnim();
			return 500;
		}
		else if(this->GetPropsType() == EPropsType_FrozenGlass)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//冰冻玻璃破碎的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsStone_destroy, false);
			}
			PlaySmashAnim();
			return 500;
		}
		else if(this->GetPropsType() == EPropsType_FrozenStone)
		{
			if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
			{
				//冰冻石头破碎的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsStone_destroy, false);
			}
			PlaySmashAnim();
			return 450;
		}
    }
    else if ((this->GetPropsType() == EPropsType_Wood || this->GetPropsType() == EPropsType_Stone || this->GetPropsType() == EPropsType_Glass || this->GetPropsType() == EPropsType_PaperBox || this->GetPropsType() == EPropsType_WoodBox)&& ratio <= kPropsBreakage2 )
    {
		//if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		//{
		//	if (this->GetPropsType() == EPropsType_Wood)
		//	{
		//		//木头破损的音效;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWood_damage, false);
		//	}
		//	else if (this->GetPropsType() == EPropsType_Stone)
		//	{
		//		//石头破损的音效;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsStone_damage, false);
		//	}
		//	else if(this->GetPropsType() == EPropsType_Glass)
		//	{
		//		//玻璃;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_damage, false);;
		//	}
		//	else if(this->GetPropsType() == EPropsType_PaperBox)
		//	{
		//		//纸箱;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_damage, false);;
		//	}
		//	else if(this->GetPropsType() == EPropsType_WoodBox)
		//	{
		//		//木箱;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_damage, false);;
		//	}
		//}
        char imageFullName[50] = {0};
        sprintf(imageFullName, "%s_%d.png", m_sBrokenImage.c_str(), 2);

		m_pSprite->initWithSpriteFrameName(imageFullName);
		return 0;
    }
    else if (( this->GetPropsType() == EPropsType_Wood || this->GetPropsType() == EPropsType_Stone|| this->GetPropsType() == EPropsType_Glass || this->GetPropsType() == EPropsType_PaperBox || this->GetPropsType() == EPropsType_WoodBox)&&ratio <= kPropsBreakage1 )
    {
		//if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		//{
		//	if (this->GetPropsType() == EPropsType_Wood)
		//	{
		//		//木头破损的音效;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWood_damage, false);
		//	}
		//	else if (this->GetPropsType() == EPropsType_Stone)
		//	{
		//		//石头破损的音效;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsStone_damage, false);
		//	}
		//	else if(this->GetPropsType() == EPropsType_Glass)
		//	{
		//		//玻璃;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_damage, false);;
		//	}
		//	else if(this->GetPropsType() == EPropsType_PaperBox)
		//	{
		//		//纸箱;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_damage, false);;
		//	}
		//	else if(this->GetPropsType() == EPropsType_WoodBox)
		//	{
		//		//木箱;
		//		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_damage, false);;
		//	}
		//}
        char imageFullName[50] = {0};
        sprintf(imageFullName, "%s_%d.png", m_sBrokenImage.c_str(), 1);

		m_pSprite->initWithSpriteFrameName(imageFullName);
		return 0;
    }  
	//替换冰冻资源;/////////////////////////////////////////////////////////////////
	else if((this->GetPropsType() == EPropsType_FrozenWood || this->GetPropsType() == EPropsType_FrozenGlass || this->GetPropsType() == EPropsType_FrozenStone) && ratio > 0)
	{
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			if (this->GetPropsType() == EPropsType_FrozenWood)
			{
				//木头冰冻的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsWood_damage, false);
			}
			else if (this->GetPropsType() == EPropsType_FrozenStone)
			{
				//石头冰冻的音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsStone_damage, false);
			}
			else if(this->GetPropsType() == EPropsType_FrozenGlass)
			{
				//冰冻玻璃音效;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsGlass_damage, false);;
			}
		}
		char imageFullName[50] = {0};
		//尾数为3的为冰冻效果图;
		sprintf(imageFullName, "%s_%d.png", m_sBrokenImage.c_str(), 3);
		m_pSprite->initWithSpriteFrameName(imageFullName);
		return 0;
	}
	return 0;
}

CCParticleSystem* Props::CreateDestroyEffect( const char* image, CCPoint point, int location )
{
	return NULL;
	CCParticleSystem* effect = CCParticleFireworks::node();
	effect->setPosition(point);
	effect->setTexture(CCTextureCache::sharedTextureCache()->addImage(image));
	effect->setTotalParticles(1.0f);
	effect->setLife(2.0f);
	effect->setLifeVar(0.5);
	effect->setGravity(CCPointMake(0, -30));
	effect->setDuration(0.5);//延迟时间;
	ccColor4F color = {1,1,1,1};
	ccColor4F colorVar = {0,0,0,0};
	effect->setStartColor(color);
	effect->setStartColorVar(colorVar);
	effect->setEndColor(color);
	effect->setIsAutoRemoveOnFinish(true);
	effect->setEndColorVar(colorVar);
	effect->setStartSize(7);
	effect->setEndSize(2);
	if ( location == 0 ) 
	{
		effect->setSpeed(20);
		effect->setSpeedVar(2);
		effect->setStartSpin(90);
		effect->setAngle(0);
	}
	else if ( location == 1 ) 
	{
		effect->setSpeed(10);
		effect->setSpeedVar(2);
		effect->setStartSpin(-90);
		effect->setAngle(45);
	}
	else if ( location == 2 )
	{
		effect->setSpeed(30);
		effect->setSpeedVar(2);
		effect->setStartSpin(45);
		effect->setAngle(90);
	}
	else if ( location == 3 )
	{
		effect->setSpeed(10);
		effect->setSpeedVar(2);
		effect->setStartSpin(-45);
		effect->setAngle(135);
	}
	else if ( location == 4 )
	{
		effect->setSpeed(10);
		effect->setSpeedVar(2);
		effect->setStartSpin(30);
		effect->setAngle(180);
	}
	else if ( location == 5 )
	{
		effect->setSpeed(10);
		effect->setSpeedVar(2);
		effect->setStartSpin(-30);
		effect->setAngle(225);
	}
	else if ( location == 6 )
	{
		effect->setSpeed(20);
		effect->setSpeedVar(2);
		effect->setStartSpin(60);
		effect->setAngle(270);
	}
	else if ( location == 7 )
	{
		effect->setSpeed(10);
		effect->setSpeedVar(2);
		effect->setStartSpin(-60);
		effect->setAngle(315);
	}
	effect->setPositionType(kCCPositionTypeRelative);
	node->addChild(effect, 10);

	return effect;
}

float Props::GetCurLife()
{
	return m_fCurLife;
}

void Props::FrozenStone()
{
	char imageFullName[50] = {0};
	sprintf(imageFullName, "%s_%d.png", m_sBrokenImage.c_str(), 2);
	m_pSprite->initWithSpriteFrameName(imageFullName);
	this->SetPropsType(EPropsType_Stone);
}

void Props::FrozenPropsBroken(CCNode* temp)
{
	Props* props = (Props*)temp;
	props->DecreaseLife(100);
}
