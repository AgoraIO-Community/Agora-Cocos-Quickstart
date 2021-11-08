LOCAL_PATH := $(call my-dir)

HAVE_TEST_FFMPEG_SO := $(shell test -f $(LOCAL_PATH)/../../../../libs/android/$(TARGET_ARCH_ABI)/libagora-ffmpeg.so && echo yes)
ifeq ($(HAVE_TEST_FFMPEG_SO),yes)
USE_VIDEO := yes
endif

include $(CLEAR_VARS)
LOCAL_MODULE := libagora-core
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../libs/android/$(TARGET_ARCH_ABI)/libagora-core.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libagora-fdkaac
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../libs/android/$(TARGET_ARCH_ABI)/libagora-fdkaac.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libagora-rtc-sdk
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../libs/android/$(TARGET_ARCH_ABI)/libagora-rtc-sdk.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libagora-soundtouch
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../libs/android/$(TARGET_ARCH_ABI)/libagora-soundtouch.so
include $(PREBUILT_SHARED_LIBRARY)

ifeq ($(USE_VIDEO),yes)
include $(CLEAR_VARS)
LOCAL_MODULE := libagora-ffmpeg
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../libs/android/$(TARGET_ARCH_ABI)/libagora-ffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libagora-mpg123
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../libs/android/$(TARGET_ARCH_ABI)/libagora-mpg123.so
include $(PREBUILT_SHARED_LIBRARY)
endif

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/TextBox/TextBox.cpp \
                   $(LOCAL_PATH)/../../../Classes/VideoFrameObserver.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../../libs/android/include

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

LOCAL_SHARED_LIBRARIES := libagora-core libagora-fdkaac libagora-rtc-sdk libagora-soundtouch

ifeq ($(USE_VIDEO), yes)
LOCAL_SHARED_LIBRARIES += libagora-ffmpeg libagora-mpg123
endif

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
