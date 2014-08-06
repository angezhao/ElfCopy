//
//  THCapture.m
//  ScreenCaptureViewTest
//
//  Created by wayne li on 11-8-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "THCapture.h"
#import "CGContextCreator.h"
#import "AWScreenshot.h"

static NSString* const kFileName=@"output.mov";

@interface THCapture()
//配置录制环境
- (BOOL)setUpWriter;
//清理录制环境
- (void)cleanupWriter;
//完成录制工作
- (BOOL)completeRecordingSession;
@end

@implementation THCapture
@synthesize startedAt=_startedAt;
@synthesize avAdaptor=_avAdaptor;
@synthesize outputPath=_outputPath;
@synthesize videoPath=_videoPath;

- (id)init
{
    self = [super init];
    if (self) {
        CGSize screenSize = [UIScreen mainScreen].currentMode.size;
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {//iphone反转
            _frameRate=30;//默认帧率为30
            width = screenSize.height;
            height = screenSize.width;
            outWidth = 480;//输出尺寸
            outHeight = 320;
        }else{
            _frameRate=10;//默认帧率为10
            width = screenSize.width;
            height = screenSize.height;
            outWidth = 256;//输出尺寸
            outHeight = 192;
        }
        NSLog(@"width=%zu,height=%zu",width,height);
    }
    
    return self;
}

- (void)dealloc {
	[self cleanupWriter];
    [super dealloc];
}

#pragma mark -
#pragma mark CustomMethod

- (bool)startRecording
{
    self.videoPath = nil;
    bool result = NO;
    if (! _recording)
    {
        result = [self setUpWriter];
        if (result)
        {
            self.startedAt = [NSDate date];
            _recording = true;
            _writing = false;
            // 绘屏的定时器
            NSLog(@"_frameRate=%lu", (unsigned long)_frameRate);
            NSDate *nowDate = [NSDate date];
            timer = [[NSTimer alloc] initWithFireDate:nowDate interval:1.0/_frameRate target:self selector:@selector(drawFrame) userInfo:nil repeats:YES];
            [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
        }
    }
	return result;
}

- (bool)stopRecording
{
    bool result = NO;

    if (_recording) {
         _recording = false;
        [timer invalidate];
        timer = nil;
        result = [self completeRecordingSession];
        [self cleanupWriter];
    }
    return result;
}

- (void)drawFrame
{
    if (!_writing) {
        //NSLog(@"start drawFrame.......");
        [self getFrame];
        //NSLog(@"end drawFrame.......");
    }
}

-(void) writeVideoFrameAtTime:(CMTime)time addImage:(CGImageRef )newImage
{
    if (![videoWriterInput isReadyForMoreMediaData]) {
		NSLog(@"Not ready for video data");
	}
	else {
		@synchronized (self) {
			CVPixelBufferRef pixelBuffer = NULL;
			//CGImageRef cgImage = CGImageCreateCopy(newImage);
            
			CFDataRef image = CGDataProviderCopyData(CGImageGetDataProvider(newImage));
			
			int status = CVPixelBufferPoolCreatePixelBuffer(kCFAllocatorDefault, self.avAdaptor.pixelBufferPool, &pixelBuffer);
			if(status != 0){
				//could not get a buffer from the pool
				NSLog(@"Error creating pixel buffer:  status=%d", status);
			}
			// set image data into pixel buffer
			CVPixelBufferLockBaseAddress( pixelBuffer, 0 );
			UInt8 * destPixels = (UInt8 *)CVPixelBufferGetBaseAddress(pixelBuffer);
			CFDataGetBytes(image, CFRangeMake(0, CFDataGetLength(image)), destPixels);  //XXX:  will work if the pixel buffer is contiguous and has the same bytesPerRow as the input data
			
			if(status == 0){
				BOOL success = [self.avAdaptor appendPixelBuffer:pixelBuffer withPresentationTime:time];
				if (!success)
					NSLog(@"Warning:  Unable to write buffer to video");
			}
			
			//clean up
			CVPixelBufferUnlockBaseAddress( pixelBuffer, 0 );
			CVPixelBufferRelease( pixelBuffer );
			CFRelease(image);
			//CGImageRelease(cgImage);
		}
	}
}

- (void)getFrame
{
    if (!_writing) {
        _writing = true;
        @try {
            
            GLuint bufferLength = width * height *4;
            GLubyte* buffer =(GLubyte*)malloc(bufferLength);
            
            // Read Pixels from OpenGL
            glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            
            // Make data provider with data.
            CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
            CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, bufferLength, NULL);
            
            // Configure image
            CGImageRef iref = CGImageCreate(width, height, 8, 32, width *4, colorSpaceRef, kCGBitmapByteOrderDefault, provider, NULL, NO, kCGRenderingIntentDefault);
            // Create buffer for output image
            uint32_t* pixels =(uint32_t*)malloc(outWidth * outHeight *4);
            CGContextRef context = CGBitmapContextCreate(pixels, outWidth, outHeight, 8, outWidth *4, colorSpaceRef, kCGImageAlphaNoneSkipFirst);//kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);//kCGImageAlphaNoneSkipFirst
            CGContextTranslateCTM(context, 0, outHeight);
            CGContextScaleCTM(context, 1, -1);
            //CGContextSetAllowsAntialiasing(context,NO);
            //CGAffineTransform flipVertical = CGAffineTransformMake(1, 0, 0,-1, 0, height);
            //CGContextConcatCTM(context, flipVertical);
            
            // Render
            CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, outWidth , outHeight), iref);
            CGImageRef cgImage = CGBitmapContextCreateImage(context);
            
            if (_recording) {
                float millisElapsed = [[NSDate date] timeIntervalSinceDate:self.startedAt] * 1000.0;
                //NSLog(@"millisElapsed = %f",millisElapsed);
                [self writeVideoFrameAtTime:CMTimeMake((int)millisElapsed, 1000) addImage:cgImage];
            }
            // Dealloc
            CGImageRelease(cgImage);
            
            CGDataProviderRelease(provider);
            CGImageRelease(iref);
            CGColorSpaceRelease(colorSpaceRef);
            CGContextRelease(context);
            free(buffer);
            free(pixels);
            
        }
        @catch (NSException *exception) {
            
        }
        _writing = false;
    }
}

- (NSString*)tempFilePath {
    NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *filePath = [[paths objectAtIndex:0] stringByAppendingPathComponent:kFileName];
	
	return filePath;
}
-(BOOL) setUpWriter {
    //Clear Old TempFile
	NSError  *error = nil;
    NSString *filePath=[self tempFilePath];
    NSFileManager* fileManager = [NSFileManager defaultManager];
	if ([fileManager fileExistsAtPath:filePath])
    {
		if ([fileManager removeItemAtPath:filePath error:&error] == NO)
        {
			NSLog(@"Could not delete old recording file at path:  %@", filePath);
            return NO;
		}
	}
    
    //Configure videoWriter
    NSURL   *fileUrl=[NSURL fileURLWithPath:filePath];
	videoWriter = [[AVAssetWriter alloc] initWithURL:fileUrl fileType:AVFileTypeQuickTimeMovie error:&error];
	NSParameterAssert(videoWriter);
	
	//Configure videoWriterInput
	NSDictionary* videoCompressionProps = [NSDictionary dictionaryWithObjectsAndKeys:
										   [NSNumber numberWithDouble:outWidth*outHeight],
                                           AVVideoAverageBitRateKey,
										   nil ];
	
	NSDictionary* videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:
								   AVVideoCodecH264, AVVideoCodecKey,
								   [NSNumber numberWithInt:outWidth], AVVideoWidthKey,
								   [NSNumber numberWithInt:outHeight], AVVideoHeightKey,
								   videoCompressionProps, AVVideoCompressionPropertiesKey,
								   nil];

	videoWriterInput = [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeVideo outputSettings:videoSettings];
	
	NSParameterAssert(videoWriterInput);
	videoWriterInput.expectsMediaDataInRealTime = YES;
	NSDictionary* bufferAttributes = [NSDictionary dictionaryWithObjectsAndKeys:
									  [NSNumber numberWithInt:kCVPixelFormatType_32ARGB], kCVPixelBufferPixelFormatTypeKey, nil];
	
	self.avAdaptor = [AVAssetWriterInputPixelBufferAdaptor assetWriterInputPixelBufferAdaptorWithAssetWriterInput:videoWriterInput sourcePixelBufferAttributes:bufferAttributes];
	
	//add input
	[videoWriter addInput:videoWriterInput];
	[videoWriter startWriting];
	[videoWriter startSessionAtSourceTime:CMTimeMake(0, 1000)];

	return YES;
}

- (void) cleanupWriter {
   
	self.avAdaptor = nil;
	
	videoWriterInput = nil;
	
	videoWriter = nil;
	
	self.startedAt = nil;
}

- (BOOL) completeRecordingSession {
    
	[videoWriterInput markAsFinished];
	
	// Wait for the video
	long status = videoWriter.status;
	while (status == AVAssetWriterStatusUnknown)
    {
		NSLog(@"Waiting...");
		[NSThread sleepForTimeInterval:0.5f];
		status = videoWriter.status;
	}
	
    BOOL success = [videoWriter finishWriting];
    if (success)
    {
        NSLog(@"Completed recording, file is stored at:  %@", [self tempFilePath]);
        self.outputPath = [self tempFilePath];
    }
    return success;
}

@end
