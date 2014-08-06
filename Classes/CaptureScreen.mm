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
#include "AWScreenshot.h"
#include "CCEAGLView.h"
#include "cocos2d.h"

using namespace cocos2d;

static THCapture *capture;

void CaptureScreen::startRecord()
{
    if (capture == NULL) {
        capture=[[THCapture alloc] init];
    }
    [capture startRecording];
}

void CaptureScreen::stopRecord(const char * audioPath)
{
    bool ret = [capture stopRecording];
    if (ret) {
        //处理保存的视频
        const char *outputPath = [capture.outputPath UTF8String];
        CCLOG("outputPath=%s", outputPath);
        NSString *aPath= [NSString stringWithUTF8String:audioPath];
        log("audioPath=%s",audioPath);
        //混合保存
        [capture setVideoPath:[THCaptureUtilities mergeVideo:capture.outputPath andAudio:aPath]];
    }
}

void CaptureScreen::saveVideo()
{
    if([capture videoPath] == nil)
        return;
    [THCaptureUtilities mergedidFinish:[capture videoPath]];
    [capture setVideoPath:nil];
}

//测试用
void CaptureScreen::drawFrame()
{
     NSLog(@"start CaptureScreen:drawFrame.......");
    /*
    cocos2d::Size size = Director::getInstance()->getWinSize();
    RenderTexture *screen = CCRenderTexture::create(size.width, size.height);
    Scene *scene = Director::getInstance()->getRunningScene();
    screen->begin();
    scene->visit();//将当前的整个scene绘出来
    screen->end();
    screen->saveToFile("MyCurScene.png", Image::Format::PNG);
    */
    /*
    std::string strPath = FileUtils::getInstance()->getWritablePath() + "MyCurScene.png";
    NSString* path = [NSString stringWithUTF8String:strPath.c_str()];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    UIImageWriteToSavedPhotosAlbum(image, nil, nil,nil);
     */
    
    //CGImageRef cgImage = [AWScreenshot takeAsCGImage];
    UIImage *currentImg = [AWScreenshot takeAsImage];
    //NSData *imageData = UIImagePNGRepresentation([UIImage imageWithCGImage:cgImage]);
    UIImageWriteToSavedPhotosAlbum(currentImg, nil, nil, nil);
    
    /*
    NSData *imageData = UIImageJPEGRepresentation(currentImg,1);
    // 获取沙盒目录
    NSString *fullPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"currentImage.png"];
    NSLog(@"path=%@",fullPath);
    // 将图片写入文件
    [imageData writeToFile:fullPath atomically:NO];
    Image* image = new Image();
    image->initWithImageData((unsigned char *)[imageData bytes], [imageData length]);
    */
    
    NSLog(@"end CaptureScreen:drawFrame.......");
}


