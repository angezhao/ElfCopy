//
//  VidioLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "MainLayer.h"
#include "VidioLayer.h"
#include "cocostudio/CocoStudio.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CaptureScreen.h"
#endif

bool VidioLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
    Widget *node = GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_5.ExportJson");
	if (node == nullptr)
	{
		return false;
	}
    
    Button* btnBack = (Button*)node->getChildByName("btnBack");
    btnBack->addTouchEventListener(this, toucheventselector(VidioLayer::goBack));
    
    Button* playBack = (Button*)node->getChildByName("playBtn");
    playBack->addTouchEventListener(this, toucheventselector(VidioLayer::playVidio));

    // 原始人
    yuanshirenBtn = (CheckBox*)node->getChildByName("yuanshirenBtn");
    yuanshirenBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    yuanshirenBg = (ImageView*)node->getChildByName("yuanshirenBg");
    
    // 功夫
    gongfuBtn = (CheckBox*)node->getChildByName("gongfuBtn");
    gongfuBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    gongfuBg = (ImageView*)node->getChildByName("gongfuBg");
    
    // 马戏团
    maxituanBtn = (CheckBox*)node->getChildByName("maxituanBtn");
    maxituanBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    maxituanBg = (ImageView*)node->getChildByName("maxituanBg");
    
    // 星星的你
    staryouBtn = (CheckBox*)node->getChildByName("staryouBtn");
    staryouBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    staryouBg = (ImageView*)node->getChildByName("staryouBg");
    
    // 打老虎
    dalaohuBtn = (CheckBox*)node->getChildByName("dalaohuBtn");
    dalaohuBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    dalaohuBg = (ImageView*)node->getChildByName("dalaohuBg");
    
    // 同学会
    tongxuehuiBtn = (CheckBox*)node->getChildByName("tongxuehuiBtn");
    tongxuehuiBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    tongxuehuiBg = (ImageView*)node->getChildByName("tongxuehuiBg");
    
    //默认同学会
    tongxuehuiBtn->setSelectedState(true);
    yuanshirenBtn->setSelectedState(false);
    gongfuBtn->setSelectedState(false);
    maxituanBtn->setSelectedState(false);
    staryouBtn->setSelectedState(false);
    dalaohuBtn->setSelectedState(false);
    tongxuehuiBg->setVisible(true);
    yuanshirenBg->setVisible(false);
    gongfuBg->setVisible(false);
    maxituanBg->setVisible(false);
    staryouBg->setVisible(false);
    dalaohuBg->setVisible(false);
    animationIndex = TONGXUEHUI;
    
    this->addChild(node);

    return true;
}

void VidioLayer::goBack(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        Layer* parent = (Layer*)this->getParent();
        this->removeFromParentAndCleanup(true);
        parent->removeFromParentAndCleanup(true);
    }
}

void VidioLayer::switchVidio(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        CheckBox* selectVidio = (CheckBox*)pSender;
        if (!selectVidio->getSelectedState()) {//选中
            switch (animationIndex) {
                case YUANSHIREN:
                    yuanshirenBtn->setSelectedState(false);
                    yuanshirenBg->setVisible(false);
                    break;
                case GONGFU:
                    gongfuBtn->setSelectedState(false);
                    gongfuBg->setVisible(false);
                    break;
                case MAXITUAN:
                    maxituanBtn->setSelectedState(false);
                    maxituanBg->setVisible(false);
                    break;
                case TONGXUEHUI:
                    tongxuehuiBtn->setSelectedState(false);
                    tongxuehuiBg->setVisible(false);
                    break;
                case STARYOU:
                    staryouBtn->setSelectedState(false);
                    staryouBg->setVisible(false);
                    break;
                case DALAOHU:
                    dalaohuBtn->setSelectedState(false);
                    dalaohuBg->setVisible(false);
                    break;
                default:
                    break;
            }

            const char* boxName = selectVidio->getName();
            if(strcmp(boxName,"yuanshirenBtn")==0){
                animationIndex = YUANSHIREN;
                yuanshirenBg->setVisible(true);
            }else if(strcmp(boxName,"gongfuBtn")==0){
                animationIndex = GONGFU;
                gongfuBg->setVisible(true);
            }else if(strcmp(boxName,"maxituanBtn")==0){
                animationIndex = MAXITUAN;
                maxituanBg->setVisible(true);
            }else if(strcmp(boxName,"staryouBtn")==0){
                animationIndex = STARYOU;
                staryouBg->setVisible(true);
            }else if(strcmp(boxName,"dalaohuBtn")==0){
                animationIndex = DALAOHU;
                dalaohuBg->setVisible(true);
            }else if(strcmp(boxName,"tongxuehuiBtn")==0){
                animationIndex = TONGXUEHUI;
                tongxuehuiBg->setVisible(true);
            }
        }else{//取消选中
            animationIndex = VIDIOMAX;
            const char* boxName = selectVidio->getName();
            if(strcmp(boxName,"yuanshirenBtn")==0){
                yuanshirenBg->setVisible(false);
            }else if(strcmp(boxName,"gongfuBtn")==0){
                gongfuBg->setVisible(false);
            }else if(strcmp(boxName,"maxituanBtn")==0){
                maxituanBg->setVisible(false);
            }else if(strcmp(boxName,"staryouBtn")==0){
                staryouBg->setVisible(false);
            }else if(strcmp(boxName,"dalaohuBtn")==0){
                dalaohuBg->setVisible(false);
            }else if(strcmp(boxName,"tongxuehuiBtn")==0){
                tongxuehuiBg->setVisible(false);
            }
        }
    }
}

void VidioLayer::makeFace(std::string spriteFrameName)
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

Armature * VidioLayer::addArmature(std::string fileInfo, std::string name, bool addEvent, int tag)
{
    Size winSize = Director::getInstance()->getWinSize();
    ArmatureDataManager::getInstance()->addArmatureFileInfo(fileInfo);
    Armature *armature = Armature::create(name);
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    if (addEvent) {
        armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VidioLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }
    this->addChild(armature, 0, tag);
    return armature;
}

void VidioLayer::updateFace(Armature *armature, std::string name, Point anchor, std::string boneName)
{
    makeFace(name);
    Skin* face = Skin::createWithSpriteFrameName("scale_" + name);
    face->setFlippedY(true);
    face->setAnchorPoint(anchor);
    Bone *tou = armature->getBone(boneName);
    tou->addDisplay(face, 1);
    tou->changeDisplayWithIndex(1, true);
}

void VidioLayer::playAudio(std::string audioPath)
{
    if (audioPath == "") return;
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(audioPath.c_str());
}

void VidioLayer::playYuanShiRen()
{
    Size winSize = Director::getInstance()->getWinSize();
    Armature *armature2 = addArmature("yuanshiren2/yuanshiren2.ExportJson", "yuanshiren2", false, 2);
    Armature *armature1 = addArmature("yuanshiren1/yuanshiren1.ExportJson", "yuanshiren1");
    updateFace(armature1, "player_face1", Point(0.44, 0.625), "tou1");
    updateFace(armature2, "player_face2", Point(0.445, 0.58), "tou2");
    playAudio("Music/yuanshiren.mp3");
}

void VidioLayer::playGongFu()
{
    Armature *armature = addArmature("gongfu/gongfu.ExportJson", "gongfu");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.442, 0.60), "tou2");
    playAudio("");
}

void VidioLayer::playTongxuehui()
{
    Armature *armature = addArmature("tongxuehui/tongxuehui.ExportJson", "tongxuehui");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.445, 0.58), "tou2");
    playAudio("Music/tongxuehui.mp3");
}

void VidioLayer::playMaxituan()
{
    Armature *armature = addArmature("maxituan/maxituan.ExportJson", "maxituan");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.442, 0.58), "tou2");
    playAudio("Music/maxituan.mp3");
}


void VidioLayer::playStaryou()
{
    Armature *armature = addArmature("laizixingxingdeni/laizixingxingdeni.ExportJson", "laizixingxingdeni");
    updateFace(armature, "player_face1", Point(0.445, 0.58), "tou1");
    updateFace(armature, "player_face2", Point(0.442, 0.58), "tou2");
    playAudio("Music/laizixingxingdeni.mp3");
}

void VidioLayer::playDalaohu()
{
    
}

void VidioLayer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
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

void VidioLayer::playVidio(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
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
                break;
        }
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // CaptureScreen::startRecord();
#endif
    }
}

void VidioLayer::drawFrame(float dt)
{
    log("drawFrame");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CaptureScreen::drawFrame();
#endif
}

void VidioLayer::stopRecord()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CaptureScreen::stopRecord();
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
}