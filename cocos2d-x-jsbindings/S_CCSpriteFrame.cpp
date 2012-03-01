//
//  S_CCSpriteFrame.cpp
//  cocos2d-x
//
//  Created By XXX on 02/22/2012
//  Copyright (c) 2011 XXX. All rights reserved.
//

#include <JavaScriptCore/JavaScriptCore.h>
#include "S_CCSpriteFrame.h"

using namespace cocos2d;


#pragma mark - CCSpriteFrame

JSClassRef js_S_CCSpriteFrame_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSpriteFrame)

JSStaticFunction* S_CCSpriteFrame::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"setRectInPixels", S_CCSpriteFrame::jsSetRectInPixels, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setRect", S_CCSpriteFrame::jsSetRect, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCSpriteFrame::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		CCRect rect;
		CCPoint *origin = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		CCPoint *size = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);

		// get tex name
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		int len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);

		rect.origin = *origin;
		rect.size = CCSize(size->x, size->y);
		CCTexture2D *tex = CCTextureCache::sharedTextureCache()->textureForKey(buff);
		result = CCSpriteFrame::initWithTexture(tex, rect);
		
		JSStringRelease(str);
		free(buff);
	}
	if (result) {
		jsObject = obj;
	}
	return result;
}

JS_STATIC_FUNC_IMP(S_CCSpriteFrame, jsSetRectInPixels)
{
	//	void setRectInPixels(const CCRect& rectInPixels);
	if (argumentCount == 1) {
		CCSpriteFrame* self = (CCSpriteFrame *)JSObjectGetPrivate(thisObject);
		CCRect rect;
		CCPoint *origin = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		CCPoint *size = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);

		rect.origin = *origin;
		rect.size = CCSize(size->x, size->y);
		self->setRectInPixels(rect);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCSpriteFrame, jsSetRect)
{
	//	void setRect(const CCRect& rect);

	if (argumentCount == 1) {
		CCSpriteFrame* self = (CCSpriteFrame *)JSObjectGetPrivate(thisObject);
		CCRect rect;
		CCPoint *origin = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		CCPoint *size = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		
		rect.origin = *origin;
		rect.size = CCSize(size->x, size->y);
		self->setRect(rect);
	}
	return JSValueMakeUndefined(ctx);
}
