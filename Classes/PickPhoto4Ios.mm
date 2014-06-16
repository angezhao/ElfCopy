//
//  PickPhoto4Ios.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-27.
//
//

#include "PickPhoto4Ios.h"
#include "ELFCamera.h"
#include "cocos2d.h"

void PickPhoto4Ios::takePickPhoto(bool takePhoto)
{
    //iOS代码
    // ELFCamera * camera = [[[ELFCamera alloc] init]autorelease];
    ELFCamera * camera = [[ELFCamera alloc] init];
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
}