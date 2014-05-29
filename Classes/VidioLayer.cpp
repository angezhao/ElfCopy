//
//  VidioLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "VidioLayer.h"
#include "StartLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"


VidioLayer::VidioLayer()
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_5.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("shareBtn");
    btnBack->addTouchEventListener(this,toucheventselector(VidioLayer::goBack));
    
    auto playBack =  myLayout->getChildByName("playBtn");
    playBack->addTouchEventListener(this,toucheventselector(VidioLayer::playVidio));
}

VidioLayer::~VidioLayer()
{
}

void VidioLayer::goBack(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new StartLayer();
        pLayer->autorelease();
    }
}

void VidioLayer::playVidio(cocos2d::Ref* pSender,TouchEventType type)
{
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren2/yuanshiren2.ExportJson");
    cocostudio::Armature *armature = cocostudio::Armature::create("yuanshiren2");
    armature->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    m_pLayer->addChild(armature);
    
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren1/yuanshiren1.ExportJson");
    cocostudio::Armature *armature2 = cocostudio::Armature::create("yuanshiren1");
    armature2->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
    armature2->getAnimation()->playWithIndex(0);
    m_pLayer->addChild(armature2);
    
    cocostudio::Bone *tou1 = armature2->getBone("tou1");
    //cocostudio::Skin* face1 = cocostudio::Skin::create("face/tou1.png");
    cocostudio::Skin* face1 = static_cast<cocostudio::Skin*>(userHead1->getVirtualRenderer());
    face1->setAnchorPoint(cocos2d::Point(-0.1, 1.2));
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    cocostudio::Bone *tou2 = armature->getBone("tou2");
    //cocostudio::Skin* face2 = cocostudio::Skin::create("face/tou2.png");
    cocostudio::Skin* face2 = static_cast<cocostudio::Skin*>(userHead2->getVirtualRenderer());
    face2->setAnchorPoint(cocos2d::Point(-0.2, 1.5));
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
}