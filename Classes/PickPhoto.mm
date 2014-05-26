//
//  PickPhoto.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-25.
//  拍照
//

#include "PickPhoto.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Camera.h"
#endif


PickPhoto::PickPhoto(bool takePhoto)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    Camera * camera = [[Camera alloc] init];
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: camera.view];
    }
    else
    {
        [camera setRootViewController:[window rootViewController]];
        // use this method on ios6
        [window setRootViewController:camera];
    }
    [camera OpenPicker:takePhoto];
#else //if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android代码
    cocos2d::JniMethodInfo methodInfo;
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
                                                          "org/cocos2dx/cpp/PicHandler",
                                                          "pickPhoto",
                                                          "()V"
                                                          );
    
    if(isHave){
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    }

#endif
    
}

PickPhoto::~PickPhoto()
{
}
