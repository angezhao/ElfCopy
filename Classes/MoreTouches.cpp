//
//  MoreTouches.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-28.
//
//

#include "MoreTouches.h"

Scene *MoreTouches::scene()
{
    Scene *scene=Scene::create();
    MoreTouches *layer=MoreTouches::create();
    //layer->setTouchEnabled(true);
    scene->addChild(layer);
    return scene;
}

bool MoreTouches::init()
{
    if(!Layer::init())
    {
        return false;
    }
    bg=Sprite::create("scene/bg.png");   //初始化目标图片
    this->addChild(bg);
    
    mscale=1.0;     //初始化图片的缩放比例
    
//    auto dispatcher = Director::getInstance()->getEventDispatcher();
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = CC_CALLBACK_2(MoreTouches::onTouchBegan,this);
//    listener->onTouchMoved = CC_CALLBACK_2(MoreTouches::onTouchMoved,this);
//    listener->onTouchEnded = CC_CALLBACK_2(MoreTouches::onTouchEnded,this);
//    listener->setSwallowTouches(true);//不向下传递触摸
//    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

//void MoreTouches::registerWithTouchDispather()
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
//}

void MoreTouches::TouchesBegan(const std::vector<Touch*>& pTouches, cocos2d::Event *pEvent)
{
    if(pTouches.size()>=2)  //如果触摸点不少于两个
    {
        auto iter=pTouches.begin();
        Point mPoint1=((Touch *)(*iter))->getLocationInView();
        mPoint1 = cocos2d::Director::getInstance()->convertToGL(mPoint1);
        iter++;
        Point mPoint2=((Touch *)(*iter))->getLocationInView();
        mPoint2 = cocos2d::Director::getInstance()->convertToGL(mPoint2);
        
        distance=sqrt((mPoint2.x-mPoint1.x)*(mPoint2.x-mPoint1.x)+(mPoint2.y-mPoint1.y)*(mPoint2.y-mPoint1.y));//计算两个触摸点距离
        deltax = (mPoint1.x + mPoint2.x)/2 - bg->getPositionX();     //得到两个触摸点中点和精灵锚点的差值
        deltay = (mPoint1.y + mPoint2.y)/2 - bg->getPositionY();
        //CCLog("ccTouchesBegan  ...");
        
    }
}

void MoreTouches::TouchesMoved(const std::vector<Touch*>& pTouches, cocos2d::Event *pEvent)
{
    if(pTouches.size()>=2)  //如果移动时触摸点的个数不少于两个
    {
        auto iter = pTouches.begin();
        Point mPoint1 = ((Touch*)(*iter))->getLocationInView();
        mPoint1 = cocos2d::Director::getInstance()->convertToGL(mPoint1);
        iter++;
        Point mPoint2 = ((Touch*)(*iter))->getLocationInView();
        mPoint2 = cocos2d::Director::getInstance()->convertToGL(mPoint2);        //获得新触摸点两点之间的距离
        double mdistance = sqrt((mPoint1.x-mPoint2.x)*(mPoint1.x-mPoint2.x)+(mPoint1.y-mPoint2.y)*(mPoint1.y-mPoint2.y));
        mscale = mdistance/distance * mscale;                      //   新的距离 / 老的距离  * 原来的缩放比例，即为新的缩放比例
        distance = mdistance;
        bg->setScale(mscale);
        
        double x = (mPoint2.x+mPoint1.x)/2 - deltax;      //计算两触点中点与精灵锚点的差值
        double y = (mPoint2.y+mPoint1.y)/2 - deltay;
        bg->setPosition(Point(x,y));                        //保持两触点中点与精灵锚点的差值不变
        deltax = (mPoint1.x+ mPoint2.x)/2 - bg->getPositionX();       //计算新的偏移量
        deltay = (mPoint2.y + mPoint1.y)/2 - bg->getPositionY();
        //CCLog("ccTouchMoved  ....");
    }
    if(pTouches.size()==1)                          //如果触摸点为一个
    {
        auto iter =  pTouches.begin();
        Point mPoint=((Touch*)(*iter))->getLocationInView();
        mPoint=cocos2d::Director::getInstance()->convertToGL(mPoint);    //坐标转换
        bg->setPosition(mPoint);                    //直接移动精灵
    }
}

void MoreTouches::TouchesEnded(const std::vector<Touch*>& pTouches, cocos2d::Event *pEvent)
{
    
}

void MoreTouches::TouchesCancellnd(const std::vector<Touch*>& pTouches, cocos2d::Event *pEvent)
{
    
    
}
void MoreTouches::onEnter()
{
    Layer::onEnter();
    //Layer::setTouchEnabled(true);
    //CCLog("onenter");
}

void MoreTouches::onExit()
{
    Layer::onExit();
    //cocos2d::Director::getInstance()->gettou
    //cocos2d::Director::getInstance()->getTouchDispatcher()->removeDelegate(this);     //移除触摸代理
}