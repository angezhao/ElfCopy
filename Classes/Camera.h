//
//  Camera.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//
//

#import <Foundation/Foundation.h>

@interface Camera :UIViewController<UIImagePickerControllerDelegate,UINavigationControllerDelegate>

@property(nonatomic,retain) UIViewController *rootViewController;

//打开摄像头或相册
-(void)OpenPicker:(BOOL) takePhoto;

@end
