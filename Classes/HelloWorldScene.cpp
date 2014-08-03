#include "HelloWorldScene.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>

// http://www.imagemagick.org/Magick++/Image.html

HelloWorld* HelloWorld::_instance = NULL;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    _instance = layer;
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255), 300, 300))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _curentImagePos = visibleSize/2;
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto *bg = Sprite::create("bg.png");
    bg->setScale(0.5);
    bg->setAnchorPoint(Vec2::ZERO);
    addChild(bg);
    
    // iOS
    sizes["29x29"] = "Icon-Small";
    sizes["40x40"] = "Icon-Small-40";
    sizes["50x50"] = "Icon-Small-50";
    sizes["57x57"] = "Icon";
    sizes["58x58"] = "Icon-Small@2x";
    sizes["60x60"] = "Icon-60";
    sizes["72x72"] = "Icon-72";
    sizes["76x76"] = "Icon-76";
    sizes["80x80"] = "Icon-Small-40@2x";
    sizes["100x100"] = "Icon-Small-50@2x";
    sizes["114x114"] = "Icon@2x";
    sizes["120x120"] = "Icon-60@2x";
    sizes["144x144"] = "Icon-72@2x";
    sizes["152x152"] = "Icon-76@2x";
    sizes["512x512"] = "iTunesArtwork";
    sizes["1024x1024"] = "iTunesArtwork@2x";
    
    
    // Android
    sizes["36x36"] = "Icon-ldpi";
    sizes["48x48"] = "Icon-mdpi";
    sizes["72x72"] = "Icon-hdpi";
    sizes["96x96"] = "Icon-xhdpi";
    sizes["144x144"] = "Icon-xxhdpi";
    
    return true;
}

string getFolder(const string& str)
{
    unsigned found = str.find_last_of("/\\");
    return str.substr(0,found);
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    string filePath = browseFolder();
    
    convert(filePath);
    
    return true;
}

bool HelloWorld::convert(string filePath)
{
    if (filePath =="")
        return false;
    
    size_t pos = filePath.find("file://");
    if (pos != string::npos){
        filePath = filePath.substr (pos+7);
    }
    
    Magick::Image masterImage(filePath);
    
    if (!masterImage.isValid()){
        return false;
    }
    
    showPreview(masterImage);
    
    
    string saveFolder = getFolder(filePath) + "/IconResized/" ;
    makeDirectory(saveFolder);
    
    string openDir;
    
    typedef map<string, string>::iterator it_type;
    for(it_type iterator = sizes.begin(); iterator != sizes.end(); iterator++) {
        // iterator->first = key
        // iterator->second = value
        // Repeat if you also want to iterate through the second map.
        string savePath = saveFolder + iterator->second;
        
        openDir = savePath;
        resizeAndWriteImage(masterImage, savePath, iterator->first);
    }
    
    openSavedFolder(openDir);
    
    return true;
}

void HelloWorld::showPreview(Magick::Image image){
    resizeAndWriteImage(image, "preview", "150x150");
    addImage("preview.png");
}

void HelloWorld::resizeAndWriteImage(Magick::Image image, string fileName, string size){
    if (image.isValid()){
        Magick::Image resizedImg = image;
        resizedImg.resize(size);
        
        printf("Saving...\n");
        cout << fileName << "\n";
        resizedImg.write(fileName+".png");
    }
}

void HelloWorld::addImage(string file){
    auto sprite = Sprite::create(file);
    if (!sprite){
        CCLOG("Can't load image");
        return;
    }
    sprite->setPosition(_curentImagePos);
    this->addChild(sprite, INT_MAX);
}
