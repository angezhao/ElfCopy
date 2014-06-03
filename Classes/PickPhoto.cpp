//
//  PickPhoto.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-25.
//  拍照
//

#include "PickPhoto.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PickPhoto4Ios.h"
#else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

PickPhoto::PickPhoto(bool takePhoto)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    PickPhoto4Ios * photo4Ios = new PickPhoto4Ios(takePhoto);
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
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
    
}

PickPhoto::~PickPhoto()
{
}