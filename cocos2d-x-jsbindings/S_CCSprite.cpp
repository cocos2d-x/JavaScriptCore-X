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

enum SpConstructType
{
    SP_CT_default = 0,
    SP_CT_spriteWithFile,
    SP_CT_spriteWithSpriteFrameName
};

static SpConstructType s_eSpConstrutType = SP_CT_default;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSprite)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCSprite, CCSprite)

JS_STATIC_FUNC_IMP(S_CCSprite, jsSpriteWithFile)
{
    CCAssert(argumentCount == 1 || argumentCount == 2, "argument count is wrong.");
    s_eSpConstrutType = SP_CT_spriteWithFile;
    return jsConstructor(ctx, thisObject, argumentCount, arguments, exception);
}

JS_STATIC_FUNC_IMP(S_CCSprite, jsSpriteWithSpriteFrameName)
{
    CCAssert(argumentCount == 1, "argument count is wrong.");
    s_eSpConstrutType = SP_CT_spriteWithSpriteFrameName;
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
    CCAssert(s_eSpConstrutType != SP_CT_default, "please use class method to create a sprite!");

    // init with texture
    JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
    int len = JSStringGetLength(str);
    char *buff = (char *)malloc(len+1);
    JSStringGetUTF8CString(str, buff, len+1);
    result = true;
	if (s_eSpConstrutType == SP_CT_spriteWithFile) 
    {
        if (argumentCount == 1) 
        {
	        if (!CCSprite::initWithFile(buff))
	        {
		        result = false;
	        }
        } 
        else 
        {
            // TODO: need to bind CCRect to javascript.
        }
    } 
    else if (s_eSpConstrutType == SP_CT_spriteWithSpriteFrameName)
    {
        if (!CCSprite::initWithSpriteFrameName(buff))
        {
            result = false;
        }
    }
    
    JSStringRelease(str);
    free(buff);
   

	if (obj) {
		setUserData(obj);
	}
    s_eSpConstrutType = SP_CT_default;
	return result;
}

#pragma mark - CCSpriteBatchNode

enum SpBNConstructType
{
    SPBN_CT_default = 0,
    SPBN_CT_batchNodeWithTexture,
    SPBN_CT_batchNodeWithFile
};

static SpBNConstructType s_eSpBNConstrutType = SPBN_CT_default;

JSClassRef js_S_CCSpriteBatchNode_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSpriteBatchNode)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCSpriteBatchNode, CCSpriteBatchNode)


JS_STATIC_FUNC_IMP(S_CCSpriteBatchNode, jsBatchNodeWithTexture)
{
    CCAssert(argumentCount == 1 || argumentCount == 2, "argument count is wrong.");
    s_eSpBNConstrutType = SPBN_CT_batchNodeWithTexture;
    return jsConstructor(ctx, thisObject, argumentCount, arguments, exception);
}

JS_STATIC_FUNC_IMP(S_CCSpriteBatchNode, jsBatchNodeWithFile)
{
    CCAssert(argumentCount == 1 || argumentCount == 2, "argument count is wrong.");
    s_eSpBNConstrutType = SPBN_CT_batchNodeWithFile;
    return jsConstructor(ctx, thisObject, argumentCount, arguments, exception);
}

JSStaticFunction* S_CCSpriteBatchNode::jsStaticFunctions()
{
    static JSStaticFunction funcs[] = {
        {"batchNodeWithTexture", S_CCSpriteBatchNode::jsBatchNodeWithTexture, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
        {"batchNodeWithFile", S_CCSpriteBatchNode::jsBatchNodeWithFile, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
        {0, 0, 0}
    };

    return funcs;
}

bool S_CCSpriteBatchNode::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
    CCAssert(s_eSpBNConstrutType != SPBN_CT_default, "please use class method to create a sprite!");

    bool ok = false;

    if (s_eSpBNConstrutType == SPBN_CT_batchNodeWithTexture)
    {
        //TODO: need to bind CCTexture2D class to javascript.
    }
    else if (s_eSpBNConstrutType == SPBN_CT_batchNodeWithFile)
    {
        JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
        size_t len = JSStringGetLength(str)+1;
        char* buff = new char[len];
        memset(buff, 0, len);
        JSStringGetUTF8CString(str, buff, len);
        unsigned int capacity = 10;
        if (argumentCount > 1) {
            capacity = JSValueToNumber(ctx, arguments[1], NULL);
        }
       
        if (CCSpriteBatchNode::initWithFile(buff, capacity)) {
            ok = true;
            setUserData(obj);
        }
        JSStringRelease(str);
        CC_SAFE_DELETE_ARRAY(buff);
    }
    s_eSpBNConstrutType = SPBN_CT_default;
	return ok;
}
