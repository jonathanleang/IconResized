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
    sizes["29x29"] = "Icon-Small.png";
    sizes["40x40"] = "Icon-Small-40.png";
    sizes["50x50"] = "Icon-Small-50.png";
    sizes["57x57"] = "Icon.png";
    sizes["58x58"] = "Icon-Small@2x.png";
    sizes["60x60"] = "Icon-60.png";
    sizes["72x72"] = "Icon-72.png";
    sizes["76x76"] = "Icon-76.png";
    sizes["80x80"] = "Icon-Small-40@2x.png";
    sizes["100x100"] = "Icon-Small-50@2x.png";
    sizes["114x114"] = "Icon@2x.png";
    sizes["120x120"] = "Icon-60@2x.png";
    sizes["144x144"] = "Icon-72@2x.png";
    sizes["152x152"] = "Icon-76@2x.png";
    sizes["512x512"] = "iTunesArtwork";
    sizes["1024x1024"] = "iTunesArtwork@2x";
    
    
    // Android
    sizes["36x36"] = "Icon-ldpi.png";
    sizes["48x48"] = "Icon-mdpi.png";
    sizes["72x72"] = "Icon-hdpi.png";
    sizes["96x96"] = "Icon-xhdpi.png";
    sizes["144x144"] = "Icon-xxhdpi.png";
    
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
    addImage("preview");
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
