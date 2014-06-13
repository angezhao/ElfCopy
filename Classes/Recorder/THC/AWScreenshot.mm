//
//  AWScreenshot.m
//  ElfCopy
//
//  Created by Ange Zhao on 14-6-13.
//
//

#import "AWScreenshot.h"
#import "CCDirector.h"
#import "platform/CCDevice.h"
#import "ccMacros.h"
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#define AWIMAGE UIImage*
#else
#define AWIMAGE CGImageRef
#endif

using namespace cocos2d;

@implementation AWScreenshot

#pragma mark -
#pragma mark Take screenshot as data

+(CGImageRef) takeAsCGImage
{
    Director *director = Director::getInstance();
    cocos2d::Size winSize = director->getWinSize();
    cocos2d::Size displaySize = director->getVisibleSize();
    
    // Create buffer for pixels
    GLuint bufferLength = displaySize.width * displaySize.height *4;
    GLubyte* buffer =(GLubyte*)malloc(bufferLength);
    
    // Read Pixels from OpenGL
    glReadPixels(0, 0, displaySize.width, displaySize.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    // Make data provider with data.
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, bufferLength, NULL);
    
    // Configure image
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGImageRef iref = CGImageCreate(displaySize.width, displaySize.height, 8, 32, displaySize.width *4, colorSpaceRef, kCGBitmapByteOrderDefault, provider, NULL, NO, kCGRenderingIntentDefault);
    
    // Create buffer for output image
    uint32_t* pixels =(uint32_t*)malloc(winSize.width * winSize.height *4);
    CGContextRef context = CGBitmapContextCreate(pixels, winSize.width, winSize.height, 8, winSize.width *4, colorSpaceRef, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    
    // Transform
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
    CGContextTranslateCTM(context, 0, displaySize.height);
    CGContextScaleCTM(context, 1, -1);
    
    /*
    switch([[UIApplication sharedApplication] statusBarOrientation])
    {
        case UIInterfaceOrientationPortrait:
            break;
        case UIInterfaceOrientationPortraitUpsideDown:
            CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(180));
            CGContextTranslateCTM(context, -displaySize.width, -displaySize.height);
            break;
        case UIInterfaceOrientationLandscapeLeft:
            CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(-90));
            CGContextTranslateCTM(context, -displaySize.height, 0);
            break;
        case UIInterfaceOrientationLandscapeRight:
            CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(90));
            CGContextTranslateCTM(context, displaySize.height-displaySize.width, -displaySize.height);
            break;
    }
    */
    
    // Render
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, displaySize.width, displaySize.height), iref);
    
#else
    CGContextTranslateCTM(context, 0, winSize.height);
    CGContextScaleCTM(context, 1, -1);
    
    // Render
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, winSize.width, winSize.height), iref);
#endif
    
    // Create image
    CGImageRef imageRef = CGBitmapContextCreateImage(context);
    
    // Dealloc
    CGDataProviderRelease(provider);
    CGImageRelease(iref);
    CGColorSpaceRelease(colorSpaceRef);
    CGContextRelease(context);
    free(buffer);
    free(pixels);
    
    return imageRef;
}

#pragma mark -
#pragma mark Take screenshot as image

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED

+(UIImage*) takeAsImage
{
    CGImageRef imageRef =[self takeAsCGImage];
    UIImage *outputImage =[[[UIImage alloc] initWithCGImage:imageRef] autorelease];
    
    CGImageRelease(imageRef);
    return outputImage;
}

#else

+(CGImageRef) takeAsImage
{
    return[self takeAsCGImage];
}

#endif

#pragma mark -
#pragma mark Take screenshot as texture

//+(Texture2D*) takeAsTexture
//{
//    AWIMAGE imageRef =[self takeAsImage];
//    Texture2D *outputTexture =[[[Texture2D alloc] initWithImage:imageRef] autorelease];
//    
//#ifndef __IPHONE_OS_VERSION_MAX_ALLOWED
//    CGImageRelease(imageRef);
//#endif
//    return outputTexture;
//}

@end
