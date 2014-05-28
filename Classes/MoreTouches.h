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
#include "ui/CocosGUI.h"

USING_NS_CC;
class MoreTouches :public Layer
{
public:
    static Scene *scene();
    virtual bool init();
    virtual void TouchesCancellnd(const std::vector<Touch*>& pTouches,Event *pEvent);
    virtual void TouchesBegan(const std::vector<Touch*>& pTouches,Event *pEvent);//注意这个方法和单点触控方法的返回类型不同
    virtual void TouchesEnded(const std::vector<Touch*>& pTouches,Event *pEvent);
    virtual void TouchesMoved(const std::vector<Touch*>& pTouches,Event *pEvent);
    CREATE_FUNC(MoreTouches);
    
public:
    double distance;    //两个触摸点之间的距离
    double deltax;    //目标x轴的改变值
    double deltay;    //目标y轴的改变值
    Sprite *bg;     //目标精灵
    double mscale;   //初始地图缩放比例
    //ui::ImageView *bg;
};

#endif /* defined(__ElfCopy__MoreTouches__) */
