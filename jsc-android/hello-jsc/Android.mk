# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello-jni


LOCAL_CFLAGS += -DENABLE_SINGLE_THREADED=1 -DUSE_FILE32API -D__LINUX__=1 -DCOMPATIBLE_GCC4=1 -D__LITTLE_ENDIAN__=1

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../jni/Source/JavaScriptCore/include \
                    $(LOCAL_PATH)/../jni/Source/JavaScriptCore/include/JavaScriptCore \
                    $(LOCAL_PATH)/../jni/Source/JavaScriptCore \
                    $(LOCAL_PATH)/../jni/Source/JavaScriptCore/wtf \
                    $(LOCAL_PATH)/../corefoundation-lite-android 

LOCAL_SRC_FILES := hello-jni.cpp \
                   JSNode.c \
                   JSNodeList.c \
                   Node.c \
                   NodeList.c \
                   unzip.cpp \
                   minidom.cpp \
                   ioapi.cpp \
                   testapi.cpp \
                   utils.cpp 

LOCAL_LDLIBS :=  -lz -llog

LOCAL_SHARED_LIBRARIES := libjs libcorefoundation

include $(BUILD_SHARED_LIBRARY)
