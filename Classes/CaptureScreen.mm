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
        capture.frameRate = 30;
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
        [THCaptureUtilities mergeVideo:capture.outputPath andAudio:nil];
    }
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
    
    UIImage *currentImg = [AWScreenshot takeAsImage];
    UIImageWriteToSavedPhotosAlbum(currentImg, nil, nil, nil);
    
    NSData *imageData = UIImageJPEGRepresentation(currentImg, 0.5);
    // 获取沙盒目录
    NSString *fullPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"currentImage.png"];
    NSLog(@"path=%@",fullPath);
    // 将图片写入文件
    [imageData writeToFile:fullPath atomically:NO];
    
    
    /*
    Image* ccImg = screen->newImage(true);
    int _width = ccImg->getWidth();
    int _height = ccImg->getHeight();
    unsigned char *_data = ccImg->getData();
    bool hasAlpha = ccImg->hasAlpha();
    bool saveToPNG = true;
    bool isToRGB = true;
    int bitsPerComponent = 8;
    int bitsPerPixel = hasAlpha ? 32 : 24;
    if ((! saveToPNG) || isToRGB)
    {
        bitsPerPixel = 24;
    }
    
    
    int bytesPerRow    = (bitsPerPixel/8) * _width;
    int myDataLength = bytesPerRow * _height;
    
    unsigned char *pixels    = _data;
    
    // The data has alpha channel, and want to save it with an RGB png file,
    // or want to save as jpg,  remove the alpha channel.
    if ((saveToPNG && hasAlpha && isToRGB)
        || (! saveToPNG))
    {
        pixels = new unsigned char[myDataLength];
        
        for (int i = 0; i < _height; ++i)
        {
            for (int j = 0; j < _width; ++j)
            {
                pixels[(i * _width + j) * 3] = _data[(i * _width + j) * 4];
                pixels[(i * _width + j) * 3 + 1] = _data[(i * _width + j) * 4 + 1];
                pixels[(i * _width + j) * 3 + 2] = _data[(i * _width + j) * 4 + 2];
            }
        }
    }
    
    // make data provider with data.
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    if (saveToPNG && hasAlpha && (! isToRGB))
    {
        bitmapInfo |= kCGImageAlphaPremultipliedLast;
    }
    CGDataProviderRef provider        = CGDataProviderCreateWithData(nullptr, pixels, myDataLength, nullptr);
    CGColorSpaceRef colorSpaceRef    = CGColorSpaceCreateDeviceRGB();
    CGImageRef iref                    = CGImageCreate(_width, _height,
                                                       bitsPerComponent, bitsPerPixel, bytesPerRow,
                                                       colorSpaceRef, bitmapInfo, provider,
                                                       nullptr, false,
                                                       kCGRenderingIntentDefault);
    
    UIImage* image                    = [[UIImage alloc] initWithCGImage:iref];
    CGImageRelease(iref);
    CGColorSpaceRelease(colorSpaceRef);
    CGDataProviderRelease(provider);
    
    NSData *data;
    
    if (saveToPNG)
    {
        data = UIImagePNGRepresentation(image);
    }
    else
    {
        data = UIImageJPEGRepresentation(image, 1.0f);
    }
    // 获取沙盒目录
    NSString *fullPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"currentImage.png"];
    [data writeToFile:fullPath atomically:YES];
    
    [image release];
    */
    NSLog(@"end CaptureScreen:drawFrame.......");
    
    
    //[capture drawFrame:curImage];
    /*
    CCEAGLView *eaglView = (CCEAGLView*)Director::getInstance()->getOpenGLView()->getEAGLView();
    UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];
    CGRect rect = [keyWindow bounds];
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef curContext = UIGraphicsGetCurrentContext();
    [eaglView.layer renderInContext:curContext];
    UIImage *currentImg = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    //CGImageRef cgImage=currentImg.CGImage;
    
    //UIImageWriteToSavedPhotosAlbum(currentImg, nil, nil, nil);
    NSData *imageData = UIImageJPEGRepresentation(currentImg, 0.5);
    // 获取沙盒目录
    NSString *fullPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"currentImage.png"];
    NSLog(@"path=%@",fullPath);
    // 将图片写入文件
    [imageData writeToFile:fullPath atomically:NO];
     */
    
    
}


