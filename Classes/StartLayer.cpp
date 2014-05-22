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
#include "Constants.h"


StartLayer::StartLayer()
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_1.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto startBtn =  myLayout->getChildByName("startBtn");
    startBtn->addTouchEventListener(this,toucheventselector(StartLayer::startGame));
    
}

StartLayer::~StartLayer()
{
}

void StartLayer::startGame(cocos2d::Ref* pSender,TouchEventType type)
{
    Layer * pLayer = new MainLayer();
    pLayer->autorelease();
}