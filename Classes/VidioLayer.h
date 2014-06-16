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
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio;

class VidioLayer : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void goBack(Ref* pSender,TouchEventType type);
    void playVidio(Ref* pSender,TouchEventType type);
    void stopRecord(float dt);
    void drawFrame(float dt);
    void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
    void makeFace(std::string spriteFrameName);
    
    // implement the "static create()" method manually
    CREATE_FUNC(VidioLayer);
};
#endif /* defined(__ElfCopy__VidioLayer__) */
