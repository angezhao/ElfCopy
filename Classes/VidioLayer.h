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

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio;

class VidioLayer : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(VidioLayer);

    void goBack(Ref* pSender,TouchEventType type);
    void playVidio(Ref* pSender,TouchEventType type);
};
#endif /* defined(__ElfCopy__VidioLayer__) */
