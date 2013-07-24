//
//  PropsBase.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-27.;
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "NodeBase.h"
#include "LevelBase.h"
#include "SceneManager.h"
#include "Level.h"
NodeBase::NodeBase()
: m_pBody(NULL)
, m_pSprite(NULL)
, m_pSpriteParent(NULL)
{
  
}

NodeBase::~NodeBase()
{
    
}

void NodeBase::CreateNodeBody(b2World* world, b2BodyDef* bodyDef, b2FixtureDef* fixtureDef,
	const char* image, LevelBaseEx* imageParent, const char* smashImage,int propsType,CCSprite *pTempSprite,const char* state,int tag,int to,int to2)
{
    if ( world == NULL || bodyDef == NULL || fixtureDef == NULL || imageParent == NULL )
        return;
    
    m_pSpriteParent = imageParent;
    m_sImage = image;
    m_sSmashImage = smashImage;
    m_pWorld = world;
    
    char imageFullName[50] = {0};
    sprintf(imageFullName, "%s.png", image);
	if ( SceneManager::SharedSceneManager()->GetCurLevel()->GetBigLevelID() <= 6/* && SceneManager::SharedSceneManager()->GetCurLevel()->GetLevelID() < 4 */)
		m_pSprite = CCSprite::spriteWithSpriteFrameName(imageFullName);
	else
		m_pSprite = CCSprite::spriteWithFile(imageFullName);
    m_pSprite->setScale(CCGetScaleX());
    m_pSpriteParent->addChild(m_pSprite);
    
    m_pBody = world->CreateBody(bodyDef);
    m_pBody->SetUserData(this);
    m_pBody->CreateFixture(fixtureDef);

//道具相连 添加;
	if (propsType == 21 || propsType == 22 || propsType == 23 || propsType == 24 || propsType == 25 || propsType == 26 || propsType == 27)//小鸟，判断是否有链接的对象，有的话就链接上去，没有的话就作为一个孤立的个体;
	{
		if (to == 1)
		{
			m_pPreBody = SceneManager::SharedSceneManager()->GetTag1Body();
			b2RevoluteJointDef jd;//旋转关节;
			jd.collideConnected = false;//不允许相连的物体发生碰撞;
			jd.Initialize(m_pPreBody,m_pBody,m_pPreBody->GetWorldCenter());
			m_pWorld->CreateJoint(&jd);//创建链接;
		}
		else if (to == 2)
		{
			m_pPreBody = SceneManager::SharedSceneManager()->GetTag2Body();
			b2RevoluteJointDef jd;//旋转关节;
			jd.collideConnected = false;//不允许相连的物体发生碰撞;
			jd.Initialize(m_pPreBody,m_pBody,m_pPreBody->GetWorldCenter());
			m_pWorld->CreateJoint(&jd);//创建链接;
		}
	}
	if (propsType == 50 || propsType == 602)//水果;
	{
		if (to == 1)
		{
			m_pPreBody = SceneManager::SharedSceneManager()->GetTag1Body();
			b2RevoluteJointDef jd;//旋转关节;
			jd.collideConnected = false;//不允许相连的物体发生碰撞;
			jd.Initialize(m_pPreBody,m_pBody,b2Vec2(m_pPreBody->GetWorldCenter().x-0.5,m_pPreBody->GetWorldCenter().y));
			m_pWorld->CreateJoint(&jd);//创建链接;
		}
		else if (to == 2)
		{
			m_pPreBody = SceneManager::SharedSceneManager()->GetTag2Body();
			b2RevoluteJointDef jd;//旋转关节;
			jd.collideConnected = false;//不允许相连的物体发生碰撞;
			jd.Initialize(m_pPreBody,m_pBody,b2Vec2(m_pPreBody->GetWorldCenter().x+0.5,m_pPreBody->GetWorldCenter().y));
			m_pWorld->CreateJoint(&jd);//创建链接;
		}
	}
	if (propsType == 205)//与两个链条连接的长木块;
	{
		if (to == 1)
		{
			m_pPreBody = SceneManager::SharedSceneManager()->GetTag1Body();
			b2RevoluteJointDef jd;//旋转关节;
			jd.collideConnected = false;//不允许相连的物体发生碰撞;
			jd.Initialize(m_pPreBody,m_pBody,b2Vec2(m_pPreBody->GetWorldCenter().x,m_pPreBody->GetWorldCenter().y-0.5));
			m_pWorld->CreateJoint(&jd);//创建链接;
		}
		if (to2 == 2)
		{
			m_pPreBody = SceneManager::SharedSceneManager()->GetTag2Body();
			b2RevoluteJointDef jd;//旋转关节;
			jd.collideConnected = false;//不允许相连的物体发生碰撞;
			jd.Initialize(m_pPreBody,m_pBody,b2Vec2(m_pPreBody->GetWorldCenter().x,m_pPreBody->GetWorldCenter().y-0.5));
			m_pWorld->CreateJoint(&jd);//创建链接;
		}
	}
	if (propsType == 603 || propsType == 615 || propsType == 633)//两道具（木块或玻璃）相连;
	{
		string t(state);
		string t1("begin_ground");
		string t2("begin_null");
		string t4("end");
		if (t == t1)
		{
			b2Body* ground = SceneManager::SharedSceneManager()->GetGroundBody();
			b2DistanceJointDef jointDef;
			jointDef.Initialize(ground, m_pBody,ground->GetWorldCenter(), m_pBody->GetWorldCenter());
			jointDef.collideConnected = true;
			m_pWorld->CreateJoint(&jointDef);
			SceneManager::SharedSceneManager()->SavePropsBody(m_pBody);
		}
		else if (t == t2)
		{
			SceneManager::SharedSceneManager()->SavePropsBody(m_pBody);
		}
		else
		{
			if (to == 1)
			{
				m_pPreBody = SceneManager::SharedSceneManager()->GetTag1Body();
			}
			else if (to == 2)
			{
				m_pPreBody = SceneManager::SharedSceneManager()->GetTag2Body();
			}
			else
			{
				m_pPreBody = SceneManager::SharedSceneManager()->GetPropsBody();
			}
			b2WeldJointDef jd;//焊接关节;
			jd.Initialize(m_pPreBody,m_pBody,m_pPreBody->GetWorldCenter());
			m_pWorld->CreateJoint(&jd);
			SceneManager::SharedSceneManager()->SavePropsBody(m_pBody);
		}
		if (t == t4)
		{
			SceneManager::SharedSceneManager()->SavePropsBody(NULL);
		}
	}
	//if (propsType == 100)//灯泡道具;
	//{
	//	b2Body* ground = SceneManager::SharedSceneManager()->GetGroundBody();
	//	/*
	//	b2DistanceJointDef jointDef;//距离关节，这里使用距离关节会使吊灯产生晃荡的效果并且如果锚点设的不好还会使吊灯原地旋转，故而选用旋转关节;
	//	jointDef.Initialize(ground, m_pBody,b2Vec2(m_pBody->GetWorldCenter().x+0.5,m_pBody->GetWorldCenter().y+4), b2Vec2(m_pBody->GetWorldCenter().x,m_pBody->GetWorldCenter().y+0.5));
	//	jointDef.collideConnected = true;
	//	m_pWorld->CreateJoint(&jointDef);
	//	*/
	//	b2RevoluteJointDef jd;//旋转关节;
	//	jd.collideConnected = false;//不允许相连的物体发生碰撞;
	//	jd.Initialize(ground,m_pBody,b2Vec2(m_pBody->GetWorldCenter().x+0.3,m_pBody->GetWorldCenter().y+4));
	//	m_pWorld->CreateJoint(&jd);//创建链接;
	//}
	if (propsType == 200)//表示链条道具（悬挂道具）;
	{
		string t(state);
		string t1("begin_ground");
		string t3("end");
		if (t == t1)//第一个链接点与背景相连;
		{
			b2Body* ground = SceneManager::SharedSceneManager()->GetGroundBody();
			/*
			b2DistanceJointDef jointDef;
			jointDef.Initialize(ground, m_pBody,b2Vec2(m_pBody->GetWorldCenter().x,m_pBody->GetWorldCenter().y), m_pBody->GetWorldCenter());
			jointDef.collideConnected = true;
			m_pWorld->CreateJoint(&jointDef);
			*/
			b2RevoluteJointDef jd;//旋转关节;
			jd.collideConnected = false;//不允许相连的物体发生碰撞;
			jd.Initialize(ground,m_pBody,b2Vec2(m_pBody->GetWorldCenter().x,m_pBody->GetWorldCenter().y+1));
			m_pWorld->CreateJoint(&jd);//创建链接;
			SceneManager::SharedSceneManager()->SavePropsBody(m_pBody);
		}
		else
		{
			if (to == 1)
			{
				m_pPreBody = SceneManager::SharedSceneManager()->GetTag1Body();
				b2RevoluteJointDef jd;//旋转关节;
				jd.collideConnected = false;//不允许相连的物体发生碰撞;
				jd.Initialize(m_pPreBody,m_pBody,m_pPreBody->GetWorldCenter());
				m_pWorld->CreateJoint(&jd);//创建链接;
			}
			else//非第一个链接点与钱一个链节点相连;
			{
				m_pPreBody = SceneManager::SharedSceneManager()->GetPropsBody();
				b2RevoluteJointDef jd;//旋转关节;
				jd.collideConnected = false;//不允许相连的物体发生碰撞;
				jd.Initialize(m_pPreBody,m_pBody,b2Vec2(m_pPreBody->GetWorldCenter().x,m_pPreBody->GetWorldCenter().y-0.5));
				m_pWorld->CreateJoint(&jd);//创建链接;
			}
			SceneManager::SharedSceneManager()->SavePropsBody(m_pBody);
		}
		if (t == t3)
		{
			SceneManager::SharedSceneManager()->SavePropsBody(NULL);
		}
	}

	if (tag == 1)
	{
		SceneManager::SharedSceneManager()->SaveTag1Body(m_pBody);
	}
	else if (tag == 2)
	{
		SceneManager::SharedSceneManager()->SaveTag2Body(m_pBody);
	}
//结束;
}

void NodeBase::ChangeSprite(const char* imageFullName)
{
    if ( m_pSprite != NULL )
    {
        m_pSprite->initWithFile(imageFullName);
    }
}

void NodeBase::RemoveSprite()
{
    if ( m_pSprite != NULL )
    {
        m_pSprite->removeFromParentAndCleanup(true);
        m_pSprite = NULL;
    }
}

void NodeBase::RemoveBody()
{
    if ( m_pBody != NULL )
    {
        m_pBody->GetWorld()->DestroyBody(m_pBody);
        m_pBody = NULL;
    }
}

void NodeBase::PlaySmashAnim()
{
       RemoveBody();
//     CCAnimation* animation = CCAnimation::animation();
//     char frameName[50] = {0};
//     for (int i = 1; i <= kMaxSmashImageCount; i++)
//     {
//         sprintf(frameName, "%s%d.png", m_sSmashImage.c_str(), i);
//         animation->addFrameWithFileName(frameName);
//     }
// 
//     CCAnimate *animate = CCAnimate::actionWithDuration(0.5f, animation, false);
	
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	//创建动画每一帧，从cache里面读取  ;
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(kMaxSmashImageCount);  

	char str[64] = {0};  

	for (int i = 1; i <= kMaxSmashImageCount; i++)
	{
		sprintf(str, "%s%d.png", m_sSmashImage.c_str(), i);

		CCSpriteFrame* frame = cache->spriteFrameByName( str );  
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,0.1f);  
	CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
	//m_pSprite->runAction(animation);
	//CCRepeatForever* mFly=CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animation, false));  
	
	//cache->removeSpriteFramesFromFile(strPlist);  

     
    m_pSprite->runAction(CCSequence::actions(animate,
        CCCallFunc::actionWithTarget(this, callfunc_selector(NodeBase::BrokenCallback)),
        NULL));
    //m_pSprite->setIsVisible(false);
    animFrames->release();  
}

void NodeBase::ActionCallBackN(CCNode * spsender)
{
	spsender->removeFromParentAndCleanup(true);
}

void NodeBase::BrokenCallback()
{
    RemoveSprite();
    this->removeFromParentAndCleanup(true);
}

void NodeBase::DestroyNodeImmediately()
{
    RemoveSprite();
    RemoveBody();
    this->removeFromParentAndCleanup(true);
}

void NodeBase::FrozenBroken()
{
	RemoveBody();
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(kMaxFrozenImageCount);
	char str[64] = {0}; 
	for (int i = 1; i <= kMaxFrozenImageCount; i++)
	{
		//使用的是prop.plsit里的碎冰效果;
		sprintf(str, "%s%d.png", m_sSmashImage.c_str(), i);
		CCSpriteFrame* frame = cache->spriteFrameByName( str );  
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,0.1f);  
	CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
	m_pSprite->runAction(CCSequence::actions(animate,
		CCCallFunc::actionWithTarget(this, callfunc_selector(NodeBase::BrokenCallback)),
		NULL));
	animFrames->release();  
}


