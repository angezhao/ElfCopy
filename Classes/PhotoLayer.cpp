//
//  PhotoLayer.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//

#include "PhotoLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"
#include "ui/CocosGUI.h"
#include "ccMacros.h"

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
    btnBack->addTouchEventListener(this, toucheventselector(PhotoLayer::goBack));

    Button* okBtn = (Button*)node->getChildByName("okBtn");
    okBtn->addTouchEventListener(this, toucheventselector(PhotoLayer::changeOk));
    
    this->head = (ImageView*)node->getChildByName("head");
    this->headBg = (ImageView*)node->getChildByName("Image_4");
    touchId1 = -1;
    touchId2 = -1;
    
    this->addChild(node, 0, 1);
    
    return true;
}

void PhotoLayer::goBack(Ref* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        this->removeFromParentAndCleanup(true);
    }
}

void PhotoLayer::changeOk(Ref* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED){
        Sprite* sprite = this->mask();
        
        ImageView* face = ImageView::create();
        Texture2D* texture = sprite->getTexture();
        SpriteFrame* spriteFrame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
        ((Sprite*)face->getVirtualRenderer())->setSpriteFrame(spriteFrame);
        ((Sprite*)face->getVirtualRenderer())->setFlippedY(true);
        
        MainLayer* layer = (MainLayer*)this->getParent()->getParent();
        layer->changeFace(face);

        Layer* parent = (Layer*)this->getParent();
        this->removeFromParentAndCleanup(true);
        parent->removeFromParentAndCleanup(true);
    }
}

void PhotoLayer::TouchesBegan(const std::vector<Touch*>& pTouches, Event  *event)
{
    // log("TouchesBegan  ...size=%lu",pTouches.size());
    if (pTouches.size() >= 2)  //如果触摸点不少于两个
    {
        auto iter=pTouches.begin();
        touchId1 =((Touch *)(*iter))->getID();
        iter++;
        touchId2 =((Touch *)(*iter))->getID();
    } else if (pTouches.size() ==1 )                          //如果触摸点为一个
    {
        auto iter =  pTouches.begin();
        int touchId = ((Touch*)(*iter))->getID();
        // log("touchId=%d",touchId);
        if (touchId1 < 0) {
            touchId1 = touchId;
            // log("touchId1=%d",touchId);
        } else if (touchId2 < 0) {
            touchId2 = touchId;
            // log("touchId2=%d",touchId);
        }
    }
    // log("touchId1=%d,touchId2=%d",touchId1,touchId2);
}

void PhotoLayer::TouchesMoved(const std::vector<Touch*>& pTouches, Event  *event)
{
    // log("TouchesMoved  ...size=%lu",pTouches.size());
    if (pTouches.size() >= 2)  //如果移动时触摸点的个数不少于两个
    {
        auto iter = pTouches.begin();
        Point mPoint1 = ((Touch*)(*iter))->getLocation();
        Point lPoint1 = ((Touch*)(*iter))->getPreviousLocation();
        iter++;
        Point mPoint2 = ((Touch*)(*iter))->getLocation();
        Point lPoint2 = ((Touch*)(*iter))->getPreviousLocation();
        
        //放大缩小
        if (distance == 0) {
            distance=sqrt((lPoint2.x-lPoint1.x)*(lPoint2.x-lPoint1.x)+(lPoint2.y-lPoint1.y)*(lPoint2.y-lPoint1.y));//计算两个触摸点距离
            deltax = (lPoint1.x + lPoint2.x)/2 - userHead->getPositionX();     //得到两个触摸点中点和精灵锚点的差值
            deltay = (lPoint1.y + lPoint2.y)/2 - userHead->getPositionY();
        }
        //获得新触摸点两点之间的距离
        double mdistance = sqrt((mPoint1.x-mPoint2.x)*(mPoint1.x-mPoint2.x)+(mPoint1.y-mPoint2.y)*(mPoint1.y-mPoint2.y));
        mscale = mdistance/distance * mscale;                      //   新的距离 / 老的距离  * 原来的缩放比例，即为新的缩放比例
        distance = mdistance;
        userHead->setScale(mscale);
        //log("mscale=%f,distance=%f",mscale,distance);
        
        //移动
        double x = (mPoint2.x+mPoint1.x)/2 - deltax;      //计算两触点中点与精灵锚点的差值
        double y = (mPoint2.y+mPoint1.y)/2 - deltay;
        userHead->setPosition(Point(x, y));                        //保持两触点中点与精灵锚点的差值不变
        deltax = (mPoint1.x+ mPoint2.x)/2 - userHead->getPositionX();       //计算新的偏移量
        deltay = (mPoint2.y + mPoint1.y)/2 - userHead->getPositionY();
        
        //旋转
        float angle = this->getRotateAngle(lPoint1, lPoint2, mPoint1, mPoint2);
		//log("delta angle=%f",angle);
		if (angle != 0.0f){
			angle += userHead->getRotation();
			userHead->setRotation(angle);
            //log("angle=%f",angle);
		}
    }
    else if (pTouches.size() == 1)                          //如果触摸点为一个
    {
        auto iter =  pTouches.begin();
        Point mPoint1 = ((Touch*)(*iter))->getLocation();//获得触摸位置
        Point lPoint1 = ((Touch*)(*iter))->getPreviousLocation();//获取触摸的前一个位置
        
        if (touchId1 >= 0 && touchId2 >= 0) {
            //Point middlePoint = Point((lPoint1.x+lPoint2.x)/2, (lPoint1.y+lPoint2.y)/2);
        }
        
        Point headPos = userHead->getPosition();
        Point offset = Point(mPoint1-lPoint1); // 获取offset，2.14是用ccpSub，3.0后直接用 - 号就可以
        Point nextPos = Point(headPos + offset);
        if (nextPos.x <= -388) {
            nextPos.x = -388;
        }
        if (nextPos.x >= 375) {
            nextPos.x = 375;
        }
        if (nextPos.y <= -318) {
            nextPos.y = -318;
        }
        if (nextPos.y >= 300) {
            nextPos.y = 300;
        }
        userHead->setPosition(nextPos);
    }
}

float PhotoLayer::getRotateAngle(Point startPos1, Point startPos2, Point endPos1, Point endPos2){
	float angle = 0.0f;
    
	//两个向量
	Point *sp = new Point(startPos2.x - startPos1.x, startPos2.y - startPos1.y);
	Point *ep = new Point(endPos2.x - endPos1.x, endPos2.y - endPos1.y);
    
	// cos(A) = (x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2))
    double n = sp->x * ep->x + sp->y * ep->y;
	double m = sqrt(sp->x * sp->x + sp->y * sp->y) * sqrt(ep->x * ep->x + ep->y * ep->y);
    double cosmn = n / m;
    if (m!=0 && (cosmn>=1.000001 || cosmn <= 0.999999)) {
        angle = CC_RADIANS_TO_DEGREES(acos(cosmn));
        //log("n=%f,m=%f,n/m=%f,cos=%f,angle=%f",n,m,n/m,acos(cosmn),angle);
    }
    
    //sin(A) = (x1 * y2 - y1 * x2 ) / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2))
    //sin（A） 小于0 则顺时针， 大于0则逆时针
	double n1 = sp->x * ep->y - sp->y * ep->x;
	if (m !=0 && n1/m > 0) {
        angle = -1 * angle;
    }
	//log("return angle=%f",angle);
	return angle;
}

void PhotoLayer::TouchesEnded(const std::vector<Touch*>& pTouches, Event  *event)
{
    // log("TouchesEnded  ...size=%lu",pTouches.size());
    if (pTouches.size()>2) {
        // log("TouchesEnded  ...error.....");
    } else if (pTouches.size() == 1)                         //如果触摸点为一个
    {
        auto iter =  pTouches.begin();
        int touchId = ((Touch*)(*iter))->getID();
        if (touchId1 == touchId) {
            touchId1 = -1;
        } else if (touchId2 == touchId) {
            touchId2 = -1;
        }
    }
}

void PhotoLayer::TouchesCancellnd(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    log("TouchesCancellnd  ...");
}

void PhotoLayer::loadImage(Image* image)
{
    Texture2D* texture = new Texture2D();
    texture->initWithImage(image);
    Sprite *imageSprite = Sprite::createWithTexture(texture);

    userHead = ImageView::create();
    Sprite* userHeadSprite = (Sprite*)userHead->getVirtualRenderer();
    userHeadSprite->setSpriteFrame(imageSprite->getSpriteFrame());

    Size headSize = this->headBg->getContentSize();
    Size imageSize = imageSprite->getContentSize();
    double mscalex = headSize.width / imageSize.width;
    double mscaley = headSize.height / imageSize.height;
    mscale =  mscalex > mscaley ? mscalex : mscaley;

    userHead->setScale(mscale);
    userHead->setTouchEnabled(true);

    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
    auto listener1 = EventListenerTouchAllAtOnce::create();//创建一个触摸监听(多点触摸）
    listener1->onTouchesBegan = CC_CALLBACK_2(PhotoLayer::TouchesBegan, this);//指定触摸的回调函数
    listener1->onTouchesEnded = CC_CALLBACK_2(PhotoLayer::TouchesEnded, this);
    listener1->onTouchesMoved = CC_CALLBACK_2(PhotoLayer::TouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);//将listener放入事件委托中
    
    this->head->addChild(userHead, 2);
}

Sprite* PhotoLayer::mask()
{
    assert(this->userHead);

    float uiSacle = 0.38f;
    uiSacle = 1;
    Sprite* userHeadSprite = (Sprite*)userHead->getVirtualRenderer();
    Sprite* textureSprite = Sprite::createWithSpriteFrame(userHeadSprite->getSpriteFrame());
    Point userHeadPos = Node::convertToWorldSpaceAR(this->userHead->getPosition());
    Point texturePosition = this->convertToNodeSpace(userHeadPos);
    textureSprite->setPosition(texturePosition);
    textureSprite->setScale(mscale * uiSacle);
    textureSprite->setRotation(this->userHead->getRotation());
    
    Sprite* maskSprite = Sprite::create("face/mask.png");
    maskSprite->setPosition(Point(512, 384));
    // 这里是为了适配动画里的骨骼大小，大概是114*121，UI层就做放大处理了。
    maskSprite->setScale(uiSacle);

    // Size size = Director::getInstance()->getVisibleSize();
    Size size = Director::getInstance()->getWinSize();
    RenderTexture* rt = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
    
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
}


