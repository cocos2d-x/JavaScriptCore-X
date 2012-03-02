//
//  S_CCSprite.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include "S_CCNode.h"
#include "S_CCSprite.h"

using namespace cocos2d;

#pragma mark - CCSprite

JSClassRef js_S_CCSprite_class;

enum ConstructType
{
    CT_DEFAULT = 0,
    CT_SpriteWithFile,
    CT_SpriteWithSpriteFrameName
};

static ConstructType s_eConstrutType = CT_DEFAULT;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSprite)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCSprite, CCSprite)

JS_STATIC_FUNC_IMP(S_CCSprite, jsSpriteWithFile)
{
    CCAssert(argumentCount == 1 || argumentCount == 2, "argument count is wrong.");
    s_eConstrutType = CT_SpriteWithFile;
    return jsConstructor(ctx, thisObject, argumentCount, arguments, exception);
}

JS_STATIC_FUNC_IMP(S_CCSprite, jsSpriteWithSpriteFrameName)
{
    CCAssert(argumentCount == 1, "argument count is wrong.");
    s_eConstrutType = CT_SpriteWithSpriteFrameName;
    return jsConstructor(ctx, thisObject, argumentCount, arguments, exception);
}

JSStaticFunction* S_CCSprite::jsStaticFunctions()
{
    static JSStaticFunction funcs[] = {
        {"spriteWithFile", S_CCSprite::jsSpriteWithFile, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
        {"spriteWithSpriteFrameName", S_CCSprite::jsSpriteWithSpriteFrameName, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
        {0, 0, 0}
    };

    return funcs;
}

bool S_CCSprite::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
    if (s_eConstrutType == CT_DEFAULT) {
		if (CCSprite::init())
		{
			result = true;
		}
    } else {
	    // init with texture
	    JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
	    int len = JSStringGetLength(str);
	    char *buff = (char *)malloc(len+1);
	    JSStringGetUTF8CString(str, buff, len+1);
	    result = true;
		if (s_eConstrutType == CT_SpriteWithFile) {
	        if (argumentCount == 1) {
		        if (!CCSprite::initWithFile(buff))
		        {
			        result = false;
		        }
	        } else {
                // TODO:
	        }
        } else if (s_eConstrutType == CT_SpriteWithSpriteFrameName) {
            if (!CCSprite::initWithSpriteFrameName(buff))
            {
                result = false;
            }
        }
        
	    JSStringRelease(str);
	    free(buff);
    } 

	if (obj) {
		setUserData(obj);
	}
    s_eConstrutType = CT_DEFAULT;
	return result;
}

#pragma mark - CCSpriteBatchNode

JSClassRef js_S_CCSpriteBatchNode_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSpriteBatchNode)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCSpriteBatchNode, CCSpriteBatchNode)

JSStaticFunction* S_CCSpriteBatchNode::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSpriteBatchNode::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	if (argumentCount > 0) {
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		size_t len = JSStringGetLength(str)+1;
		char* buff = new char[len];
        memset(buff, 0, len);
		JSStringGetUTF8CString(str, buff, len);
		unsigned int capacity = 10;
		if (argumentCount > 1) {
			capacity = JSValueToNumber(ctx, arguments[1], NULL);
		}
		bool ok = false;
		if (CCSpriteBatchNode::initWithFile(buff, capacity)) {
			ok = true;
			setUserData(obj);
		}
		JSStringRelease(str);
        CC_SAFE_DELETE_ARRAY(buff);
		return ok;
	}
	return false;
}
