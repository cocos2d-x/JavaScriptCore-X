/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <android/log.h>
/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/HelloJni/HelloJni.java
 */
 
#include "utils.h"

int minidom_main();
int testapi_main();

extern "C"
{
 jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    return JNI_VERSION_1_4;
}
    
jstring
Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
    LOGD("-------------------------------------------------------");
    LOGD("-------------------minidom_begin-------------------------");
    minidom_main();
    LOGD("-------------------minidom_end-------------------------");
    LOGD("-------------------------------------------------------");
    LOGD("-------------------testapi_begin-------------------------");
    testapi_main();
    LOGD("-------------------testapi_end-------------------------");
    LOGD("-------------------------------------------------------");
    return env->NewStringUTF("Hello JavaScriptCore !");
}

void Java_com_example_hellojni_HelloJni_nativeSetPaths(JNIEnv*  env, jobject thiz, jstring apkPath)
{
    LOGD("nativeSetPaths1");
    const char* str;
    jboolean isCopy;
    str = env->GetStringUTFChars(apkPath, &isCopy);
    if (isCopy) {
    LOGD("nativeSetPaths2");
        setResourcePath(str);
        LOGD("nativeSetPaths3");
        env->ReleaseStringUTFChars(apkPath, str);
    }
    LOGD("nativeSetPaths4");
}

}