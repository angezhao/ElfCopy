//
//  PhotoLayer.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#ifndef __ElfCopy__PhotoLayer__
#define __ElfCopy__PhotoLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class PhotoLayer : public cocos2d::Layer
{
public:
    PhotoLayer(const char *photofile);
    ~PhotoLayer();
    
    virtual void TouchesCancellnd(const std::vector<cocos2d::Touch*>& pTouches,cocos2d::Event *pEvent);
    virtual void TouchesBegan(const std::vector<cocos2d::Touch*>& pTouches,cocos2d::Event *pEvent);//注意这个方法和单点触控方法的返回类型不同
    virtual void TouchesEnded(const std::vector<cocos2d::Touch*>& pTouches,cocos2d::Event *pEvent);
    virtual void TouchesMoved(const std::vector<cocos2d::Touch*>& pTouches,cocos2d::Event *pEvent);

    void goBack(Ref* pSender,cocos2d::ui::TouchEventType type);
    void changeOk(Ref* pSender,cocos2d::ui::TouchEventType type);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
    
    cocos2d::Sprite* createMaskedSprite(cocos2d::Sprite* src, const char* maskFile);
    void mask(cocos2d::ui::ImageView* src,cocos2d::ui::ImageView* maskHead);
private:
    double distance;    //两个触摸点之间的距离
    double deltax;    //目标x轴的改变值
    double deltay;    //目标y轴的改变值
    double mscale;   //初始地图缩放比例
    cocos2d::ui::ImageView *maskHead;
    cocos2d::ui::ImageView *userHead;
};


#endif /* defined(__ElfCopy__PhotoLayer__) */
