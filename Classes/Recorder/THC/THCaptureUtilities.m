//
//  THCaptureUtilities.m
//  ScreenCaptureViewTest
//
//  Created by wayne li on 11-9-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "THCaptureUtilities.h"

@implementation THCaptureUtilities

+ (NSString*)mergeVideo:(NSString *)videoPath andAudio:(NSString *)audioPath
{
    if (audioPath == nil) {
        //直接存入相册中
        //if (UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(videoPath)) {
        //    UISaveVideoAtPathToSavedPhotosAlbum(videoPath, nil, @selector(video:didFinishSavingWithError:contextInfo:), nil);
        //}
        return videoPath;
    }
    
    AVMutableComposition* mixComposition = [AVMutableComposition composition];
	//混合音乐
    NSURL *audioUrl=[NSURL fileURLWithPath:audioPath];
    AVURLAsset* audioAsset = [[AVURLAsset alloc]initWithURL:audioUrl options:nil];
    AVMutableCompositionTrack *compositionCommentaryTrack = [mixComposition addMutableTrackWithMediaType:AVMediaTypeAudio
                                                                                            preferredTrackID:kCMPersistentTrackID_Invalid];
    [compositionCommentaryTrack insertTimeRange:CMTimeRangeMake(kCMTimeZero, audioAsset.duration)
                                            ofTrack:[[audioAsset tracksWithMediaType:AVMediaTypeAudio] objectAtIndex:0]
                                             atTime:kCMTimeZero error:nil];
	
	//混合视频
    NSURL *videoUrl=[NSURL fileURLWithPath:videoPath];
	AVURLAsset* videoAsset = [[AVURLAsset alloc]initWithURL:videoUrl options:nil];
	AVMutableCompositionTrack *compositionVideoTrack = [mixComposition addMutableTrackWithMediaType:AVMediaTypeVideo 
																				   preferredTrackID:kCMPersistentTrackID_Invalid];
	[compositionVideoTrack insertTimeRange:CMTimeRangeMake(kCMTimeZero, videoAsset.duration) 
								   ofTrack:[[videoAsset tracksWithMediaType:AVMediaTypeVideo] objectAtIndex:0] 
									atTime:kCMTimeZero error:nil];
	AVAssetExportSession* _assetExport = [[AVAssetExportSession alloc] initWithAsset:mixComposition 
																		  presetName:AVAssetExportPresetPassthrough];   
	
	//[audioAsset release];
    //[videoAsset release];
    
	//保存混合后的文件的过程
	NSString* videoName = @"export2.mov";
	NSString *exportPath = [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:videoName];
	NSURL    *exportUrl = [NSURL fileURLWithPath:exportPath];
	
	if ([[NSFileManager defaultManager] fileExistsAtPath:exportPath]) 
	{
		[[NSFileManager defaultManager] removeItemAtPath:exportPath error:nil];
	}
	
	_assetExport.outputFileType = @"com.apple.quicktime-movie";
	NSLog(@"file type %@",_assetExport.outputFileType);
	_assetExport.outputURL = exportUrl;
	_assetExport.shouldOptimizeForNetworkUse = YES;
	
    
	[_assetExport exportAsynchronouslyWithCompletionHandler:
	 ^(void ) 
    {    
        NSLog(@"完成了");
        //[THCaptureUtilities mergedidFinish:exportPath];
     }];
    //[_assetExport release];
    return exportPath;
}

+(void)mergedidFinish:(NSString *)videoPath
 {
     NSDateFormatter* dateFormatter=[[NSDateFormatter alloc] init];
     [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:SS"];
     NSString* currentDateStr=[dateFormatter stringFromDate:[NSDate date]];
     
     NSString* fileName=[NSString stringWithFormat:@"白板录制,%@.mov",currentDateStr];
     
     NSString* path=[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:[NSString stringWithFormat:@"/%@",fileName]];
     
     if ([[NSFileManager defaultManager] fileExistsAtPath:videoPath])
     {
         NSError *err=nil;
         [[NSFileManager defaultManager] moveItemAtPath:videoPath toPath:path error:&err];
     }
     
     if ([[NSUserDefaults standardUserDefaults] objectForKey:@"allVideoInfo"]) {
         NSMutableArray* allFileArr=[[NSMutableArray alloc] init];
         [allFileArr addObjectsFromArray:[[NSUserDefaults standardUserDefaults] objectForKey:@"allVideoInfo"]];
         [allFileArr insertObject:fileName atIndex:0];
         [[NSUserDefaults standardUserDefaults] setObject:allFileArr forKey:@"allVideoInfo"];
     }
     else{
         NSMutableArray* allFileArr=[[NSMutableArray alloc] init];
         [allFileArr addObject:fileName];
         [[NSUserDefaults standardUserDefaults] setObject:allFileArr forKey:@"allVideoInfo"];
     }
     
     //音频与视频合并结束，存入相册中
     if (UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(path)) {
         //UISaveVideoAtPathToSavedPhotosAlbum(path, self, @selector(video:didFinishSavingWithError:contextInfo:), nil);
         UISaveVideoAtPathToSavedPhotosAlbum(path, nil, @selector(video:didFinishSavingWithError:contextInfo:), nil);
     }
}

+ (void)video: (NSString *)videoPath didFinishSavingWithError:(NSError *) error contextInfo: (void *)contextInfo
{
    if (error) {
        NSLog(@"---%@",[error localizedDescription]);
    }
}
@end
