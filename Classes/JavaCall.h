#ifndef JAVA_CALL_H
#define JAVA_CALL_H

#include "cocos2d.h"
#include "PhotoLayer.h"

USING_NS_CC;

void setPhotoPath(const char * path){
	CCLog("path: %s", path);

	PhotoLayer * layer = new PhotoLayer();
	layer->autorelease();
	//Director::getInstance()->getRunningScene()->addChild(layer);
}
#endif