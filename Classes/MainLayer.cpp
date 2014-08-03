//
//  MainLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "MainLayer.h"
#include "PhotoMenu.h"
#include "VideoLayer.h"
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
    
    headBtn1 = (CheckBox*)node->getChildByName("headBtn1");
    headBtn1->addTouchEventListener(this, toucheventselector(MainLayer::changePhoto1));
    
    headBtn2 = (CheckBox*)node->getChildByName("headBtn2");
    headBtn2->addTouchEventListener(this, toucheventselector(MainLayer::changePhoto2));
    
    if(this->getChildByTag(2)!=NULL){
        headBtn1->setSelectedState(false);
    }else{
        headBtn1->setSelectedState(true);
    }
    
    if(this->getChildByTag(3)!=NULL){
        headBtn2->setSelectedState(false);
    }else{
        headBtn2->setSelectedState(true);
    }
    
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
        if (this->getChildByTag(2)!=NULL && this->getChildByTag(3)!=NULL) {
            VideoLayer *layer = VideoLayer::create();
            this->addChild(layer);
        }
    }
}

void MainLayer::changeFace(ImageView* face)
{
    if (m_intHead == 1) {
        this->addChild(face,0,2);
        face->setPosition(Point(333, 394));
        headBtn1->setSelectedState(false);
    } else if (m_intHead == 2) {
        this->addChild(face,0,3);
        face->setPosition(Point(705, 394));
        headBtn2->setSelectedState(false);
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
        if (headBtn1->getSelectedState()) {
            headBtn1->setSelectedState(false);
            m_intHead = 1;
            PhotoMenu *layer = PhotoMenu::create();
            this->addChild(layer, 0, 1);
        }
        else{
            this->removeChildByTag(2);
        }
    }
}

void MainLayer::changePhoto2(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        if (headBtn2->getSelectedState()) {
            headBtn2->setSelectedState(false);
            m_intHead = 2;
            PhotoMenu *layer = PhotoMenu::create();
            this->addChild(layer, 0, 1);
        }
        else{
            this->removeChildByTag(3);
        }
    }
}
