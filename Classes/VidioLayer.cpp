//
//  VidioLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "VidioLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"


VidioLayer::VidioLayer()
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_5.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("shareBtn");
    btnBack->addTouchEventListener(this,toucheventselector(VidioLayer::goBack));
    
}

VidioLayer::~VidioLayer()
{
}

void VidioLayer::goBack(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new MainLayer();
        pLayer->autorelease();
    }
}