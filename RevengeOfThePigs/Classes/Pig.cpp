//
//  Pig.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-20;
//  Copyright 2012年 Cloud Game. All rights reserved.
// 

#include "Pig.h"
#include "Props.h"
#include "LevelBase.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "Level.h"


Pig::Pig()
: m_state(EPigState_BeginFly)
, m_bFirstPathPoint(true)
, m_bDrawPathPoint(false)
, bSmallPathPoint(true)
, bUpdated(false)
, pig_score(0)
, bFirstHitProps(false)
, bFirstHitGround(false)
{
    
}

Pig::~Pig()
{
    
}

Pig* Pig::CreatePig(EPigType type, b2World* world, const char* image,
                     LevelBaseEx* imageParent, const char* smashImage, CCPoint pos,
                     CCObject* pListener, DrawPointHandler handle)
{
    Pig* pig = new Pig();
    pig->autorelease();
    
    return pig->InitPig(type, world, image, imageParent, smashImage, pos, pListener, handle);
}

Pig* Pig::InitPig(EPigType type, b2World* world, const char* image,
               LevelBaseEx* imageParent, const char* smashImage, CCPoint pos,
               CCObject* pListener, DrawPointHandler handle)
{
    m_type = type;
    m_pHandleListener = pListener;
    m_drawPointHandle = handle;
    
	//创建物体定义，用物体定义来创建物体;
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
    bodyDef.angle = CC_DEGREES_TO_RADIANS(0);
	
    char imageFullName[50] = {0};
    sprintf(imageFullName, "%s.png", image);
	CCSprite *pTempSprite = NULL;
	if ( SceneManager::SharedSceneManager()->GetCurLevel()->GetBigLevelID() <= 6 /*&& SceneManager::SharedSceneManager()->GetCurLevel()->GetLevelID() < 4*/)
		pTempSprite = CCSprite::spriteWithSpriteFrameName(imageFullName);
	else
		pTempSprite = CCSprite::spriteWithFile(imageFullName);
	b2CircleShape dynamicBox;
    dynamicBox.m_radius = pTempSprite->getContentSize().width*CCGetScaleX()/2/PTM_RATIO;
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;	
    if(type == EPigType_Normal)
    {
	    fixtureDef.density = 0.90f;
	    fixtureDef.friction = 1.0f;
        fixtureDef.restitution=0.1f;
    }else if(type == EPigType_Separate) //分身猪;
    {
        fixtureDef.density = 0.70f;
        fixtureDef.friction = 1.0f;
        fixtureDef.restitution=0.1f;
    }else if(type == EPigType_Speedup)  //加速猪;
    {
        fixtureDef.density = 0.80f;
        fixtureDef.friction = 1.0f;
        fixtureDef.restitution=0.1f;
    }else if(type == EPigType_Bomb){    //爆炸猪;
        fixtureDef.density = 0.90f;
        fixtureDef.friction = 1.0f;
        fixtureDef.restitution=0.1f;
    }
	else if ( type == EPigType_Ice )
	{
		fixtureDef.density = 0.90f;
		fixtureDef.friction = 1.0f;
		fixtureDef.restitution=0.1f;
	}
	else if( type == EPigType_Ceram )
	{
		fixtureDef.density = 0.90f;
		fixtureDef.friction = 1.0f;
		fixtureDef.restitution=0.1f;
	}

	
    CreateNodeBody(world, &bodyDef, &fixtureDef, image, imageParent, smashImage,NULL,NULL,"",0,0,0);
    
    return this;
}

void Pig::DrawPoint(ccTime delta)
{
    if ( m_bFirstPathPoint )
    {
        CCSprite* pSprite = NULL;
        if ( bSmallPathPoint )
            pSprite = CCSprite::spriteWithSpriteFrameName(s_pPathEffect_PointSmall);
        else
            pSprite = CCSprite::spriteWithSpriteFrameName(s_pPathEffect_PointBig);
        bSmallPathPoint = !bSmallPathPoint;
        
        pSprite->setScale(CCGetScaleX());
        pSprite->setPosition(this->GetSprite()->getPosition());
        if ( m_pHandleListener != NULL && m_drawPointHandle )
        {
            (m_pHandleListener->*m_drawPointHandle)(pSprite);
        }
        m_lastPoint = this->GetSprite()->getPosition();
        m_bFirstPathPoint = false;
        return;
    }
    
    float len = ccpDistance(this->GetSprite()->getPosition(), m_lastPoint);
    if ( len >= kDistancePathPoints )
    {
        CCSprite* pSprite = NULL;
        if ( bSmallPathPoint )
            pSprite = CCSprite::spriteWithSpriteFrameName(s_pPathEffect_PointSmall);
        else
            pSprite = CCSprite::spriteWithSpriteFrameName(s_pPathEffect_PointBig);
        bSmallPathPoint = !bSmallPathPoint;
        
        pSprite->setScale(CCGetScaleX());
        pSprite->setPosition(this->GetSprite()->getPosition());
        if ( m_pHandleListener != NULL && m_drawPointHandle )
        {
            (m_pHandleListener->*m_drawPointHandle)(pSprite);
        }
        m_lastPoint = this->GetSprite()->getPosition();
    }
}

void Pig::EdgesJuges(ccTime delta)
{
	//如果小鸟的坐标超过边界，则清除小鸟，并使得发射出的小鸟数量减1;
	if (this->GetSprite()->getPosition().x<0 || this->GetSprite()->getPosition().x > CCGetWinSize().width*1.5)
	{
		CurPigExist = false;//将当前小鸟的生存状态设为空，即已经不存在了，防止之后对已经消失的小鸟还有操作(如爆炸、分身);
		m_pSpriteParent->disCount = m_pSpriteParent->disCount -1;
		//CCLOG("discount=%d",m_pSpriteParent->disCount);
		PlaySmashAnim();
		if(m_pSpriteParent->disCount == 0)
		{
			node = m_pSpriteParent->GetLevelParent()->getChildByTag(1000);
			CCActionInterval* actionBy = CCMoveTo::actionWithDuration(1, CCPointMake(-CCGetWinSize().width*(node->getScale()-0.6667)*0.5,node->getPosition().y));//设定一个动作;
            CCActionInterval* actionScale = CCScaleTo::actionWithDuration(1, node->getScale());
            CCActionInterval* spw = CCSpawn::actionOneTwo(actionBy, actionScale);
            node->runAction( CCSequence::actions(CCDelayTime::actionWithDuration(1.0f),spw,NULL));
			SceneManager::SharedSceneManager()->SetZero(true);
			m_pSpriteParent->LevelIsWin();
			if(m_pSpriteParent->GetPigZero())
				m_pSpriteParent->LevelIsLose();
		}
		this->unschedule(schedule_selector(Pig::EdgesJuges));//鸟消失的时候结束该函数的调用;
	}
}

void Pig::SetState(EPigState state)
{
    if ( m_state == state )
        return;
    
    m_state = state;
    bUpdated = true;
}

void Pig::SetDrawPathPoint(bool bDraw)
{
    m_bDrawPathPoint = bDraw;
	this->schedule(schedule_selector(Pig::EdgesJuges));
    if ( bDraw )
    {
        this->schedule(schedule_selector(Pig::DrawPoint));
    }
    else
    {
        this->unschedule(schedule_selector(Pig::DrawPoint));
    }
}

void Pig::WaitForDestroy(ccTime delta)
{
    b2Body* body = GetBody();
	if ( body == NULL )
	{
		this->unschedule(schedule_selector(Pig::WaitForDestroy));
		return;
	}

    //if ( body != NULL && !body->IsAwake() )
    {
		node = m_pSpriteParent->GetLevelParent()->getChildByTag(1000);
		float a=body->GetPosition().x*36;
		float b=body->GetPosition().y*44;
        this->unschedule(schedule_selector(Pig::WaitForDestroy));
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			//小猪消失时的音效;
			if (m_type == EPigType_Normal)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_destroy, false);
			}
			else if (m_type == EPigType_Speedup)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_destroy, false);
			}
			else if (m_type == EPigType_Separate)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_destroy, false);
			}
			else if (m_type == EPigType_Bomb)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_destroy, false);
			}
			else if (m_type == EPigType_Ice)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathNormalPig_destroy, false);
			}
		}

		PlaySmashAnim();
		m_pSpriteParent->disCount--;
		if(m_pSpriteParent->disCount == 0) //打完笼子后, 屏幕回到原大小;
		{
            //node=m_pSpriteParent->GetLevelParent()->getChildByTag(1000);
            CCActionInterval* actionBy = CCMoveTo::actionWithDuration(1, CCPointMake(-CCGetWinSize().width*(node->getScale()-0.6667)*0.5,node->getPosition().y));//设定一个动作;
            CCActionInterval* actionScale = CCScaleTo::actionWithDuration(1, node->getScale());
            CCActionInterval* spw = CCSpawn::actionOneTwo(actionBy, actionScale);
            node->runAction( CCSequence::actions(CCDelayTime::actionWithDuration(1.0f),spw,NULL));
			SceneManager::SharedSceneManager()->SetZero(true);
         //   m_pSpriteParent->LevelIsWin();
            if(m_pSpriteParent->GetPigZero() && m_pSpriteParent->GetLockEnemyCount() != 0)
                m_pSpriteParent->LevelIsLose();
		}
// 		else
// 			SceneManager::SharedSceneManager()->SetZero(false);
    }
}

CCParticleSystem* Pig::CreatePigDestroyEffect( const char* image, CCPoint point, int location  )
{
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

void Pig::WaitForBomb(ccTime delta)
{
	if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
	{
		//爆炸猪的声音;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsExplosionPig_explosion, false);
	}

    this->unschedule(schedule_selector(Pig::WaitForBomb));
    if (!CurPigExist)//判断小鸟状态是否处于飞行状态，或者小鸟是否已经消失了;
        return;    
    m_pSpriteParent->disCount--;
    float bombPigX = m_pSprite->getPosition().x;
    float bombPigY = m_pSprite->getPosition().y;

    CCSprite *action;
	char imageFullName[50] = {0};
	sprintf(imageFullName, "%s%d.png", s_pPathEffect_BombFog,1);
    action=CCSprite::spriteWithSpriteFrameName(imageFullName);
    action->setPosition(m_pSprite->getPosition());

    action->setScale(CCGetScaleX()*2.0);
    float radius;
    radius=action->getContentSize().width*3/2;

	CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>(15);
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    char frameName[50] = {0};
    for (int i = 1; i <= 5; i++)
    {
        sprintf(frameName, "%s%d.png",s_pPathEffect_BombFog, i);
		CCSpriteFrame *frame = cache->spriteFrameByName(frameName);
		animFrames->addObject(frame);
        //animation->addFrameWithFileName(frameName);
    }

	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,0.1f);
    CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
    //播放完动画后,删除;
    action->runAction(CCSequence::actions(animate,CCCallFuncN::actionWithTarget(this,callfuncN_selector(NodeBase::ActionCallBackN)),NULL));  
    m_pSpriteParent->addChild(action);


    b2Body* curBody = m_pWorld->GetBodyList();
    b2Body* nextBody = NULL;
    while ( curBody != NULL )
    {
        nextBody = curBody->GetNext();

        NodeBase* pNode = (NodeBase*)curBody->GetUserData();
		Props* props = (Props*)pNode;
        if ( pNode != NULL && pNode->GetSprite() != NULL )
        {
            CCSprite *pSprite = pNode->GetSprite();
            CCRect spriteBound=pSprite->boundingBox();
            //爆炸范围矩形第一二个参数是左下角坐标，后面的是宽高;
            CCRect explodeRange = CCRectMake(bombPigX-radius,bombPigY-radius,radius*2,radius*2);
            if(CCRect::CCRectIntersectsRect(spriteBound,explodeRange))
            {
                CCPoint bombCentre;
                bombCentre.x=bombPigX;bombCentre.y=bombPigY;
                float param = 200.0f; 
                CCPoint curPos = pSprite->getPosition();
                CCPoint vector = ccpSub(curPos, bombCentre);   //物体到 爆炸中心的距离;
                b2Vec2 force = b2Vec2(b2Vec2(param/vector.x,param/vector.y));
                curBody->ApplyForceToCenter(force);  

				b2Vec2 length = b2Vec2(vector.x,vector.y);
				if(length.Length() <= 30.0f && pNode->GetPropsType() != EPropsType_Pig){
					props->DecreaseLife(5.0);
				}
				else if(length.Length() <= 50.0f && length.Length() > 30.0f && pNode->GetPropsType() != EPropsType_Pig){
					props->DecreaseLife(3.0);
				}
            }
        }


        curBody = nextBody;
    }

    m_pSpriteParent->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(4.0f),
        CCCallFunc::actionWithTarget(this, callfunc_selector(Pig::DoNothing)),
        NULL));
    DestroyNodeImmediately();
}

int Pig::UpdateLogic()
{
// 	if(m_state == EPigState_EndFly&&this->GetSprite()->getPosition().y < CCGetWinSize().height * 2/5 && GetBody()->GetLinearDamping() != 2.0f)
// 		{
// 			GetBody()->SetLinearDamping(2.0f);
// 			GetBody()->SetAngularDamping(2.0f);	
// 		}

    if ( !bUpdated )
        return 0;
    bUpdated = false;
    b2Body* body = GetBody();
    if ( m_state == EPigState_Fly )
    {
		CurPigExist = true;//将当前小猪生存状态设为真;
        SetDrawPathPoint(true);//画小猪的飞行轨迹;
		if(GetPigType()  == EPigType_Bomb)
		{
			//if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
			//	m_pSprite->initWithSpriteFrameName("BombPigIceFly.png");
			//else
				m_pSprite->initWithSpriteFrameName("BombPigFly.png");
		}
		else if(GetPigType() == EPigType_Separate)
		{
			//if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
			//	m_pSprite->initWithSpriteFrameName("NinjaPigIceFly.png");
			//else
				m_pSprite->initWithSpriteFrameName("NinjaPigFly.png");
		}
		else if(GetPigType() == EPigType_Normal)
		{
			//if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
			//	m_pSprite->initWithSpriteFrameName("NormalPigIceFly.png");
			//else
				m_pSprite->initWithSpriteFrameName("NormalPigFly.png");
		}
		else if(GetPigType() == EPigType_Speedup)
		{
			//if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
			//	m_pSprite->initWithSpriteFrameName("SpeedPigIceFly.png");
			//else
				m_pSprite->initWithSpriteFrameName("SpeedPigFly.png");
		}
		else if(GetPigType() == EPigType_Ice)
		{
			m_pSprite->initWithSpriteFrameName("FreezePigIceFly.png");
		}
    }
    else if ( m_state == EPigState_EndFly )
    {
        SetDrawPathPoint(false);//当小鸟不在飞行时，停止画小鸟的飞行轨迹;
         if(GetPigType()== EPigType_Bomb)  //爆炸猪;
        {
            this->schedule(schedule_selector(Pig::WaitForBomb),3.0f);
            //m_pSprite->initWithFile("Fog/GroundFog/PigBombing.png");
			m_pSprite->initWithSpriteFrameName("PigBombing.png");
        }else{
             this->schedule(schedule_selector(Pig::WaitForDestroy), 6.0f);
        }

		 if(GetPigType()  == EPigType_Bomb)
		 {
		//	 m_pSprite->initWithSpriteFrameName("BombPigEnd.png");
		 }
		 else if(GetPigType() == EPigType_Separate)
		 {
			 //if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
				//m_pSprite->initWithSpriteFrameName("NinjaPigIceEnd.png");
			 //else
				 m_pSprite->initWithSpriteFrameName("NinjaPigEnd.png");
		 }
		 else if(GetPigType() == EPigType_Normal)
		 {
			 //if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
				//m_pSprite->initWithSpriteFrameName("NormalPigIceEnd.png");
			 //else
				 m_pSprite->initWithSpriteFrameName("NormalPigEnd.png");
		 }
		 else if(GetPigType() == EPigType_Speedup)
		 {
			 //if (SceneManager::SharedSceneManager()->GetGameVersion() == EGameVersion_BXJ)
				//m_pSprite->initWithSpriteFrameName("SpeedPigIceEnd.png");
			 //else
				 m_pSprite->initWithSpriteFrameName("SpeedPigEnd.png");
		 }
		 else if(GetPigType() == EPigType_Ice)
		 {
			 m_pSprite->initWithSpriteFrameName("FreezePigIceEnd.png");
		 }

    }

    if(!body->IsAwake())   //防止 木块压鸟 老是得分的bug;
    {
        return 0;
    }
	return pig_score;
}

void Pig::SingleTouchBeginCallback()
{
    if ( m_state != EPigState_Fly || !CurPigExist)//判断小鸟状态是否处于飞行状态，或者小鸟是否已经消失了;
        return;
    
	if ( m_type == EPigType_Separate )
	{
		DoSeparatePigSkill();
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			//分身猪的声音;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsSeparatePig_nimpo, false);
		}
	}
	else if ( m_type == EPigType_Bomb )
	{
		DoBombPigSkill();
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			//爆炸猪的声音;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsExplosionPig_explosion, false);
		}
	}
	else if ( m_type == EPigType_Speedup )
	{
		DoSpeedupPigSkill();
		if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
		{
			//加速猪的声音;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsSpeedUpPig_fly, false);
		}
	}
	else if( m_type == EPigType_Ceram )
	{
		DoCeramPigSkill();
		//音效;
	}
}

void Pig::BombTouchBeginCallback()
{
    if (!CurPigExist)//判断小鸟状态是否处于飞行状态，或者小鸟是否已经消失了;
        return;
    if ( m_type == EPigType_Bomb )
    {
        DoBombPigSkill();
        if (SceneManager::SharedSceneManager()->GetPlayBackgroundMusicState())
        {
            //爆炸猪的声音;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_pPathsExplosionPig_explosion, false);
        }
    }
	else if( m_type == EPigType_Ceram )
	{
		DoCeramPigSkill();
		//音效;
	}
}

void Pig::SingleTouchEndCallback()
{
    if ( m_state != EPigState_BeginFly )
        return;
}

void Pig::DoSeparatePigSkill()
{
	SceneManager::SharedSceneManager()->SetPigFlyState(true);
	m_pSpriteParent->disCount = m_pSpriteParent->disCount + 2;
	//分出的三只猪的作用力;
    b2Vec2 force0 = b2Vec2(m_pBody->GetLinearVelocity().x*7, m_pBody->GetLinearVelocity().y*7);
	b2Vec2 force1 = b2Vec2(m_pBody->GetLinearVelocity().x*7, (m_pBody->GetLinearVelocity().y+50.0f/PTM_RATIO)*7);
	b2Vec2 force2 = b2Vec2(m_pBody->GetLinearVelocity().x*7, (m_pBody->GetLinearVelocity().y-50.0f/PTM_RATIO)*7);
    
    Pig* pPig0 = Pig::CreatePig(EPigType_Separate, m_pWorld, m_sImage.c_str(), m_pSpriteParent, s_pPathDispearFog,
                                    m_pSprite->getPosition(),
                                    m_pSpriteParent, drawPoint_selector(LevelBaseEx::AddFlyPathPoint));
    pPig0->SetState(EPigState_Fly);
    m_pSpriteParent->addChild(pPig0);
    pPig0->GetBody()->ApplyForceToCenter(force0);
    
    Pig* pPig1 = Pig::CreatePig(EPigType_Separate, m_pWorld, m_sImage.c_str(), m_pSpriteParent, s_pPathDispearFog,
                                   m_pSprite->getPosition(),
                                   m_pSpriteParent, drawPoint_selector(LevelBaseEx::AddFlyPathPoint));
    pPig1->SetState(EPigState_Fly);
    m_pSpriteParent->addChild(pPig1);
    pPig1->GetBody()->ApplyForceToCenter(force1);
    
    Pig* pPig2 = Pig::CreatePig(EPigType_Separate, m_pWorld, m_sImage.c_str(), m_pSpriteParent, s_pPathDispearFog,
                                    m_pSprite->getPosition(),
                                    m_pSpriteParent, drawPoint_selector(LevelBaseEx::AddFlyPathPoint));
    pPig2->SetState(EPigState_Fly);
    m_pSpriteParent->addChild(pPig2);
    pPig2->GetBody()->ApplyForceToCenter(force2);
    
    DestroyNodeImmediately();
}

void Pig::DoSpeedupPigSkill()
{
    m_type = EPigType_Speedup;
    m_pBody->ApplyForceToCenter(b2Vec2(m_pBody->GetLinearVelocity().x*13, m_pBody->GetLinearVelocity().y*13));
}

void Pig::DoBombPigSkill()
{
    float bombPigX = m_pSprite->getPosition().x;
    float bombPigY = m_pSprite->getPosition().y;

    m_pSpriteParent->disCount--;
    CCSprite *action;
	

	char fullname[50] = {0};
	sprintf(fullname,"%s%d.png",s_pPathEffect_BombFog,1);
    action=CCSprite::spriteWithSpriteFrameName(fullname);
    action->setPosition(m_pSprite->getPosition());
    action->setScale(CCGetScaleX()*2.0);

    float radius;
    radius=action->getContentSize().width*3/2;

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(10);

    char frameName[50] = {0};
    for (int i = 1; i <= 5; i++)
    {
        sprintf(frameName, "%s%d.png",s_pPathEffect_BombFog, i);
		CCSpriteFrame* frames = cache->spriteFrameByName(frameName);
		animFrames->addObject(frames);
        //animation->addFrameWithFileName(frameName);
    }

	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,0.1f); 
    CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
    //播放完动画后,删除;
    action->runAction(CCSequence::actions(animate,CCCallFuncN::actionWithTarget(this,callfuncN_selector(NodeBase::ActionCallBackN)),NULL));  
    m_pSpriteParent->addChild(action);


    b2Body* curBody = m_pWorld->GetBodyList();
    b2Body* nextBody = NULL;
    while ( curBody != NULL )
    {
        nextBody = curBody->GetNext();

		//获取用户数据是通过创建物体时，物体对象通过调用SetUserData设置的，见CreateNodeBody函数;
        NodeBase* pNode = (NodeBase*)curBody->GetUserData();
		Props* props = (Props*)pNode; 
        if ( pNode != NULL && pNode->GetSprite() != NULL )
        {
            CCSprite *pSprite = pNode->GetSprite();
            CCRect spriteBound=pSprite->boundingBox();
            //爆炸范围矩形第一二个参数是左下角坐标，后面的是宽高;
            CCRect explodeRange = CCRectMake(bombPigX-radius,bombPigY-radius,radius*2,radius*2);
            if(CCRect::CCRectIntersectsRect(spriteBound,explodeRange))
            {
                CCPoint bombCentre;
                bombCentre.x=bombPigX;
				bombCentre.y=bombPigY;
                float param = 200.0f; 
                CCPoint curPos = pSprite->getPosition();
                CCPoint point = ccpSub(curPos, bombCentre);   //物体到 爆炸中心的距离;
                b2Vec2 force = b2Vec2(b2Vec2(param/point.x,param/point.y));
                curBody->ApplyForceToCenter(force);  

				b2Vec2 length = b2Vec2(point.x,point.y);
				if(length.Length() <= 30.0f && pNode->GetPropsType() != EPropsType_Pig){
					props->DecreaseLife(5.0);
				}
				if(length.Length() <= 50.0f && length.Length() > 30.0f && pNode->GetPropsType() != EPropsType_Pig){
					props->DecreaseLife(3.0);
				}

            }
        }
        curBody = nextBody;
    }

	
	m_pSpriteParent->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(4.0f),
		CCCallFunc::actionWithTarget(this, callfunc_selector(Pig::DoNothing)),
		NULL));
    DestroyNodeImmediately();
}

void Pig::DoCeramPigSkill()
{
    float bombPigX = m_pSprite->getPosition().x;
    float bombPigY = m_pSprite->getPosition().y;

    m_pSpriteParent->disCount--;
    CCSprite *action;
	char fullname[50] = {0};
	sprintf(fullname,"%s%d.png",s_pPathEffect_SteamFog,1);
    action=CCSprite::spriteWithSpriteFrameName(fullname);
    action->setPosition(m_pSprite->getPosition());
    action->setScale(CCGetScaleX()*2.0);

    float radius;
    radius=action->getContentSize().width;

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(10);  
    //CCAnimation* animation = CCAnimation::animation();
    char frameName[50] = {0};
    for (int i = 1; i <= 5; i++)
    {
        sprintf(frameName, "%s%d.png",s_pPathEffect_SteamFog, i);
        CCSpriteFrame* frame = cache->spriteFrameByName(frameName);
		animFrames->addObject(frame);
    }

	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,0.1f);
    CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
    //播放完动画后,删除;
    action->runAction(CCSequence::actions(animate,CCCallFuncN::actionWithTarget(this,callfuncN_selector(NodeBase::ActionCallBackN)),NULL));  
    m_pSpriteParent->addChild(action);


    b2Body* curBody = m_pWorld->GetBodyList();
    b2Body* nextBody = NULL;
    while ( curBody != NULL )
    {
        nextBody = curBody->GetNext();

		//获取用户数据是通过创建物体时，物体对象通过调用SetUserData设置的，见CreateNodeBody函数;
        NodeBase* pNode = (NodeBase*)curBody->GetUserData();
		Props* props = (Props*)pNode; 
        if ( pNode != NULL && pNode->GetSprite() != NULL )
        {
            CCSprite *pSprite = pNode->GetSprite();
            CCRect spriteBound=pSprite->boundingBox();
            //爆炸范围矩形第一二个参数是左下角坐标，后面的是宽高;
            CCRect explodeRange = CCRectMake(bombPigX-0.8f*radius,bombPigY-0.8f*radius,radius*1.6f,radius*1.6f);
            if(CCRect::CCRectIntersectsRect(spriteBound,explodeRange))
            {
                CCPoint bombCentre;
                bombCentre.x=bombPigX;
				bombCentre.y=bombPigY;
                float param = 140.0f; 
                CCPoint curPos = pSprite->getPosition();
                CCPoint point = ccpSub(curPos, bombCentre);   //物体到 爆炸中心的距离;
                b2Vec2 force = b2Vec2(b2Vec2(param/point.x,param/point.y));
                curBody->ApplyForceToCenter(force);  

				b2Vec2 length = b2Vec2(point.x,point.y);
				if(length.Length() <= 30.0f && pNode->GetPropsType() != EPropsType_Pig){
					props->DecreaseLife(4.0);
				}
				if(length.Length() <= 50.0f && length.Length() > 30.0f && pNode->GetPropsType() != EPropsType_Pig){
					props->DecreaseLife(2.4);
				}

            }
        }
        curBody = nextBody;
    }

	
	m_pSpriteParent->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(4.0f),
		CCCallFunc::actionWithTarget(this, callfunc_selector(Pig::DoNothing)),
		NULL));
    DestroyNodeImmediately();
}

void Pig::SetPigScore(int s)
{
    pig_score=s;
    bUpdated=true;
}

void Pig::DoNothing()
{
	DoNothing2();
}

void Pig::DoNothing2()
{
	if (m_pSpriteParent->disCount == 0)
	{
		m_pSpriteParent->LevelIsWin();
		if(m_pSpriteParent->GetPigZero())
			m_pSpriteParent->LevelIsLose();
	}
}

int Pig::GetPigScore()
{
    return pig_score;
}

void Pig::PlayHitEffect()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	char str[64] = {0};  
	sprintf(str, "%s%d.png", m_sSmashImage.c_str(), 1);

	CCSprite *action;
	action=CCSprite::spriteWithSpriteFrameName(str);
	action->setPosition(m_pSprite->getPosition());
	action->setScale(CCGetScaleX());

	CCAnimation* animation = CCAnimation::animation();
	for (int i = 1; i <= 5; i++)
	{
		sprintf(str, "%s%d.png", m_sSmashImage.c_str(), i);
		animation->addFrame(cache->spriteFrameByName(str));
	}

	CCAnimate *animate = CCAnimate::actionWithDuration(0.4f, animation, false);
	action->runAction(CCSequence::actions(animate,CCCallFuncN::actionWithTarget(this,callfuncN_selector(Pig::ActionCallBackN)),NULL));  
	m_pSpriteParent->addChild(action);
}

////////////////////////////////////////////////////////////
PigWithNoBody::PigWithNoBody()
{
    this->schedule(schedule_selector(PigWithNoBody::RandomJumpAnim), 3);
}

PigWithNoBody::~PigWithNoBody()
{
    
}

PigWithNoBody* PigWithNoBody::spriteWithFile(const char *pszFileName, EPigType type)
{
    PigWithNoBody *pobSprite = new PigWithNoBody();
    char imageFullName[50] = {0};
    sprintf(imageFullName, "%s.png", pszFileName);
	if ( SceneManager::SharedSceneManager()->GetCurLevel()->GetBigLevelID() <= 6  /*&& SceneManager::SharedSceneManager()->GetCurLevel()->GetLevelID() < 4*/)
	{
		if (pobSprite && pobSprite->initWithSpriteFrameName(imageFullName))
		{
			pobSprite->SetImage(pszFileName);
			pobSprite->SetPigType(type);
			pobSprite->autorelease();
			return pobSprite;
		}
	}
	else
	{
		if (pobSprite && pobSprite->initWithFile(imageFullName))
		{
			pobSprite->SetImage(pszFileName);
			pobSprite->SetPigType(type);
			pobSprite->autorelease();
			return pobSprite;
		}
	}
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void PigWithNoBody::RandomJumpAnim(ccTime delta)
{
    CCMoveBy* action1 = CCMoveBy::actionWithDuration(0.3f, CCPointMake(0, 20));
    CCMoveBy* action2 = CCMoveBy::actionWithDuration(0.3f, CCPointMake(0, -20));
    CCMoveBy* action3 = CCMoveBy::actionWithDuration(0.1f, CCPointMake(0, 5));
    CCMoveBy* action4 = CCMoveBy::actionWithDuration(0.1f, CCPointMake(0, -5));  
    CCRotateBy* rot = CCRotateBy::actionWithDuration(0.8f, 360);
	CCAction* seq = CCSequence::actions(action1, action2, action3, action4,NULL);
		this->runAction(seq);
		this->runAction(rot);
}

void PigWithNoBody::SetState(EPigState state)
{
    m_pigState = state;
    
    if ( state != EPigState_Idle )
        this->unschedule(schedule_selector(PigWithNoBody::RandomJumpAnim));
}

