#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
// #include "cocostudio/CocoStudio.h"
// #include "cocostudio/ComRender.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //HelloWorld *layer = HelloWorld::create();
    //scene->addChild(layer);
    
    
    Size winSize = Director::getInstance()->getWinSize();
    
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren2/yuanshiren2.ExportJson");
    cocostudio::Armature *armature = cocostudio::Armature::create("yuanshiren2");
    armature->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature->getAnimation()->playWithIndex(0);
    scene->addChild(armature);
    
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("yuanshiren1/yuanshiren1.ExportJson");
    cocostudio::Armature *armature2 = cocostudio::Armature::create("yuanshiren1");
    armature2->setPosition(Point(winSize.width / 2, winSize.height / 2));
    armature2->getAnimation()->playWithIndex(0);
    scene->addChild(armature2);
    
    cocostudio::Bone *tou1 = armature2->getBone("tou1");
    cocostudio::Skin* face1 = cocostudio::Skin::create("face/tou1.png");
    face1->setAnchorPoint(Point(-0.1, 1.2));
    tou1->addDisplay(face1, 1);
    tou1->changeDisplayWithIndex(1, true);
    
    cocostudio::Bone *tou2 = armature->getBone("tou2");
    cocostudio::Skin* face2 = cocostudio::Skin::create("face/tou2.png");
    face2->setAnchorPoint(Point(-0.2, 1.5));
    tou2->addDisplay(face2, 1);
    tou2->changeDisplayWithIndex(1, true);
    
    
    //Node *node = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("publish/test.json");
    //scene->addChild(node);
    
    //cocostudio::ComRender *pLoadRender = (cocostudio::ComRender *)(node->getChildByTag(10005)->getComponent("CCArmature"));
    //cocostudio::Armature *myMan = (cocostudio::Armature *)(pLoadRender->getNode());

    
//    cocostudio::Bone *wbone = myMan->getBone("white_face");
//    cocostudio::Skin* wskin = cocostudio::Skin::create("face/woman.png");
//    wbone->addDisplay(wskin, 1);
//    wbone->changeDisplayWithIndex(1, true);
//
//    cocostudio::Bone *ybone = myMan->getBone("yellow_face");
//    cocostudio::Skin* yskin = cocostudio::Skin::create("face/man.png");
//    ybone->addDisplay(yskin, 1);
//    ybone->changeDisplayWithIndex(1, true);
//    
//    cocostudio::Bone *swbone = myMan->getBone("woman");
//    cocostudio::Skin* swskin = cocostudio::Skin::create("face/woman.png");
//    swbone->addDisplay(swskin, 1);
//    swbone->changeDisplayWithIndex(1, true);
//    
//    cocostudio::Bone *sybone = myMan->getBone("man");
//    cocostudio::Skin* syskin = cocostudio::Skin::create("face/man.png");
//    sybone->addDisplay(syskin, 1);
//    sybone->changeDisplayWithIndex(1, true);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    ImageView* face = ImageView::create();
    face->loadTexture("scene/bg.png");
    cocos2d::Sprite* show_sprite = this->mask(face);
    show_sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(show_sprite, 0);
    
//    cocos2d::Sprite* src_sprite = cocos2d::Sprite::create("scene/bg.png");
//    cocos2d::Sprite* show_sprite = this->createMaskedSprite(src_sprite, "face/mask.png");
//    show_sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(show_sprite, 0);
    
    /*
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    */
    
    /*
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //TakePhoto::takePhoto();
    /*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
     */
}

cocos2d::Sprite* HelloWorld::createMaskedSprite(cocos2d::Sprite* src, const char* maskFile)
{
    cocos2d::Sprite* mask = cocos2d::Sprite::create(maskFile);
    
    assert(src);
    assert(mask);
    
    cocos2d::Size srcContent = src->getContentSize();
    //cocos2d::Size maskContent = mask->getContentSize();
    
    cocos2d::RenderTexture* rt = cocos2d::RenderTexture::create(srcContent.width, srcContent.height, cocos2d::Texture2D::PixelFormat::RGBA8888);
    
    /*
     float ratiow = srcContent.width / maskContent.width;
     float ratioh = srcContent.height / maskContent.height;
     mask->setScaleX(ratiow);
     mask->setScaleY(ratioh);*/
    
    mask->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    src->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    
    cocos2d::BlendFunc blendFunc2 = { GL_ONE, GL_ZERO };
    mask->setBlendFunc(blendFunc2);
    cocos2d::BlendFunc blendFunc3 = { GL_DST_ALPHA, GL_ZERO };
    src->setBlendFunc(blendFunc3);
    
    rt->begin();
    mask->visit();
    src->visit();
    rt->end();
    
    cocos2d::Sprite* retval = cocos2d::Sprite::createWithTexture(rt->getSprite()->getTexture());
    retval->setFlippedY(true);
    return retval;
}

cocos2d::Sprite* HelloWorld::mask(cocos2d::ui::ImageView* srcImg)
{
    ImageView* maskImg = ImageView::create();
    maskImg->loadTexture("face/mask.png");
    
    assert(srcImg);
    assert(maskImg);
    
    cocos2d::Sprite* src = static_cast<cocos2d::Sprite*>(srcImg->getVirtualRenderer());
    cocos2d::Sprite* mask = static_cast<cocos2d::Sprite*>(maskImg->getVirtualRenderer());
    cocos2d::Size srcContent = src->getContentSize();
    cocos2d::Size maskContent = mask->getContentSize();
    
    cocos2d::RenderTexture* rt = cocos2d::RenderTexture::create(srcContent.width, srcContent.height, cocos2d::Texture2D::PixelFormat::RGBA8888);
    
    /*
     float ratiow = srcContent.width / maskContent.width;
     float ratioh = srcContent.height / maskContent.height;
     mask->setScaleX(ratiow);
     mask->setScaleY(ratioh);*/
    
    mask->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    src->setPosition(cocos2d::Point(srcContent.width / 2, srcContent.height / 2));
    
    cocos2d::BlendFunc blendFunc2 = { GL_ONE, GL_ZERO };
    mask->setBlendFunc(blendFunc2);
    cocos2d::BlendFunc blendFunc3 = { GL_DST_ALPHA, GL_ZERO };
    src->setBlendFunc(blendFunc3);
    
    rt->begin();
    mask->visit();
    src->visit();
    rt->end();
    
//    cocos2d::Sprite* retval = cocos2d::Sprite::createWithTexture(rt->getSprite()->getTexture());
//    retval->setFlippedY(true);
//    return retval;
    
    cocos2d::Texture2D* texture = rt->getSprite()->getTexture();
    cocos2d::SpriteFrame* spriteFrame = cocos2d::SpriteFrame::createWithTexture(texture, cocos2d::Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    src->setSpriteFrame(spriteFrame);
    return src;
}
