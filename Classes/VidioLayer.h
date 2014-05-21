//
//  VidioLayer.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#ifndef __ElfCopy__VidioLayer__
#define __ElfCopy__VidioLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class VidioLayer : public cocos2d::Layer
{
public:
    VidioLayer();
    ~VidioLayer();
    
    void goBack(cocos2d::Ref* pSender,TouchEventType type);
};
#endif /* defined(__ElfCopy__VidioLayer__) */
