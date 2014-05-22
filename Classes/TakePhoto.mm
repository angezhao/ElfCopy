//
//  TakePhoto.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-22.
//  拍照
//

#include "TakePhoto.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Camera.h"
#endif
#include "MainLayer.h"
#include "PhotoMenu.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"


TakePhoto::TakePhoto()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    //[Camera PickPhoto];
    //Camera * photo = [[Camera alloc]init];
    //[photo OpenCamera];//要手动添加，否则无法显示按钮
#else
    //Android代码
#endif
    
}

TakePhoto::~TakePhoto()
{
}