#ifndef __UTILS_ANDROID_H__
#define __UTILS_ANDROID_H__

#include <assert.h>
#include <android/log.h>
#include "unzip.h"

#define CC_BREAK_IF(cond)			if(cond) break;
#define CCAssert(cond, msg)         assert(cond)

#if 1
#define  LOG_TAG    "cocos2d"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

void setResourcePath(const char* pszResourcePath);
unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize);
unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);

#endif /* __UTILS_ANDROID_H__ */
