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


void MainLayer::goBack(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        this->removeFromParentAndCleanup(true);
    }
}

void MainLayer::goNext(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        if(hasFace1 && hasFace2){
            Layer *layer = VidioLayer::create();
            this->addChild(layer);
        }
    }
}

void MainLayer::changeFace(Sprite* sprite)
{
    ImageView* face = ImageView::create();
    Texture2D* texture = sprite->getTexture();
    SpriteFrame* spriteFrame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    ((Sprite*)face->getVirtualRenderer())->setSpriteFrame(spriteFrame);
    ((Sprite*)face->getVirtualRenderer())->setFlippedY(true);

    if(m_intHead == 1){
        hasFace1 = true;
        headBtn1->removeChildByTag(1);
        Size btnSize = headBtn1->getContentSize();
        Size faceSize = face->getContentSize();
        //double mscalex = btnSize.width/faceSize.width;
        //double mscaley = btnSize.height/faceSize.height;
        //face->setScale((mscalex + mscaley)/2);
        face->setPosition(headBtn1->getPosition());
        headBtn1->addChild(face,0,1);
        Point a = headBtn1->getPosition();
        Point b = face->getPosition();
    }else if(m_intHead == 2){
        hasFace2 = true;
        headBtn2->removeChildByTag(1);
        face->setPosition(headBtn2->getPosition());
        headBtn2->addChild(face,0,1);
    }
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
