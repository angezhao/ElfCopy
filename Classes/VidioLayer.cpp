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
    
    auto btnBack =  node->getChildByName("btnBack");
    btnBack->addTouchEventListener(this,toucheventselector(VidioLayer::goBack));
    
    auto playBack =  node->getChildByName("playBtn");
    playBack->addTouchEventListener(this,toucheventselector(VidioLayer::playVidio));
    
    this->addChild(node);
    
    return true;
}

void VidioLayer::goBack(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
//        Layer* parent = (Layer*)this->getParent();
//        this->removeFromParentAndCleanup(true);
//        parent->removeFromParentAndCleanup(true);
        CaptureScreen::drawFrame();

    }
}

void VidioLayer::makeFace(std::string spriteFrameName)
{
    float uiSacle = 0.38f;
    Sprite *face = Sprite::createWithSpriteFrameName(spriteFrameName);
    face->setFlippedY(true);
    face->setScale(uiSacle);
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

void VidioLayer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    std::string id = movementID;

    CCLOG("kering -> animationEvent, %d", movementType);
	if (movementType == LOOP_COMPLETE)
	{
        // this->scheduleOnce(schedule_selector(VidioLayer::stopRecord), 0);
        schedule_selector(VidioLayer::stopRecord);
        CCLOG("kering -> animationEvent, LOOP_COMPLETE");
	} else if (movementType == COMPLETE) {
        CCLOG("kering -> animationEvent, COMPLETE");
    } else if (movementType == START) {
        CCLOG("kering -> animationEvent, START");
    }
}

void VidioLayer::playVidio(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        Size winSize = Director::getInstance()->getWinSize();
    
        ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren2/yuanshiren2.ExportJson");
        Armature *armature2 = Armature::create("yuanshiren2");
        armature2->setPosition(Point(winSize.width / 2, winSize.height / 2));
        armature2->getAnimation()->playWithIndex(0);
        this->addChild(armature2, 0, 1);
    
        ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren1/yuanshiren1.ExportJson");
        Armature *armature1 = Armature::create("yuanshiren1");
        armature1->setPosition(Point(winSize.width / 2, winSize.height / 2));
        armature1->getAnimation()->playWithIndex(0);
        armature1->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VidioLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        this->addChild(armature1, 0, 2);
        
        this->makeFace("player_face1");
        Skin* face1 = Skin::createWithSpriteFrameName("scale_player_face1");
        face1->setFlippedY(true);
        // face1->setAnchorPoint(Point(0.453, 0.65));
        face1->setAnchorPoint(Point(0.44, 0.62));
        Bone *tou1 = armature1->getBone("tou1");
        tou1->addDisplay(face1, 1);
        tou1->changeDisplayWithIndex(1, true);

        this->makeFace("player_face2");
        Skin* face2 = Skin::createWithSpriteFrameName("scale_player_face2");
        face2->setFlippedY(true);
        // face2->setAnchorPoint(Point(0.43, 0.68));
        face2->setAnchorPoint(Point(0.418, 0.64));
        Bone *tou2 = armature2->getBone("tou2");
        tou2->addDisplay(face2, 1);
        tou2->changeDisplayWithIndex(1, true);
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CaptureScreen::startRecord();
        //this->schedule(schedule_selector(VidioLayer::drawFrame), (1.0 / 6), kRepeatForever, 0.01);
        // this->scheduleOnce(schedule_selector(VidioLayer::stopRecord),20);
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

void VidioLayer::stopRecord(float dt)
{
    log("stopRecord");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CaptureScreen::stopRecord();
#endif
    this->removeChildByTag(1);
    this->removeChildByTag(2);
}