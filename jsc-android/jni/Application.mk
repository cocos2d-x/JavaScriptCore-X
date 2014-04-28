APP_STL := gnustl_static
APP_OPTIM := release
APP_CPPFLAGS := -frtti

# not compile corefundation library for android.
# corefoundation
APP_MODULES := icuuc icui18n cutils js hello-jni

