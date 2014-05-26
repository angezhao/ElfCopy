//
//  PickPhoto.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-25.
//
//

#ifndef __ElfCopy__PickPhoto__
#define __ElfCopy__PickPhoto__

#include "cocos2d.h"

class PickPhoto : public cocos2d::Layer
{
public:
    PickPhoto(bool takePhoto);//takePhoto:true拍照
    ~PickPhoto();
};

#endif /* defined(__ElfCopy__PickPhoto__) */
