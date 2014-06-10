//
//  PickPhoto.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-25.
//  拍照
//

#include "PickPhoto.h"
#include "PhotoLayer.h"
#include "Constants.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PickPhoto4Ios.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

bool PickPhoto::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    PickPhoto4Ios::takePickPhoto(selectOrPick);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android代码
    cocos2d::JniMethodInfo methodInfo;
    
	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
                                                          "org/cocos2dx/cpp/PicHandler",
                                                          "getPhoto",
                                                          "(Z)V"
                                                          );
	
    
    if(isHave){
		jboolean jTakePhoto = takePhoto;
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jTakePhoto);
    }
    
#endif

    return true;
}

void PickPhoto::pickOk(Image* image)
{
    // 退回上一层
    Layer* parent = (Layer*)this->getParent();
    this->removeFromParentAndCleanup(true);
    PhotoLayer * layer = PhotoLayer::create();
    layer->loadImage(image);
    parent->addChild(layer, 0, 1);
}