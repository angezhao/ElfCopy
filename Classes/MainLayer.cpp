//
//  MainLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "MainLayer.h"
#include "PhotoMenu.h"
#include "VidioLayer.h"
#include "Constants.h"
#include "cocostudio/CocoStudio.h"

bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
     m_intHead = 0;
    Widget *node = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_2.ExportJson");
	if (node == nullptr)
	{
		return false;
	}
    
    Button* btnBack = (Button*)node->getChildByName("btnBack");
    btnBack->addTouchEventListener(this, toucheventselector(MainLayer::goBack));
    
    Button* nextBtn = (Button*)node->getChildByName("nextBtn");
    nextBtn->addTouchEventListener(this, toucheventselector(MainLayer::goNext));
    
    headBtn1 = (Button*)node->getChildByName("headBtn1");
    headBtn1->addTouchEventListener(this, toucheventselector(MainLayer::changePhoto1));
    
    headBtn2 = (Button*)node->getChildByName("headBtn2");
    headBtn2->addTouchEventListener(this, toucheventselector(MainLayer::changePhoto2));
    
    this->addChild(node);
    
    return true;
}


void MainLayer::goBack(Ref* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        this->removeFromParentAndCleanup(true);
    }
}

void MainLayer::goNext(Ref* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        //if (headBtn1->getChildrenCount() > 0 && headBtn2->getChildrenCount() > 0) {
            VidioLayer *layer = VidioLayer::create();
            this->addChild(layer);
        //}
    }
}

void MainLayer::changeFace(ImageView* face)
{
    if (m_intHead == 1) {
        headBtn1->addChild(face);
    } else if (m_intHead == 2) {
        headBtn2->addChild(face);
    }

    std::string frameIndex = m_intHead == 1 ? "1" : "2";
    std::string spriteFrameName = "player_face" + frameIndex;
    SpriteFrameCache::getInstance()->removeSpriteFrameByName(spriteFrameName);
    SpriteFrame* spriteFrame = ((Sprite*)face->getVirtualRenderer())->getSpriteFrame();
    SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, spriteFrameName);
}

void MainLayer::changePhoto1(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        m_intHead = 1;
        PhotoMenu *layer = PhotoMenu::create();
        this->addChild(layer, 0, 1);
    }
}

void MainLayer::changePhoto2(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        m_intHead = 2;
        PhotoMenu *layer = PhotoMenu::create();
        this->addChild(layer, 0, 1);
    }
}
