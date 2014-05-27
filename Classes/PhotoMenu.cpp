//
//  PhotoMenu.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-21.
//
//

#include "PhotoMenu.h"
#include "PickPhoto.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"
#include "PhotoLayer.h"


PhotoMenu::PhotoMenu()
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_3.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("btnBack");
    btnBack->addTouchEventListener(this,toucheventselector(PhotoMenu::goBack));
    
    auto cameraBtn =  myLayout->getChildByName("cameraBtn");
    cameraBtn->addTouchEventListener(this,toucheventselector(PhotoMenu::takePhoto));
    
    auto photoBtn =  myLayout->getChildByName("photoBtn");
    photoBtn->addTouchEventListener(this,toucheventselector(PhotoMenu::selectPhoto));
    
}

PhotoMenu::~PhotoMenu()
{
}

void PhotoMenu::goBack(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new MainLayer();
        pLayer->autorelease();
    }
}

void PhotoMenu::takePhoto(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new PickPhoto(true);
        pLayer->autorelease();
        m_pLayer->addChild(pLayer);
    }
}

void PhotoMenu::selectPhoto(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        //Layer * pLayer = new PickPhoto(false);
        //pLayer->autorelease();
        cocos2d::Layer * pLayer = new PhotoLayer("");
        pLayer->autorelease();
        m_pLayer->addChild(pLayer);
    }
}
