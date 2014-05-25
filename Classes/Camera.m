//
//  Camera.m
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//
//

#import "Camera.h"

@implementation Camera

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        //hasLoadedCamera = false;
    }
    return self;
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
//    if (!hasLoadedCamera){
//        [self performSelector:@selector(OpenCamera) withObject:nil afterDelay:0.3];
//        hasLoadedCamera = true;
//    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
//    if (!hasLoadedCamera){
//        [self performSelector:@selector(OpenCamera) withObject:nil afterDelay:0.3];
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
    NSLog(@"打开相机");
    // 跳转到相机
    UIImagePickerController *imagePickerController = [[[UIImagePickerController alloc] init] autorelease];
    imagePickerController.delegate = self;
    imagePickerController.allowsEditing = YES;
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
    }
    else
    {
        NSLog(@"模拟器无法打开相机");
    }
    [self presentModalViewController:imagePickerController animated:YES];
}

-(void)OpenPhotos
{
    NSLog(@"打开相册");
    // 跳转到相册页面
    UIImagePickerController *imagePickerController = [[[UIImagePickerController alloc] init] autorelease];
    imagePickerController.delegate = self;
    imagePickerController.allowsEditing = YES;
    imagePickerController.sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
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
//    
//    [self.imageView setImage:savedImage];
//    
//    self.imageView.tag = 100;
    

//    UIImage *originImage = [info objectForKey:UIImagePickerControllerOriginalImage];
//    //保存原图到相册
//    UIImageWriteToSavedPhotosAlbum(originImage, nil, nil, nil);
    
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
    [_imageView release];
    [self release];
    [super dealloc];
}

@end
