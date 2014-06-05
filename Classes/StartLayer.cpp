//
//  StartLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-21.
//
//

#include "StartLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"

bool StartLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
    Widget *node = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_1.ExportJson");
	if (node == nullptr)
	{
		return false;
	}
    
    Button* startButton = (Button*)node->getChildByName("startBtn");
    startButton->addTouchEventListener(this, toucheventselector(StartLayer::startGame));
    this->addChild(node);

    return true;
}

void StartLayer::startGame(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        MainLayer * layer = MainLayer::create();
        this->addChild(layer, 0, 1);
    }
}