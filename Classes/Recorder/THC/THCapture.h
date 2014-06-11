//
//  THCapture.h
//  ScreenCaptureViewTest
//
//  Created by wayne li on 11-8-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
@protocol THCaptureDelegate;
@interface THCapture : NSObject{
    
    AVAssetWriter *videoWriter;
	AVAssetWriterInput *videoWriterInput;
	AVAssetWriterInputPixelBufferAdaptor *_avAdaptor;
    //recording state
	BOOL           _recording;     //正在录制中
    BOOL           _writing;       //正在将帧写入文件
	NSDate         *_startedAt;     //录制的开始时间
    CGContextRef   context;        //绘制layer的context
    NSTimer        *timer;         //按帧率写屏的定时器
    
    //Capture Layer
    CALayer *_captureLayer;              //要绘制的目标layer
    NSUInteger  _frameRate;              //帧速
    NSString *_outputPath;//输出结果
}
@property(assign) NSUInteger frameRate;
@property(nonatomic, strong) CALayer *captureLayer;
@property(nonatomic, strong) NSDate *startedAt;
@property(nonatomic, strong) AVAssetWriterInputPixelBufferAdaptor *avAdaptor;
@property(nonatomic, strong) NSString *outputPath;

//开始录制
- (bool)startRecording;
//结束录制
- (bool)stopRecording;

@end

@protocol THCaptureDelegate <NSObject>

- (void)recordingFinished:(NSString*)outputPath;
- (void)recordingFaild:(NSError *)error;

@end