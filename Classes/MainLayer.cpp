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


MainLayer::MainLayer(cocos2d::Sprite* face1,cocos2d::Sprite* face2)
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
    
    if(face1 != NULL)
    {
        //cocos2d::Sprite* src_sprite = static_cast<cocos2d::Sprite*>(userHead1->getVirtualRenderer());
        //cocos2d::Sprite* face = cocos2d::Sprite::createWithTexture(src_sprite->getTexture());
        headBtn1->addChild(face1);
    }

    if(face2 != NULL)
    {
        //cocos2d::Sprite* src_sprite = static_cast<cocos2d::Sprite*>(userHead2->getVirtualRenderer());
        //cocos2d::Sprite* face = cocos2d::Sprite::createWithTexture(src_sprite->getTexture());
        headBtn2->addChild(face2);
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
        //if (face1 == NULL || face2 == NULL)
        //    return;
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
        /*
        ImageView* face = ImageView::create();
        face->loadTexture("face/tou1.png");
        //face->loadTexture("scene/bg.png");
        //cocos2d::Sprite* src_sprite =
        this->mask(face);
        face->setPosition(cocos2d::Point(0, 0));
        cocos2d::ui::Button* headBtn1 = static_cast<cocos2d::ui::Button*>(pSender);
        headBtn1->addChild(face);
        */
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

void MainLayer::mask(cocos2d::ui::ImageView* src)
{
    ImageView* mask = ImageView::create();
    mask->loadTexture("face/mask.png");
    
    assert(src);
    assert(mask);
    
    cocos2d::Sprite* src_sprite = static_cast<cocos2d::Sprite*>(src->getVirtualRenderer());
    cocos2d::Sprite* msk_sprite = static_cast<cocos2d::Sprite*>(mask->getVirtualRenderer());
    cocos2d::Size srcContent = src_sprite->getContentSize();
    cocos2d::Size maskContent = msk_sprite->getContentSize();
    
    cocos2d::RenderTexture* rt = cocos2d::RenderTexture::create(srcContent.width, srcContent.height, cocos2d::Texture2D::PixelFormat::RGBA8888);
    
    /*
     float ratiow = srcContent.width / maskContent.width;
     float ratioh = srcContent.height / maskContent.height;
     mask->setScaleX(ratiow);
     mask->setScaleY(ratioh);*/
    
    mask->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    src->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    
    cocos2d::BlendFunc blendFunc2 = { GL_ONE, GL_ZERO };
    msk_sprite->setBlendFunc(blendFunc2);
    cocos2d::BlendFunc blendFunc3 = { GL_DST_ALPHA, GL_ZERO };
    src_sprite->setBlendFunc(blendFunc3);
    
    rt->begin();
    msk_sprite->visit();
    src_sprite->visit();
    rt->end();
    
    cocos2d::Texture2D* texture = rt->getSprite()->getTexture();
    cocos2d::SpriteFrame* spriteFrame = cocos2d::SpriteFrame::createWithTexture(texture, cocos2d::Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    src_sprite->setSpriteFrame(spriteFrame);
}
