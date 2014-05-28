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

USING_NS_CC;

class PhotoLayer : public Layer
{
public:
    PhotoLayer(const char *photofile);
    ~PhotoLayer();

    void goBack(Ref* pSender,cocos2d::ui::TouchEventType type);
    void changeOk(Ref* pSender,cocos2d::ui::TouchEventType type);
    void headTouch(Ref* pSender,cocos2d::ui::TouchEventType type);
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchMoved(Touch* touch, Event  *event);
    void onTouchEnded(Touch* touch, Event  *event);
    
    Sprite* createMaskedSprite(Sprite* src, const char* maskFile);
    
private:
    double distance;    //两个触摸点之间的距离
    double deltax;    //目标x轴的改变值
    double deltay;    //目标y轴的改变值
    Sprite *bg;     //目标精灵
    double mscale;   //初始地图缩放比例
    ui::ImageView *userHead;
    
};


#endif /* defined(__ElfCopy__PhotoLayer__) */
