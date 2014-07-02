//
//  MainLayer.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#ifndef __ElfCopy__MainLayer__
#define __ElfCopy__MainLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class MainLayer : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(MainLayer);

    void changeFace(ImageView* face);
    void goBack(Ref* pSender,TouchEventType type);
    void goNext(Ref* pSender,TouchEventType type);
    void changePhoto1(Ref* pSender,TouchEventType type);
    void changePhoto2(Ref* pSender,TouchEventType type);
    
    CheckBox* headBtn1;
    CheckBox* headBtn2;
};

#endif /* defined(__ElfCopy__MainLayer__) */
