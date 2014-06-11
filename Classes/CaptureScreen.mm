//
//  CaptureScreen.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-6-10.
//
//

#include "CaptureScreen.h"
#include "THCapture.h"
#include "THCaptureUtilities.h"
#include "CCEAGLView.h"
#include "cocos2d.h"
using namespace cocos2d;

static THCapture *capture;

void CaptureScreen::startRecord()
{
    if (capture == NULL) {
        CCEAGLView *eaglView = (CCEAGLView*)cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView();
        capture=[[THCapture alloc] init];
        capture.frameRate = 60;
        capture.captureLayer = eaglView.layer;
    }
    [capture startRecording];
}

void CaptureScreen::stopRecord()
{
    bool ret = [capture stopRecording];
    if (ret) {
        //处理保存的视频
        const char *outputPath = [capture.outputPath UTF8String];
        log("outputPath=%s",outputPath);
        //混合保存
        //[THCaptureUtilities mergeVideo:capture.outputPath andAudio:path];
    }
}

void CaptureScreen::drawFrame()
{
    [capture drawFrame];
}

