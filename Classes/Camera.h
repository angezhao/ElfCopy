//
//  Camera.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-28.
//
//

#import <UIKit/UIKit.h>

@interface Camera :UIViewController<UIImagePickerControllerDelegate,UINavigationControllerDelegate>

@property(nonatomic,retain) UIViewController *rootViewController;

//打开摄像头或相册
-(void)OpenPicker:(BOOL) takePhoto;

@end
