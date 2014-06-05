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

bool PhotoLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
    Widget *node = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_4.ExportJson");
	if (node == nullptr)
	{
		return nullptr;
	}
    
    Button* btnBack = (Button*)node->getChildByName("btnBack");
    btnBack->addTouchEventListener(this, toucheventselector(PhotoMenu::goBack));
    
    Button* okBtn = (Button*)node->getChildByName("okBtn");
    okBtn->addTouchEventListener(this, toucheventselector(PhotoLayer::changeOk));
    
    ImageView* head = (ImageView*)node->getChildByName("head");
    this->maskHead =  (ImageView*)head->getChildByName("mask");
    this->userHead =  (ImageView*)head->getChildByName("userHead");
    userHead->setTouchEnabled(true);
    //userHead->loadTexture("face/tou1.png",UI_TEX_TYPE_LOCAL);
    //userHead->loadTexture(photofile,UI_TEX_TYPE_LOCAL);
    
    mscale=1;     //初始化图片的缩放比例
    // userHead->setScale(mscale);
    
    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
    auto listener1 = EventListenerTouchAllAtOnce::create();//创建一个触摸监听(多点触摸）
    listener1->onTouchesBegan = CC_CALLBACK_2(PhotoLayer::TouchesBegan, this);//指定触摸的回调函数
    listener1->onTouchesEnded = CC_CALLBACK_2(PhotoLayer::TouchesEnded, this);
    listener1->onTouchesMoved = CC_CALLBACK_2(PhotoLayer::TouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);//将listener放入事件委托中
    
    this->addChild(node,1,1);
    
    return true;
}

void PhotoLayer::goBack(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        this->removeFromParentAndCleanup(true);
    }
}

void PhotoLayer::changeOk(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        // 进行遮罩处理
//        Widget* node = (Widget*)this->getChildByTag(1);
//        ImageView* head = (ImageView*)node->getChildByName("head");
//        ImageView* userHead = (ImageView*)head->getChildByName("userHead");
        // Sprite* textureSprite = Sprite::create("scene/bg.png");
        Sprite* textureSprite = (Sprite*)userHead->getVirtualRenderer();
        Sprite* sprite = this->mask(textureSprite);
        
        //MainLayer* layer = (MainLayer*)this->getParent()->getParent()->getParent();
        MainLayer* layer = (MainLayer*)this->getParent()->getParent();
        layer->changeFace(sprite);

        Layer* parent = (Layer*)this->getParent();
        this->removeFromParentAndCleanup(true);
        parent->removeFromParentAndCleanup(true);
    }
}

/*
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
    auto endPos = touch->getPreviousLocationInView();//获取触摸的前一个位置
    endPos = Director::getInstance()->convertToGL(endPos);//转换坐标
    
    auto offset = Point(beginPos-endPos);//获取offset，2.14是用ccpSub，3.0后直接用 - 号就可以
    auto nextPos = Point(headPos + offset);//获取女主的下一步计划，2.14用的是ccpAdd，
    userHead->setPosition(nextPos);
}

void PhotoLayer::onTouchEnded(Touch* touch, Event  *event)
{
    log("onTouchEnded  ...");
}
*/

void PhotoLayer::TouchesBegan(const std::vector<Touch*>& pTouches, Event  *event)
{
    log("TouchesBegan  ...");
    if(pTouches.size()>=2)  //如果触摸点不少于两个
    {
        auto iter=pTouches.begin();
        Point mPoint1=((Touch *)(*iter))->getLocationInView();
        mPoint1 = Director::getInstance()->convertToGL(mPoint1);
        iter++;
        Point mPoint2=((Touch *)(*iter))->getLocationInView();
        mPoint2 = Director::getInstance()->convertToGL(mPoint2);
        
        distance=sqrt((mPoint2.x-mPoint1.x)*(mPoint2.x-mPoint1.x)+(mPoint2.y-mPoint1.y)*(mPoint2.y-mPoint1.y));//计算两个触摸点距离
        deltax = (mPoint1.x + mPoint2.x)/2 - userHead->getPositionX();     //得到两个触摸点中点和精灵锚点的差值
        deltay = (mPoint1.y + mPoint2.y)/2 - userHead->getPositionY();
        log("ccTouchesBegan  ...");
    }
}

void PhotoLayer::TouchesMoved(const std::vector<Touch*>& pTouches, Event  *event)
{
    log("TouchesMoved  ...");
    
    if(pTouches.size()>=2)  //如果移动时触摸点的个数不少于两个
    {
        auto iter = pTouches.begin();
        Point mPoint1 = ((Touch*)(*iter))->getLocationInView();
        mPoint1 = Director::getInstance()->convertToGL(mPoint1);
        iter++;
        Point mPoint2 = ((Touch*)(*iter))->getLocationInView();
        mPoint2 = Director::getInstance()->convertToGL(mPoint2);        //获得新触摸点两点之间的距离
        double mdistance = sqrt((mPoint1.x-mPoint2.x)*(mPoint1.x-mPoint2.x)+(mPoint1.y-mPoint2.y)*(mPoint1.y-mPoint2.y));
        mscale = mdistance/distance * mscale;                      //   新的距离 / 老的距离  * 原来的缩放比例，即为新的缩放比例
        distance = mdistance;
        userHead->setScale(mscale);
        
        double x = (mPoint2.x+mPoint1.x)/2 - deltax;      //计算两触点中点与精灵锚点的差值
        double y = (mPoint2.y+mPoint1.y)/2 - deltay;
        userHead->setPosition(Point(x,y));                        //保持两触点中点与精灵锚点的差值不变
        deltax = (mPoint1.x+ mPoint2.x)/2 - userHead->getPositionX();       //计算新的偏移量
        deltay = (mPoint2.y + mPoint1.y)/2 - userHead->getPositionY();
    }
    if(pTouches.size()==1)                          //如果触摸点为一个
    {
        auto iter =  pTouches.begin();
        Point mPoint=((Touch*)(*iter))->getLocationInView();
        mPoint=Director::getInstance()->convertToGL(mPoint);    //坐标转换
        userHead->setPosition(mPoint);                    //直接移动精灵
    }
}

void PhotoLayer::TouchesEnded(const std::vector<Touch*>& pTouches, Event  *event)
{
    log("TouchesEnded  ...");
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

void PhotoLayer::TouchesCancellnd(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    log("TouchesCancellnd  ...");
}

Sprite* PhotoLayer::mask(Sprite* textureSprite)
{
    assert(userHead);
    assert(maskHead);
    
    //Sprite* textureSprite = static_cast<Sprite*>(userHead->getVirtualRenderer());
    //Sprite* maskSprite = static_cast<Sprite*>(maskHead->getVirtualRenderer());
    
    // Sprite* textureSprite = Sprite::create("scene/bg.png");
    Sprite* maskSprite = Sprite::create("face/mask.png");
    Size textureContent = textureSprite->getContentSize();
    Size maskContent = maskSprite->getContentSize();
    
    RenderTexture* rt = RenderTexture::create(textureContent.width, textureContent.height, Texture2D::PixelFormat::RGBA8888);
    
    textureSprite->setPosition(Point(textureContent.width / 2, textureContent.height / 2));
    maskSprite->setPosition(Point(textureContent.width / 2, textureContent.height / 2));
    
    BlendFunc maskBlendFunc = { GL_ONE, GL_ZERO };
    maskSprite->setBlendFunc(maskBlendFunc);
    BlendFunc textureBlendFunc = { GL_DST_ALPHA, GL_ZERO };
    textureSprite->setBlendFunc(textureBlendFunc);
    
    rt->begin();
    maskSprite->visit();
    textureSprite->visit();
    rt->end();
    
    Sprite* retval = Sprite::createWithTexture(rt->getSprite()->getTexture());
    return retval;
    
    /*
    Texture2D* texture = rt->getSprite()->getTexture();
    SpriteFrame* spriteFrame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    src_sprite->setSpriteFrame(spriteFrame);*/
}


