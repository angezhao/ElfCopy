//
//  Camera.m
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//
//

#import "Camera.h"
#include "cocos2d.h"

@implementation Camera

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        hasLoadedCamera = false;
    }
    return self;
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    //show camera...
    //if (!hasLoadedCamera)
    //    [self performSelector:@selector(showcamera) withObject:nil afterDelay:0.3];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    //if (!hasLoadedCamera)
    //    [self performSelector:@selector(showcamera) withObject:nil afterDelay:0.3];

}


- (void)showcamera {
    hasLoadedCamera=true;
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    [imagePicker setDelegate:self];
    [imagePicker setSourceType:UIImagePickerControllerSourceTypeCamera];
    [imagePicker setAllowsEditing:YES];
    [self presentModalViewController:imagePicker animated:YES];
}

//+(Camera*)PickPhoto
//{
//    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
//    Camera *viewController = [[Camera alloc] init];
//    [window addSubview:viewController.view];
//    [viewController OpenCamera];
//    
//    return viewController;
//}
//
//-(void)OpenCamera
//{
//    NSLog(@"启动相机");
//    UIImagePickerController *picker= [[UIImagePickerController alloc] init];
//    picker.delegate = self;
//    picker.allowsEditing = YES;
//    
//    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
//    {
//        picker.sourceType = UIImagePickerControllerSourceTypeCamera;
//        
//    }
//    else
//    {
//        NSLog(@"模拟器无法打开相机");
//    }
//
//    [self presentViewController:picker animated:YES completion:^{}];
//    //[self presentViewController:picker animated:YES completion:nil];
//    [picker release];
//    
////    UIImagePickerController * ipc = [[UIImagePickerController alloc]init];
////    ipc.sourceType = UIImagePickerControllerSourceTypeCamera;
////    ipc.delegate = self;
////    ipc.wantsFullScreenLayout=YES;
////    ipc.allowsImageEditing=NO;
////    [self presentModalViewController:ipc animated:YES];
//    
//}

//拍照
- (void)imagePickerController:(UIImagePickerController *)picker
didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSLog(@"拍照");
    UIImage *originImage = [info objectForKey:UIImagePickerControllerOriginalImage];
    //保存原图到相册
    UIImageWriteToSavedPhotosAlbum(originImage, nil, nil, nil);
    
    [picker dismissViewControllerAnimated:false completion:nil];
    [self.view removeFromSuperview];
    
    
}
//取消
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    NSLog(@"取消");
    
    [picker dismissViewControllerAnimated:false completion:nil];
    [self.view removeFromSuperview];
    
    
}

-(void) dealloc
{
    [self release];
    [super dealloc];
}

@end
