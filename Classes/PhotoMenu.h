//
//  PhotoMenu.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-21.
//
//

#ifndef __ElfCopy__PhotoMenu__
#define __ElfCopy__PhotoMenu__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class PhotoMenu : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(PhotoMenu);

    void goBack(Ref* pSender,TouchEventType type);
    void takePhoto(Ref* pSender,TouchEventType type);//拍照
    void selectPhoto(Ref* pSender,TouchEventType type);//相册选照
};


#endif /* defined(__ElfCopy__PhotoMenu__) */
