//
//  GameContactListener.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-23.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _GAMECONTACTLISTENER_H_
#define _GAMECONTACTLISTENER_H_

#include "Box2D/Box2D.h"

class GameContactListener : public b2ContactListener
{
public:
    GameContactListener();
    virtual ~GameContactListener();
    
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);    
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif