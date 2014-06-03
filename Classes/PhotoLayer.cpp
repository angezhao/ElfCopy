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
#include "ui/CocosGUI.h"

PhotoLayer::PhotoLayer(const char *photofile)
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_4.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("btnBack");
    btnBack->addTouchEventListener(this,toucheventselector(PhotoLayer::goBack));
    
    auto okBtn =  myLayout->getChildByName("okBtn");
    okBtn->addTouchEventListener(this,toucheventselector(PhotoLayer::changeOk));
    
    auto head =  myLayout->getChildByName("head");
    this->maskHead =  (ImageView*)head->getChildByName("mask");
    this->userHead =  (cocos2d::ui::ImageView*)head->getChildByName("userHead");
    userHead->setTouchEnabled(true);
    userHead->loadTexture("face/tou1.png",UI_TEX_TYPE_LOCAL);
    //userHead->loadTexture(photofile,UI_TEX_TYPE_LOCAL);
    
    mscale=3;     //初始化图片的缩放比例
    userHead->setScale(mscale);
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();//创建一个触摸监听(单点触摸）
    listener->onTouchBegan = CC_CALLBACK_2(PhotoLayer::onTouchBegan, this);//指定触摸的回调函数
    listener->onTouchEnded = CC_CALLBACK_2(PhotoLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(PhotoLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将listener放入事件委托中
    
//    this->setTouchEnabled(true);
//    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
//    auto listener1 = EventListenerTouchAllAtOnce::create();//创建一个触摸监听(多点触摸）
//    listener1->onTouchesBegan = CC_CALLBACK_2(PhotoLayer::TouchesBegan, this);//指定触摸的回调函数
//    listener1->onTouchesEnded = CC_CALLBACK_2(PhotoLayer::TouchesEnded, this);
//    listener1->onTouchesMoved = CC_CALLBACK_2(PhotoLayer::TouchesMoved, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);//将listener放入事件委托中
    
    
}

PhotoLayer::~PhotoLayer()
{
}

void PhotoLayer::goBack(Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Layer * pLayer = new PhotoMenu();
        pLayer->autorelease();
    }
}

void PhotoLayer::changeOk(Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        //进行遮罩处理
        this->mask(userHead,maskHead);
        //userHead->setPosition(cocos2d::Point(0, 0));

        cocos2d::Sprite* face1;
        cocos2d::Sprite* face2;
        if(m_intHead==1){
            //userHead1 = userHead;
            cocos2d::Sprite* src_sprite = static_cast<cocos2d::Sprite*>(userHead->getVirtualRenderer());
            face1 = cocos2d::Sprite::createWithTexture(src_sprite->getTexture());
        }else if(m_intHead==2){
            //userHead2 = userHead;
            cocos2d::Sprite* src_sprite = static_cast<cocos2d::Sprite*>(userHead->getVirtualRenderer());
            face2 = cocos2d::Sprite::createWithTexture(src_sprite->getTexture());
        }
        Layer * pLayer = new MainLayer(face1,face2);
        pLayer->autorelease();
    }
}

bool PhotoLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event)
{
    return true;//返回true表示接收触摸事件
}

void PhotoLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event)
{
    cocos2d::log("onTouchMoved  ...");
    auto beginPos = touch->getLocationInView();//获得触摸位置
    beginPos = cocos2d::Director::getInstance()->convertToGL(beginPos);//坐标转换
    auto headPos = userHead->getPosition();//获取女主的位置
    auto headSize = userHead->getContentSize();//获取女主的三围（大小）
    auto endPos = touch->getPreviousLocationInView();//获取触摸的前一个位置
    endPos = cocos2d::Director::getInstance()->convertToGL(endPos);//转换坐标
    
    auto offset = cocos2d::Point(beginPos-endPos);//获取offset，2.14是用ccpSub，3.0后直接用 - 号就可以
    auto nextPos = cocos2d::Point(headPos + offset);//获取女主的下一步计划，2.14用的是ccpAdd，
    userHead->setPosition(nextPos);
}

void PhotoLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event)
{
    cocos2d::log("onTouchEnded  ...");
}


void PhotoLayer::TouchesBegan(const std::vector<cocos2d::Touch*>& pTouches, cocos2d::Event  *event)
{
    if(pTouches.size()>=2)  //如果触摸点不少于两个
    {
        auto iter=pTouches.begin();
        cocos2d::Point mPoint1=((cocos2d::Touch *)(*iter))->getLocationInView();
        mPoint1 = cocos2d::Director::getInstance()->convertToGL(mPoint1);
        iter++;
        cocos2d::Point mPoint2=((cocos2d::Touch *)(*iter))->getLocationInView();
        mPoint2 = cocos2d::Director::getInstance()->convertToGL(mPoint2);
        
        distance=sqrt((mPoint2.x-mPoint1.x)*(mPoint2.x-mPoint1.x)+(mPoint2.y-mPoint1.y)*(mPoint2.y-mPoint1.y));//计算两个触摸点距离
        deltax = (mPoint1.x + mPoint2.x)/2 - userHead->getPositionX();     //得到两个触摸点中点和精灵锚点的差值
        deltay = (mPoint1.y + mPoint2.y)/2 - userHead->getPositionY();
        cocos2d::log("ccTouchesBegan  ...");
    }
}

void PhotoLayer::TouchesMoved(const std::vector<cocos2d::Touch*>& pTouches, cocos2d::Event  *event)
{
    cocos2d::log("onTouchMoved  ...");
    
    if(pTouches.size()>=2)  //如果移动时触摸点的个数不少于两个
    {
        auto iter = pTouches.begin();
        cocos2d::Point mPoint1 = ((cocos2d::Touch*)(*iter))->getLocationInView();
        mPoint1 = cocos2d::Director::getInstance()->convertToGL(mPoint1);
        iter++;
        cocos2d::Point mPoint2 = ((cocos2d::Touch*)(*iter))->getLocationInView();
        mPoint2 = cocos2d::Director::getInstance()->convertToGL(mPoint2);        //获得新触摸点两点之间的距离
        double mdistance = sqrt((mPoint1.x-mPoint2.x)*(mPoint1.x-mPoint2.x)+(mPoint1.y-mPoint2.y)*(mPoint1.y-mPoint2.y));
        mscale = mdistance/distance * mscale;                      //   新的距离 / 老的距离  * 原来的缩放比例，即为新的缩放比例
        distance = mdistance;
        userHead->setScale(mscale);
        
        double x = (mPoint2.x+mPoint1.x)/2 - deltax;      //计算两触点中点与精灵锚点的差值
        double y = (mPoint2.y+mPoint1.y)/2 - deltay;
        userHead->setPosition(cocos2d::Point(x,y));                        //保持两触点中点与精灵锚点的差值不变
        deltax = (mPoint1.x+ mPoint2.x)/2 - userHead->getPositionX();       //计算新的偏移量
        deltay = (mPoint2.y + mPoint1.y)/2 - userHead->getPositionY();
    }
    if(pTouches.size()==1)                          //如果触摸点为一个
    {
        auto iter =  pTouches.begin();
        cocos2d::Point mPoint=((cocos2d::Touch*)(*iter))->getLocationInView();
        mPoint=cocos2d::Director::getInstance()->convertToGL(mPoint);    //坐标转换
        userHead->setPosition(mPoint);                    //直接移动精灵
    }
}

void PhotoLayer::TouchesEnded(const std::vector<cocos2d::Touch*>& pTouches, cocos2d::Event  *event)
{
    cocos2d::log("onTouchEnded  ...");
//    auto lastPos = touch->getLocationInView();
//    lastPos = Director::getInstance()->convertToGL(lastPos);
//    
//    auto rect = Rect(400,300,100,150);//建立一个选中区域，女主如果拖动到这个框内就可以瞬移进来，反之是小三进来
//    MoveTo* moveTo_1;//女主的动作
//    MoveTo* moveTo_3;//小三的动作
//    if(rect.containsPoint(lastPos))
//    {
//        moveTo_1 = MoveTo::create(0.1f,Point(450,370));
//        moveTo_3 = MoveTo::create(0.1f,Point(250,250));
//    }
//    else
//    {
//        moveTo_1 = MoveTo::create(0.1f,Point(250,250));
//        moveTo_3 = MoveTo::create(0.1f,Point(450,370));
//    }
//    girl_1->runAction(moveTo_1);//男主争夺战~~
//    girl_3->runAction(moveTo_3);
}

void PhotoLayer::TouchesCancellnd(const std::vector<cocos2d::Touch*>& pTouches, cocos2d::Event *pEvent)
{
    
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

void PhotoLayer::mask(cocos2d::ui::ImageView* userHead,cocos2d::ui::ImageView* maskHead)
{
    assert(userHead);
    assert(maskHead);
    
    cocos2d::Sprite* src_sprite = static_cast<cocos2d::Sprite*>(userHead->getVirtualRenderer());
    cocos2d::Sprite* msk_sprite = static_cast<cocos2d::Sprite*>(maskHead->getVirtualRenderer());
    cocos2d::Size srcContent = src_sprite->getContentSize();
    cocos2d::Size maskContent = msk_sprite->getContentSize();
    
    cocos2d::RenderTexture* rt = cocos2d::RenderTexture::create(srcContent.width, srcContent.height, cocos2d::Texture2D::PixelFormat::RGBA8888);
    
    /*
     float ratiow = srcContent.width / maskContent.width;
     float ratioh = srcContent.height / maskContent.height;
     mask->setScaleX(ratiow);
     mask->setScaleY(ratioh);*/
    
    maskHead->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    userHead->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    
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


