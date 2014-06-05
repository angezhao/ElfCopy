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

using namespace cocos2d;

class PickPhoto : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(PickPhoto);
    
    void pickOk(Image* image);
};

#endif /* defined(__ElfCopy__PickPhoto__) */
