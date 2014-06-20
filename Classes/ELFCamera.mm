//
//  Camera.m
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-28.
//
//

#import "ELFCamera.h"
#include "GameScene.h"
#include "StartLayer.h"
#include "MainLayer.h"
#include "PhotoMenu.h"
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
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        [self presentModalViewController:imagePickerController animated:YES];
    }
    else {
        popoverController = [[UIPopoverController alloc] initWithContentViewController:imagePickerController];
        [popoverController presentPopoverFromRect:CGRectMake(0, 0, 600, 600) inView:self.view permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
    }
}

#pragma mark - image picker delegte
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSLog(@"拍照");
    UIImage *originImage = [info objectForKey:UIImagePickerControllerOriginalImage];
    // 判断是否原图到相册
    if (picker.sourceType == UIImagePickerControllerSourceTypeCamera)
    {
        // 不需要保存到相册里去
        // UIImageWriteToSavedPhotosAlbum(originImage, nil, nil, nil);
    }
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        [self dismissViewControllerAnimated:false completion:nil];
    }
    else {
        [popoverController dismissPopoverAnimated:YES];
    }
    
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
    
    NSData *imageData = UIImageJPEGRepresentation(originImage, 0.8);
    Image* image = new Image();
    image->initWithImageData((unsigned char *)[imageData bytes], [imageData length]);
    
    auto director = Director::getInstance();
    GameScene* layer1 = (GameScene*)director->getRunningScene()->getChildByTag(1);
    StartLayer* layer2 = (StartLayer*)layer1->getChildByTag(1);
    MainLayer* layer3 = (MainLayer*)layer2->getChildByTag(1);
    PhotoMenu* layer4 = (PhotoMenu*)layer3->getChildByTag(1);
    PickPhoto* layer = (PickPhoto*)layer4->getChildByTag(1);
    layer->pickOk(image);
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
	NSLog(@"取消");
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        [self dismissViewControllerAnimated:false completion:nil];
    }
    else {
        [popoverController dismissPopoverAnimated:YES];
    }
    
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
