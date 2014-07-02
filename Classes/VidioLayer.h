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

typedef enum {
	YUANSHIREN = 1,
    GONGFU = 2,
    MAXITUAN = 3,
    TONGXUEHUI = 4,
    STARYOU = 5,
    DALAOHU = 6,
    VIDIOMAX = 7
} AnimationName;

class VidioLayer : public Layer
{
public:
    AnimationName animationName;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void goBack(Ref* pSender, TouchEventType type);
    void switchVidio(Ref* pSender, TouchEventType type);
//    void switchGongfu(Ref* pSender, TouchEventType type);
//    void switchMaxituan(Ref* pSender, TouchEventType type);
//    void switchTongxuehui(Ref* pSender, TouchEventType type);
    void playVidio(Ref* pSender, TouchEventType type);
    void stopRecord();
    void drawFrame(float dt);
    void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
    void makeFace(std::string spriteFrameName);

    void playYuanShiRen();
    void playGongFu();
    void playMaxituan();
    void playTongxuehui();
    void playStaryou();
    void playDalaohu();
    
    CheckBox* yuanshirenBtn;
    CheckBox* gongfuBtn;
    CheckBox* maxituanBtn;
    CheckBox* staryouBtn;
    CheckBox* dalaohuBtn;
    CheckBox* tongxuehuiBtn;
    
    // implement the "static create()" method manually
    CREATE_FUNC(VidioLayer);
};
#endif /* defined(__ElfCopy__VidioLayer__) */
