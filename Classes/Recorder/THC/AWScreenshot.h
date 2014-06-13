//
//  AWScreenshot.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-6-13.
//
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface AWScreenshot :NSObject
{
}

+(CGImageRef) takeAsCGImage;

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
+(UIImage*) takeAsImage;
#else
+(CGImageRef) takeAsImage;
#endif

//+(cocos2d::Texture2D*) takeAsTexture;

@end
