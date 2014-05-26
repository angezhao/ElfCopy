//
//  PhotoMenu.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-21.
//
//

#include "PhotoMenu.h"
#include "PhotoLayer.h"
#include "TakePhoto.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif



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
      //  Layer * pLayer = new TakePhoto();
      //  pLayer->autorelease();
      //  m_pLayer->addChild(pLayer);
    }
}

void PhotoMenu::selectPhoto(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
       
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;
		bool isHave = cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
			"org/cocos2dx/cpp/PicHandler",
			"pickPhoto",
			"()V"					
			);

		if(isHave){
			//调用这个函数
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		}
		

#else
		Layer * pLayer = new PhotoLayer();
		pLayer->autorelease();
		m_pLayer->addChild(pLayer);

#endif

    }
}
