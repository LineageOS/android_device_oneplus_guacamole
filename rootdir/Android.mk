LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := init.display.guacamole.rc
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES := etc/init.display.guacamole.rc
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_ETC)/init/
include $(BUILD_PREBUILT)

