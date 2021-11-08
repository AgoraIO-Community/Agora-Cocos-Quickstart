/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class MyIGamingRtcEngineEventHandler
    : public agora::rtc::IRtcEngineEventHandler {
private:
  HelloWorld *mUi;

public:
  explicit MyIGamingRtcEngineEventHandler(HelloWorld *ui) : mUi(ui) {}

  void onJoinChannelSuccess(const char *channel, uid_t uid,
                            int elapsed) override {
    CCLOG("[General C++]:onJoinChannelSuccess %s %d %d", channel, uid, elapsed);
    std::stringstream rawMsg;
    rawMsg << "onJoinChannelSuccess " << channel << " " << uid << " "
           << elapsed;
    mUi->updateMsgContent(rawMsg.str());
    mUi->addTextureRender(0, 640, 480);
  }

  void onLeaveChannel(const agora::rtc::RtcStats &stats) override {
    CCLOG("[General C++]:onLeaveChannel %d %d %d", stats.duration,
          stats.txBytes, stats.rxBytes);
    std::stringstream rawMsg;
    rawMsg << "onLeaveChannel " << stats.duration << " " << stats.txBytes << " "
           << stats.rxBytes;
    mUi->updateMsgContent(rawMsg.str());
    mUi->removeAllTextureRenders();
  }

  void onUserJoined(uid_t uid, int elapsed) override {
    CCLOG("[General C++]:onUserJoined %d %d", uid, elapsed);
    std::stringstream rawMsg;
    rawMsg << "onUserJoined " << uid << " " << elapsed;
    mUi->updateMsgContent(rawMsg.str());
  }

  void onUserOffline(uid_t uid,
                     agora::rtc::USER_OFFLINE_REASON_TYPE reason) override {
    CCLOG("[General C++]:onUserOffline %d %d", uid, reason);
    std::stringstream rawMsg;
    rawMsg << "onUserOffline " << uid << " " << reason;
    mUi->updateMsgContent(rawMsg.str());
    mUi->removeTextureRender(uid);
  }

  void onFirstRemoteVideoDecoded(uid_t uid, int width, int height,
                                 int elapsed) override {
    CCLOG("[General C++]:onFirstRemoteVideoDecoded %d %d %d %d", uid, width,
          height, elapsed);
    mUi->addTextureRender(uid, width, height);
  }
};

Scene *HelloWorld::createScene() { return HelloWorld::create(); }

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in "
         "front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
  //////////////////////////////
  // 1. super init first
  if (!Scene::init()) {
    return false;
  }

  scheduleUpdate();

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  /////////////////////////////
  // 2. add a menu item with "X" image, which is clicked to quit the program
  //    you may modify it.

  // add a "close" icon to exit the progress. it's an autorelease object
  auto closeItem =
      MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

  if (closeItem == nullptr || closeItem->getContentSize().width <= 0 ||
      closeItem->getContentSize().height <= 0) {
    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
  } else {
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));
  }

  // create menu, it's an autorelease object
  auto menu = Menu::create(closeItem, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);

  /////////////////////////////
  // 3. add your codes below...

  // create and initialize a label

  auto label = Label::createWithTTF("HelloWorld", "fonts/Marker Felt.ttf", 24);
  if (label == nullptr) {
    problemLoading("'fonts/Marker Felt.ttf'");
  } else {
    // position the label on the center of the screen
    label->setPosition(
        Vec2(origin.x + visibleSize.width / 2,
             origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
  }

  textBox = TextBox::create("TextBox.png");
  if (textBox == nullptr) {
    problemLoading("'TextBox.png'");
  } else {
    textBox->setSize(220, 160);

    textBox->setPosition(Vec2(
        origin.x + visibleSize.width / 2,
        origin.y +
            (visibleSize.height - label->getContentSize().height * 1.5f) / 2));

    this->addChild(textBox, 0);
  }

  float leftPadding = 10;

  editBox = cocos2d::ui::EditBox::create(cocos2d::Size(120, 30), "TextBox.png");
  if (editBox == nullptr) {
    problemLoading("'TextBox.png'");
  } else {
    editBox->setPlaceHolder("Channel ID");

    editBox->setPosition(
        Vec2(origin.x + leftPadding + editBox->getContentSize().width / 2,
             origin.y + visibleSize.height -
                 editBox->getContentSize().height * 1.5f));

    this->addChild(editBox, 0);
  }

  auto joinButton = cocos2d::ui::Button::create(
      "Button.png", "ButtonPressed.png", "ButtonPressed.png");
  if (joinButton == nullptr) {
    problemLoading("'Button.png' and 'ButtonPressed.png'");
  } else {
    joinButton->setTitleText("Join Channel");

    joinButton->setPosition(
        Vec2(origin.x + leftPadding + joinButton->getContentSize().width / 2,
             origin.y + visibleSize.height -
                 1 * joinButton->getContentSize().height -
                 2 * editBox->getContentSize().height));

    joinButton->addTouchEventListener(
        [&](cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
          switch (type) {
          case ui::Widget::TouchEventType::BEGAN:
            break;
          case ui::Widget::TouchEventType::ENDED:
            onJoinChannelClicked();
            break;
          default:
            break;
          }
        });

    this->addChild(joinButton, 0);
  }

  auto leaveButton = ui::Button::create("Button.png", "ButtonPressed.png",
                                        "ButtonPressed.png");
  if (leaveButton == nullptr) {
    problemLoading("'Button.png' and 'ButtonPressed.png'");
  } else {
    leaveButton->setTitleText("Leave Channel");

    leaveButton->setPosition(
        Vec2(origin.x + leftPadding + leaveButton->getContentSize().width / 2,
             origin.y + visibleSize.height -
                 2 * leaveButton->getContentSize().height -
                 2 * editBox->getContentSize().height));

    leaveButton->addTouchEventListener(
        [&](cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
          switch (type) {
          case ui::Widget::TouchEventType::BEGAN:
            break;
          case ui::Widget::TouchEventType::ENDED:
            onLeaveChannelClicked();
            break;
          default:
            break;
          }
        });

    this->addChild(leaveButton, 0);
  }

  return true;
}

void HelloWorld::menuCloseCallback(Ref *pSender) {
  // Close the cocos2d-x game scene and quit the application
  Director::getInstance()->end();

  /*To navigate back to native iOS screen(if present) without quitting the
   * application  ,do not use Director::getInstance()->end() as given
   * above,instead trigger a custom event created in RootViewController.mm as
   * below*/

  // EventCustom customEndEvent("game_scene_close_event");
  //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::updateMsgContent(const std::string &msg) {
  textBox->addText(msg);
}

void HelloWorld::onLeaveChannelClicked() { engine->leaveChannel(); }

void HelloWorld::onJoinChannelClicked() {
  if (editBox == nullptr || strlen(editBox->getText()) == 0) {
    return;
  }

  engine->enableVideo();
  engine->setChannelProfile(agora::rtc::CHANNEL_PROFILE_GAME);
  engine->joinChannel(AGORA_TOKEN, editBox->getText(), "Cocos2d", 0);
}

void HelloWorld::onEnter() {
  cocos2d::Scene::onEnter();
  eventHandler = new MyIGamingRtcEngineEventHandler(this);

  engine = createAgoraRtcEngine();
  agora::rtc::RtcEngineContext context;
  context.appId = AGORA_APP_ID;
  context.eventHandler = eventHandler;
  engine->initialize(context);

  agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
  mediaEngine.queryInterface(engine, agora::AGORA_IID_MEDIA_ENGINE);
  if (mediaEngine) {
    videoFrameObserver = new agora::cocos::VideoFrameObserver;
    mediaEngine->registerVideoFrameObserver(videoFrameObserver);
  }
}

void HelloWorld::onExit() {
  Node::onExit();
  agora::rtc::IRtcEngine::release(true);
  engine = nullptr;
  delete eventHandler;
  eventHandler = nullptr;
  delete videoFrameObserver;
  videoFrameObserver = nullptr;
}

void HelloWorld::update(float delta) {
  Node::update(delta);
  for (auto user : users) {
    auto sprite =
        this->getChildByName<Sprite *>("uid:" + std::to_string(user.first));
    if (sprite) {
      auto texture = sprite->getSpriteFrame()->getTexture();

      int textureId = texture->getName();
      videoFrameObserver->bindTextureId(textureId, user.first);
    }
  }
}

void HelloWorld::addTextureRender(uid_t uid, int width, int height) {
  Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
    if (users.find(uid) == users.end()) {
      users[uid] = true;
    }

    auto texture = new cocos2d::Texture2D;
    MipmapInfo info;
    texture->initWithMipmaps(&info, 1, Texture2D::PixelFormat::RGBA4444,
                             width / 2, height / 2);
    auto sprite = Sprite::createWithTexture(texture);
    if (sprite != nullptr) {
      auto visibleSize = Director::getInstance()->getVisibleSize();
      Vec2 origin = Director::getInstance()->getVisibleOrigin();

      // position the sprite on the center of the screen
      sprite->setPosition(Vec2(
          origin.x + visibleSize.width - sprite->getContentSize().width / 2,
          origin.y + visibleSize.height + sprite->getContentSize().height / 2 -
              sprite->getContentSize().height * users.size()));

      // add the sprite as a child to this layer
      this->addChild(sprite, 0, "uid:" + std::to_string(uid));
    }
  });
}

void HelloWorld::removeTextureRender(uid_t uid) {
  Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
    if (users.find(uid) != users.end()) {
      users.erase(uid);
    }

    this->removeChildByName("uid:" + std::to_string(uid));
  });
}

void HelloWorld::removeAllTextureRenders() {
  Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
    for (auto user : users) {
      this->removeChildByName("uid:" + std::to_string(user.first));
    }
    users.clear();
  });
}
