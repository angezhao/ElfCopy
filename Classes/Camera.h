//
//  Camera.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//
//

#import <Foundation/Foundation.h>
#include "cocos2d.h"

@interface Camera :UIViewController<UIImagePickerControllerDelegate,UINavigationControllerDelegate> {
    Boolean hasLoadedCamera;
}
//+(Camera*)PickPhoto;
//打开摄像头
-(void)showcamera;
//-(void)OpenCamera;
@end
