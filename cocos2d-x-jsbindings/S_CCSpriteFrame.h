//
//  S_CCSpriteFrame.h
//  cocos2d-x
//
//  Created By XXX on 02/22/2012
//  Copyright (c) 2011 XXX. All rights reserved.
//

#ifndef cocos2dx-javascript_S_CCSpriteFrame_h
#define cocos2dx-javascript_S_CCSpriteFrame_h

#include "cocos2d.h"
#include "ScriptingCore.h"

class S_CCSpriteFrame : public cocos2d::CCSpriteFrame
{
	JSObjectRef jsObject;
public:

	S_CCSpriteFrame() : CCSpriteFrame() {};

	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsSetRectInPixels);
	JS_STATIC_FUNC_DEF(jsSetRect);
};

#endif

