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

using namespace cocos2d::ui;

class PhotoMenu : public cocos2d::Layer
{
public:
    PhotoMenu();
    ~PhotoMenu();
    
    void goBack(cocos2d::Ref* pSender,TouchEventType type);
    void changePhoto(cocos2d::Ref* pSender,TouchEventType type);
    
};


#endif /* defined(__ElfCopy__PhotoMenu__) */
