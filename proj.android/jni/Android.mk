LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   hellocpp/JavaToC.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/Constants.cpp \
				   ../../Classes/MainLayer.cpp \
				   ../../Classes/PhotoLayer.cpp \
				   ../../Classes/PhotoMenu.cpp \
				   ../../Classes/StartLayer.cpp \
				   ../../Classes/VidioLayer.cpp \
				   ../../Classes/PickPhoto.cpp 
				   
				   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,editor-support/cocostudio)
$(call import-module,Box2D)
