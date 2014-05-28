//
//  MoreTouches.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-28.
//
//

#ifndef __ElfCopy__MoreTouches__
#define __ElfCopy__MoreTouches__

#include "cocos2d.h"
USING_NS_CC;
class MoreTouches :public Layer
{
public:
    static Scene *scene();
    virtual bool init();
    //virtual void registerWithTouchDispather(void);    //由于是继承自CCLayer，这个方法就不用重写了,但下面几个方法还是要重写滴
    virtual void TouchesCancellnd(const std::vector<Touch*>& pTouches,Event *pEvent);
    virtual void TouchesBegan(const std::vector<Touch*>& pTouches,Event *pEvent);//注意这个方法和单点触控方法的返回类型不同
    virtual void TouchesEnded(const std::vector<Touch*>& pTouches,Event *pEvent);
    virtual void TouchesMoved(const std::vector<Touch*>& pTouches,Event *pEvent);
    virtual void onEnter();
    virtual void onExit();
    CREATE_FUNC(MoreTouches);
    
public:
    double distance;    //两个触摸点之间的距离
    double deltax;    //目标x轴的改变值
    double deltay;    //目标y轴的改变值
    Sprite *bg;     //目标精灵
    double mscale;   //初始地图缩放比例
    
};

#endif /* defined(__ElfCopy__MoreTouches__) */
