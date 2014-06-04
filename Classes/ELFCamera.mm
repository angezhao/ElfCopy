//
//  Camera.m
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-28.
//
//

#import "ELFCamera.h"
#include "PickPhoto.h"

@interface ELFCamera ()

@end

@implementation ELFCamera

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


-(void)OpenPicker:(BOOL) takePhoto
{
    NSLog(@"打开相机或相册");
    // 跳转到相机或相册
    UIImagePickerController *imagePickerController = [[[UIImagePickerController alloc] init] autorelease];
    imagePickerController.delegate = self;
    //imagePickerController.allowsEditing = YES;
    
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        if (takePhoto) {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
        }
        else
        {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        }
    }
    else
    {
        //NSLog(@"模拟器无法打开相机");
        imagePickerController.sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
    }
    [self presentModalViewController:imagePickerController animated:YES];
}

#pragma mark - image picker delegte
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSLog(@"拍照");
    UIImage *originImage = [info objectForKey:UIImagePickerControllerOriginalImage];
    //判断是否原图到相册
    if (picker.sourceType == UIImagePickerControllerSourceTypeCamera)
    {
        UIImageWriteToSavedPhotosAlbum(originImage, nil, nil, nil);
    }
    
    [self dismissViewControllerAnimated:false completion:nil];
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    // Set ViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [self.view removeFromSuperview];
        //[window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:[self rootViewController]];
    }
    //转到图片处理
    NSString *fullPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"currentImage.png"];
    const char *photofile = [fullPath UTF8String];
    
    //PickPhoto* layer = (PickPhoto*)this->getParent()->getParent();
    //layer->pickOk(photofile);
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
	NSLog(@"取消");
    [self dismissViewControllerAnimated:false completion:nil];
    
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    // Set ViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [self.view removeFromSuperview];
        //[window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:[self rootViewController]];
    }
}

-(void) dealloc
{
    [self release];
    [super dealloc];
}

@end
