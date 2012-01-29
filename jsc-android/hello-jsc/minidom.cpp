/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2007 Alp Toker <alp@atoker.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "JSContextRef.h"
#include "JSNode.h"
#include "JSObjectRef.h"
#include "JSStringRef.h"
#include <stdio.h>
#include <stdlib.h>
#include <wtf/Assertions.h>
#include <wtf/UnusedParam.h>
#include "unzip.h"
#include "assert.h"

#include <string>
using namespace std;

static char* createStringWithContentsOfFile(const char* fileName);
static JSValueRef print(JSContextRef context, JSObjectRef object, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);

#define CC_BREAK_IF(cond)			if(cond) break;
#define CCAssert(cond, msg)         assert(cond)
#include <android/log.h>
#if 1
#define  LOG_TAG    "cocos2d"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif
// record the resource path
static string s_strResourcePath = "";

void setResourcePath(const char* pszResourcePath)
{
    CCAssert(pszResourcePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");

    string tmp(pszResourcePath);

    if ((! pszResourcePath) || tmp.find(".apk") == string::npos)
    {
        return;
    }

    s_strResourcePath = pszResourcePath;
}

static unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    unzFile pFile = NULL;
    *pSize = 0;
LOGD("getFileDataFromZip line=%d", __LINE__);
    do 
    {
        CC_BREAK_IF(!pszZipFilePath || !pszFileName);
        CC_BREAK_IF(strlen(pszZipFilePath) == 0);
LOGD("getFileDataFromZip line=%d", __LINE__);
        pFile = unzOpen(pszZipFilePath);
        CC_BREAK_IF(!pFile);
LOGD("getFileDataFromZip line=%d", __LINE__);
        int nRet = unzLocateFile(pFile, pszFileName, 1);
        CC_BREAK_IF(UNZ_OK != nRet);
LOGD("getFileDataFromZip line=%d", __LINE__);
        char szFilePathA[260];
        unz_file_info FileInfo;
        nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
        CC_BREAK_IF(UNZ_OK != nRet);
LOGD("getFileDataFromZip line=%d", __LINE__);
        nRet = unzOpenCurrentFile(pFile);
        CC_BREAK_IF(UNZ_OK != nRet);
LOGD("getFileDataFromZip line=%d", __LINE__);
        pBuffer = new unsigned char[FileInfo.uncompressed_size+1];
        memset(pBuffer, 0, FileInfo.uncompressed_size+1);
        int nSize = 0;
        nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
        CCAssert(nSize == 0 || nSize == (int)FileInfo.uncompressed_size, "the file size is wrong");
LOGD("getFileDataFromZip line=%d", __LINE__);
        *pSize = FileInfo.uncompressed_size;
        unzCloseCurrentFile(pFile);
    } while (0);
LOGD("getFileDataFromZip line=%d", __LINE__);
    if (pFile)
    {LOGD("getFileDataFromZip line=%d", __LINE__);
        unzClose(pFile);
    }LOGD("getFileDataFromZip line=%d", __LINE__);

    return pBuffer;
}

static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{	
    unsigned char * pData = 0;
    string fullPath(pszFileName);

    if ((! pszFileName) || (! pszMode))
    {
        return 0;
    }

    if (pszFileName[0] != '/')
    {
        // read from apk
        fullPath.insert(0, "assets/");
        LOGD("s_strResourcePath=%s, fullPath=%s", s_strResourcePath.c_str(), fullPath.c_str());
        pData =  getFileDataFromZip(s_strResourcePath.c_str(), fullPath.c_str(), pSize);
    }
    else
    {
        do 
        {
            // read rrom other path than user set it
            FILE *fp = fopen(pszFileName, pszMode);
            CC_BREAK_IF(!fp);

            unsigned long size;
            fseek(fp,0,SEEK_END);
            size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pData = new unsigned char[size];
            size = fread(pData,sizeof(unsigned char), size,fp);
            fclose(fp);

            if (pSize)
            {
                *pSize = size;
            }			
        } while (0);		
    }

    //     if (! pData && getIsPopupNotify())
    //     {
    //         std::string title = "Notification";
    //         std::string msg = "Get data from file(";
    //         msg.append(fullPath.c_str()).append(") failed!");
    //         CCMessageBox(msg.c_str(), title.c_str());
    //     }

    return pData;
}


extern "C" int jsc_main()
{
    const char *scriptPath = "minidom.js";
LOGD("jsc_main, line=%d", __LINE__);
    
    JSGlobalContextRef context = JSGlobalContextCreateInGroup(NULL, NULL);
    JSObjectRef globalObject = JSContextGetGlobalObject(context);
    
    JSStringRef printIString = JSStringCreateWithUTF8CString("print");
    JSObjectSetProperty(context, globalObject, printIString, JSObjectMakeFunctionWithCallback(context, printIString, print), kJSPropertyAttributeNone, NULL);
    JSStringRelease(printIString);
    
    JSStringRef node = JSStringCreateWithUTF8CString("Node");
    JSObjectSetProperty(context, globalObject, node, JSObjectMakeConstructor(context, JSNode_class(context), JSNode_construct), kJSPropertyAttributeNone, NULL);
    JSStringRelease(node);
    LOGD("jsc_main, line=%d", __LINE__);
    //char* scriptUTF8 = createStringWithContentsOfFile(scriptPath);
    unsigned long iSize = 0;
    unsigned char* scriptUTF8 = getFileData(scriptPath, "rb", &iSize);
    LOGD("size = %d", iSize);
    JSStringRef script = JSStringCreateWithUTF8CString((char*)scriptUTF8);
    JSValueRef exception;
    JSValueRef result = JSEvaluateScript(context, script, NULL, NULL, 1, &exception);
    if (result)
        LOGD("PASS: Test script executed successfully.\n");
    else {
        LOGD("FAIL: Test script threw exception:\n");
        JSStringRef exceptionIString = JSValueToStringCopy(context, exception, NULL);
        size_t exceptionUTF8Size = JSStringGetMaximumUTF8CStringSize(exceptionIString);
        char* exceptionUTF8 = (char*)malloc(exceptionUTF8Size);
        JSStringGetUTF8CString(exceptionIString, exceptionUTF8, exceptionUTF8Size);
        LOGD("%s\n", exceptionUTF8);
        free(exceptionUTF8);
        JSStringRelease(exceptionIString);
    }
    JSStringRelease(script);
    delete[] scriptUTF8;

    globalObject = 0;
    JSGlobalContextRelease(context);
    LOGD("PASS: Program exited normally.\n");
    return 0;
}

static JSValueRef print(JSContextRef context, JSObjectRef object, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    UNUSED_PARAM(object);
    UNUSED_PARAM(thisObject);

    if (argumentCount > 0) {
        JSStringRef string = JSValueToStringCopy(context, arguments[0], exception);
        size_t numChars = JSStringGetMaximumUTF8CStringSize(string);
        char stringUTF8[numChars];
        JSStringGetUTF8CString(string, stringUTF8, numChars);
        LOGD("%s\n", stringUTF8);
    }
    
    return JSValueMakeUndefined(context);
}

static char* createStringWithContentsOfFile(const char* fileName)
{
    char* buffer;
    
    size_t buffer_size = 0;
    size_t buffer_capacity = 1024;
    buffer = (char*)malloc(buffer_capacity);
    
    FILE* f = fopen(fileName, "r");
    if (!f) {
        LOGD("Could not open file: %s\n", fileName);
        return 0;
    }
    
    while (!feof(f) && !ferror(f)) {
        buffer_size += fread(buffer + buffer_size, 1, buffer_capacity - buffer_size, f);
        if (buffer_size == buffer_capacity) { /* guarantees space for trailing '\0' */
            buffer_capacity *= 2;
            buffer = (char*)realloc(buffer, buffer_capacity);
            ASSERT(buffer);
        }
        
        ASSERT(buffer_size < buffer_capacity);
    }
    fclose(f);
    buffer[buffer_size] = '\0';
    
    return buffer;
}
