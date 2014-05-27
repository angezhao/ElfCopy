//
//  Camera.m
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//
//

#import "Camera.h"
#include "PhotoLayer.h"
#include "Constants.h"
#include "cocos2d.h"

@implementation Camera

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
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
}

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

#pragma mark - 保存图片至沙盒
- (void) saveImage:(UIImage *)currentImage withName:(NSString *)imageName
{
    
    //NSData *imageData = UIImageJPEGRepresentation(currentImage, 0.5);
    // 获取沙盒目录
    
    //NSString *fullPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:imageName];
    
    // 将图片写入文件
    
    //[imageData writeToFile:fullPath atomically:NO];
}

#pragma mark - image picker delegte
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSLog(@"拍照");
//    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
//    
//    [self saveImage:image withName:@"currentImage.png"];
//    
//    NSString *fullPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"currentImage.png"];
//    
//    UIImage *savedImage = [[UIImage alloc] initWithContentsOfFile:fullPath];
    

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
    cocos2d::Layer * pLayer = new PhotoLayer(photofile);
    pLayer->autorelease();
    m_pLayer->addChild(pLayer);
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
