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
#include "CaptureUtils.h"
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
        Layer* parent = (Layer*)this->getParent();
        this->removeFromParentAndCleanup(true);
        parent->removeFromParentAndCleanup(true);
    }
}

void VidioLayer::playVidio(Ref* pSender,TouchEventType type)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren2/yuanshiren2.ExportJson");
    Armature *armature2 = Armature::create("yuanshiren2");
    armature2->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature2->getAnimation()->playWithIndex(0);
    this->addChild(armature2);
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren1/yuanshiren1.ExportJson");
    Armature *armature1 = Armature::create("yuanshiren1");
    armature1->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature1->getAnimation()->playWithIndex(0);
    this->addChild(armature1);

    Skin* face1 = Skin::createWithSpriteFrameName("player_face1");
    face1->setFlippedY(true);
    face1->setAnchorPoint(Point(0.442, 0.63));
    Bone *tou1 = armature1->getBone("tou1");
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);

    Skin* face2 = Skin::createWithSpriteFrameName("player_face2");
    face2->setFlippedY(true);
    face2->setAnchorPoint(Point(0.419, 0.66));
    Bone *tou2 = armature2->getBone("tou2");
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
     
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //CaptureUtils::startRecord();
#endif
}