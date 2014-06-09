//
//  Camera.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-28.
//
//

#import <UIKit/UIKit.h>
#include "cocos2d.h"

using namespace cocos2d;

@interface ELFCamera :UIViewController<UIImagePickerControllerDelegate,UINavigationControllerDelegate> {
    UIPopoverController *popoverController;
}

@property(nonatomic,retain) UIViewController *rootViewController;

//打开摄像头或相册
-(void)OpenPicker:(BOOL) takePhoto;

@end
