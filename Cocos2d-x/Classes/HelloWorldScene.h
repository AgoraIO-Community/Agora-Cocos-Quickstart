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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#ifdef __APPLE__
#include <AgoraRtcKit/IAgoraRtcEngine.h>
#elif __ANDROID__
#include "IAgoraRtcEngine.h"
#endif

#include "./TextBox/TextBox.h"
#include "VideoFrameObserver.h"
#include "ui/CocosGUI.h"
#include <map>

// PLEASE KEEP THIS App ID IN SAFE PLACE -->
// Get your own App ID at https://dashboard.agora.io/
// After you entered the App ID, remove <##> outside of Your App ID
#define AGORA_APP_ID <#YOUR APP ID#>
// For formal released project, please use Dynamic Key
// https://docs.agora.io/en/Agora%20Platform/token
#define AGORA_TOKEN <#YOUR TOKEN#>

class HelloWorld : public cocos2d::Scene {
public:
  static cocos2d::Scene *createScene();

  bool init() override;

  void onEnter() override;

  void onExit() override;

  void update(float delta) override;

  // a selector callback
  void menuCloseCallback(cocos2d::Ref *pSender);

  // implement the "static create()" method manually
  CREATE_FUNC(HelloWorld);

public:
  void updateMsgContent(const std::string &msg);

  void addTextureRender(uid_t uid, int width, int height);

  void removeTextureRender(uid_t uid);

  void removeAllTextureRenders();

private:
  void onJoinChannelClicked();

  void onLeaveChannelClicked();

private:
  TextBox *textBox;
  cocos2d::ui::EditBox *editBox;
  agora::rtc::IRtcEngine *engine;
  agora::rtc::IRtcEngineEventHandler *eventHandler;
  agora::cocos::VideoFrameObserver *videoFrameObserver;
  std::map<uid_t, bool> users;
};

#endif // __HELLOWORLD_SCENE_H__
