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

using namespace cocos2d::ui;

class StartLayer : public cocos2d::Layer
{
public:
    StartLayer();
    ~StartLayer();
    
    void startGame(cocos2d::Ref* pSender,TouchEventType type);
};

#endif /* defined(__ElfCopy__StartLayer__) */
