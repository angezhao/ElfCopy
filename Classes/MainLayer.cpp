//
//  MainLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "MainLayer.h"
#include "StartLayer.h"
#include "VidioLayer.h"
#include "PhotoMenu.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"


MainLayer::MainLayer()
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_2.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("btnBack");
    btnBack->addTouchEventListener(this,toucheventselector(MainLayer::goBack));
    
    auto nextBtn =  myLayout->getChildByName("nextBtn");
    nextBtn->addTouchEventListener(this,toucheventselector(MainLayer::goNext));
    
    auto headBtn1 =  myLayout->getChildByName("headBtn1");
    headBtn1->addTouchEventListener(this,toucheventselector(MainLayer::changePhoto));
    
    auto headBtn2 =  myLayout->getChildByName("headBtn2");
    headBtn2->addTouchEventListener(this,toucheventselector(MainLayer::changePhoto));

}

MainLayer::~MainLayer()
{
}

void MainLayer::goBack(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new StartLayer();
        pLayer->autorelease();
    }
}

void MainLayer::goNext(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new VidioLayer();
        pLayer->autorelease();
    }
}

void MainLayer::changePhoto(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new PhotoMenu();
        pLayer->autorelease();
    }
}