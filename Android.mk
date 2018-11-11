LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := codec_test
LOCAL_SRC_FILES := codec_test.cpp

LOCAL_LDFLAGS += -ldl


LOCAL_SHARED_LIBRARIES := \
        libcutils \
        libutils
include $(BUILD_EXECUTABLE)

