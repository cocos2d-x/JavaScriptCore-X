LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_logic_static

LOCAL_MODULE_FILENAME := libgame_logic

include $(LOCAL_PATH)/../../JSBindings/Android.mk
LOCAL_SRC_FILES := $(addprefix ../../JSBindings/,$(LOCAL_SRC_FILES))

LOCAL_SRC_FILES += AppDelegate.cpp \
                   HelloWorldScene.cpp
                   


                    
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES := png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
                
LOCAL_SHARED_LIBRARIES := cocosdenshion_shared js_shared_prebuilt
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx/platform/third_party/android/modules/libpng)
$(call import-module,cocos2dx/platform/third_party/android/modules/libxml2)
$(call import-module,cocos2dx/platform/third_party/android/modules/libjpeg)
$(call import-module,JSBindings/libraries/android)
