//
//  PhotoLayer.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#ifndef __ElfCopy__PhotoLayer__
#define __ElfCopy__PhotoLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class PhotoLayer : public cocos2d::Layer
{
public:
    PhotoLayer();
    ~PhotoLayer();
    
    void goBack(cocos2d::Ref* pSender,TouchEventType type);
    void changeOk(cocos2d::Ref* pSender,TouchEventType type);
    cocos2d::Sprite* createMaskedSprite(cocos2d::Sprite* src, const char* maskFile);
};


#endif /* defined(__ElfCopy__PhotoLayer__) */
