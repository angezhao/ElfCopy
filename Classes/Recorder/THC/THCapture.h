//
//  THCapture.h
//  ScreenCaptureViewTest
//
//  Created by wayne li on 11-8-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface THCapture : NSObject{
    
    AVAssetWriter *videoWriter;
	AVAssetWriterInput *videoWriterInput;
	AVAssetWriterInputPixelBufferAdaptor *_avAdaptor;
    //recording state
	BOOL           _recording;     //正在录制中
    BOOL           _writing;       //正在将帧写入文件
	NSDate         *_startedAt;     //录制的开始时间
    size_t width;
    size_t height;
    size_t outWidth;
    size_t outHeight;
    NSTimer        *timer;         //按帧率写屏的定时器
    
    NSUInteger  _frameRate;              //帧速
    NSString *_outputPath;//输出结果
    NSString *_videoPath;//混合视频缓存文件
}
@property(nonatomic, strong) NSDate *startedAt;
@property(nonatomic, strong) AVAssetWriterInputPixelBufferAdaptor *avAdaptor;
@property(nonatomic, strong) NSString *outputPath;
@property(nonatomic, strong) NSString *videoPath;

//开始录制
- (bool)startRecording;
//结束录制
- (bool)stopRecording;
//录制每一帧
- (void)drawFrame;

@end
