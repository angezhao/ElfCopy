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
#include "MainLayer.h"
#include "PhotoMenu.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"
#include "cocos2d.h"


PickPhoto::PickPhoto()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    //[Camera PickPhoto];
    //Camera * camera = [[Camera alloc] init];
    //[camera viewDidLoad];
    Camera * viewController = [[Camera alloc] init];
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    [viewController OpenCamera];
    
#else
    //Android代码
#endif
    
}

PickPhoto::~PickPhoto()
{
}
