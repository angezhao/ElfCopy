//
//  PhotoLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "PhotoLayer.h"
#include "MainLayer.h"
#include "PhotoMenu.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"


PhotoLayer::PhotoLayer()
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_4.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("btnBack");
    btnBack->addTouchEventListener(this,toucheventselector(PhotoLayer::goBack));
    
    auto okBtn =  myLayout->getChildByName("okBtn");
    okBtn->addTouchEventListener(this,toucheventselector(PhotoLayer::changeOk));
    
    auto headBg =  myLayout->getChildByName("headBg");
    
    cocos2d::Sprite* src_sprite = cocos2d::Sprite::create("scene/bg.png");
    cocos2d::Sprite* show_sprite = this->createMaskedSprite(src_sprite, "face/mask.png");
    //headBg->getPosition()
    show_sprite->setPosition(headBg->getPosition());
    this->addChild(show_sprite, 0);
    
}

PhotoLayer::~PhotoLayer()
{
}

void PhotoLayer::goBack(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new PhotoMenu();
        pLayer->autorelease();
    }
}


void PhotoLayer::changeOk(cocos2d::Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new MainLayer();
        pLayer->autorelease();
    }
}

cocos2d::Sprite* PhotoLayer::createMaskedSprite(cocos2d::Sprite* src, const char* maskFile)
{
    cocos2d::Sprite* mask = cocos2d::Sprite::create(maskFile);
    
    assert(src);
    assert(mask);
    
    cocos2d::Size srcContent = src->getContentSize();
    cocos2d::Size maskContent = mask->getContentSize();
    
    cocos2d::RenderTexture* rt = cocos2d::RenderTexture::create(srcContent.width, srcContent.height, cocos2d::Texture2D::PixelFormat::RGBA8888);
    
    /*
     float ratiow = srcContent.width / maskContent.width;
     float ratioh = srcContent.height / maskContent.height;
     mask->setScaleX(ratiow);
     mask->setScaleY(ratioh);*/
    
    mask->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    src->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    
    cocos2d::BlendFunc blendFunc2 = { GL_ONE, GL_ZERO };
    mask->setBlendFunc(blendFunc2);
    cocos2d::BlendFunc blendFunc3 = { GL_DST_ALPHA, GL_ZERO };
    src->setBlendFunc(blendFunc3);
    
    rt->begin();
    mask->visit();
    src->visit();
    rt->end();
    
    cocos2d::Sprite* retval = cocos2d::Sprite::createWithTexture(rt->getSprite()->getTexture());
    retval->setFlippedY(true);
    return retval;
}

