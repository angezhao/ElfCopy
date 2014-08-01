//
//  VidioLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "MainLayer.h"
#include "VidioLayer.h"
#include "cocostudio/CocoStudio.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CaptureScreen.h"
#endif

bool VidioLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
    Widget *node = GUIReader::getInstance()->widgetFromJsonFile("ElfYourSelfUi/ElfYourSelfUi_5.ExportJson");
	if (node == nullptr)
	{
		return false;
	}
    
    Button* btnBack = (Button*)node->getChildByName("btnBack");
    btnBack->addTouchEventListener(this, toucheventselector(VidioLayer::goBack));
    
    Button* playBack = (Button*)node->getChildByName("playBtn");
    playBack->addTouchEventListener(this, toucheventselector(VidioLayer::playVidio));

    // 原始人
    yuanshirenBtn = (CheckBox*)node->getChildByName("yuanshirenBtn");
    yuanshirenBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    yuanshirenBg = (ImageView*)node->getChildByName("yuanshirenBg");
    
    // 功夫
    gongfuBtn = (CheckBox*)node->getChildByName("gongfuBtn");
    gongfuBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    gongfuBg = (ImageView*)node->getChildByName("gongfuBg");
    
    // 马戏团
    maxituanBtn = (CheckBox*)node->getChildByName("maxituanBtn");
    maxituanBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    maxituanBg = (ImageView*)node->getChildByName("maxituanBg");
    
    // 星星的你
    staryouBtn = (CheckBox*)node->getChildByName("staryouBtn");
    staryouBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    staryouBg = (ImageView*)node->getChildByName("staryouBg");
    
    // 打老虎
    dalaohuBtn = (CheckBox*)node->getChildByName("dalaohuBtn");
    dalaohuBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    dalaohuBg = (ImageView*)node->getChildByName("dalaohuBg");
    
    // 同学会
    tongxuehuiBtn = (CheckBox*)node->getChildByName("tongxuehuiBtn");
    tongxuehuiBtn->addTouchEventListener(this, toucheventselector(VidioLayer::switchVidio));
    tongxuehuiBg = (ImageView*)node->getChildByName("tongxuehuiBg");
    
    //默认同学会
    tongxuehuiBtn->setSelectedState(true);
    yuanshirenBtn->setSelectedState(false);
    gongfuBtn->setSelectedState(false);
    maxituanBtn->setSelectedState(false);
    staryouBtn->setSelectedState(false);
    dalaohuBtn->setSelectedState(false);
    tongxuehuiBg->setVisible(true);
    yuanshirenBg->setVisible(false);
    gongfuBg->setVisible(false);
    maxituanBg->setVisible(false);
    staryouBg->setVisible(false);
    dalaohuBg->setVisible(false);
    animationIndex = TONGXUEHUI;
    
    this->addChild(node);
    return true;
}

void VidioLayer::goBack(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        Layer* parent = (Layer*)this->getParent();
        this->removeFromParentAndCleanup(true);
        parent->removeFromParentAndCleanup(true);
    }
}

void VidioLayer::switchVidio(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        CheckBox* selectVidio = (CheckBox*)pSender;
        if (!selectVidio->getSelectedState()) {//选中
            switch (animationIndex) {
                case YUANSHIREN:
                    yuanshirenBtn->setSelectedState(false);
                    yuanshirenBg->setVisible(false);
                    break;
                case GONGFU:
                    gongfuBtn->setSelectedState(false);
                    gongfuBg->setVisible(false);
                    break;
                case MAXITUAN:
                    maxituanBtn->setSelectedState(false);
                    maxituanBg->setVisible(false);
                    break;
                case TONGXUEHUI:
                    tongxuehuiBtn->setSelectedState(false);
                    tongxuehuiBg->setVisible(false);
                    break;
                case STARYOU:
                    staryouBtn->setSelectedState(false);
                    staryouBg->setVisible(false);
                    break;
                case DALAOHU:
                    dalaohuBtn->setSelectedState(false);
                    dalaohuBg->setVisible(false);
                    break;
                default:
                    break;
            }

            const char* boxName = selectVidio->getName();
            if(strcmp(boxName,"yuanshirenBtn")==0){
                animationIndex = YUANSHIREN;
                yuanshirenBg->setVisible(true);
            }else if(strcmp(boxName,"gongfuBtn")==0){
                animationIndex = GONGFU;
                gongfuBg->setVisible(true);
            }else if(strcmp(boxName,"maxituanBtn")==0){
                animationIndex = MAXITUAN;
                maxituanBg->setVisible(true);
            }else if(strcmp(boxName,"staryouBtn")==0){
                animationIndex = STARYOU;
                staryouBg->setVisible(true);
            }else if(strcmp(boxName,"dalaohuBtn")==0){
                animationIndex = DALAOHU;
                dalaohuBg->setVisible(true);
            }else if(strcmp(boxName,"tongxuehuiBtn")==0){
                animationIndex = TONGXUEHUI;
                tongxuehuiBg->setVisible(true);
            }
        }else{//取消选中
            animationIndex = VIDIOMAX;
            const char* boxName = selectVidio->getName();
            if(strcmp(boxName,"yuanshirenBtn")==0){
                yuanshirenBg->setVisible(false);
            }else if(strcmp(boxName,"gongfuBtn")==0){
                gongfuBg->setVisible(false);
            }else if(strcmp(boxName,"maxituanBtn")==0){
                maxituanBg->setVisible(false);
            }else if(strcmp(boxName,"staryouBtn")==0){
                staryouBg->setVisible(false);
            }else if(strcmp(boxName,"dalaohuBtn")==0){
                dalaohuBg->setVisible(false);
            }else if(strcmp(boxName,"tongxuehuiBtn")==0){
                tongxuehuiBg->setVisible(false);
            }
        }
    }
}

void VidioLayer::makeFace(std::string spriteFrameName)
{
    // 114*121
    // 261*281
    // 0.436
    // 0.431
    float uiSacleX = 0.436f;
    float uiSacleY = 0.431f;
    Sprite *face = Sprite::createWithSpriteFrameName(spriteFrameName);
    face->setFlippedY(true);
    face->setScaleX(uiSacleX);
    face->setScaleY(uiSacleY);
    Size size = face->getContentSize();
    face->setPosition(Point(size.width / 2, size.height / 2));

    RenderTexture* rt = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
    rt->begin();
    face->visit();
    rt->end();
    
    Sprite* retval = Sprite::createWithTexture(rt->getSprite()->getTexture());
    std::string scaleSpriteFrameName = "scale_" + spriteFrameName;
    SpriteFrameCache::getInstance()->removeSpriteFrameByName(scaleSpriteFrameName);
    SpriteFrame* spriteFrame = retval->getSpriteFrame();
    SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, scaleSpriteFrameName);
}

void VidioLayer::playYuanShiRen()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren2/yuanshiren2.ExportJson");
    Armature *armature2 = Armature::create("yuanshiren2");
    armature2->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature2->getAnimation()->playWithIndex(0);
    this->addChild(armature2, 0, 1);
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren1/yuanshiren1.ExportJson");
    Armature *armature1 = Armature::create("yuanshiren1");
    armature1->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature1->getAnimation()->playWithIndex(0);
    armature1->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VidioLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->addChild(armature1, 0, 2);
    
    this->makeFace("player_face1");
    Skin* face1 = Skin::createWithSpriteFrameName("scale_player_face1");
    face1->setFlippedY(true);
    // face1->setAnchorPoint(Point(0.453, 0.65));
    face1->setAnchorPoint(Point(0.44, 0.625));
    Bone *tou1 = armature1->getBone("tou1");
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    this->makeFace("player_face2");
    Skin* face2 = Skin::createWithSpriteFrameName("scale_player_face2");
    face2->setFlippedY(true);
    face2->setAnchorPoint(Point(0.445, 0.58));
    Bone *tou2 = armature2->getBone("tou2");
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
}

void VidioLayer::playGongFu()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("gongfu/gongfu.ExportJson");
    Armature *armature = Armature::create("gongfu");
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VidioLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->addChild(armature, 0, 1);
    
    this->makeFace("player_face1");
    Skin* face1 = Skin::createWithSpriteFrameName("scale_player_face1");
    face1->setFlippedY(true);
    face1->setAnchorPoint(Point(0.445, 0.58));
    Bone *tou1 = armature->getBone("tou1");
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    this->makeFace("player_face2");
    Skin* face2 = Skin::createWithSpriteFrameName("scale_player_face2");
    face2->setFlippedY(true);
    face2->setAnchorPoint(Point(0.442, 0.60));
    Bone *tou2 = armature->getBone("tou2");
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
}

void VidioLayer::playTongxuehui()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("tongxuehui/tongxuehui.ExportJson");
    Armature *armature = Armature::create("tongxuehui");
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VidioLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->addChild(armature, 0, 1);
    
    this->makeFace("player_face1");
    Skin* face1 = Skin::createWithSpriteFrameName("scale_player_face1");
    face1->setFlippedY(true);
    face1->setAnchorPoint(Point(0.445, 0.58));
    Bone *tou1 = armature->getBone("tou1");
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    this->makeFace("player_face2");
    Skin* face2 = Skin::createWithSpriteFrameName("scale_player_face2");
    face2->setFlippedY(true);
    face2->setAnchorPoint(Point(0.445, 0.58));
    Bone *tou2 = armature->getBone("tou2");
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
}

void VidioLayer::playMaxituan()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("maxituan/maxituan.ExportJson");
    Armature *armature = Armature::create("maxituan");
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VidioLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->addChild(armature, 0, 1);
    
    this->makeFace("player_face1");
    Skin* face1 = Skin::createWithSpriteFrameName("scale_player_face1");
    face1->setFlippedY(true);
    face1->setAnchorPoint(Point(0.445, 0.58));
    Bone *tou1 = armature->getBone("tou1");
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    this->makeFace("player_face2");
    Skin* face2 = Skin::createWithSpriteFrameName("scale_player_face2");
    face2->setFlippedY(true);
    face2->setAnchorPoint(Point(0.442, 0.58));
    Bone *tou2 = armature->getBone("tou2");
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
}


void VidioLayer::playStaryou()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("laizixingxingdeni/laizixingxingdeni.ExportJson");
    Armature *armature = Armature::create("laizixingxingdeni");
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(VidioLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->addChild(armature, 0, 1);
    
    this->makeFace("player_face1");
    Skin* face1 = Skin::createWithSpriteFrameName("scale_player_face1");
    face1->setFlippedY(true);
    face1->setAnchorPoint(Point(0.445, 0.58));
    Bone *tou1 = armature->getBone("tou1");
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    this->makeFace("player_face2");
    Skin* face2 = Skin::createWithSpriteFrameName("scale_player_face2");
    face2->setFlippedY(true);
    face2->setAnchorPoint(Point(0.442, 0.60));
    Bone *tou2 = armature->getBone("tou2");
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
}

void VidioLayer::playDalaohu()
{
    
}

void VidioLayer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    std::string id = movementID;
    
	if (movementType == LOOP_COMPLETE)
	{
        this->stopRecord();
	} else if (movementType == COMPLETE) {
        this->stopRecord();
    } else if (movementType == START) {
    }
}

void VidioLayer::playVidio(Ref* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        switch (animationIndex) {
            case YUANSHIREN:
                this->audioPath = "Music/yuanshiren.mp3";
                this->playYuanShiRen();
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(this->audioPath);
                break;
            case GONGFU:
                this->playGongFu();
                break;
            case MAXITUAN:
                this->audioPath = "Music/maxituan.mp3";
                this->playMaxituan();
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(this->audioPath);
                break;
            case TONGXUEHUI:
                this->audioPath = "Music/tongxuehui.mp3";
                this->playTongxuehui();
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(this->audioPath);
                break;
            case STARYOU:
                this->audioPath = "Music/laizixingxingdeni.mp3";
                this->playStaryou();
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(this->audioPath);
                break;
            case DALAOHU:
                this->playDalaohu();
                break;
            default:
                break;
        }
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // CaptureScreen::startRecord();
#endif
    }
}

void VidioLayer::drawFrame(float dt)
{
    log("drawFrame");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CaptureScreen::drawFrame();
#endif
}

void VidioLayer::stopRecord()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CaptureScreen::stopRecord(this->audioPath);
#endif
    for (int i = 1; i < 10; i ++) {
        if (this->getChildByTag(i)) {
            this->removeChildByTag(i);
        }
    }
}