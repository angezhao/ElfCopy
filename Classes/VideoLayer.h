//
//  VideoLayer.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#ifndef __ElfCopy__VideoLayer__
#define __ElfCopy__VideoLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

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
} AnimationIndex;

class VideoLayer : public Layer
{
public:
    AnimationIndex animationIndex;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void goBack(Ref* pSender, TouchEventType type);
    void switchVidio(Ref* pSender, TouchEventType type);
//    void switchGongfu(Ref* pSender, TouchEventType type);
//    void switchMaxituan(Ref* pSender, TouchEventType type);
//    void switchTongxuehui(Ref* pSender, TouchEventType type);
    void playVidio(Ref* pSender, TouchEventType type);
    void saveVidio(Ref* pSender, TouchEventType type);
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
    CheckBox* maxituanBtn;
    CheckBox* staryouBtn;
    CheckBox* tongxuehuiBtn;

    ImageView* tongxuehuiBg;
    
    // implement the "static create()" method manually
    CREATE_FUNC(VideoLayer);

private:
    // CCArray *animationFiles;
    std::string audioPath;
    
    Armature * addArmature(std::string fileInfo, std::string name, bool addEvent = true, int tag = 1);
    void updateFace(Armature *armature, std::string name, Point anchor, std::string boneName);
    void playAudio(std::string audioPath);
    
    bool isPlaying;
};
#endif /* defined(__ElfCopy__VideoLayer__) */
