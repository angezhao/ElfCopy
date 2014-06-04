//
//  StartLayer.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-21.
//
//

#ifndef __ElfCopy__StartLayer__
#define __ElfCopy__StartLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class StartLayer : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(StartLayer);
    
    void startGame(Ref* pSender, TouchEventType type);
};

#endif /* defined(__ElfCopy__StartLayer__) */
