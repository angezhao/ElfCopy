//
//  GameScene.cpp
//  ElfCopy
//
//  Created by Ange Zhao on 14-5-20.
//
//
#include "GameScene.h"
#include "StartLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.h"

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer, 0, 1);
    
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /////////////////////////////////
    StartLayer * layer = StartLayer::create();
    this->addChild(layer, 0, 1);
    
    return true;
}


