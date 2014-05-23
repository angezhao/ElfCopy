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
    if (!hasLoadedCamera){
        //[self performSelector:@selector(OpenCamera) withObject:nil afterDelay:3];
        hasLoadedCamera = true;
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
//    if (!hasLoadedCamera){
//        [self performSelector:@selector(OpenCamera) withObject:nil afterDelay:1];
//        hasLoadedCamera = true;
//    }

}

+(Camera*)PickPhoto
{
    Camera *viewController = [[Camera alloc] init];
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    // Set ViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }

    [viewController OpenCamera];
    
    return viewController;
}

-(void)OpenCamera
{
    hasLoadedCamera=true;
    NSLog(@"启动相机");
    UIImagePickerController *picker= [[[UIImagePickerController alloc] init] autorelease];
    picker.delegate = self;
    picker.allowsEditing = YES;
    picker.wantsFullScreenLayout = YES;
    
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;//UIImagePickerControllerSourceTypeCamera;//UIImagePickerControllerSourceTypePhotoLibrary
    }
    else
    {
        NSLog(@"模拟器无法打开相机");
    }
    UIDeviceOrientation c = [[UIDevice currentDevice] orientation];
    NSUInteger a = [self supportedInterfaceOrientations];
    BOOL b = [self shouldAutorotate];

    [self presentModalViewController:picker animated:YES];
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

//- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
//    // Return YES for supported orientations
//    BOOL a = (interfaceOrientation == UIInterfaceOrientationPortrait);
//    return a;
//}
//
//- (NSUInteger)supportedInterfaceOrientations
//{;
//    NSUInteger a =UIInterfaceOrientationIsPortrait(UIInterfaceOrientationMaskPortrait|| UIInterfaceOrientationMaskPortraitUpsideDown);
//    return a;
//    
//}


//- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation
//{
//    if (self.interfaceOrientation == UIInterfaceOrientationPortrait)
//    {
//        return UIInterfaceOrientationPortrait;
//    }
//    else if ([self interfaceOrientation] == UIInterfaceOrientationLandscapeLeft||[self interfaceOrientation] == UIInterfaceOrientationLandscapeRight)
//    {
//        return UIInterfaceOrientationMaskAll;
//    }
//}

//-(NSUInteger)supportedInterfaceOrientations{
//    return UIInterfaceOrientationPortrait;
//}

//- (BOOL)shouldAutorotate
//{
//    return NO;
//}

//-(UIInterfaceOrientation)preferredInterfaceOrientationForPresentation
//{
//    return UIInterfaceOrientationPortrait;
//}

//- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window {
//    return UIInterfaceOrientationPortrait;
//}

@end
