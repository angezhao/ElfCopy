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

USING_NS_CC;

PhotoLayer::PhotoLayer(const char *photofile)
{
    auto myLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_4.ExportJson");
    m_pLayer->addChild(myLayout);
    
    auto btnBack =  myLayout->getChildByName("btnBack");
    btnBack->addTouchEventListener(this,toucheventselector(PhotoLayer::goBack));
    
    auto okBtn =  myLayout->getChildByName("okBtn");
    okBtn->addTouchEventListener(this,toucheventselector(PhotoLayer::changeOk));
    
    auto head =  myLayout->getChildByName("head");
    //ImageView *mask =  (ImageView*)head->getChildByName("mask");
    this->userHead =  (ui::ImageView*)head->getChildByName("userHead");
    userHead->setTouchEnabled(true);
    //userHead->addTouchEventListener(this,toucheventselector(PhotoLayer::headTouch));
    
    auto listener = EventListenerTouchOneByOne::create();//创建一个触摸监听(单点触摸）
    listener->onTouchBegan = CC_CALLBACK_2(PhotoLayer::onTouchBegan, this);//指定触摸的回调函数
    listener->onTouchEnded = CC_CALLBACK_2(PhotoLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(PhotoLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将listener放入事件委托中
    
    //m_pLayer->registerWithTouchDispatcher()
//    Sprite* src_sprite = Sprite::create(photofile);
//    Sprite* show_sprite = this->createMaskedSprite(src_sprite, "face/mask.png");
//    show_sprite->setPosition(headBg->getPosition());
//    this->addChild(show_sprite, 0);
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
        Layer * pLayer = new MainLayer();
        pLayer->autorelease();
    }
}

bool PhotoLayer::onTouchBegan(Touch* touch, Event  *event)
{
    return true;//返回true表示接收触摸事件
}

void PhotoLayer::onTouchMoved(Touch* touch, Event  *event)
{
    log("onTouchMoved  ...");
    auto beginPos = touch->getLocationInView();//获得触摸位置
    beginPos = Director::getInstance()->convertToGL(beginPos);//坐标转换
    auto headPos = userHead->getPosition();//获取女主的位置
    auto headSize = userHead->getContentSize();//获取女主的三围（大小）
    //针对女主的坐标和三围定制一个凶..框框
    //auto rect = Rect(girlPos.x - girlSize.width/2,girlPos.y - girlSize.height/2,girlSize.width + 10,girlSize.height + 10);
    //if(rect.containsPoint(beginPos))//判断触点是否在女主身上！
    //{
        auto endPos = touch->getPreviousLocationInView();//获取触摸的前一个位置
        endPos = Director::getInstance()->convertToGL(endPos);//转换坐标

        auto offset = Point(beginPos-endPos);//获取offset，2.14是用ccpSub，3.0后直接用 - 号就可以
        auto nextPos = Point(headPos + offset);//获取女主的下一步计划，2.14用的是ccpAdd，
        userHead->setPosition(nextPos);
    //}
}

void PhotoLayer::onTouchEnded(Touch* touch, Event  *event)
{
    log("onTouchEnded  ...");
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

void PhotoLayer::headTouch(Ref* pSender,TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED)
    {
//        if(pTouches.size()>=2)  //如果触摸点不少于两个
//        {
//            auto iter=pTouches.begin();
//            Point mPoint1=((Touch *)(*iter))->getLocationInView();
//            mPoint1 = Director::getInstance()->convertToGL(mPoint1);
//            iter++;
//            Point mPoint2=((Touch *)(*iter))->getLocationInView();
//            mPoint2 = Director::getInstance()->convertToGL(mPoint2);
//            
//            distance=sqrt((mPoint2.x-mPoint1.x)*(mPoint2.x-mPoint1.x)+(mPoint2.y-mPoint1.y)*(mPoint2.y-mPoint1.y));//计算两个触摸点距离
//            deltax = (mPoint1.x + mPoint2.x)/2 - bg->getPositionX();     //得到两个触摸点中点和精灵锚点的差值
//            deltay = (mPoint1.y + mPoint2.y)/2 - bg->getPositionY();
//            CCLog("ccTouchesBegan  ...");
//            
//        }
    }else if(type == TOUCH_EVENT_MOVED)
    {
//        if(pTouches.size()>=2)  //如果移动时触摸点的个数不少于两个
//        {
//            auto iter = pTouches.begin();
//            Point mPoint1 = ((Touch*)(*iter))->getLocationInView();
//            mPoint1 = Director::getInstance()->convertToGL(mPoint1);
//            iter++;
//            Point mPoint2 = ((Touch*)(*iter))->getLocationInView();
//            mPoint2 = Director::getInstance()->convertToGL(mPoint2);        //获得新触摸点两点之间的距离
//            double mdistance = sqrt((mPoint1.x-mPoint2.x)*(mPoint1.x-mPoint2.x)+(mPoint1.y-mPoint2.y)*(mPoint1.y-mPoint2.y));
//            mscale = mdistance/distance * mscale;                      //   新的距离 / 老的距离  * 原来的缩放比例，即为新的缩放比例
//            distance = mdistance;
//            bg->setScale(mscale);
//            
//            double x = (mPoint2.x+mPoint1.x)/2 - deltax;      //计算两触点中点与精灵锚点的差值
//            double y = (mPoint2.y+mPoint1.y)/2 - deltay;
//            bg->setPosition(Point(x,y));                        //保持两触点中点与精灵锚点的差值不变
//            deltax = (mPoint1.x+ mPoint2.x)/2 - bg->getPositionX();       //计算新的偏移量
//            deltay = (mPoint2.y + mPoint1.y)/2 - bg->getPositionY();
//            CCLog("ccTouchMoved  ....");
//        }
//        if(pTouches.size()==1)                          //如果触摸点为一个
//        {
//            auto iter =  pTouches.begin();
//            Point mPoint=((Touch*)(*iter))->getLocationInView();
//            mPoint=Director::getInstance()->convertToGL(mPoint);    //坐标转换
//            bg->setPosition(mPoint);                    //直接移动精灵
//        }
    }
}

Sprite* PhotoLayer::createMaskedSprite(Sprite* src, const char* maskFile)
{
    Sprite* mask = Sprite::create(maskFile);
    
    assert(src);
    assert(mask);
    
    Size srcContent = src->getContentSize();
    Size maskContent = mask->getContentSize();
    
    RenderTexture* rt = RenderTexture::create(srcContent.width, srcContent.height, Texture2D::PixelFormat::RGBA8888);
    
    /*
     float ratiow = srcContent.width / maskContent.width;
     float ratioh = srcContent.height / maskContent.height;
     mask->setScaleX(ratiow);
     mask->setScaleY(ratioh);*/
    
    mask->setPosition(Point(srcContent.width / 2, srcContent.height / 2));
    src->setPosition(Point(srcContent.width / 2, srcContent.height / 2));
    
    BlendFunc blendFunc2 = { GL_ONE, GL_ZERO };
    mask->setBlendFunc(blendFunc2);
    BlendFunc blendFunc3 = { GL_DST_ALPHA, GL_ZERO };
    src->setBlendFunc(blendFunc3);
    
    rt->begin();
    mask->visit();
    src->visit();
    rt->end();
    
    Sprite* retval = Sprite::createWithTexture(rt->getSprite()->getTexture());
    retval->setFlippedY(true);
    return retval;
}

