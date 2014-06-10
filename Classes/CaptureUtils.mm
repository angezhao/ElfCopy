//
//  CaptureUtils.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-6-10.
//
//

#include "CaptureUtils.h"
#include "RootViewController.h"

void CaptureUtils::startRecord()
{
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    RootViewController *rootViewController;
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        //[window addSubView];
    }
    else
    {
        
        rootViewController = [window rootViewController];
        [rootViewController startCapture];
    }

}

void CaptureUtils::stopRecord()
{
    
}