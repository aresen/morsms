# v0.1 initial by Quentin
# December 12, 2012
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := morse
LOCAL_SRC_FILES := slimmorse.cpp

include $(BUILD_SHARED_LIBRARY)