LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := js_shared_prebuilt
LOCAL_MODULE_FILENAME := libjs
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libjs.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../.. \
                           $(LOCAL_PATH)/../../include 
                           
include $(PREBUILT_SHARED_LIBRARY)
