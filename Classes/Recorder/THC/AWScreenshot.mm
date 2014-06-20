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
    CGSize outSize = CGSizeMake(1024, 768);
    CGSize screenSize = [UIScreen mainScreen].currentMode.size;
    int height = screenSize.height;
    int width = screenSize.width;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {//iphone反转
        height = screenSize.width;
        width = screenSize.height;
    }
    // Create buffer for pixels
    GLuint bufferLength = width * height *4;
    GLubyte* buffer =(GLubyte*)malloc(bufferLength);
    
    // Read Pixels from OpenGL
    //glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    // Make data provider with data.
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, bufferLength, NULL);
    
//#if __IPHONE_OS_VERSION_MAX_ALLOWED > __IPHONE_6_1
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault | kCGImageAlphaPremultipliedLast;
//#else
    //CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast;
//#endif
    
    // Configure image
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGImageRef iref = CGImageCreate(width, height, 8, 32, width*4, colorSpaceRef, kCGBitmapByteOrderDefault, provider, NULL, NO, kCGRenderingIntentDefault);
    
    // Create buffer for output image
    uint32_t* pixels =(uint32_t*)malloc(outSize.width * outSize.height *4);

    CGContextRef context = CGBitmapContextCreate(pixels, outSize.width, outSize.height, 8, outSize.width *4, colorSpaceRef, bitmapInfo);
    //kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);//kCGImageAlphaNoneSkipFirst
    
    // Transform
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
    CGContextTranslateCTM(context, 0, outSize.height);
    CGContextScaleCTM(context, 1, -1);
    
    /*
    switch([[UIDevice currentDevice] orientation])
    {
//            UIDeviceOrientationUnknown,
//            UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
//            UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
//            UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
//            UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
//            UIDeviceOrientationFaceUp,              // Device oriented flat, face up
//            UIDeviceOrientationFaceDown             // Device oriented flat, face down
            
        case UIDeviceOrientationPortrait:break;
        case UIDeviceOrientationPortraitUpsideDown:
            CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(180));
            CGContextTranslateCTM(context, -displaySize.width, -displaySize.height);
            break;
        case UIDeviceOrientationLandscapeLeft:
            CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(-90));
            CGContextTranslateCTM(context, -displaySize.height, 0);
            break;
        case UIDeviceOrientationLandscapeRight:
            CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(90));
            CGContextTranslateCTM(context, displaySize.height-displaySize.width, -displaySize.height);
            break;
        case UIDeviceOrientationFaceUp:
            break;
        case UIDeviceOrientationFaceDown:
            break;
        default:
            break;
    }
    */
    
    // Render
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, outSize.width, outSize.height), iref);
    
#else
    CGContextTranslateCTM(context, 0, outSize.height);
    CGContextScaleCTM(context, 1, -1);
    
    // Render
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, outSize.width, outSize.height), iref);
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
