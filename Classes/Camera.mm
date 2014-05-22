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
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    if (!hasLoadedCamera){
        [self performSelector:@selector(OpenCamera) withObject:nil afterDelay:0.3];
        hasLoadedCamera = true;
    }

}

+(Camera*)PickPhoto
{
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    Camera *viewController = [[Camera alloc] init];
    [window addSubview:viewController.view];
    //[viewController OpenCamera];
    
    return viewController;
}

-(void)OpenCamera
{
    hasLoadedCamera=true;
    NSLog(@"启动相机");
    UIImagePickerController *picker= [[UIImagePickerController alloc] init];
    picker.delegate = self;
    picker.allowsEditing = YES;
    picker.wantsFullScreenLayout = YES;
    
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        picker.sourceType = UIImagePickerControllerSourceTypeCamera;
        
    }
    else
    {
        NSLog(@"模拟器无法打开相机");
    }

    //[self presentViewController:picker animated:YES completion:nil];
    [self presentModalViewController:picker animated:FALSE];
    [picker release];
    
}

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
