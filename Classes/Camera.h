//
//  Camera.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//
//

#import <Foundation/Foundation.h>

@interface Camera :UIViewController<UIImagePickerControllerDelegate,UINavigationControllerDelegate> {
    Boolean hasLoadedCamera;
}

+(Camera*)PickPhoto;

@property(nonatomic,retain) UIImageView *imageView;
@property(nonatomic,retain) UIViewController *rootViewController;

//打开摄像头
-(void)OpenCamera;
//打开相册
-(void)OpenPhotos;

@end
