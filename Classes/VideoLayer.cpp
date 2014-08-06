//
//  VideoLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "MainLayer.h"
#include "VideoLayer.h"
#include "cocostudio/CocoStudio.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CaptureScreen.h"
#endif

bool VideoLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    isPlaying = false;
    
    /////////////////////////////////
    Widget *node = GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_5.ExportJson");
	if (node == nullptr)
	{
		return false;
	}
    
    Button* backBtn = (Button*)node->getChildByName("backBtn");
    backBtn->addTouchEventListener(this, toucheventselector(VideoLayer::goBack));
    
    Button* playBack = (Button*)node->getChildByName("playBtn");
    playBack->addTouchEventListener(this, toucheventselector(VideoLayer::playVidio));
    
    Button* saveBtn = (Button*)node->getChildByName("saveBtn");
    saveBtn->addTouchEventListener(this, toucheventselector(VideoLayer::saveVidio));
    
    // 同学会
    tongxuehuiBtn = (CheckBox*)node->getChildByName("tongxuehuiBtn");
    tongxuehuiBtn->setTag(TONGXUEHUI);
    tongxuehuiBtn->addTouchEventListener(this, toucheventselector(VideoLayer::switchVidio));
    
    // 马戏团
    maxituanBtn = (CheckBox*)node->getChildByName("maxituanBtn");
    maxituanBtn->setTag(MAXITUAN);
    maxituanBtn->addTouchEventListener(this, toucheventselector(VideoLayer::switchVidio));

    // 原始人
    yuanshirenBtn = (CheckBox*)node->getChildByName("yuanshirenBtn");
    yuanshirenBtn->setTag(YUANSHIREN);
    yuanshirenBtn->addTouchEventListener(this, toucheventselector(VideoLayer::switchVidio));
    
    // 星星的你
    staryouBtn = (CheckBox*)node->getChildByName("staryouBtn");
    staryouBtn->setTag(STARYOU);
    staryouBtn->addTouchEventListener(this, toucheventselector(VideoLayer::switchVidio));
    
    //默认同学会
    tongxuehuiBtn->setSelectedState(true);
    yuanshirenBtn->setSelectedState(false);
    maxituanBtn->setSelectedState(false);
    staryouBtn->setSelectedState(false);

    tongxuehuiBg = (ImageView*)node->getChildByName("tongxuehuiBg");
    tongxuehuiBg->setVisible(true);

    animationIndex = TONGXUEHUI;
    
    this->addChild(node);

    return true;
}

void VideoLayer::goBack(Ref* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        Layer* parent = (Layer*)this->getParent();
        this->removeFromParentAndCleanup(true);
        parent->removeFromParentAndCleanup(true);
    }
}


void VideoLayer::saveVidio(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        CaptureScreen::saveVideo();
    }
}

void VideoLayer::switchVidio(Ref* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        tongxuehuiBtn->setSelectedState(false);
        maxituanBtn->setSelectedState(false);
        yuanshirenBtn->setSelectedState(false);
        staryouBtn->setSelectedState(false);

        CheckBox* checkBox = (CheckBox*)pSender;

        Sprite *preview = (Sprite *)tongxuehuiBg->getVirtualRenderer();
        SpriteFrame *spriteFrame;
        animationIndex = (AnimationIndex)checkBox->getTag();
        switch (animationIndex) {
            case TONGXUEHUI:
                spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ui5/tongxuehui.png");
                break;
            case MAXITUAN:
                spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ui5/maxituan.png");
                break;
            case YUANSHIREN:
                spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ui5/yuanshiren.png");
                break;
            case GONGFU:
                break;
            case STARYOU:
                spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ui5/staryou.png");
                break;
            case DALAOHU:
                break;
            default:
                break;
        }
        
        if (spriteFrame != NULL) {
            preview->setSpriteFrame(spriteFrame);
        }
    }
}

void VideoLayer::makeFace(std::string spriteFrameName)
{
    // 114*121
    // 261*281
    // 0.436
    // 0.431
    float uiSacleX = 0.436f;
    float uiSacleY = 0.431f;
    Sprite *face = Sprite::createWithSpriteFrameName(spriteFrameName);
    face->setFlippedY(true);
    face->setScaleX(uiSacleX);
    face->setScaleY(uiSacleY);
    Size size = face->getContentSize();
    face->setPosition(Point(size.width / 2, size.height / 2));

    RenderTexture* rt = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
    rt->begin();
    face->visit();
    rt->end();
    
    Sprite* retval = Sprite::createWithTexture(rt->getSprite()->getTexture());
    std::string scaleSpriteFrameName = "scale_" + spriteFrameName;
    SpriteFrameCache::getInstance()->removeSpriteFrameByName(scaleSpriteFrameName);
    SpriteFrame* spriteFrame = retval->getSpriteFrame();
    SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, scaleSpriteFrameName);
}

Armature * VideoLayer::addArmature(std::string fileInfo, std::string name, bool addEvent, int tag)
{
    Size winSize = Director::getInstance()->getWinSize();
    ArmatureDataManager::getInstance()->addArmatureFileInfo(fileInfo);
    Armature *armature = Armature::create(name);
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    if (addEvent) {
        armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VideoLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }
    this->addChild(armature, 0, tag);
    return armature;
}

void VideoLayer::updateFace(Armature *armature, std::string name, Point anchor, std::string boneName)
{
    makeFace(name);
    Skin* face = Skin::createWithSpriteFrameName("scale_" + name);
    face->setFlippedY(true);
    face->setAnchorPoint(anchor);
    Bone *tou = armature->getBone(boneName);
    tou->addDisplay(face, 1);
    tou->changeDisplayWithIndex(1, true);
}

void VideoLayer::playAudio(std::string audioPath)
{
    if (audioPath == "") return;
    this->audioPath = audioPath;
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(audioPath.c_str());
}

void VideoLayer::playYuanShiRen()
{
    Size winSize = Director::getInstance()->getWinSize();
    Armature *armature2 = addArmature("yuanshiren2/yuanshiren2.ExportJson", "yuanshiren2", false, 2);
    Armature *armature1 = addArmature("yuanshiren1/yuanshiren1.ExportJson", "yuanshiren1");
    updateFace(armature1, "player_face1", Point(0.44, 0.625), "tou1");
    updateFace(armature2, "player_face2", Point(0.445, 0.58), "tou2");
    playAudio("Music/yuanshiren.mp3");
}

void VideoLayer::playGongFu()
{
    Armature *armature = addArmature("gongfu/gongfu.ExportJson", "gongfu");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.442, 0.60), "tou2");
    playAudio("");
}

void VideoLayer::playTongxuehui()
{
    Armature *armature = addArmature("tongxuehui/tongxuehui.ExportJson", "tongxuehui");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.445, 0.58), "tou2");
    playAudio("Music/tongxuehui.mp3");
}

void VideoLayer::playMaxituan()
{
    Armature *armature = addArmature("maxituan/maxituan.ExportJson", "maxituan");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.442, 0.58), "tou2");
    playAudio("Music/maxituan.mp3");
}


void VideoLayer::playStaryou()
{
    Armature *armature = addArmature("laizixingxingdeni/laizixingxingdeni.ExportJson", "laizixingxingdeni");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.442, 0.58), "tou2");
    playAudio("Music/laizixingxingdeni.mp3");
}

void VideoLayer::playDalaohu()
{
    
}

void VideoLayer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    std::string id = movementID;
    
	if (movementType == LOOP_COMPLETE)
	{
        this->stopRecord();
	} else if (movementType == COMPLETE) {
        this->stopRecord();
    } else if (movementType == START) {
    }
}

void VideoLayer::playVidio(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        if (isPlaying) {
            return;
        }

        isPlaying = true;
        switch (animationIndex) {
            case YUANSHIREN:
                this->playYuanShiRen();
                break;
            case GONGFU:
                this->playGongFu();
                break;
            case MAXITUAN:
                this->playMaxituan();
                break;
            case TONGXUEHUI:
                this->playTongxuehui();
                break;
            case STARYOU:
                this->playStaryou();
                break;
            case DALAOHU:
                this->playDalaohu();
                break;
            default:
                isPlaying = false;
                break;
        }
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CaptureScreen::startRecord();
#endif
    }
}

void VideoLayer::drawFrame(float dt)
{
    log("drawFrame");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CaptureScreen::drawFrame();
#endif
}

void VideoLayer::stopRecord()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CaptureScreen::stopRecord(CCFileUtils::getInstance()->fullPathForFilename(this->audioPath).c_str());
#endif
    for (int i = 1; i < 10; i ++) {
        if (this->getChildByTag(i)) {
            this->removeChildByTag(i);
        }
    }

    switch (animationIndex) {
        case YUANSHIREN:
            ArmatureDataManager::getInstance()->removeArmatureFileInfo("yuanshiren2/yuanshiren2.ExportJson");
            ArmatureDataManager::getInstance()->removeArmatureFileInfo("yuanshiren1/yuanshiren1.ExportJson");
            break;
        case GONGFU:
            ArmatureDataManager::getInstance()->removeArmatureFileInfo("gongfu/gongfu.ExportJson");
            break;
        case MAXITUAN:
            ArmatureDataManager::getInstance()->removeArmatureFileInfo("maxituan/maxituan.ExportJson");
            break;
        case TONGXUEHUI:
            ArmatureDataManager::getInstance()->removeArmatureFileInfo("tongxuehui/tongxuehui.ExportJson");
            break;
        case STARYOU:
            ArmatureDataManager::getInstance()->removeArmatureFileInfo("laizixingxingdeni/laizixingxingdeni.ExportJson");
            break;
        case DALAOHU:
            break;
        default:
            break;
    }
    
    isPlaying = false;
}