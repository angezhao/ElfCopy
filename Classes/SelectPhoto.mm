//
//  SelectPhoto.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//  选照
//

#include "SelectPhoto.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Camera.h"
#endif
#include "cocostudio/CocoStudio.h"
#include "Constants.h"
#include "cocos2d.h"


SelectPhoto::SelectPhoto()
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
    [camera OpenPhotos];
    
#else
    //Android代码
#endif
    
}

SelectPhoto::~SelectPhoto()
{
}