//
//  PhotoMenu.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-21.
//
//

#include "PhotoMenu.h"
#include "PickPhoto.h"
#include "PhotoLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"

bool PhotoMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
    Widget *node = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_3.ExportJson");
	if (node == nullptr)
	{
		return false;
	}
    
    Button* btnBack = (Button*)node->getChildByName("btnBack");
    btnBack->addTouchEventListener(this, toucheventselector(PhotoMenu::goBack));
    
    Button* cameraBtn = (Button*)node->getChildByName("cameraBtn");
    cameraBtn->addTouchEventListener(this, toucheventselector(PhotoMenu::takePhoto));
    
    Button* photoBtn = (Button*)node->getChildByName("photoBtn");
    photoBtn->addTouchEventListener(this, toucheventselector(PhotoMenu::selectPhoto));
    
    this->addChild(node);
    
    return true;
}

void PhotoMenu::goBack(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        this->removeFromParentAndCleanup(true);
    }
}

void PhotoMenu::takePhoto(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        selectOrPick = true;
        PickPhoto * layer = PickPhoto::create();
        this->addChild(layer,0,1);
    }
}

void PhotoMenu::selectPhoto(Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        selectOrPick = false;
        PickPhoto * layer = PickPhoto::create();
        this->addChild(layer,0,1);
    }
}

