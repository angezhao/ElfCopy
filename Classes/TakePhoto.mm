//
//  TakePhoto.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//  拍照
//

#include "TakePhoto.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Camera.h"
#include "ViewController.h"
#endif
#include "MainLayer.h"
#include "PhotoMenu.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"
#include "cocos2d.h"


TakePhoto::TakePhoto()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    [Camera PickPhoto];
//    ViewController * viewController = [[ViewController alloc] init];
//    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
//    // Set RootViewController to window
//    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
//    {
//        // warning: addSubView doesn't work on iOS6
//        [window addSubview: viewController.view];
//    }
//    else
//    {
//        // use this method on ios6
//        [window setRootViewController:viewController];
//    }
//    [viewController OpenCamera];
    
    //auto director = cocos2d::Director::getInstance();
    //UIView *glview = (UIView*)director->getOpenGLView();
    //[glview addSubview:viewController.view];
    //[[Director sharedDirector] pause];
    //Director::sharedDirector()->end();
    //[self dismissViewControllerAnimated:YES completion:nil];
    //[[[Director sharedDirector] _openGLView] addSubview:imagePickerController.view];

    
    //cocos2d::Director::getInstance()->pause();
    //cocos2d::Director::getInstance()->setOpenGLView(viewController.view)
    //[[[Director sharedDirector] openGLView] addSubview:controller.view];
    //[[Director sharedDirector] pause];
    //UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];
    //[keyWindow.rootViewController.view addSubview: viewController.view];
    //UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    //[window addSubview:viewController.view];
    
    
    
#else
    //Android代码
#endif
    
}

TakePhoto::~TakePhoto()
{
}