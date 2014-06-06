//
//  VidioLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "VidioLayer.h"
#include "cocostudio/CocoStudio.h"

bool VidioLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
    Widget *node = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_5.ExportJson");
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
    
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren2/yuanshiren2.ExportJson");
    cocostudio::Armature *armature = cocostudio::Armature::create("yuanshiren2");
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    //m_pLayer->addChild(armature);
    
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren1/yuanshiren1.ExportJson");
    cocostudio::Armature *armature2 = cocostudio::Armature::create("yuanshiren1");
    armature2->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature2->getAnimation()->playWithIndex(0);
    //m_pLayer->addChild(armature2);
    
    cocostudio::Bone *tou1 = armature2->getBone("tou1");
    cocostudio::Skin* face1 = cocostudio::Skin::create("face/tou1.png");
    //cocostudio::Skin* face01 = static_cast<cocostudio::Skin*>(face1);
    face1->setAnchorPoint(Point(-0.1, 1.2));
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    cocostudio::Bone *tou2 = armature->getBone("tou2");
    cocostudio::Skin* face2 = cocostudio::Skin::create("face/tou2.png");
    //cocostudio::Skin* face02 = static_cast<cocostudio::Skin*>(face2);
    face2->setAnchorPoint(Point(-0.2, 1.5));
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
}