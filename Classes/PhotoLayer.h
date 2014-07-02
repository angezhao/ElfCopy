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

using namespace cocos2d;
using namespace cocos2d::ui;

class PhotoLayer : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(PhotoLayer);
    
    virtual void TouchesCancellnd(const std::vector<Touch*>& pTouches,Event *pEvent);
    virtual void TouchesBegan(const std::vector<Touch*>& pTouches,Event *pEvent);//注意这个方法和单点触控方法的返回类型不同
    virtual void TouchesEnded(const std::vector<Touch*>& pTouches,Event *pEvent);
    virtual void TouchesMoved(const std::vector<Touch*>& pTouches,Event *pEvent);
    
    void goBack(Ref* pSender,TouchEventType type);
    void changeOk(Ref* pSender,TouchEventType type);

    void loadImage(Image* image);
    Sprite* mask();
private:
    double distance;    //两个触摸点之间的距离
    double deltax;    //目标x轴的改变值
    double deltay;    //目标y轴的改变值
    double mscale;   //初始地图缩放比例
    ImageView* head;
    ImageView *userHead;
    ImageView* headBg;
    int touchId1;
    int touchId2;
    
    float getRotateAngle(Point startPos1, Point startPos2, Point endPos1, Point endPos2);  //获取旋转角度
};


#endif /* defined(__ElfCopy__PhotoLayer__) */
