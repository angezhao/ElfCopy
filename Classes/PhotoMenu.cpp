//
//  PhotoMenu.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-21.
//
//

#include "PhotoMenu.h"
#include "PhotoLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#import "Constants.h"


PhotoMenu::PhotoMenu()
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_3.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("btnBack");
    btnBack->addTouchEventListener(this,toucheventselector(PhotoMenu::goBack));
    
    auto cameraBtn =  myLayout->getChildByName("cameraBtn");
    cameraBtn->addTouchEventListener(this,toucheventselector(PhotoMenu::changePhoto));
    
    auto photoBtn =  myLayout->getChildByName("photoBtn");
    photoBtn->addTouchEventListener(this,toucheventselector(PhotoMenu::changePhoto));
    
}

PhotoMenu::~PhotoMenu()
{
}

void PhotoMenu::goBack(cocos2d::Ref* pSender,TouchEventType type)
{
    Layer * pLayer = new MainLayer();
    pLayer->autorelease();
}

void PhotoMenu::changePhoto(cocos2d::Ref* pSender,TouchEventType type)
{
    Layer * pLayer = new PhotoLayer();
    pLayer->autorelease();
}
