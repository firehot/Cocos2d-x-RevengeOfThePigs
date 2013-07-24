//
//  UIBgLightLayer.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-5-27.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _UIBGLIGHTLAYER_H_
#define _UIBGLIGHTLAYER_H_

#include "GameIncludeHeader.h"

class UIBgLightLayer : public CCLayer
{
public:
    UIBgLightLayer();
    virtual ~UIBgLightLayer();
    
	/** 用于实现对该层图像的渲染 */
    virtual void visit();
    virtual bool init();
    static CCScene* scene();
    LAYER_NODE_FUNC(UIBgLightLayer);
};

#endif