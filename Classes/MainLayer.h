//
//  MainLayer.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#ifndef __ElfCopy__MainLayer__
#define __ElfCopy__MainLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class MainLayer : public cocos2d::Layer
{
public:
    MainLayer(cocos2d::Sprite* face1,cocos2d::Sprite* face2);
    ~MainLayer();
    
    void goBack(cocos2d::Ref* pSender,TouchEventType type);
    void goNext(cocos2d::Ref* pSender,TouchEventType type);
    void changePhoto1(cocos2d::Ref* pSender,TouchEventType type);
    void changePhoto2(cocos2d::Ref* pSender,TouchEventType type);
    void mask(cocos2d::ui::ImageView* src);
};

#endif /* defined(__ElfCopy__MainLayer__) */
