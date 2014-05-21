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
    MainLayer();
    ~MainLayer();
    
    void goBack(cocos2d::Ref* pSender,TouchEventType type);
    void goNext(cocos2d::Ref* pSender,TouchEventType type);
    void changePhoto(cocos2d::Ref* pSender,TouchEventType type);
};

#endif /* defined(__ElfCopy__MainLayer__) */
