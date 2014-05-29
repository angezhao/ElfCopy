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
    
    Button* headBtn1 =  (Button*)myLayout->getChildByName("headBtn1");
    headBtn1->addTouchEventListener(this,toucheventselector(MainLayer::changePhoto1));
    
    auto headBtn2 =  myLayout->getChildByName("headBtn2");
    headBtn2->addTouchEventListener(this,toucheventselector(MainLayer::changePhoto2));
    
    if(userHead1 != NULL)
    {
        
        //headBtn1->addChild(userHead1);
//        Button* tmp = static_cast<Button*>(userHead1->getVirtualRenderer());
//        userHead1->getUserData()
//        headBtn1->loadTextureNormal(tmp->_normalFileName.c_str(), tmp->_normalTexType);
//        headBtn1->loadTexturePressed(tmp->_clickedFileName.c_str(), tmp->_pressedTexType);
//        
//        
//        headBtn1->copySpecialProperties(tmp);
    }

    if(userHead2 != NULL)
    {
        //headBtn2->addChild(userHead2);
    }
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
        if (userHead1 == NULL || userHead2 == NULL)
            return;
        Layer * pLayer = new VidioLayer();
        pLayer->autorelease();
    }
}

void MainLayer::changePhoto1(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        m_intHead = 1;
        Layer * pLayer = new PhotoMenu();
        pLayer->autorelease();
    }
}

void MainLayer::changePhoto2(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        m_intHead = 2;
        Layer * pLayer = new PhotoMenu();
        pLayer->autorelease();
    }
}