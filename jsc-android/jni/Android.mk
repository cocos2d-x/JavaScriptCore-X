LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(LOCAL_PATH)/../hello-jsc/Android.mk \
           $(LOCAL_PATH)/../platform_external_icu4c/Android.mk \
           $(LOCAL_PATH)/Source/JavaScriptCore/cutils/Android.mk \
           $(LOCAL_PATH)/Android_jsc.mk

include $(subdirs)
