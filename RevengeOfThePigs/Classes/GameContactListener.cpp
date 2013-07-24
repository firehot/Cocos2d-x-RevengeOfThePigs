//
//  GameContactListener.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-23;
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "GameContactListener.h"
#include "Props.h"
#include "Pig.h"
#include "SceneManager.h"

GameContactListener::GameContactListener()
{
    
}

GameContactListener::~GameContactListener()
{
    
}

void GameContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	NodeBase* nodeBaseA = (NodeBase*)bodyA->GetUserData();
	NodeBase* nodeBaseB = (NodeBase*)bodyB->GetUserData();
	if(nodeBaseA!= NULL && nodeBaseB!= NULL)
	{
		if((nodeBaseA->GetPropsType() == EPropsType_Flower ||nodeBaseA->GetPropsType() ==EPropsType_Fruit /*|| nodeBaseA->GetPropsType() == EPropsType_SP01*/)  &&
			(nodeBaseB->GetPropsType() == EPropsType_Pig || nodeBaseB->GetPropsType() == EPropsType_Wood ||nodeBaseB->GetPropsType() == EPropsType_Glass))
		{
			Props* props = (Props*)nodeBaseA;
			props->DecreaseLife(1);
		}
		if((nodeBaseA->GetPropsType() == EPropsType_Pig || nodeBaseA->GetPropsType() == EPropsType_Wood ||nodeBaseA->GetPropsType() == EPropsType_Glass)&&
			(nodeBaseB->GetPropsType() == EPropsType_Flower || nodeBaseB->GetPropsType() == EPropsType_Fruit /*|| nodeBaseA->GetPropsType() == EPropsType_SP01*/))
		{
			Props* props = (Props*)nodeBaseB;
			props->DecreaseLife(1);
		}
		if(nodeBaseA->GetPropsType() == EPropsType_Grass &&(nodeBaseB->GetPropsType() == EPropsType_Pig || nodeBaseB->GetPropsType() == EPropsType_Wood ||nodeBaseB->GetPropsType() == EPropsType_Glass))
		{
			Props* props = (Props*)nodeBaseA;
			props->DecreaseLife(1);
		}
		if(nodeBaseB->GetPropsType() == EPropsType_Grass &&(nodeBaseA->GetPropsType() == EPropsType_Pig || nodeBaseA->GetPropsType() == EPropsType_Wood ||nodeBaseA->GetPropsType() == EPropsType_Glass))
		{
			Props* props = (Props*)nodeBaseB;
			props->DecreaseLife(1);
		}
		if(nodeBaseA->GetPropsType() == EPropsType_Pig && nodeBaseB->GetPropsType() == EPropsType_Wood)
		{
			Props* props = (Props*)nodeBaseB;
			Pig* pig = (Pig*)nodeBaseA;
			props->DecreaseLife(1);
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() > 0))
			{
				props->SetPropsType(EPropsType_FrozenWood);
			}
		}
		if(nodeBaseB->GetPropsType() == EPropsType_Pig && nodeBaseA->GetPropsType() == EPropsType_Wood)
		{
			Props* props = (Props*)nodeBaseA;
			Pig* pig = (Pig*)nodeBaseB;
			props->DecreaseLife(1);
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() > 0))
			{
				props->SetPropsType(EPropsType_FrozenWood);
			}
		}
		if(nodeBaseA->GetPropsType() == EPropsType_Pig && nodeBaseB->GetPropsType() == EPropsType_Glass)
		{
			Props* props = (Props*)nodeBaseB;
			Pig* pig = (Pig*)nodeBaseA;
			props->DecreaseLife(1);
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() > 0))
			{
				props->SetPropsType(EPropsType_FrozenGlass);
			}
		}
		if(nodeBaseB->GetPropsType() == EPropsType_Pig && nodeBaseA->GetPropsType() == EPropsType_Glass)
		{
			Props* props = (Props*)nodeBaseA;
			Pig* pig = (Pig*)nodeBaseB;
			props->DecreaseLife(1);
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() > 0))
			{
				props->SetPropsType(EPropsType_FrozenGlass);
			}
		}
		if(nodeBaseA->GetPropsType() == EPropsType_Pig && nodeBaseB->GetPropsType() == EPropsType_Stone)
		{
			Props* props = (Props*)nodeBaseB;
			Pig* pig = (Pig*)nodeBaseA;
			props->DecreaseLife(1);
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() > 0))
			{
				props->SetPropsType(EPropsType_FrozenStone);
			}
		}
		if(nodeBaseB->GetPropsType() == EPropsType_Pig && nodeBaseA->GetPropsType() == EPropsType_Stone)
		{
			Props* props = (Props*)nodeBaseA;
			Pig* pig = (Pig*)nodeBaseB;
			props->DecreaseLife(1);
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() > 0))
			{
				props->SetPropsType(EPropsType_FrozenStone);
			}
		}
		if(nodeBaseA->GetPropsType() == EPropsType_Balloon && (nodeBaseB->GetPropsType() == EPropsType_Pig || nodeBaseB->GetPropsType() == EPropsType_Wood || nodeBaseB->GetPropsType() == EPropsType_Stone))
		{
			Props* props = (Props*)nodeBaseA;
			props->DecreaseLife(2);
		}
		if(nodeBaseB->GetPropsType() == EPropsType_Balloon && (nodeBaseA->GetPropsType() == EPropsType_Pig || nodeBaseA->GetPropsType() == EPropsType_Wood || nodeBaseA->GetPropsType() == EPropsType_Stone))
		{
			Props* props = (Props*)nodeBaseB;
			props->DecreaseLife(2);
		}
	}

}

void GameContactListener::EndContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	NodeBase* nodeBaseA = (NodeBase*)bodyA->GetUserData();
	NodeBase* nodeBaseB = (NodeBase*)bodyB->GetUserData();
	if(nodeBaseA != NULL && nodeBaseB != NULL)
	{
		if(nodeBaseA->GetPropsType() == EPropsType_Pig && (nodeBaseB->GetPropsType() == EPropsType_FrozenGlass || 
			nodeBaseB->GetPropsType() == EPropsType_FrozenWood /*|| nodeBaseB->GetPropsType() == EPropsType_FrozenStone*/)){
				Pig* pig = (Pig*)nodeBaseA;
				Props* props = (Props*)nodeBaseB;
				if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() >= 0))
				{
					props->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(2.0f),
						CCCallFuncN::actionWithTarget(props, callfuncN_selector(Props::FrozenPropsBroken)),
						NULL));
				}
		}
		if(nodeBaseB->GetPropsType() == EPropsType_Pig && (nodeBaseA->GetPropsType() == EPropsType_FrozenGlass || 
			nodeBaseA->GetPropsType() == EPropsType_FrozenWood /*|| nodeBaseA->GetPropsType() == EPropsType_FrozenStone*/)){
				Props* props = (Props*)nodeBaseA;
				Pig* pig = (Pig*)nodeBaseB;
				if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() >= 0))
				{
					props->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(2.0f),
						CCCallFuncN::actionWithTarget(props, callfuncN_selector(Props::FrozenPropsBroken)),
						NULL));
				}
		}
		if(nodeBaseA->GetPropsType() == EPropsType_Pig && nodeBaseB->GetPropsType() == EPropsType_FrozenStone)
		{
			Pig* pig = (Pig*)nodeBaseA;
			Props* props = (Props*)nodeBaseB;
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() >= 0))
			{
				props->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(2.0f),
					CCCallFunc::actionWithTarget(props, callfunc_selector(Props::FrozenStone)),
					NULL));
			}
		}
		if(nodeBaseB->GetPropsType() == EPropsType_Pig && nodeBaseA->GetPropsType() == EPropsType_FrozenStone)
		{
			Pig* pig = (Pig*)nodeBaseB;
			Props* props = (Props*)nodeBaseA;
			if((pig->GetPigType() == EPigType_Ice) && (props->GetCurLife() >= 0))
			{
				props->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(2.0f),
					CCCallFunc::actionWithTarget(props, callfunc_selector(Props::FrozenStone)),
					NULL));
			}
		}
	}
}

void GameContactListener::PreSolve(b2Contact* contact, 
                                 const b2Manifold* oldManifold)
{
    
     
}

void GameContactListener::PostSolve(b2Contact* contact, 
                                  const b2ContactImpulse* impulse)
{
	int count = contact->GetManifold()->pointCount;

    float maxNormalImpulse = 0.0f;
    //float maxTangentImpulse = 0.0f;
    for ( int i = 0; i < count; ++i )
    {
        maxNormalImpulse=b2Max(maxNormalImpulse,impulse->normalImpulses[i]);
        //maxTangentImpulse=b2Max(maxTangentImpulse,impulse->tangentImpulses[i]);
    }
    //if ( maxImpulse > 10.0f )
    
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();
        NodeBase* nodeBaseA = (NodeBase*)bodyA->GetUserData();
        NodeBase* nodeBaseB = (NodeBase*)bodyB->GetUserData();

        //pig & pig
        if ( nodeBaseA != NULL && nodeBaseB != NULL && nodeBaseA->GetPropsType() == nodeBaseB->GetPropsType()
            && nodeBaseA->GetPropsType() == EPropsType_Pig )
            return;
        //grass & grass
        if ( nodeBaseA != NULL && nodeBaseB != NULL && nodeBaseA->GetPropsType() == nodeBaseB->GetPropsType()
            && nodeBaseA->GetPropsType() == EPropsType_Grass )
            return;
        //grass & ground
        if ( bodyA != NULL && bodyA != NULL &&
            ((nodeBaseA != NULL && nodeBaseA->GetPropsType() == EPropsType_Grass && nodeBaseB == NULL) ||
            (nodeBaseB != NULL && nodeBaseB->GetPropsType() == EPropsType_Grass && nodeBaseA == NULL)) )
            return;

        if ( nodeBaseA != NULL )
        {
            if ( nodeBaseA->GetPropsType() == EPropsType_Wood || nodeBaseA->GetPropsType() == EPropsType_WoodBox) //|| nodeBaseA->GetPropsType() == EPropsType_Stone || nodeBaseA->GetPropsType() == EPropsType_Glass;
            {
                if(nodeBaseB != NULL && nodeBaseB->GetPropsType()==EPropsType_Pig)
                {
                    float a=maxNormalImpulse*1000;
                    int b=a;
                    Pig* pig = (Pig*)nodeBaseB;
                    Props* props = (Props*)nodeBaseA;
                    
                    if(pig->GetPigType()== EPigType_Speedup)   //加速猪;
                       if(maxNormalImpulse>0.20){    
						   props->DecreaseLife(2.0);
					   }
                    if(a>150)
                    {
                        pig->SetPigScore(b);
                    }     
                }
            }else if(nodeBaseA->GetPropsType() == EPropsType_Glass|| nodeBaseA->GetPropsType() == EPropsType_PaperBox)
            {
                if(nodeBaseB != NULL && nodeBaseB->GetPropsType()==EPropsType_Pig)
                {
                    float a=maxNormalImpulse*1000;
                    int b=a;
                    Pig* pig = (Pig*)nodeBaseB;
                    Props* props = (Props*)nodeBaseA;

                    if(pig->GetPigType()== EPigType_Separate)   //分身猪;
                        if(maxNormalImpulse>0.18)    
                            props->DecreaseLife(1.2);
                    if(a>150)
                    {
                        pig->SetPigScore(b);
                    }     
                }
            }
			//else if(nodeBaseA->GetPropsType() == EPropsType_Stone)
   //         {
   //             if(nodeBaseB != NULL && nodeBaseB->GetPropsType()==EPropsType_Pig)
   //             {
   //                 float a=maxNormalImpulse*1000;
   //                 int b=a;
   //                 Pig* pig = (Pig*)nodeBaseB;
   //                 Props* props = (Props*)nodeBaseA;

   //                 if(pig->GetPigType()== EPigType_Bomb)   //爆炸猪;
   //                     if(maxNormalImpulse>0.8)    
   //                         props->DecreaseLife(5.0);
   //                 if(a>150)
   //                 {
   //                     pig->SetPigScore(b);
   //                 }  
   //              }
   //         }


            if (nodeBaseA->GetPropsType() == EPropsType_SP01 ||
				nodeBaseA->GetPropsType() == EPropsType_SP02 ||
				nodeBaseA->GetPropsType() == EPropsType_SP03 ||
				nodeBaseA->GetPropsType() == EPropsType_SP04 ||
				nodeBaseA->GetPropsType() == EPropsType_SP05)   //|| nodeBaseA->GetPropsType() == EPropsType_Grass ;
            {
                
                if(maxNormalImpulse>0.2f)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(maxNormalImpulse);
                } 
                
            }
			else if (nodeBaseA->GetPropsType() == EPropsType_Flower ||nodeBaseA->GetPropsType() == EPropsType_Grass|| nodeBaseA->GetPropsType() == EPropsType_Lamp)
			{
				if(maxNormalImpulse>0.6)
				{
					Props* props = (Props*)nodeBaseA;
					props->DecreaseLife(1.25);
				}else if(maxNormalImpulse>0.5)
				{
					Props* props = (Props*)nodeBaseA;
					props->DecreaseLife(maxNormalImpulse);
				}
			}
			else if(nodeBaseA->GetPropsType() == EPropsType_Wood|| nodeBaseA->GetPropsType() == EPropsType_WoodBox){
                if(maxNormalImpulse>0.6)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(1.25);
                }else if(maxNormalImpulse>0.5)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(maxNormalImpulse);
                }
            }else if( nodeBaseA->GetPropsType() == EPropsType_Glass|| nodeBaseA->GetPropsType() == EPropsType_PaperBox ){
                if(maxNormalImpulse>0.5)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(1.0);
                }else if(maxNormalImpulse>0.4)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(maxNormalImpulse);
                }
            }
            else if(nodeBaseB->GetPropsType() == EPropsType_EnemyA||nodeBaseB->GetPropsType() ==EPropsType_EnemyB||nodeBaseB->GetPropsType() ==EPropsType_EnemyC||nodeBaseB->GetPropsType() ==EPropsType_EnemyD||nodeBaseB->GetPropsType() ==EPropsType_EnemyE||nodeBaseB->GetPropsType() ==EPropsType_EnemyF)
            {
                if(maxNormalImpulse>0.1f)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(maxNormalImpulse);
                }
            }else if(nodeBaseA->GetPropsType() == EPropsType_Stone)
            {
                if(maxNormalImpulse>3.0)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(5.0);
                }else if(maxNormalImpulse>2.0)
                {
                    Props* props = (Props*)nodeBaseA;
                    props->DecreaseLife(maxNormalImpulse);
                }   
            }
            if ( nodeBaseA->GetPropsType() == EPropsType_Pig)
            {
                //当小鸟发生碰撞时，设定飞行状态为假，即结束飞行;
                Pig* pig = (Pig*)nodeBaseA;
                pig->SetState(EPigState_EndFly);
                SceneManager::SharedSceneManager()->SetPigFlyState(false);
                if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
                {
                    //小猪碰撞的音效;
                    if ( pig->GetPigType() == EPigType_Normal)
                    {
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_coll,false);
                    }
                    else if ( pig->GetPigType() == EPigType_Speedup)
                    {
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsExplosionPig_coll,false);
                    }
                    else if ( pig->GetPigType() == EPigType_Separate)
                    {
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsSeparatePig_coll,false);
                    }
                    else if ( pig->GetPigType() == EPigType_Bomb)
                    {
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsSpeedUpPig_coll,false);
                    }
					else if(pig->GetPigType() == EPigType_Ice)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_coll);
					}
                }

				if ( bodyB == SceneManager::SharedSceneManager()->GetGroundBody() )
				{
					if ( !pig->bFirstHitGround )
					{
						pig->PlayHitEffect();
						pig->bFirstHitGround = true;
					}
				}
				else if ( nodeBaseB != NULL )
				{
					if ( !pig->bFirstHitProps )
					{
						pig->PlayHitEffect();
						pig->bFirstHitProps = true;
					}
				}
            }
        }

        if ( nodeBaseB != NULL )
        {

            if ( nodeBaseB->GetPropsType() == EPropsType_Wood || nodeBaseB->GetPropsType() == EPropsType_Stone ||nodeBaseB->GetPropsType() == EPropsType_Glass || nodeBaseB->GetPropsType() == EPropsType_PaperBox || nodeBaseB->GetPropsType() == EPropsType_WoodBox)
            {
                if(nodeBaseA != NULL && nodeBaseA->GetPropsType()==EPropsType_Pig)
                {
                    float a=maxNormalImpulse*1000;
                    int b=a;
                    Pig* pig = (Pig*)nodeBaseA;
                    if(a>150)
                    {
                        pig->SetPigScore(b);
                    } 
                }
            }

			if (nodeBaseB->GetPropsType() == EPropsType_SP01 ||
				nodeBaseB->GetPropsType() == EPropsType_SP02 ||
				nodeBaseB->GetPropsType() == EPropsType_SP03 ||
				nodeBaseB->GetPropsType() == EPropsType_SP04 ||
				nodeBaseB->GetPropsType() == EPropsType_SP05)   //|| nodeBaseB->GetPropsType() == EPropsType_Grass;
            {              
                if(maxNormalImpulse>0.2f)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(maxNormalImpulse);
                }            
            }
			else if (nodeBaseB->GetPropsType() == EPropsType_Flower ||nodeBaseB->GetPropsType() == EPropsType_Grass|| nodeBaseB->GetPropsType() == EPropsType_Lamp)
			{
				if(maxNormalImpulse>0.6)
				{
					Props* props = (Props*)nodeBaseB;
					props->DecreaseLife(1.25);
				}else if(maxNormalImpulse>0.5)
				{
					Props* props = (Props*)nodeBaseB;
					props->DecreaseLife(maxNormalImpulse);
				}
			}
			else if(nodeBaseB->GetPropsType() == EPropsType_Wood|| nodeBaseB->GetPropsType() == EPropsType_WoodBox){
                if(maxNormalImpulse>0.6)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(1.25);
                }else if(maxNormalImpulse>0.5)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(maxNormalImpulse);
                }
            }else if( nodeBaseB->GetPropsType() == EPropsType_Glass|| nodeBaseB->GetPropsType() == EPropsType_PaperBox ){
                if(maxNormalImpulse>0.5)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(1.0);
                }else if(maxNormalImpulse>0.4)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(maxNormalImpulse);
                }
            }else if(nodeBaseB->GetPropsType() == EPropsType_EnemyA||nodeBaseB->GetPropsType() ==EPropsType_EnemyB||nodeBaseB->GetPropsType() ==EPropsType_EnemyC||nodeBaseB->GetPropsType() ==EPropsType_EnemyD||nodeBaseB->GetPropsType() ==EPropsType_EnemyE||nodeBaseB->GetPropsType() ==EPropsType_EnemyF)
            {
                if(maxNormalImpulse>0.1f)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(maxNormalImpulse);
                } 
            }            
            else if(nodeBaseB->GetPropsType() ==  EPropsType_Stone)
            {
                if(maxNormalImpulse>3.0)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(5.0);
                }else if(maxNormalImpulse>2.0)
                {
                    Props* props = (Props*)nodeBaseB;
                    props->DecreaseLife(maxNormalImpulse);
                }  
            }
            if ( nodeBaseB->GetPropsType() == EPropsType_Pig )
            {
				//当小鸟发生碰撞时，设定飞行状态为假，即结束飞行;
                Pig* pig = (Pig*)nodeBaseB;
                pig->SetState(EPigState_EndFly);
                SceneManager::SharedSceneManager()->SetPigFlyState(false);

				if ( bodyA == SceneManager::SharedSceneManager()->GetGroundBody() )
				{
					if ( !pig->bFirstHitGround )
					{
						pig->PlayHitEffect();
						pig->bFirstHitGround = true;
					}
				}
				else if ( nodeBaseA != NULL )
				{
					if ( !pig->bFirstHitProps )
					{
						pig->PlayHitEffect();
						pig->bFirstHitProps = true;
					}
				}
            }
        }  
}


